#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Battlefield.h"

namespace game_framework {
	Battlefield::Battlefield() {
		x = y = 0;
		weapon2.SetInitialXY(486, 290);
		weapon2.Initialize(true);
		skill_1 = new Skill();
		skill_2 = new Skill();
		Initialize();
	}

	bool Battlefield::GetWeaponAlive(int num) {
		switch (num)
		{
		case 1:
			return weapon1.IsAlive();
		case 2:
			return weapon2.IsAlive();
		default:
			return false;
		}
	}

	bool Battlefield::GetSkillActivated(int skill_num) {
		if (skill_num == 1)
			return skill_1->IsActivated();
		else
			return skill_2->IsActivated();
	}

	bool Battlefield::GetSkillUsed(int skill_num) {
		if (skill_num == 1)
			return skill_1->GetUsed();
		else
			return skill_2->GetUsed();
	}

	bool Battlefield::GetLaserAlive() {
		return skill_1->GetAlive();
	}

	/*bool Battlefield::AbleToMove() {
		if (player1_hit && skill_1->GetActivated())
			return false;
		else if (player2_hit && skill_2->GetActivated())
			return false;
		return true;
	}*/

	int Battlefield::GetSkillType(int skill_num) {
		if (skill_num == 1)
			return skill_1->GetType();
		else
			return skill_2->GetType();
	}

	int Battlefield::GetHealth(int player_num) {
		switch (player_num)
		{
		case 1:
			return playerPointer1->GetHealth();
		case 2:
			return playerPointer2->GetHealth();
		default:
			return 0;
		}
	}

	int Battlefield::GetParalyze(int player_num) {
		switch (player_num)
		{
		case 1:
			return player1_paralyzed;
		case 2:
			return player2_paralyzed;
		default:
			return 0;
		}
	}

	int Battlefield::GetAngle(int weapon_num) {
		switch (weapon_num)
		{
		case 1:
			return weapon1.GetAngle();
		case 2:
			return weapon2.GetAngle();
		default:
			return 0;
		}
	}

	void Battlefield::Initialize() {
		switch (skill_1->GetType())
		{
		case 1:
			skill_1 = new Paralyze(skill_1->GetType());
			break;
		case 2:
			skill_1 = new Twice(skill_1->GetType());
			break;
		case 3:
			skill_1 = new SuckBlood(skill_1->GetType());
			break;
		case 4:
			skill_1 = new Laser(skill_1->GetType());
			break;
		default:
			skill_1 = new Skill(skill_1->GetType());
			//skill_1->ReloadAnimation();
			break;
		}
		switch (skill_2->GetType())
		{
		case 1:
			skill_2 = new Paralyze(skill_2->GetType());
			break;
		case 2:
			skill_2 = new Twice(skill_2->GetType());
			break;
		case 3:
			skill_2 = new SuckBlood(skill_2->GetType());
			break;
		case 4:
			skill_2 = new Laser(skill_2->GetType());
			break;
		default:
			skill_2 = new Skill(skill_2->GetType());
			break;
		}
		//weapon2.SetInvertSpeed();
		player1_paralyzed = player2_paralyzed = false;
		player1_useLaser = false;
		skill_1->SetActivated(false);
		skill_2->SetActivated(false);
	}

	void Battlefield::ChangeCharacter(int number, int number2) {
		playerPointer1 = new BattlePlayer(number);
		s_code = number;
		playerPointer2 = new BattlePlayer(number2);
		s_code2 = number2;
		playerPointer1->LoadBitmap();
		playerPointer2->LoadBitmap();
		playerPointer2->SetPlayer2();
	}

	void Battlefield::ChangeWeapon(int number, int number2) {
		weapon1.SetWeapon(number);
		weapon2.SetWeapon(number2);
	}

	void Battlefield::ChangeSkill(int type1, int type2) {
		skill_1->SetType(type1);
		skill_2->SetType(type2);
		Initialize();
		skill_1->ReloadBitmap();
		skill_2->ReloadBitmap();
	}

	void Battlefield::SetAngle(int angle1, int angle2) {
		weapon1.SetAngle(angle1);
		weapon2.SetAngle(angle2, true);
	}

	void Battlefield::LoadBitmap() {
		for (int i = 0; i < 5; i++)
			background.AddBitmap(IDB_BATTLE_BACKGROUND_1);
		for (int i = 0; i < 5; i++)
			background.AddBitmap(IDB_BATTLE_BACKGROUND_2);
		for (int i = 0; i < 5; i++)
			background.AddBitmap(IDB_BATTLE_BACKGROUND_1);
		for (int i = 0; i < 5; i++)
			background.AddBitmap(IDB_BATTLE_BACKGROUND_3);

		playerPointer1->LoadBitmap();
		playerPointer2->LoadBitmap();
		playerPointer2->SetPlayer2();

		weapon1.LoadBitmap();
		weapon2.LoadBitmap();

		healthbar_background.LoadBitmap(IDB_HEALTHBAR_BACKGROUND, RGB(255, 255, 255));
		healthbar.LoadBitmap(IDB_HEALTHBAR, RGB(255, 255, 255));

		energy1->LoadBitmap();
		energy2->LoadBitmap();

		skill_1->LoadBitmap();
		skill_2->LoadBitmap();

		test.LoadBitmap(IDB_0);
	}

	void Battlefield::OnMove() {
		background.OnMove();

		energy1->OnMove();
		if (energy1->GetCharging())
			weapon1.SetPower(energy1->GetPower());
		energy2->OnMove();
		if (energy2->GetCharging())
			weapon2.SetPower(energy2->GetPower(), true);
		bool weapon1_alive = weapon1.IsAlive(), weapon2_alive = weapon2.IsAlive();
		weapon1.OnMove();
		weapon2.OnMove(true);
		CheckHit();
		if (weapon1.IsAlive() == false && weapon1_alive == true) {
			if (skill_1->GetType() == 2 && skill_1->IsActivated())
				weapon1.SetAlive(true);
			skill_1->SetActivated(false);
		}

		if (weapon2.IsAlive() == false && weapon2_alive == true) {
			if (skill_2->GetType() == 2 && skill_2->IsActivated())
				weapon2.SetAlive(true, true);
			skill_2->SetActivated(false);
		}
		
		skill_1->OnMove();
		skill_2->OnMove();

		if (skill_1->GetType() == 4) {
			if (skill_1->GetShowedTimes() == 0)
				playerPointer2->SetHealth(playerPointer2->GetHealth() - 2);
			if (skill_2->GetShowedTimes() == 0)
				playerPointer1->SetHealth(playerPointer1->GetHealth() - 2);
		}
		
	}

	void Battlefield::OnShow() {
		background.SetTopLeft(x, y);
		background.OnShow();
		playerPointer1->OnShow();
		playerPointer2->OnShow();
		//CheckHit();
		/*if (weapon1.IsAlive()) {
			weapon1.OnShow();
		}
		else if (weapon2.IsAlive()) {
			weapon2.OnShow();
		}*/
		energy1->OnShow();
		weapon1.OnShow();
		energy2->OnShow();
		weapon2.OnShow();

		healthbar.SetTopLeft(-111 + (playerPointer1->GetHealth()*176/100), 20); //血量條長度176, 左框左上(65, 20)
		healthbar.ShowBitmap();

		healthbar.SetTopLeft(254 + (playerPointer2->GetHealth()*176/100), 20);	//血量條長度176, 右框左上(430, 20)
		healthbar.ShowBitmap();

		healthbar_background.SetTopLeft(0, 0);
		healthbar_background.ShowBitmap();

		skill_1->OnShow(65, 70);
		skill_2->OnShow(430, 70);

		if (player1_paralyzed)
			skill_2->ShowAnimation(20, 290);
		if (player2_paralyzed)
			skill_1->ShowAnimation(490, 290);

		if (skill_1->GetType() == 3)
			skill_1->ShowOnce(490, 290);
		if (skill_2->GetType() == 3)
			skill_2->ShowOnce(20, 290);

		if (skill_1->GetType() == 4)
			skill_1->ShowOnce(150, 0);
		if (skill_2->GetType() == 4)
			skill_2->ShowOnce(450, 0);

		if (skill_1->IsActivated()) {
			test.SetTopLeft(10, 10);
			test.ShowBitmap();
		}			

	}


	void Battlefield::SetCharge(int num, bool flag) {
		switch (num)
		{
		case 1:
			energy1->SetCharging(flag);			
			break;
		case 2:
			energy2->SetCharging(flag);
			break;
		default:
			break;
		}
	}

	void Battlefield::SetSkillActivated(int skill_num, bool flag) {
		switch (skill_num)
		{
		case 1:
			skill_1->SetActivated(flag);
			break;
		case 2:
			skill_2->SetActivated(flag);
			break;
		default:
			break;
		}
	}

	void Battlefield::SetSkillUsed(int skill_num, bool used) {
		switch (skill_num)
		{
		case 1:
			skill_1->SetUsed(used);
			break;
		case 2:
			skill_2->SetUsed(used);
			break;
		default:
			break;
		}
	}

	void Battlefield::SetParalyze(int player_num, bool paralyze) {
		switch (player_num)
		{
		case 1:
			player1_paralyzed = paralyze;
			break;
		case 2:
			player2_paralyzed = paralyze;
			break;
		default:
			break;
		}
	}

	void Battlefield::ResetSkillAnimation(int skill_num) {
		switch (skill_num)
		{
		case 1:
			skill_1->ResetAnimation();
			weapon1.SetAlive(false);
			break;
		case 2:
			skill_2->ResetAnimation();
			weapon2.SetAlive(false, true);
			break;
		default:
			break;
		}
	}

	void Battlefield::OnAttack(int num) {
		switch (num)
		{
		case 1:
			//player1_hit = false;
			weapon1.SetAlive(true);
			break;
		case 2:
			//player2_hit = false;
			weapon2.SetAlive(true);
			break;
		default:
			break;
		}
	}

	void Battlefield::OnLaserAttack() {
		skill_1->ResetShowed();
		//player1_useLaser = true;
	}

	void Battlefield::CheckHit() {
		if (weapon2.IsAlive() && (weapon2.GetX1() < playerPointer1->GetX2() - 10 && weapon2.GetX2() > playerPointer1->GetX1() + 10 && weapon2.GetY1() < playerPointer1->GetY2() - 10 && weapon2.GetY2() > playerPointer1->GetY1() + 10)) {
			//playerPointer1->SetHit(true);
			//if (skill_2->IsActivated() && skill_2->GetType() == 1) {
			if (skill_2->IsActivated() && skill_2->GetType() == 1) {
				player1_paralyzed = true;
				//skill_2->SetActivated(false);
			}
			if (skill_2->IsActivated() && skill_2->GetType() == 3) {
				if (playerPointer2->GetHealth() < 100)
					playerPointer2->SetHealth(playerPointer2->GetHealth() + 20);
				skill_2->ResetShowed();
			}

			weapon2.SetAlive(false, true);
			playerPointer1->GotAttack();
			if (skill_2->GetType() == 2 && skill_2->IsActivated())
				weapon2.SetAlive(true, true);
			skill_2->SetActivated(false);
		}
		else if (weapon1.IsAlive() && (weapon1.GetX1() < playerPointer2->GetX2() - 10 && weapon1.GetX2() > playerPointer2->GetX1() + 10 && weapon1.GetY1() < playerPointer2->GetY2() - 10 && weapon1.GetY2() > playerPointer2->GetY1() + 10)) {
			//player1_hit = true;
			//if (skill_1->IsActivated() && skill_1->GetType() == 1) {
			if (skill_1->IsActivated() && skill_1->GetType() == 1) {
				player2_paralyzed = true;
				//skill_1->SetActivated(false);
			}
			if (skill_1->IsActivated() && skill_1->GetType() == 3) {
				if (playerPointer1->GetHealth() < 100)
					playerPointer1->SetHealth(playerPointer1->GetHealth() + 20);
				skill_1->ResetShowed();
			}			
			weapon1.SetAlive(false);
			playerPointer2->GotAttack();
			if (skill_1->GetType() == 2 && skill_1->IsActivated())
				weapon1.SetAlive(true);
			skill_1->SetActivated(false);
		}
	}
}
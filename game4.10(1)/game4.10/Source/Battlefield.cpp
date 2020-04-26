#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Battlefield.h"

namespace game_framework {
	Battlefield::Battlefield() {
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

	void Battlefield::Initialize() {
		x = y = 0;
		weapon2.SetInitialXY(486, 290);
		weapon2.SetInvertSpeed();
	}

	void Battlefield::ChangeCharacter(int number, int number2) {
		playerPointer1 = new BattlePlayer(number);
		s_code = number;
		playerPointer2 = new BattlePlayer(number2);
		s_code2 = number2;
	}

	void Battlefield::ChangeWeapon(int number, int number2) {
		weapon1.SetWeapon(number);
		weapon2.SetWeapon(number2);
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
	}

	void Battlefield::OnMove() {
		background.OnMove();
		weapon1.OnMove();
		weapon2.OnMove();
		
	}

	void Battlefield::OnShow() {
		background.SetTopLeft(x, y);
		background.OnShow();
		playerPointer1->OnShow();
		playerPointer2->OnShow();
		if (weapon1.IsAlive()) {
			weapon1.OnShow();
		}
		else if (weapon2.IsAlive()) {
			weapon2.OnShow();
		}
	}

	void Battlefield::OnAttack(int num) {
		switch (num)
		{
		case 1:
			weapon1.SetAlive(true);
			break;
		case 2:
			weapon2.SetAlive(true);
			break;
		default:
			break;
		}
	}
}
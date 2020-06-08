#pragma once
#include "BattlePlayer.h"
#include "Weapon.h"
#include "Energy.h"
#include "Skill.h"

namespace game_framework {
	class Battlefield {
	public:
		Battlefield();
		bool GetWeaponAlive(int num);
		int  GetHealth(int player_num);
		int  GetAngle(int weapon_num);
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		//void Charge(int num);
		void SetCharge(int num, bool flag);
		void OnAttack(int num);
		void ChangeCharacter(int number = 0, int number2 = 0);
		void ChangeWeapon(int number, int number2);
		void ChangeSkill(int type1 = 0, int type2 = 0);
		void SetAngle(int angle1, int angle2);
		void CheckHit();
	protected:
		CAnimation background;
		CMovingBitmap healthbar_background;
		CMovingBitmap healthbar;
		Skill skill_1, skill_2;
		//BattlePlayer playerChar1;
		//BattlePlayer playerChar2;
		BattlePlayer * playerPointer1 = new BattlePlayer(0);
		BattlePlayer * playerPointer2 = new BattlePlayer(0);
		Weapon weapon1, weapon2;
		Energy *energy1 = new Energy(0, 250);
		Energy *energy2 = new Energy(520, 250, true);
		int x, y;
		int s_code, s_code2;
	};
}
#pragma once
#include "BattlePlayer.h"
#include "Weapon.h"

namespace game_framework {
	class Battlefield {
	public:
		Battlefield();
		bool GetWeaponAlive(int num);
		int  GetHealth(int player_num);
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		void OnAttack(int num);
		void ChangeCharacter(int number = 0, int number2 = 0);
		void ChangeWeapon(int number, int number2);
		void SetAngle(int angle1, int angle2);
		void CheckHit();
	protected:
		CAnimation background;
		CMovingBitmap healthbar_background;
		CMovingBitmap healthbar;
		//BattlePlayer playerChar1;
		//BattlePlayer playerChar2;
		BattlePlayer * playerPointer1 = new BattlePlayer(0);
		BattlePlayer * playerPointer2 = new BattlePlayer(0);
		Weapon weapon1, weapon2;
		int x, y;
		int s_code, s_code2;
	};
}
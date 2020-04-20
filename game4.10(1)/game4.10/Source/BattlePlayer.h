#pragma once

namespace game_framework {
	class BattlePlayer {
	public:
		BattlePlayer(int s_code);
		void Initialize(int s_code);
		//void SetBitmap(int s_code);
		void LoadBitmap();
		void UnderAttack();
		void LowOfHealth();
		void SetPlayer2();
		void OnShow();
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		void SetXY(int x, int y);
		//void SetHPLow();
	protected:
		//CAnimation animation[10];
		CAnimation * aniPointer_recent, * aniPointer, * aniPointer_wounded, * aniPointer_under_attack;
		CAnimation animation[10];
		CAnimation animation_wounded[10];
		CAnimation animation_under_attack[10];
		CAnimation rf_animation[10];
		CAnimation rf_animation_wounded[10];
		CAnimation rf_animation_under_attack[10];
		int x, y;
		int Health;
		int s_code;
	};
}
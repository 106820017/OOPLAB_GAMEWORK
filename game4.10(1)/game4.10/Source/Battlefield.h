#pragma once
#include "BattlePlayer.h"

namespace game_framework {
	class Battlefield {
	public:
		Battlefield();
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		void ChangeCharacter(int number, int number2);
	protected:
		CAnimation background;
		//BattlePlayer playerChar1;
		//BattlePlayer playerChar2;
		BattlePlayer * playerPointer1 = new BattlePlayer(0);
		BattlePlayer * playerPointer2 = new BattlePlayer(0);
		int x, y;
		int s_code, s_code2;
	};
}
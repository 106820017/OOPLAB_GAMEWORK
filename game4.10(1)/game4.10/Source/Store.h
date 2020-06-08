#pragma once
#include "Alphabet.h"

namespace game_framework {
	class Store {
	public:
		Store();
		//void Initialize();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void ClearCurrent();
		void NextOption();
		void SetCharacter(int char_num);
		void SetChoosingCharacter(bool choosingCharacter);
		void SetPlayerGet(int char_num);
		int GetOptionNum();
		int GetProfileNum();
		bool IsChoosingCharacter();
		bool GetPlayerAble(int char_num);
	protected:
		CMovingBitmap bitmap, back_arrow, sign, announcement, clerk, pad, textBar, unable, frame;
		CMovingBitmap profile[5];
		CMovingBitmap skill_icon[5];
		CMovingBitmap *current_player;
		CAnimation play_arrow;
		Alphabet lines, mm, leave;

		int x, y;
		int option_num, profile_num;
		int put_pad[10][10] = { {1, 1, 1, 1, 1, 1 ,1 , 1, 1, 1},
							 {1, 0, 0, 0, 0, 0 ,0 , 0, 0, 1},
							 {1, 0, 0, 0, 0, 0 ,0 , 0, 0, 1},
							 {1, 0, 0, 0, 0, 0 ,0 , 0, 0, 1},
							 {1, 0, 0, 0, 0, 0 ,0 , 0, 0, 1},
							 {1, 0, 0, 0, 0, 0 ,0 , 0, 0, 1},
							 {1, 0, 0, 0, 0, 0 ,0 , 0, 0, 1},
							 {1, 0, 0, 0, 0, 0 ,0 , 0, 0, 1},
							 {1, 0, 0, 0, 0, 0 ,0 , 0, 0, 1},
							 {1, 1, 1, 1, 1, 1 ,1 , 1, 1, 1}, };

		bool choosingCharacter, choosingSkill;
		bool playersGet[5];
	};
}

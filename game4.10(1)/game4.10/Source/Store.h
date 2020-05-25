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
		int GetOptionNum();
	protected:
		CMovingBitmap bitmap, back_arrow, sign, announcement, clerk, pad, textBar;
		CAnimation play_arrow;
		Alphabet lines, mm, leave;

		int x, y;
		int option_num;
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
	};
}

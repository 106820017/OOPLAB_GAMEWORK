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
	protected:
		CMovingBitmap bitmap, back_arrow, sign, announcement, clerk, pad;
		Alphabet lines;

		int x, y;
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

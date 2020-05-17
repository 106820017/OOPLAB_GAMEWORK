#pragma once
//#include "Map.h"
#include "Random.h"

namespace game_framework {
	class Opponent {
	public:
		Opponent();
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		void Initialize();
		void LoadBitmap();
		void OnShow(int sx, int sy);
		void OnMove(unsigned seed);

	protected:
		CMovingBitmap bitmap;
		Random random;
		int x, y;

		void RandomMove(unsigned seed);
	};
}

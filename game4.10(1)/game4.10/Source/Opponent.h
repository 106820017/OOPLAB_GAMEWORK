#pragma once
//#include "Map.h"
#include "Random.h"

namespace game_framework {
	class Opponent {
	public:
		Opponent();
		Opponent(int num);
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		void Initialize();
		void LoadBitmap();
		void OnShow(int sx, int sy);
		void OnMove(unsigned seed);
		void SetNum(int num);

	protected:
		CMovingBitmap bitmap0;
		//CAnimation ani;
		Random random, random20;
		int x, y;
		int num;

		void RandomMove(unsigned seed);
	};
}

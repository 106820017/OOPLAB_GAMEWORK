#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Opponent.h"

namespace game_framework {
	Opponent::Opponent() {
		Initialize();
	}

	int Opponent::GetX1()
	{
		return x;
	}

	int Opponent::GetY1()
	{
		return y;
	}

	int Opponent::GetX2()
	{
		return x + bitmap.Width();
	}

	int Opponent::GetY2()
	{
		return y + bitmap.Height();
	}

	void Opponent::Initialize() {
		/*unsigned seed;
		seed = (unsigned)time(NULL) * (rand()%10); // 取得時間序列
		srand(seed);
		x = rand() % 3600;
		y = rand() % 3600;*/
		random.SetSeed(3600);

		x = random.GetRand();
		y = random.GetRand();
		//x = random.GetRand(3600);
		//y = random.GetRand(3600);
		/*while (!isEmpty) {
			x = rand() % 3600;
			y = rand() % 3600;
		}	*/		
	}

	void Opponent::LoadBitmap() {
		bitmap.LoadBitmap(IDB_OPPONENT_SCENT, RGB(255, 255, 255));

	}

	void Opponent::OnShow(int sx, int sy) {
		bitmap.SetTopLeft(x-sx, y-sy);
		bitmap.ShowBitmap();
	}

	void Opponent::OnMove(unsigned seed) {
		/*unsigned seed;
		seed = (unsigned)time(NULL); // 取得時間序列*/
		
		RandomMove(seed);
		//bitmap.SetTopLeft(x, y);
		/*bitmap.SetTopLeft(x - sx, y - sy);
		bitmap.ShowBitmap();*/
	}

	void Opponent::RandomMove(unsigned seed) {	//隨機上下左右移動
		/*unsigned seed;
		seed = (unsigned)time(NULL); // 取得時間序列*/
		srand(seed);

		if (x <= 0)
			x += rand() % 3;
		else if (x >= 3599)
			x -= rand() % 3;
		else
			x += (rand() % 5 - 2);

		if (y <= 0)
			y += rand() % 3;
		else if (y >= 3599)
			y -= rand() % 3;
		else
			y += (rand() % 5 - 2);
	}
}
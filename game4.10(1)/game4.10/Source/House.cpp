#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "House.h"

namespace game_framework {
	House::House() {
		Initialize();
	}

	void House::Initialize() {
		x = 0;
		y = 0;
	}

	void House::LoadBitmap() {
		bitmap[0][0].LoadBitmap(IDB_HOUSE_1, RGB(255, 255, 255));
		bitmap[1][0].LoadBitmap(IDB_HOUSE_2, RGB(255, 255, 255));
		bitmap[2][0].LoadBitmap(IDB_HOUSE_3, RGB(255, 255, 255));
		bitmap[3][0].LoadBitmap(IDB_HOUSE_4, RGB(255, 255, 255));
		bitmap[4][0].LoadBitmap(IDB_HOUSE_5, RGB(255, 255, 255));
		bitmap[0][1].LoadBitmap(IDB_HOUSE_6, RGB(255, 255, 255));
		bitmap[1][1].LoadBitmap(IDB_HOUSE_7, RGB(255, 255, 255));
		bitmap[2][1].LoadBitmap(IDB_HOUSE_8, RGB(255, 255, 255));
		bitmap[3][1].LoadBitmap(IDB_HOUSE_9, RGB(255, 255, 255));
		bitmap[4][1].LoadBitmap(IDB_HOUSE_10, RGB(255, 255, 255));
		bitmap[0][2].LoadBitmap(IDB_HOUSE_11, RGB(255, 255, 255));
		bitmap[1][2].LoadBitmap(IDB_HOUSE_12, RGB(255, 255, 255));
		bitmap[2][2].LoadBitmap(IDB_HOUSE_13, RGB(255, 255, 255));
		bitmap[3][2].LoadBitmap(IDB_HOUSE_14, RGB(255, 255, 255));
		bitmap[4][2].LoadBitmap(IDB_HOUSE_15, RGB(255, 255, 255));
		bitmap[0][3].LoadBitmap(IDB_HOUSE_16, RGB(255, 255, 255));
		bitmap[1][3].LoadBitmap(IDB_HOUSE_17, RGB(255, 255, 255));
		bitmap[2][3].LoadBitmap(IDB_HOUSE_18, RGB(255, 255, 255));
		bitmap[3][3].LoadBitmap(IDB_HOUSE_19, RGB(255, 255, 255));
		bitmap[4][3].LoadBitmap(IDB_HOUSE_20, RGB(255, 255, 255));
		bitmap[0][4].LoadBitmap(IDB_HOUSE_21, RGB(255, 255, 255));
		bitmap[1][4].LoadBitmap(IDB_HOUSE_22, RGB(255, 255, 255));
		bitmap[2][4].LoadBitmap(IDB_HOUSE_23, RGB(255, 255, 255));
		bitmap[3][4].LoadBitmap(IDB_HOUSE_24, RGB(255, 255, 255));
		bitmap[4][4].LoadBitmap(IDB_HOUSE_25, RGB(255, 255, 255));
	}

	void House::OnShow() {
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++) {
				bitmap[i][j].SetTopLeft(x+120*i, y+120*j);
				bitmap[i][j].ShowBitmap();
			}
	}

	void House::SetXY(int nx, int ny) {
		x = nx; y = ny;
	}
}
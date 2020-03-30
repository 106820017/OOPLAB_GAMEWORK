#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Rock.h"

namespace game_framework {
	Rock::Rock() {
		Initialize();
	}

	void Rock::Initialize() {
		x = 0;
		y = 0;
	}

	int Rock::GetX1() {
		return x;
	}

	int Rock::GetY1() {
		return y;
	}

	int Rock::GetX2() {
		return x + bitmap.Width();
	}

	int Rock::GetY2() {
		return y + bitmap.Height();
	}

	void Rock::LoadBitmap() {
		bitmap.LoadBitmap(IDB_TEST_ROCK, RGB(255, 255, 255));
	}

	void Rock::OnShow() {
		bitmap.SetTopLeft(x, y);
		bitmap.ShowBitmap();
	}

	void Rock::SetXY(int nx, int ny) {
		x = nx; y = ny;
	}
}
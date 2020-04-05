#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Store.h"

namespace game_framework {
	Store::Store() {
		x = y = 10;
	}

	/*void Initialize() {

	}*/

	void Store::LoadBitmap() {
		bitmap.LoadBitmap(IDB_SHOP_BACKGROUND, RGB(255, 255, 255));
		sign.LoadBitmap(IDB_SIGN, RGB(255, 255, 255));
		announcement.LoadBitmap(IDB_ANNOUNCEMENT, RGB(255, 255, 255));
		//back_arrow.LoadBitmap(IDB_LEFT_ARROW, RGB(255, 255, 255));
	}

	void Store::OnShow() {
		bitmap.SetTopLeft(x, y);
		bitmap.ShowBitmap();
		sign.SetTopLeft(x + 10, y + 10);
		sign.ShowBitmap();
		announcement.SetTopLeft(250, 250);
		announcement.ShowBitmap();
	}
}
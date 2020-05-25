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
		pad.LoadBitmap(IDB_STORE_PAD, RGB(255, 255, 255));
		sign.LoadBitmap(IDB_SIGN, RGB(255, 255, 255));
		announcement.LoadBitmap(IDB_ANNOUNCEMENT, RGB(255, 255, 255));
		//back_arrow.LoadBitmap(IDB_LEFT_ARROW, RGB(255, 255, 255));
		
		clerk.LoadBitmap(IDB_CLERK, RGB(0, 255, 0));
		lines.LoadBitmap();
	}

	void Store::OnMove() {
		lines.OnMove();
	}

	void Store::OnShow() {
		bitmap.SetTopLeft(x, y);
		bitmap.ShowBitmap();
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (put_pad[j][i] == 1) {
					pad.SetTopLeft(x+i*62, y+j*46);
					pad.ShowBitmap();
				}

			}
		}
		sign.SetTopLeft(x + 10, y + 10);
		sign.ShowBitmap();
		announcement.SetTopLeft(250, 250);
		announcement.ShowBitmap();

		clerk.SetTopLeft(x + 10, y + 350);
		clerk.ShowBitmap();

		lines.ShowString("Welcome!!\n  What do you want?", x+80, y+350);
	}

	void Store::ClearCurrent() {
		lines.ClearCurrent();
	}

}
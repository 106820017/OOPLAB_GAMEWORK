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
		option_num = 0;
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
		textBar.LoadBitmap(IDB_TEXTBAR, RGB(255, 255, 255));
		lines.LoadBitmap();

		mm.LoadBitmap();

		leave.LoadBitmap();

		play_arrow.AddBitmap(IDB_PLAY_2, RGB(255, 255, 255));
		play_arrow.AddBitmap(IDB_PLAY_2, RGB(255, 255, 255));
		play_arrow.AddBitmap(IDB_PLAY_1, RGB(255, 255, 255));
		play_arrow.AddBitmap(IDB_PLAY_1, RGB(255, 255, 255));
		play_arrow.AddBitmap(IDB_PLAY_0, RGB(255, 255, 255));
		play_arrow.AddBitmap(IDB_PLAY_0, RGB(255, 255, 255));

	}

	void Store::OnMove() {
		lines.OnMove();
		play_arrow.OnMove();
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
		/*announcement.SetTopLeft(250, 250);
		announcement.ShowBitmap();*/

		textBar.SetTopLeft(x+52, y+264);
		textBar.ShowBitmap();

		clerk.SetTopLeft(x + 484, y + 340);
		clerk.ShowBitmap();

		lines.ShowString("Welcome!!\n  What can I help?", x+85, y+290);

		mm.SetCurrent(20);
		if (option_num == 0)
			mm.ShowString("Change my character.", x + 85, y + 375);
		leave.SetCurrent(12);
		if (option_num == 1)
			leave.ShowString("Leave store.", x + 85, y + 375);

		play_arrow.SetTopLeft(x + 450, y + 350);
		play_arrow.OnShow();
	}

	void Store::ClearCurrent() {
		lines.ClearCurrent();
	}

	void Store::NextOption() {
		if (option_num < 1)
			option_num++;
		else
			option_num = 0;
	}

	int Store::GetOptionNum() {
		return option_num;
	}

}
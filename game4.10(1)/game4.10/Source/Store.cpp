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
		profile_num = 0;
		skill_num = 0;
		choosingCharacter = false;
		choosingSkill = false;
		playersGet[0] = true;
		for (int i = 1; i < 5; i++) {
			playersGet[i] = false;
		}
	}

	void Store::Initialize() {
		option_num = 0;
		profile_num = 0;
		skill_num = 0;
		for (int i = 1; i < 5; i++) {
			playersGet[i] = false;
		}
		choosingCharacter = false;
		choosingSkill = false;
	}

	void Store::LoadBitmap() {
		bitmap.LoadBitmap(IDB_SHOP_BACKGROUND, RGB(255, 255, 255));
		pad.LoadBitmap(IDB_STORE_PAD, RGB(255, 255, 255));
		sign.LoadBitmap(IDB_SIGN, RGB(255, 255, 255));
		announcement.LoadBitmap(IDB_ANNOUNCEMENT, RGB(255, 255, 255));
		
		clerk.LoadBitmap(IDB_CLERK, RGB(0, 255, 0));
		textBar.LoadBitmap(IDB_TEXTBAR, RGB(255, 255, 255));
		lines.LoadBitmap();

		ccharacter.LoadBitmap();
		cskill.LoadBitmap();
		leave.LoadBitmap();

		play_arrow.AddBitmap(IDB_PLAY_2, RGB(255, 255, 255));
		play_arrow.AddBitmap(IDB_PLAY_2, RGB(255, 255, 255));
		play_arrow.AddBitmap(IDB_PLAY_1, RGB(255, 255, 255));
		play_arrow.AddBitmap(IDB_PLAY_1, RGB(255, 255, 255));
		play_arrow.AddBitmap(IDB_PLAY_0, RGB(255, 255, 255));
		play_arrow.AddBitmap(IDB_PLAY_0, RGB(255, 255, 255));

		profile[0].LoadBitmap(IDB_KARBY_PROFILE, RGB(0, 255, 0));
		profile[1].LoadBitmap(IDB_PIKACHU_PROFILE, RGB(0, 255, 0));
		profile[2].LoadBitmap(IDB_STITCH_PROFILE, RGB(0, 255, 0));
		profile[3].LoadBitmap(IDB_SNOOPY_PROFILE, RGB(0, 255, 0));
		profile[4].LoadBitmap(IDB_CAPOO_PROFILE, RGB(0, 255, 0));

		skill_icon[0].LoadBitmap("res/blank.bmp", RGB(255, 255, 255));
		skill_icon[1].LoadBitmap(IDB_PARALYZE_ICON_BIG, RGB(255, 255, 255));
		skill_icon[2].LoadBitmap("res/twice_icon_big.bmp", RGB(255, 255, 255));
		skill_icon[3].LoadBitmap("res/suckblood_icon_big.bmp", RGB(255, 255, 255));
		skill_icon[4].LoadBitmap("res/lightbeam_icon_big.bmp", RGB(255, 255, 255));

		unable.LoadBitmap(IDB_PROFILE_UNABLE, RGB(255, 255, 255));

		frame.LoadBitmap(IDB_PROFILE_FRAME, RGB(255, 255, 255));
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

		textBar.SetTopLeft(x+52, y+264);
		textBar.ShowBitmap();

		clerk.SetTopLeft(x + 484, y + 340);
		clerk.ShowBitmap();

		if (!choosingSkill) {
			profile[0].SetTopLeft(x + 142, y + 100);
			profile[0].ShowBitmap();
			profile[1].SetTopLeft(x + 286, y + 100);
			profile[1].ShowBitmap();
			profile[2].SetTopLeft(x + 410, y + 100);
			profile[2].ShowBitmap();
			profile[3].SetTopLeft(x + 208, y + 200);
			profile[3].ShowBitmap();
			profile[4].SetTopLeft(x + 363, y + 200);
			profile[4].ShowBitmap();

			for (int i = 1; i < 5; i++) {
				if (!playersGet[i]) {
					unable.SetTopLeft(profile[i].Left(), profile[i].Top());
					unable.ShowBitmap();
				}
			}

			frame.SetTopLeft(profile[profile_num].Left(), profile[profile_num].Top());
			frame.ShowBitmap();
		}	
		else {
			skill_icon[skill_num].SetTopLeft(x + 250, y + 100);
			skill_icon[skill_num].ShowBitmap();
		}

		lines.ShowString("Welcome!!\n  What can I help?", x+85, y+290);

		ccharacter.SetCurrent(20);
		if (option_num == 0)
			ccharacter.ShowString("Change my character.", x + 85, y + 375);
		cskill.SetCurrent(16);
		if (option_num == 1)
			cskill.ShowString("Change my skill.", x + 85, y + 375);
		leave.SetCurrent(12);
		if (option_num == 2)
			leave.ShowString("Leave store.", x + 85, y + 375);

		play_arrow.SetTopLeft(x + 450, y + 350);
		play_arrow.OnShow();
	}

	void Store::ClearCurrent() {
		lines.ClearCurrent();
	}

	void Store::NextOption() {
		if (option_num < 2)
			option_num++;
		else
			option_num = 0;
	}

	void Store::SetCharacter(int char_num) {
		profile_num = char_num;
	}

	void Store::NextSkill() {
		if (skill_num < 4)
			skill_num++;
		else
			skill_num = 0;
	}

	void Store::LastSkill() {
		if (skill_num > 0)
			skill_num--;
		else
			skill_num = 4;
	}

	void Store::SetChoosingCharacter(bool choosingCharacter) {
		this->choosingCharacter = choosingCharacter;
	}

	void Store::SetChoosingSkill(bool choosingSkill) {
		this->choosingSkill = choosingSkill;
	}

	void Store::SetPlayerGet(int char_num) {
		playersGet[char_num] = true;
	}

	int Store::GetOptionNum() {
		return option_num;
	}

	int Store::GetProfileNum() {
		return profile_num;
	}

	int Store::GetSkillNum() {
		return skill_num;
	}

	bool Store::IsChoosingCharacter() {
		return choosingCharacter;
	}

	bool Store::IsChoosingSkill() {
		return choosingSkill;
	}

	bool Store::GetPlayerAble(int char_num) {
		return playersGet[char_num];
	}
}
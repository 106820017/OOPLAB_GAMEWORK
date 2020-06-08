#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Skill.h"

namespace game_framework {
	Skill::Skill(int type) {
		this->type = type;
		Initialize();
	}

	void Skill::Initialize() {

	}

	void Skill::LoadBitmap() {
		bitmap.LoadBitmap(IDB_PARALYZE_ICON_SMALL, RGB(255, 255, 255));
		bitmap_big.LoadBitmap(IDB_PARALYZE_ICON, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PLAY_0, RGB(255, 255, 255));
	}

	void Skill::OnMove() {
		animation.OnMove();
	}

	void Skill::OnShow(int x, int y) {
		bitmap.SetTopLeft(x, y);
		bitmap.ShowBitmap();
	}

	void Skill::ShowBig(int x, int y) {
		bitmap_big.SetTopLeft(x, y);
		bitmap_big.ShowBitmap();
	}

	void Skill::ShowAnimation(int x, int y) {
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}

	void Skill::SetType(int type) {
		this->type = type;
	}

	int Skill::GetType() {
		return type;
	}

	Paralyze::Paralyze(int type) : Skill(type) {
		Initialize();
	}

	void Paralyze::Initialize() {
		//x = y = 0;
	}

	void Paralyze::LoadBitmap() {
		bitmap.LoadBitmap(IDB_PARALYZE_ICON, RGB(255, 255, 255));
		bitmap_big.LoadBitmap(IDB_PARALYZE_ICON_BIG, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PLAY_0, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PLAY_1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PLAY_2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PLAY_1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PLAY_2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PLAY_0, RGB(255, 255, 255));
	}

	void Paralyze::ShowAnimation(int x, int y) {
		animation.SetDelayCount(3);
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}

}
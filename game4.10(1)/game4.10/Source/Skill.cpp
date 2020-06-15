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
		used = false;
		activated = false;
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

	void Skill::SetActivated(bool activated) {
		this->activated = activated;
	}

	void Skill::SetUsed(bool used) {
		this->used = used;
	}

	int Skill::GetType() {
		return type;
	}

	bool Skill::IsActivated() {
		return activated;
	}

	bool Skill::GetUsed() {
		return used;
	}

	Paralyze::Paralyze(int type) : Skill(type) {
		Initialize();
	}

	void Paralyze::Initialize() {
		//x = y = 0;
		used = false;
		activated = false;
	}

	void Paralyze::LoadBitmap() {
		bitmap.LoadBitmap(IDB_PARALYZE_ICON_SMALL, RGB(255, 255, 255));
		bitmap_big.LoadBitmap(IDB_PARALYZE_ICON_BIG, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PARALYZE_0, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PARALYZE_1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PARALYZE_2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PARALYZE_1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PARALYZE_2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PARALYZE_0, RGB(255, 255, 255));
	}

	void Paralyze::ShowAnimation(int x, int y) {
		animation.SetDelayCount(3);
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}

}
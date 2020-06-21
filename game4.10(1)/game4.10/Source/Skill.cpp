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
		showed_times = 2;
		//animation = new CAnimation();
	}

	void Skill::LoadBitmap() {
		bitmap[0].LoadBitmap(IDB_PARALYZE_ICON_SMALL, RGB(255, 255, 255));
		bitmap_big[0].LoadBitmap(IDB_PARALYZE_ICON, RGB(255, 255, 255));
		bitmap[1].LoadBitmap(IDB_PARALYZE_ICON_SMALL, RGB(255, 255, 255));
		bitmap_big[1].LoadBitmap(IDB_PARALYZE_ICON_BIG, RGB(255, 255, 255));
		bitmap[2].LoadBitmap("res/suckblood_icon_small.bmp", RGB(255, 255, 255));
		bitmap_big[2].LoadBitmap("res/suckblood_icon_big.bmp", RGB(255, 255, 255));
		bitmap[3].LoadBitmap("res/suckblood_icon_small.bmp", RGB(255, 255, 255));
		bitmap_big[3].LoadBitmap("res/suckblood_icon_big.bmp", RGB(255, 255, 255));
		bitmap[4].LoadBitmap("res/suckblood_icon_small.bmp", RGB(255, 255, 255));
		bitmap_big[4].LoadBitmap("res/suckblood_icon_big.bmp", RGB(255, 255, 255));

		animation.AddBitmap(IDB_PLAY_0, RGB(255, 255, 255));
	}

	void Skill::OnMove() {
		animation.OnMove();
	}

	void Skill::OnShow(int x, int y) {
		bitmap[type].SetTopLeft(x, y);
		bitmap[type].ShowBitmap();
	}

	void Skill::ShowBig(int x, int y) {
		bitmap_big[type].SetTopLeft(x, y);
		bitmap_big[type].ShowBitmap();
	}

	void Skill::ReloadBitmap() {

	}

	void Skill::ShowAnimation(int x, int y) {
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}

	void Skill::ShowOnce(int x, int y) {
		animation.SetDelayCount(3);
		animation.SetTopLeft(x, y);
		if (showed_times < 2)
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

	void Skill::ResetShowed() {
		showed_times = 0;
		animation.Reset();
	}

	void Skill::ResetAnimation() {
		showed_times = 2;
		animation.Reset();
	}

	int Skill::GetType() {
		return type;
	}

	int Skill::GetShowedTimes() {
		return showed_times;
	}

	bool Skill::IsActivated() {
		return activated;
	}

	bool Skill::GetUsed() {
		return used;
	}

	bool Skill::GetAlive() {
		return false;
	}

	Paralyze::Paralyze(int type) : Skill(type) {
		Initialize();
	}

	void Paralyze::Initialize() {
		//x = y = 0;
		used = false;
		activated = false;
		showed_times = 2;
		//animation = new CAnimation();
	}

	/*void Paralyze::LoadBitmap() {
		bitmap.LoadBitmap(IDB_PARALYZE_ICON_SMALL, RGB(255, 255, 255));
		bitmap_big.LoadBitmap(IDB_PARALYZE_ICON_BIG, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PARALYZE_0, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PARALYZE_1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PARALYZE_2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PARALYZE_1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PARALYZE_2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_PARALYZE_0, RGB(255, 255, 255));
	}*/

	/*void Paralyze::OnShow(int x, int y) {
		bitmap[1].SetTopLeft(x, y);
		bitmap[1].ShowBitmap();
	}*/

	void Paralyze::ReloadBitmap() {
		//animation.ClearBitmap();
		bitmap[0].LoadBitmap(IDB_PARALYZE_ICON_SMALL, RGB(255, 255, 255));
		bitmap_big[0].LoadBitmap(IDB_PARALYZE_ICON, RGB(255, 255, 255));
		bitmap[1].LoadBitmap(IDB_PARALYZE_ICON_SMALL, RGB(255, 255, 255));
		bitmap_big[1].LoadBitmap(IDB_PARALYZE_ICON_BIG, RGB(255, 255, 255));
		bitmap[2].LoadBitmap("res/suckblood_icon_small.bmp", RGB(255, 255, 255));
		bitmap_big[2].LoadBitmap("res/suckblood_icon_big.bmp", RGB(255, 255, 255));
		bitmap[3].LoadBitmap("res/suckblood_icon_small.bmp", RGB(255, 255, 255));
		bitmap_big[3].LoadBitmap("res/suckblood_icon_big.bmp", RGB(255, 255, 255));
		bitmap[4].LoadBitmap("res/suckblood_icon_small.bmp", RGB(255, 255, 255));
		bitmap_big[4].LoadBitmap("res/suckblood_icon_big.bmp", RGB(255, 255, 255));

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

	SuckBlood::SuckBlood(int type) : Skill(type) {
		Initialize();
	}

	void SuckBlood::Initialize() {
		used = false;
		activated = false;
		showed_times = 2;
		//animation = new CAnimation();
	}

	/*void SuckBlood::LoadBitmap() {
		bitmap.LoadBitmap("res/suckblood_icon_small.bmp", RGB(255, 255, 255));
		bitmap_big.LoadBitmap("res/suckblood_icon_big.bmp", RGB(255, 255, 255));
		animation.AddBitmap("res/bubble1.bmp", RGB(255, 255, 255));
		animation.AddBitmap("res/bubble2.bmp", RGB(255, 255, 255));
		animation.AddBitmap("res/bubble3.bmp", RGB(255, 255, 255));
		animation.AddBitmap("res/bubble4.bmp", RGB(255, 255, 255));
		animation.AddBitmap("res/bubble5.bmp", RGB(255, 255, 255));
		//animation.AddBitmap(IDB_PARALYZE_0, RGB(255, 255, 255));
	}*/

	void SuckBlood::OnMove() {
		animation.OnMove();
		if (animation.IsFinalBitmap())
			showed_times++;
	}

	/*void SuckBlood::OnShow(int x, int y) {
		bitmap[3].SetTopLeft(x, y);
		bitmap[3].ShowBitmap();
	}*/

	void SuckBlood::ReloadBitmap() {
		//animation.ClearBitmap();
		bitmap[0].LoadBitmap(IDB_PARALYZE_ICON_SMALL, RGB(255, 255, 255));
		bitmap_big[0].LoadBitmap(IDB_PARALYZE_ICON, RGB(255, 255, 255));
		bitmap[1].LoadBitmap(IDB_PARALYZE_ICON_SMALL, RGB(255, 255, 255));
		bitmap_big[1].LoadBitmap(IDB_PARALYZE_ICON_BIG, RGB(255, 255, 255));
		bitmap[2].LoadBitmap("res/suckblood_icon_small.bmp", RGB(255, 255, 255));
		bitmap_big[2].LoadBitmap("res/suckblood_icon_big.bmp", RGB(255, 255, 255));
		bitmap[3].LoadBitmap("res/suckblood_icon_small.bmp", RGB(255, 255, 255));
		bitmap_big[3].LoadBitmap("res/suckblood_icon_big.bmp", RGB(255, 255, 255));
		bitmap[4].LoadBitmap("res/suckblood_icon_small.bmp", RGB(255, 255, 255));
		bitmap_big[4].LoadBitmap("res/suckblood_icon_big.bmp", RGB(255, 255, 255));

		animation.AddBitmap("res/bubble1.bmp", RGB(255, 255, 255));
		animation.AddBitmap("res/bubble2.bmp", RGB(255, 255, 255));
		animation.AddBitmap("res/bubble3.bmp", RGB(255, 255, 255));
		animation.AddBitmap("res/bubble4.bmp", RGB(255, 255, 255));
		animation.AddBitmap("res/bubble5.bmp", RGB(255, 255, 255));
	}

	void SuckBlood::ShowAnimation(int x, int y) {
		animation.SetDelayCount(3);
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}

	void SuckBlood::ShowOnce(int x, int y) {
		animation.SetDelayCount(5);
		animation.SetTopLeft(x, y);
		if (showed_times < 2)
			animation.OnShow();
	}

	Laser::Laser(int type) : Skill(type) {
		Initialize();
	}

	void Laser::Initialize() {
		used = false;
		activated = false;
		showed_times = 1;
		alive = false;
	}

	void Laser::OnMove() {
		animation.OnMove();
		if (animation.IsFinalBitmap())
			showed_times++;
	}

	void Laser::ReloadBitmap() {
		bitmap[0].LoadBitmap(IDB_PARALYZE_ICON_SMALL, RGB(255, 255, 255));
		bitmap_big[0].LoadBitmap(IDB_PARALYZE_ICON, RGB(255, 255, 255));
		bitmap[1].LoadBitmap(IDB_PARALYZE_ICON_SMALL, RGB(255, 255, 255));
		bitmap_big[1].LoadBitmap(IDB_PARALYZE_ICON_BIG, RGB(255, 255, 255));
		bitmap[2].LoadBitmap("res/suckblood_icon_small.bmp", RGB(255, 255, 255));
		bitmap_big[2].LoadBitmap("res/suckblood_icon_big.bmp", RGB(255, 255, 255));
		bitmap[3].LoadBitmap("res/suckblood_icon_small.bmp", RGB(255, 255, 255));
		bitmap_big[3].LoadBitmap("res/suckblood_icon_big.bmp", RGB(255, 255, 255));
		bitmap[4].LoadBitmap("res/lightbeam_icon_small.bmp", RGB(255, 255, 255));
		bitmap_big[4].LoadBitmap("res/lightbeam_icon_big.bmp", RGB(255, 255, 255));

		animation.AddBitmap("res/laser_1.bmp", RGB(255, 255, 255));
		for (int i = 0; i < 4; i++) {
			animation.AddBitmap("res/laser_2.bmp", RGB(255, 255, 255));
			animation.AddBitmap("res/laser_3.bmp", RGB(255, 255, 255));
		}
		animation.AddBitmap("res/laser_1.bmp", RGB(255, 255, 255));
	}

	void Laser::ShowAnimation(int x, int y) {
		animation.SetDelayCount(3);
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}

	void Laser::ShowOnce(int x, int y) {
		animation.SetDelayCount(3);
		animation.SetTopLeft(x, y);
		if (showed_times < 1) {
			animation.OnShow();
			alive = true;
		}
		else
			alive = false;

	}

	bool Laser::GetAlive() {
		return alive;
	}
}
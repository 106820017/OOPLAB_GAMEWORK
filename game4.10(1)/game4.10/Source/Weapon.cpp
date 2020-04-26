#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Weapon.h"

namespace game_framework {
	Weapon::Weapon() {
		Initialize();
	}

	void Weapon::Initialize() {
		x = ini_x;
		y = ini_y;
		centerX = x + 8;
		centerY = y + 8;
		x_speed = ini_x_speed;
		y_speed = -32;
		aniPointer = animation;
		alive = false;
	}

	void Weapon::SetInitialXY(int x, int y) {
		ini_x = x;
		ini_y = y;
		this->x = x;
		this->y = y;
		centerX = x + 8;
		centerY = y + 8;
	}

	void Weapon::SetWeapon(int s_code) {
		aniPointer = animation + s_code;
	}

	void Weapon::LoadBitmap() {
		animation[0].AddBitmap(IDB_TEST_WEAPON, RGB(255, 255, 255));
	}

	int Weapon::GetX1()
	{
		return x;
	}

	int Weapon::GetY1()
	{
		return y;
	}

	int Weapon::GetX2()
	{
		return x + aniPointer->Width();
	}

	int Weapon::GetY2()
	{
		return y + aniPointer->Height();
	}

	bool Weapon::IsAlive() {
		return alive;
	}

	void Weapon::SetXY(int x, int y) {
		this->x = x;
		this->y = y;
		centerX = x + 8;
		centerY = y + 8;
	}

	void Weapon::SetInvertSpeed() {
		ini_x_speed = -ini_x_speed;
		x_speed = -x_speed;
	}

	/*void Weapon::SetXY() {
		x = centerX - 8;
		y = centerY - 8;
	}*/

	void Weapon::OnMove() {
		if (!alive) {
			return;
		}
		SetXY(x+x_speed, y+y_speed);
		y_speed += drop_acceleration;
		CheckAlive();
	}

	void Weapon::OnShow() {
		if (alive) {
			aniPointer->SetTopLeft(x, y);
			aniPointer->OnShow();
		}
	}

	void Weapon::CheckAlive() {
		if (alive) {
			if (x < -20 || GetX2() >= 680 || GetY2() >= 520) {
				alive = false;
				Initialize();
			}
		}
	}

	void Weapon::SetAlive(bool isAlive) {
		alive = isAlive;
	}
}
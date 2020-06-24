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

	void Weapon::Initialize(bool invert) {
		x = ini_x;
		y = ini_y;
		centerX = x + 8;
		centerY = y + 8;
		if (!invert)
			x_speed = parabola.GetSpeed()[0];
		else
			x_speed = -parabola.GetSpeed()[0];
		y_speed = parabola.GetSpeed()[1];
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
		parabola.SetXY(x, y);
	}

	void Weapon::SetWeapon(int s_code) {
		aniPointer = animation + s_code;
	}

	void Weapon::LoadBitmap() {
		parabola.LoadBitmap();
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

	int Weapon::GetAngle()
	{
		return parabola.GetAngle();
	}

	int Weapon::GetPower()
	{
		return parabola.GetPower();
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
		x_speed = -x_speed;
	}

	void Weapon::OnMove(bool invert) {
		if (!alive) {
			return;
		}
		SetXY(x+x_speed, y+y_speed);
		y_speed += drop_acceleration;
		CheckAlive(invert);
	}

	void Weapon::OnShow() {
		parabola.OnShow();
		if (alive) {
			aniPointer->SetTopLeft(x, y);
			aniPointer->OnShow();
		}

	}

	void Weapon::CheckAlive(bool invert) {
		if (alive) {
			if (x < -20 || GetX2() >= 680 || GetY2() >= 520) {
				alive = false;
				Initialize(invert);
			}
		}
	}

	void Weapon::SetAlive(bool isAlive, bool invert) {
		alive = isAlive;
		if (isAlive == false)
			Initialize(invert);
	}

	void Weapon::SetAngle(int angle, bool invert) {
		parabola.SetAngle(angle, invert);
	}

	void Weapon::SetPower(int power, bool invert) {
		parabola.SetPower(power+1, invert);
		if (!invert)
			x_speed = parabola.GetSpeed()[0];
		else
			x_speed = -parabola.GetSpeed()[0];
		y_speed = parabola.GetSpeed()[1];
	}

}
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"

namespace game_framework {
	Character::Character() {
		Initialize();
	}

	int Character::GetX1()
	{
		return x;
	}

	int Character::GetY1()
	{
		return y;
	}

	int Character::GetX2()
	{
		return x + animation.Width();
	}

	int Character::GetY2()
	{
		return y + animation.Height();
	}

	int Character::GetWidth()
	{
		return animation.Width();
	}

	int Character::GetHeight()
	{
		return animation.Height();
	}

	void Character::Initialize() {
		const int X_POS = 0;
		const int Y_POS = 0;
		animation.SetDelayCount(5);
		animation_back.SetDelayCount(5);
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void Character::OnMove(Map * m){
		if (isMovingLeft || isMovingRight || isMovingUp || isMovingDown)
			aniPointer->OnMove();
		if (isMovingRight) {	//想往右
			if (m->IsEmpty(x + aniPointer->Width(), y) && m->IsEmpty(x + aniPointer->Width(), y + aniPointer->Height() - 1) && x + aniPointer->Width() < 3600) {
				x += 10;
				m->SetSX(x);
			}
		}

		if (isMovingLeft) {	//想往左
			if (m->IsEmpty(x - 1, y) && m->IsEmpty(x - 1, y + aniPointer->Height() - 1) && x > 0) {
				x -= 10;
				m->SetSX(x);
			}
		}

		if (isMovingDown) {	//想往下
			if (m->IsEmpty(x, y + aniPointer->Height()) && m->IsEmpty(x + aniPointer->Width() - 1, y + aniPointer->Height()) && y + aniPointer->Height() < 3600) {
				y += 10;
				m->SetSY(y);
			}
		}

		if (isMovingUp) {	//想往上
			if (m->IsEmpty(x, y - 1) && m->IsEmpty(x + aniPointer->Width() - 1, y - 1) && y > 0) {
				y -= 10;
				m->SetSY(y);
			}
		}
	}

	void Character::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Character::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Character::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Character::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void Character::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Character::LoadBitmap() {
		animation.AddBitmap(IDB_CHARACTER_1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_CHARACTER_2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_CHARACTER_3, RGB(255, 255, 255));
		animation.AddBitmap(IDB_CHARACTER_4, RGB(255, 255, 255));
		animation.AddBitmap(IDB_CHARACTER_5, RGB(255, 255, 255));
		animation.AddBitmap(IDB_CHARACTER_6, RGB(255, 255, 255));
		animation_back.AddBitmap(IDB_RF_CHARACTER_1, RGB(255, 255, 255));
		animation_back.AddBitmap(IDB_RF_CHARACTER_2, RGB(255, 255, 255));
		animation_back.AddBitmap(IDB_RF_CHARACTER_3, RGB(255, 255, 255));
		animation_back.AddBitmap(IDB_RF_CHARACTER_4, RGB(255, 255, 255));
		animation_back.AddBitmap(IDB_RF_CHARACTER_5, RGB(255, 255, 255));
		animation_back.AddBitmap(IDB_RF_CHARACTER_6, RGB(255, 255, 255));
	}

	void Character::OnShow(Map * m) {
		if (isMovingLeft)
			aniPointer = &animation_back;
		if (isMovingRight)
			aniPointer = &animation;
		aniPointer->SetTopLeft(m->ScreenX(x), m->ScreenY(y));
		aniPointer->OnShow();

		//animation.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
		//animation.OnShow();	//對應ShowBitamp
		
	}
}
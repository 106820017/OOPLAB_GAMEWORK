#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Parabola.h"
#include <cmath>

#define PI 3.1415926


namespace game_framework {
	Parabola::Parabola() {
		Initialize();
	}

	int Parabola::GetAngle() {
		return angle;
	}

	int Parabola::GetPower() {
		return power;
	}

	int* Parabola::GetSpeed() {
		//int speedX = (int)(sqrt(337)*cos((double)angle*(PI / 180)));
		//int speedY = -(int)(sqrt(337)*sin((double)angle*(PI / 180)));
		//int speedX = (int)(sqrt(1348)*cos((double)angle*(PI / 180)));
		//int speedY = -(int)(sqrt(1348)*sin((double)angle*(PI / 180)));
		int speedX = (int)(energy*cos((double)angle*(PI / 180)));
		int speedY = -(int)(energy*sin((double)angle*(PI / 180)));
		return new int[2] {speedX, speedY};
	}

	void Parabola::Initialize() {
		angle = 0;
		power = 1;
		energy = ((double)power / 9) * sqrt(1348);
		x1 = 120, y1 = 290;
		invert = false;
	}

	void Parabola::LoadBitmap() {
		dot.LoadBitmap(IDB_DOT, RGB(255, 255, 255));

	}

	void Parabola::SetAngle(int angle, bool invert) {
		this->angle = angle;
		this->invert = invert;
	}

	void Parabola::SetPower(int power, bool invert) {
		this->power = power;
		this->energy = (((double)power) / 9.0) * sqrt(1348);
		this->invert = invert;
	}

	void Parabola::SetXY(int x1, int y1) {
		this->x1 = x1, this->y1 = y1;
	}

	void Parabola::OnShow() {
		for (int i = -1; i < 7; i++) {
			int cosX;
			if (!invert)
				cosX = (int)(10.0*cos((double)angle*(PI / 180)));
			else
				cosX = -(int)(10.0*cos((double)angle*(PI / 180)));
			int cosY = (int)(10.0*sin((double)angle*(PI / 180)));
			#pragma warning(disable:4244)
			dot.SetTopLeft(x1+i*cosX, y1-i*cosY);
			#pragma warning(default:4244)
			dot.ShowBitmap();
		}
	}
}
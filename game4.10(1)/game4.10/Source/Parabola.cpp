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

	int* Parabola::GetSpeed() {
		int speedX = (int)(sqrt(337)*cos((double)angle*(PI / 180)));
		int speedY = -(int)(sqrt(337)*sin((double)angle*(PI / 180)));
		return new int[2] {speedX, speedY};
	}

	void Parabola::Initialize() {
		angle = 0;
		x1 = 120, y1 = 290;
	}

	void Parabola::LoadBitmap() {
		dot.LoadBitmap(IDB_DOT, RGB(255, 255, 255));

	}

	void Parabola::SetAngle(int angle) {
		this->angle = angle;

	}

	void Parabola::SetXY(int x1, int y1) {
		this->x1 = x1, this->y1 = y1;
	}

	void Parabola::OnShow() {
		for (int i = 0; i < 5; i++) {
			int cosX = (int)(10.0*cos((double)angle*(PI / 180)));
			int cosY = (int)(10.0*sin((double)angle*(PI / 180)));
			#pragma warning(disable:4244)
			dot.SetTopLeft(x1+cosX, y1-cosY);
			#pragma warning(default:4244)
			dot.ShowBitmap();
		}
	}
}
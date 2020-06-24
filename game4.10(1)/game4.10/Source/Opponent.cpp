#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Opponent.h"

namespace game_framework {
	Opponent::Opponent() {
		Initialize();
	}

	Opponent::Opponent(int num) {
		SetNum(num);
		Initialize();
	}

	int Opponent::GetX1()
	{
		return x;
	}

	int Opponent::GetY1()
	{
		return y;
	}

	int Opponent::GetX2()
	{
		return x + ani.Width();
	}

	int Opponent::GetY2()
	{
		return y + ani.Height();
	}

	int Opponent::GetNum()
	{
		return num;
	}

	bool Opponent::IsAlive()
	{
		return alive;
	}

	void Opponent::Initialize() {
		ani.SetDelayCount(3);

		random.SetSeed(3600);
		random20.SetSeed(20);

		x = random.GetRand();
		y = random.GetRand();

		play_wait = 8;

		alive = true;
	}

	void Opponent::LoadBitmap() {		
		ani.AddBitmap(IDB_OPPONENT_SCENT_4, RGB(255, 255, 255));
		ani.AddBitmap(IDB_OPPONENT_SCENT_3, RGB(255, 255, 255));
		ani.AddBitmap(IDB_OPPONENT_SCENT_2, RGB(255, 255, 255));
		ani.AddBitmap(IDB_OPPONENT_SCENT_1, RGB(255, 255, 255));
		ani.AddBitmap(IDB_OPPONENT_SCENT_0, RGB(255, 255, 255));
		ani.AddBitmap(IDB_OPPONENT_SCENT_1, RGB(255, 255, 255));
		ani.AddBitmap(IDB_OPPONENT_SCENT_2, RGB(255, 255, 255));
		ani.AddBitmap(IDB_OPPONENT_SCENT_3, RGB(255, 255, 255));
		ani.AddBitmap(IDB_OPPONENT_SCENT_4, RGB(255, 255, 255));
	}

	void Opponent::OnShow(int sx, int sy) {
		ani.SetTopLeft(x - sx, y - sy);
		ani.OnShow();
	}

	void Opponent::OnMove(unsigned seed) {
		bool play = true;

		if (ani.GetCurrentBitmapNumber() == 0) {
			if (random20.GetRand() < 18) {
				play = false;
			}
		}

		if (play) {
			ani.OnMove();
		}

		if (alive)
			RandomMove(seed);
		else {
			x = -100;
			y = -100;
		}
	}

	void Opponent::RandomMove(unsigned seed) {	//隨機上下左右移動
		srand(seed);

		if (x <= 0)
			x += rand() % 3;
		else if (x >= 3599)
			x -= rand() % 3;
		else
			x += (rand() % 5 - 2);

		if (y <= 0)
			y += rand() % 3;
		else if (y >= 3599)
			y -= rand() % 3;
		else
			y += (rand() % 5 - 2);
	}

	void Opponent::SetNum(int num) {
		this->num = num;
	}

	void Opponent::SetAlive(bool alive) {
		this->alive = alive;
	}

	void Opponent::SetXY(int x, int y) {
		this->x = x;
		this->y = y;
	}
}
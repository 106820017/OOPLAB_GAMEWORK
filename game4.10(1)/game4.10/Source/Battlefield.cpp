#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Battlefield.h"

namespace game_framework {
	Battlefield::Battlefield() {
		Initialize();
	}

	void Battlefield::Initialize() {
		x = y = 0;
	}

	void Battlefield::ChangeCharacter(int number, int number2) {
		playerPointer1 = new BattlePlayer(number);
		s_code = number;
		playerPointer2 = new BattlePlayer(number2);
		s_code2 = number2;
	}

	void Battlefield::LoadBitmap() {
		for (int i = 0; i < 5; i++)
			background.AddBitmap(IDB_BATTLE_BACKGROUND_1);
		for (int i = 0; i < 5; i++)
			background.AddBitmap(IDB_BATTLE_BACKGROUND_2);
		for (int i = 0; i < 5; i++)
			background.AddBitmap(IDB_BATTLE_BACKGROUND_1);
		for (int i = 0; i < 5; i++)
			background.AddBitmap(IDB_BATTLE_BACKGROUND_3);

		/*playerPointer1->LoadBitmap();
		playerPointer2->LoadBitmap();*/
	}

	void Battlefield::OnMove() {
		background.OnMove();
	}

	void Battlefield::OnShow() {
		background.SetTopLeft(x, y);
		background.OnShow();
	}
}
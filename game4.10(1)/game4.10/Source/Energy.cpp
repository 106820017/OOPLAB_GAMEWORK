#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Energy.h"

namespace game_framework {
	Energy::Energy() {
		invert = false;
		Initialize();
		x = 0, y = 0;
	}

	Energy::Energy(int x, int y, bool invert) {
		this->invert = invert;
		Initialize();
		SetXY(x, y);		
	}

	int Energy::GetPower() {
		return power;
	}

	bool Energy::GetCharging() {
		return is_charging;
	}

	void Energy::Initialize() {
		power = 0;
		if (!invert)
			present_state = states;
		else
			present_state = rf_states;
		is_charging = false;
	}

	void Energy::LoadBitmap() {
		states[0].LoadBitmap(IDB_ENERGY_0, RGB(255, 255, 255));
		states[1].LoadBitmap(IDB_ENERGY_1, RGB(255, 255, 255));
		states[2].LoadBitmap(IDB_ENERGY_2, RGB(255, 255, 255));
		states[3].LoadBitmap(IDB_ENERGY_3, RGB(255, 255, 255));
		states[4].LoadBitmap(IDB_ENERGY_4, RGB(255, 255, 255));
		states[5].LoadBitmap(IDB_ENERGY_5, RGB(255, 255, 255));
		states[6].LoadBitmap(IDB_ENERGY_6, RGB(255, 255, 255));
		states[7].LoadBitmap(IDB_ENERGY_7, RGB(255, 255, 255));
		states[8].LoadBitmap(IDB_ENERGY_8, RGB(255, 255, 255));
		rf_states[0].LoadBitmap(IDB_RF_ENERGY_0, RGB(255, 255, 255));
		rf_states[1].LoadBitmap(IDB_RF_ENERGY_1, RGB(255, 255, 255));
		rf_states[2].LoadBitmap(IDB_RF_ENERGY_2, RGB(255, 255, 255));
		rf_states[3].LoadBitmap(IDB_RF_ENERGY_3, RGB(255, 255, 255));
		rf_states[4].LoadBitmap(IDB_RF_ENERGY_4, RGB(255, 255, 255));
		rf_states[5].LoadBitmap(IDB_RF_ENERGY_5, RGB(255, 255, 255));
		rf_states[6].LoadBitmap(IDB_RF_ENERGY_6, RGB(255, 255, 255));
		rf_states[7].LoadBitmap(IDB_RF_ENERGY_7, RGB(255, 255, 255));
		rf_states[8].LoadBitmap(IDB_RF_ENERGY_8, RGB(255, 255, 255));
	}

	void Energy::OnMove() {
		if (is_charging)
			Charge();
	}

	void Energy::OnShow() {
		present_state->SetTopLeft(x, y);
		present_state->ShowBitmap();
	}

	void Energy::SetXY(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void Energy::SetCharging(bool flag) {
		is_charging = flag;
	}

	void Energy::Charge() {
		if (power <= 7)
			power++;
		else
			power = 0;
		if (!invert)
			present_state = states + power;
		else
			present_state = rf_states + power;
	}
}
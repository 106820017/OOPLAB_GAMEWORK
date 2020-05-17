#pragma once

namespace game_framework {
	class Energy {
	public:
		Energy();
		Energy(int x, int y, bool invert = false);
		int  GetPower();
		bool GetCharging();
		void Initialize();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetXY(int x, int y);
		void SetCharging(bool flag);
		void Charge();
	protected:
		CMovingBitmap states[9];
		CMovingBitmap rf_states[9];
		CMovingBitmap * present_state;

		int x, y;
		int power;

		bool invert;
		bool is_charging;
	};
}

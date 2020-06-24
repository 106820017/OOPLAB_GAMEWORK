#pragma once

namespace game_framework {
	class Parabola {
	public:
		Parabola();
		int  GetAngle();
		int  GetPower();
		int* GetSpeed();
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void SetAngle(int angle, bool invert = false);
		void SetPower(int power, bool invert = false);
		void SetXY(int x1, int y1);
	protected:
		CMovingBitmap dot;
		int x1, y1;
		int angle;
		int power;	//¯à¶q1-9
		double energy;	//power / 9 * ®Ú¸¹1348
		bool invert;
	};
}

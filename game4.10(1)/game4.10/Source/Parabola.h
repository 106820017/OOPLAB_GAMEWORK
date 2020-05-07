#pragma once

namespace game_framework {
	class Parabola {
	public:
		Parabola();
		/*int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();*/
		int* GetSpeed();
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void SetAngle(int angle);
		void SetXY(int x1, int y1);
	protected:
		CMovingBitmap dot;
		int x1, y1;
		int angle;
	};
}

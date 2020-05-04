#pragma once

namespace game_framework {
	class Weapon {
	public:
		Weapon();
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		bool IsAlive();
		bool WasHit();
		void SetWeapon(int s_code);
		void Initialize();
		void SetInitialXY(int x, int y);	//作為初始用的
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetXY(int x, int y);
		void SetInvertSpeed();	//設為反方向速度
		//void SetXY();	//轉換centerXY為XY
		void SetAlive(bool isAlive);
		void CheckAlive();

	protected:
		CAnimation * aniPointer;
		CAnimation animation[10];
		int x, y;
		int ini_x = 120, ini_y = 290;
		int centerX, centerY;
		int x_speed, y_speed;
		int ini_x_speed = 18;
		const int drop_acceleration = 3;
		bool alive;
		//bool get_hit;
	};
}

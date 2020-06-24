#pragma once
#include "Parabola.h"

namespace game_framework {
	class Weapon {
	public:
		Weapon();
		//Weapon(bool invert);
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		int  GetAngle();
		int  GetPower();
		bool IsAlive();
		void SetWeapon(int s_code);
		void Initialize(bool invert = false);
		void SetInitialXY(int x, int y);	//作為初始用的
		void LoadBitmap();
		void OnMove(bool invert = false);	//參數為設定反方向
		void OnShow();
		void SetXY(int x, int y);
		void SetInvertSpeed();	//設為反方向速度
		void SetAngle(int angle = 0, bool invert = false);	//設定角度
		void SetPower(int power = 0, bool invert = false);	//設定力量, power 0-8
		void SetAlive(bool isAlive, bool invert = false);
		void CheckAlive(bool invert);

	protected:
		CAnimation * aniPointer;
		CAnimation animation[10];
		Parabola parabola;
		int angle;
		int x, y;
		int ini_x = 120, ini_y = 290;
		int centerX, centerY;
		int x_speed, y_speed;
		const int drop_acceleration = 3;
		bool alive;
	};
}

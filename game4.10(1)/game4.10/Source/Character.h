#include "Map.h"

namespace game_framework {
	class Character {
	public:
		Character();
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		void Initialize();
		void LoadBitmap();
		void OnMove(Map * m);
		void OnShow(Map * m);
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetXY(int nx, int ny);
	protected:
		CAnimation animation, animation_back;
		CAnimation * aniPointer = &animation;
		int x, y;
		bool isMovingDown;
		bool isMovingLeft;
		bool isMovingRight;	
		bool isMovingUp;
	};
}

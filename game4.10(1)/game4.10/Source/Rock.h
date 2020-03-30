

namespace game_framework {
	class Rock {
	public:
		Rock();
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void SetXY(int nx, int ny);
	protected:
		CMovingBitmap bitmap;
		int x, y;
	};
}
#pragma once

namespace game_framework {
	class House {
	public:
		House();
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void SetXY(int nx, int ny);
	protected:
		CMovingBitmap bitmap[5][5];
		int x, y;
	};
}

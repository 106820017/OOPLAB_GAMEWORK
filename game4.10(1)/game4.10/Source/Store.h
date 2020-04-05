#pragma once

namespace game_framework {
	class Store {
	public:
		Store();
		//void Initialize();
		void LoadBitmap();
		void OnShow();
	protected:
		CMovingBitmap bitmap, back_arrow, sign, announcement;
		int x, y;
	};
}

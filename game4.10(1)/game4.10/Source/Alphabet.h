#pragma once
#include <string>

namespace game_framework {
	class Alphabet {
	public:
		Alphabet();
		void LoadBitmap();
		void OnMove();
		void ShowString(string input, int x, int y);
		void ClearCurrent();
		void SetCurrent(int current);
	protected:
		int x, y;
		int current_letter;
		int wait;

		CMovingBitmap capitals[26], lowers[26], punctuation[5];
	};
}

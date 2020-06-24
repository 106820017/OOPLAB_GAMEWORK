#pragma once
#include <deque>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib> 

namespace game_framework {
	class Random {
	public:
		Random();
		void SetSeed(int range);
		int GetRand();
	protected:
		std::vector<int> numbers;
	};
}
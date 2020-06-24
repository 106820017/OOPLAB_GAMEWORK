#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Random.h"
#include <cmath>

namespace game_framework {
	Random::Random() {

	}

	void Random::SetSeed(int range) {
		unsigned seed;
		seed = (unsigned)time(NULL) * (rand() % 25);	// 取得時間序列
		srand(seed);

		if (!numbers.empty())
			numbers.clear();

		for (int i = 0; i < 1000; i++) {
			numbers.push_back(rand() % range);
		}
		std::random_shuffle(numbers.begin(), numbers.end());
	}

	int Random::GetRand() {
		//unsigned seed;
		/*seed = (unsigned)pow(time(NULL), 100);	// 取得時間序列
		srand(seed);*/
		//seed = (unsigned)time(NULL) * (rand() % 10) * (rand() % 25); // 取得時間序列
		//srand(seed);
		//return rand() % range;
		int num = numbers.front();
		std::random_shuffle(numbers.begin(), numbers.end());
		
		return num;
	}
}
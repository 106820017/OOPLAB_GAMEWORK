#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"

namespace game_framework {
	Map::Map()
	:sx(0),sy(0),MH(120),MW(120){
		Initialize();
	}

	void Map::Initialize() {
		for (int i = 0; i < 30; i++)
			for (int j = 0; j < 30; j++)
				map[i][j] = 0;
		for (int i = 0; i < 30; i++)
			for (int j = 0; j < 30; j++)
				map[i][j] = obstacle[j][i];
		/*for (int i = 3; i < 30; i += 3)
			for (int j = 0; j < 30; j += 3)
				map[i][j] = 2;*/
	}

	int Map::ScreenX(int x) {
		return x - sx;
	}

	int Map::ScreenY(int y) {
		return y - sy;
	}

	bool Map::IsEmpty(int x, int y) {
		int blockX = x / 120;
		int blockY = y / 120;
		return (map[blockX][blockY] == 0 || map[blockX][blockY] == 4);
	}

	bool Map::EnterHouse(int x, int y) {
		int blockX = x / 120;
		int blockY = y / 120;
		return (map[blockX + 1][blockY] == 3 && map[blockX][blockY - 1] == 3);
	}

	void Map::SetEmpty(int x, int y) {
		int blockX = x / 120;
		int blockY = y / 120;
		map[blockX][blockY] = 0;
	}

	void Map::LoadBitmap() {
		bitmap.LoadBitmap(IDB_GRASS);
		rock.LoadBitmap(IDB_TEST_ROCK, RGB(255, 255, 255));
		bush.LoadBitmap(IDB_BUSH, RGB(255, 255, 255));
		house.LoadBitmap();
		//house.LoadBitmap(IDB_TEST);
	}

	void Map::OnShow() {
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				int x = i * 120 - sx;
				int y = j * 120 - sy;
				bitmap.SetTopLeft(x, y);
				bitmap.ShowBitmap();
				switch (map[i][j]) {
				case 1:
					bush.SetTopLeft(x, y);
					bush.ShowBitmap();
					break;
				case 2:
					rock.SetTopLeft(x, y);
					rock.ShowBitmap();
					break;
				case 4:
					house.SetXY(x, y);
					//house.OnShow();
					break;
				}
			}
			house.OnShow();
		}
	}

	void Map::SetSX(int x) {	//��Jx������y��
		if (x != sx + 260) {	//���⤣�b�ù������� �ù���640*480
			/*if (x > 260 && x < 11620) {	//���
				sx = x - 260;
			}*/
			if (x > 260 && x < 3220)
				sx = x - 260;
		}
	}

	void Map::SetSY(int y) {	//��Jy������y��
		if (y != sy + 179) {	//���⤣�b�ù�������
			/*if (y > 179 && y < 11700) {	//���
				sy = y - 179;
			}*/
			if (y > 179 && y < 3360)
				sy = y - 179;
		}
	}

}
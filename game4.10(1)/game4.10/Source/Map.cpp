#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"

namespace game_framework {
	Map::Map()
		:sx(0), sy(0), MH(120), MW(120) {
		Initialize();
		/*unsigned seed;
		seed = (unsigned)time(NULL) * 100; // 取得時間序列
		srand(seed);*/
	}

	void Map::Initialize() {
		for (int i = 0; i < 30; i++)
			for (int j = 0; j < 30; j++)
				map[i][j] = 0;
		for (int i = 0; i < 30; i++)
			for (int j = 0; j < 30; j++)
				map[i][j] = obstacle[j][i];

		opponent1 = new Opponent(0);
		opponent2 = new Opponent(1);
		opponent3 = new Opponent(2);
		opponent4 = new Opponent(3);
		opponent5 = new Opponent(4);
		
		opponents_pointer = new Opponent[5] { *opponent1, *opponent2, *opponent3, *opponent4, *opponent5 };

		battling_num = -1;

		//opponent1 = new Opponent(0);
		//opponent2 = new Opponent(0);
		/*Opponent ops[5] = { opponent1, opponent2, opponent3, opponent4, opponent5 };
		for (int i = 0; i < 5; i++)
			opponents[i] = ops[i];*/
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

	int Map::GetBattlingNum() {
		return battling_num;
	}

	int Map::GetOpponentX1() {
		switch (battling_num)
		{
		case 0:
			return opponent1->GetX1();
		case 1:
			return opponent2->GetX1();
		case 2:
			return opponent3->GetX1();
		case 3:
			return opponent4->GetX1();
		case 4:
			return opponent5->GetX1();
		default:
			return 0;
		}
	}

	int Map::GetOpponentY1() {
		switch (battling_num)
		{
		case 0:
			return opponent1->GetY1();
		case 1:
			return opponent2->GetY1();
		case 2:
			return opponent3->GetY1();
		case 3:
			return opponent4->GetY1();
		case 4:
			return opponent5->GetY1();
		default:
			return 0;
		}
	}

	int Map::GetOpponentX2() {
		switch (battling_num)
		{
		case 0:
			return opponent1->GetX2();
		case 1:
			return opponent2->GetX2();
		case 2:
			return opponent3->GetX2();
		case 3:
			return opponent4->GetX2();
		case 4:
			return opponent5->GetX2();
		default:
			return 0;
		}
	}

	int Map::GetOpponentY2() {
		switch (battling_num)
		{
		case 0:
			return opponent1->GetY2();
		case 1:
			return opponent2->GetY2();
		case 2:
			return opponent3->GetY2();
		case 3:
			return opponent4->GetY2();
		case 4:
			return opponent5->GetY2();
		default:
			return 0;
		}
	}

	bool Map::IsEmpty(int x, int y) {
		int blockX = x / 120;
		int blockY = y / 120;
		return (map[blockX][blockY] == 0 || map[blockX][blockY] == 4);
	}

	bool Map::EnterHouse(int x, int y) {
		int blockX = x / 120;
		int blockY = y / 120;
		return (map[blockX + 1][blockY] == 3 && map[blockX][blockY - 1] == 3 && map[blockX + 1][blockY - 1] == 3 && map[blockX + 2][blockY] == 3 && map[blockX][blockY - 2] == 3);
	}

	bool Map::InBattle(int x1, int x2, int y1, int y2) {
		int points[5][4] = { {opponent1->GetX1(), opponent1->GetX2(), opponent1->GetY1(), opponent1->GetY2()},
								  {opponent2->GetX1(), opponent2->GetX2(), opponent2->GetY1(), opponent2->GetY2()},
								  {opponent3->GetX1(), opponent3->GetX2(), opponent3->GetY1(), opponent3->GetY2()},
								  {opponent4->GetX1(), opponent4->GetX2(), opponent4->GetY1(), opponent4->GetY2()},
								  {opponent5->GetX1(), opponent5->GetX2(), opponent5->GetY1(), opponent5->GetY2()} };
		for (int i = 0; i < 5; i++) {
			if (!((x2 < points[i][0]) || (x1 > points[i][1])) && !((y2 < points[i][2]) || (y1 > points[i][3]))) { //檢查腳色與怪物重疊
				battling_num = i;
				return true;
			}
		}
		battling_num = -1;
		return false;
	}

	bool Map::GetOpponentAlive(int num) {
		switch (num)
		{
		case 0:
			return opponent1->IsAlive();
		case 1:
			return opponent2->IsAlive();
		case 2:
			return opponent3->IsAlive();
			break;
		case 3:
			return opponent4->IsAlive();
		case 4:
			return opponent5->IsAlive();
		default:
			return false;
		}
	}

	void Map::SetEmpty(int x, int y) {
		int blockX = x / 120;
		int blockY = y / 120;
		map[blockX][blockY] = 0;
	}

	void Map::LoadBitmap() {
		bitmap.LoadBitmap(IDB_GRASS);
		rock.LoadBitmap(IDB_ROCK, RGB(255, 255, 255));
		bush.LoadBitmap(IDB_BUSH, RGB(255, 255, 255));
		house.LoadBitmap();
		opponent1->LoadBitmap();
		opponent2->LoadBitmap();
		opponent3->LoadBitmap();
		opponent4->LoadBitmap();
		opponent5->LoadBitmap();
		
		/*for (int i = 0; i < 5; i++)
			opponents2[i].LoadBitmap();*/

		/*for (int i = 0; i < 5; i++)
			opponents[i].LoadBitmap();*/
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
		opponent1->OnShow(sx, sy);
		opponent2->OnShow(sx, sy);
		opponent3->OnShow(sx, sy);
		opponent4->OnShow(sx, sy);
		opponent5->OnShow(sx, sy);
		/*for (int i = 0; i < 5; i++)
			opponents[i].OnShow(sx, sy);*/
	}

	void Map::SetSX(int x) {	//輸入x為角色座標
		if (x != sx + 260) {	//角色不在螢幕正中間 螢幕為640*480
			/*if (x > 260 && x < 11620) {	//邊界
				sx = x - 260;
			}*/
			if (x > 260 && x < 3220)
				sx = x - 260;
		}
	}

	void Map::SetSY(int y) {	//輸入y為角色座標
		if (y != sy + 179) {	//角色不在螢幕正中間
			/*if (y > 179 && y < 11700) {	//邊界
				sy = y - 179;
			}*/
			if (y > 179 && y < 3360)
				sy = y - 179;
		}
	}

	void Map::OpponentsOnMove() {
		unsigned seed;
		seed = (unsigned)time(NULL);

		opponent1->OnMove(seed);
		opponent2->OnMove(seed * 2);
		opponent3->OnMove(seed * 3);
		opponent4->OnMove(seed * 4);
		opponent5->OnMove(seed * 5);
		/*for (int i = 0; i < 5; i++)
			opponents[i].OnMove(sx, sy);*/
	}

	void Map::SetOpponentAlive(bool alive) {
		//opponents_pointer[battling_num].SetAlive(alive);
		switch (battling_num)
		{
		case 0:
			opponent1->SetAlive(alive);
			break;
		case 1:
			opponent2->SetAlive(alive);
			break;
		case 2:
			opponent3->SetAlive(alive);
			break;
		case 3:
			opponent4->SetAlive(alive);
			break;
		case 4:
			opponent5->SetAlive(alive);
			break;
		default:
			break;
		}
	}

	void Map::SetOpponentXY(int num, int x, int y) {
		switch (num)
		{
		case 0:
			opponent1->SetXY(x, y);
			break;
		case 1:
			opponent2->SetXY(x, y);
			break;
		case 2:
			opponent3->SetXY(x, y);
			break;
		case 3:
			opponent4->SetXY(x, y);
			break;
		case 4:
			opponent5->SetXY(x, y);
			break;
		default:
			break;
		}
	}

	void Map::OpponentsInitialize() {
		opponent1->Initialize();
		opponent2->Initialize();
		opponent3->Initialize();
		opponent4->Initialize();
		opponent5->Initialize();
		sx = 0;
		sy = 0;
	}
}
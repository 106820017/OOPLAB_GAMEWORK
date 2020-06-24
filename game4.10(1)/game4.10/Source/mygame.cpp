
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0);	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	logo.LoadBitmap(IDB_BACKGROUND);
	start_page.LoadBitmap("res/start.bmp", RGB(255, 255, 255));
	how_to.LoadBitmap("res/how.bmp");
	start_button.LoadBitmap("res/play.bmp", RGB(255, 255, 255));
	quit_button.LoadBitmap("res/quit.bmp", RGB(255, 255, 255));
	howTo_button.LoadBitmap("res/howtoplay_small.bmp");
	credit_button.LoadBitmap("res/credit.bmp", RGB(255, 255, 255));
	selection_frame.LoadBitmap("res/start_selection_frame.bmp", RGB(255, 255, 255));
	teacher_credit.LoadBitmap("res/teacher_credit.bmp", RGB(255, 255, 255));
	yu.LoadBitmap("res/yu.bmp", RGB(255, 255, 255));
	Sleep(300);				
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	const char KEY_UP = 0x26; // keyboard上箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	if (nChar == KEY_UP && selecting > 0 && !show_how_to && !show_teacher_credit && !show_student_credit)
		selecting--;
	else if (nChar == KEY_DOWN && selecting < 3 && !show_how_to && !show_teacher_credit && !show_student_credit)
		selecting++;
	else if (nChar == KEY_SPACE && !show_how_to && !show_teacher_credit && !show_student_credit) {
		if (selecting == 0)
			GotoGameState(GAME_STATE_RUN);
		else if (selecting == 1)
			show_how_to = true;
		else if (selecting == 2)
			show_teacher_credit = true;
		else if (selecting == 3)
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
	}
	else if (nChar == KEY_ESC) {
		if (show_how_to)
			show_how_to = false;
		else if (show_teacher_credit || show_student_credit) {
			show_teacher_credit = false;
			show_student_credit = false;
		}
	}
	else if (nChar == KEY_RIGHT && show_teacher_credit) {
		show_teacher_credit = false;
		show_student_credit = true;
	}
	else if (nChar == KEY_LEFT && show_student_credit) {
		show_teacher_credit = true;
		show_student_credit = false;
	}
		
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateInit::OnShow()
{
	//
	// 貼上logo
	//
	/*logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();*/
	if (!show_how_to && !show_teacher_credit && !show_student_credit) {
		start_page.SetTopLeft(0, 0);
		start_page.ShowBitmap();
		start_button.SetTopLeft(270, 220);
		start_button.ShowBitmap();
		howTo_button.SetTopLeft(270, 280);
		howTo_button.ShowBitmap();
		credit_button.SetTopLeft(270, 340);
		credit_button.ShowBitmap();
		quit_button.SetTopLeft(270, 400);
		quit_button.ShowBitmap();
		selection_frame.SetTopLeft(270, 220 + selecting * 60);
		selection_frame.ShowBitmap();
	}	
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
	if (show_how_to) {
		how_to.SetTopLeft(0, 0);
		how_to.ShowBitmap();
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		pDC->TextOut(10, 445, "ESC to return.");		
		pDC->SelectObject(fp);						// 放掉 font f 
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	if (show_teacher_credit) {
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		pDC->TextOut(450, 10, "ESC to return.");
		pDC->TextOut(140, 10, "授課老師:");
		pDC->TextOut(490, 450, "作者資訊 →");
		//pDC->TextOut(150, 10, "指導老師:");
		/*pDC->TextOut(5, 395, "Press Ctrl-F to switch in between window mode and full screen mode.");
		if (ENABLE_GAME_PAUSE)
			pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");
		pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");*/
		pDC->SelectObject(fp);						// 放掉 font f 
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		teacher_credit.SetTopLeft(110, 50);
		teacher_credit.ShowBitmap();
	}

	if (show_student_credit) {
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		pDC->TextOut(450, 10, "ESC to return.");
		pDC->TextOut(140, 10, "作者資訊:");
		pDC->TextOut(140, 50, "OOP實習 組別34");
		pDC->TextOut(140, 150, "電資三");
		pDC->TextOut(140, 190, "106820017  劉騏毓");
		pDC->TextOut(140, 290, "電資三");
		pDC->TextOut(140, 330, "106820038  林庭");
		pDC->TextOut(0, 450, "← 老師資訊");
		/*pDC->TextOut(5, 395, "Press Ctrl-F to switch in between window mode and full screen mode.");
		if (ENABLE_GAME_PAUSE)
			pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");
		pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");*/
		pDC->SelectObject(fp);						// 放掉 font f 
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC		
		yu.SetTopLeft(335, 329);
		yu.ShowBitmap();
	}
}								

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);		
		//PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Congrats ! You've got all of the characters ! (%d)", counter / 30);
	pDC->TextOut(60,210,str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMBALLS(28)
{
	//ball = new CBall [NUMBALLS];
}

CGameStateRun::~CGameStateRun()
{
	//delete [] ball;
}

void CGameStateRun::OnBeginState()
{
	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 10;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 15;
	
	character.Initialize();	
	help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	
	CAudio::Instance()->Play(AUDIO_GAME, true);			// 撥放 MIDI
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	//
	// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	
	character.OnMove(mapp);
	bool wasInBattle = in_battle;
	CheckInBattle();
	
	if (!in_battle && !in_store) {
		gamemap.OpponentsOnMove();
	}
	else {
		battlefield.OnMove();
	}

	if (in_battle && !music_played) {
		CAudio::Instance()->Stop(AUDIO_GAME);
		CAudio::Instance()->Play(AUDIO_FIGHT, true);
		music_played = true;
	}
	else if (in_store && !music_played) {
		CAudio::Instance()->Stop(AUDIO_GAME);
		CAudio::Instance()->Play(AUDIO_STORE, true);
		music_played = true;
	}
	else if (!in_store && !in_battle && music_played) {
		CAudio::Instance()->Stop(AUDIO_STORE);
		CAudio::Instance()->Stop(AUDIO_FIGHT);
		CAudio::Instance()->Play(AUDIO_GAME, true);
		music_played = false;
	}

	if (in_store) {
		store.OnMove();
	}
	else
	{
		store.ClearCurrent();
	}

	if (battlefield.GetParalyze(2)) {
		player1_attacked = false;		
	}

	if (in_battle && player1_attacked && !battlefield.GetWeaponAlive(1) && !battlefield.GetWeaponAlive(2)) {
		AngleMove();
		Charge();
	}

	if (!wasInBattle && in_battle && battling_num != -1) {
		battlefield.ChangeCharacter(store.GetProfileNum(), battling_num);
	}

	if (battlefield.GetHealth(1) <= 0 || battlefield.GetHealth(2) <= 0) {
		LeaveBattle();
		battlefield.ChangeCharacter(store.GetProfileNum(), 0);

	}

	int quit = 0;
	for (int i = 0; i < 5; i++) {
		if (store.GetPlayerAble(i))
			quit++;
	}

	if (in_store && quit >= 5) {
		mapp->OpponentsInitialize();
		store.Initialize();
		character.Initialize();
		in_store = false;
		battlefield.ChangeSkill(0);
		battlefield.ChangeCharacter(0);
		GotoGameState(GAME_STATE_OVER);
		CAudio::Instance()->Stop(AUDIO_STORE);
	}
		
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	//
	// 開始載入資料
	//

	gamemap.LoadBitmap();
	store.LoadBitmap();
	battlefield.LoadBitmap();

	character.LoadBitmap();
	//
	// 完成部分Loading動作，提高進度
	//
	ShowInitProgress(50);
	Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 繼續載入其他資料
	//
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// 載入說明的圖形
	corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
	hits_left.LoadBitmap();		
	rand20.SetSeed(20);
	rand10.SetSeed(10);
	angle = 35;

	CAudio::Instance()->Load(AUDIO_GAME,  "sounds\\game.mp3");	// 載入編號0的聲音
	CAudio::Instance()->Load(AUDIO_FIGHT, "sounds\\fight.mp3");
	CAudio::Instance()->Load(AUDIO_STORE, "sounds\\store.mp3");
	CAudio::Instance()->Load(AUDIO_PRESS, "sounds\\press.mp3");
	CAudio::Instance()->Load(AUDIO_SELECT, "sounds\\select.mp3");
	CAudio::Instance()->Load(AUDIO_UNABLE, "sounds\\unable.mp3");
	CAudio::Instance()->Load(AUDIO_HIT, "sounds\\hit.mp3");
	CAudio::Instance()->Load(AUDIO_LASER, "sounds\\laser.mp3");
	CAudio::Instance()->Load(AUDIO_PARALYZE, "sounds\\paralyze.mp3");
	CAudio::Instance()->Load(AUDIO_REVIVE, "sounds\\revive.mp3");
	//
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_ESC	 = 0x1B; // keyboard ESC
	const char KEY_SPACE = 0x20; // keyboard空白鍵
	const char KEY_ENTER = 0x0D; // keyboard Enter
	const char KEY_Z	 = 0x5A; // keyboard_Z
	const char KEY_K	 = 0x4B; //keyboard_K
	CheckInStore();
	if (!in_store && !in_battle) {
		if (nChar == KEY_LEFT)
			character.SetMovingLeft(true);
		if (nChar == KEY_RIGHT)
			character.SetMovingRight(true);
		if (nChar == KEY_UP)
			character.SetMovingUp(true);
		if (nChar == KEY_DOWN)
			character.SetMovingDown(true);
	}

	if (in_store && !store.IsChoosingCharacter() && !store.IsChoosingSkill() && nChar == KEY_RIGHT) {
		CAudio::Instance()->Play(AUDIO_PRESS);
		store.NextOption();
	}

	if (in_store && !store.IsChoosingCharacter() && !store.IsChoosingSkill()) {
		if (store.GetOptionNum() == 0 && nChar == KEY_SPACE) {
			CAudio::Instance()->Play(AUDIO_SELECT);
			store.SetChoosingCharacter(true);
		}
		else if (store.GetOptionNum() == 1 && nChar == KEY_SPACE) {
			CAudio::Instance()->Play(AUDIO_SELECT);
			store.SetChoosingSkill(true);
		}
	}
	else if (in_store && store.IsChoosingCharacter()) {
		int able[5] = {store.GetPlayerAble(0), store.GetPlayerAble(1), store.GetPlayerAble(2), store.GetPlayerAble(3), store.GetPlayerAble(4) };
		int next_num = 0, prev_num = 0;
		switch (nChar)
		{
		case KEY_RIGHT:
			if (store.GetProfileNum() < 4) {
				for (int i = store.GetProfileNum() + 1; i <= 4; i++) {
					if (able[i]) {
						next_num = i;
						store.SetCharacter(next_num);
						CAudio::Instance()->Play(AUDIO_PRESS);
						break;
					}
				}					
				CAudio::Instance()->Play(AUDIO_UNABLE);
			}
			break;
		case KEY_LEFT:
			if (store.GetProfileNum() > 0) {
				for (int i = store.GetProfileNum() - 1; i >= 0; i--) {
					if (able[i]) {
						prev_num = i;
						store.SetCharacter(prev_num);
						CAudio::Instance()->Play(AUDIO_PRESS);
						break;
					}
				}
				CAudio::Instance()->Play(AUDIO_UNABLE);
			}
			break;
		case KEY_UP:
			if ((store.GetProfileNum() == 3)) {
				if (store.GetPlayerAble(0)) {
					store.SetCharacter(0);
					CAudio::Instance()->Play(AUDIO_PRESS);
				}					
				else if (store.GetPlayerAble(1)) {
					CAudio::Instance()->Play(AUDIO_PRESS);
					store.SetCharacter(1);
				}			
				else {
					CAudio::Instance()->Play(AUDIO_UNABLE);
				}
			}
			else if ((store.GetProfileNum() == 4)) {
				if (store.GetPlayerAble(2)) {
					CAudio::Instance()->Play(AUDIO_PRESS);
					store.SetCharacter(2);
				}
				else if (store.GetPlayerAble(1)) {
					CAudio::Instance()->Play(AUDIO_PRESS);
					store.SetCharacter(1);
				}
				else {
					CAudio::Instance()->Play(AUDIO_UNABLE);
				}
			}
			break;
		case KEY_DOWN:
			if ((store.GetProfileNum() == 0)) {
				if (store.GetPlayerAble(3)) {
					CAudio::Instance()->Play(AUDIO_PRESS);
					store.SetCharacter(3);
				}
				else {
					CAudio::Instance()->Play(AUDIO_UNABLE);
				}
			}
			else if ((store.GetProfileNum() == 1)) {
				if (store.GetPlayerAble(3)) {
					CAudio::Instance()->Play(AUDIO_PRESS);
					store.SetCharacter(3);
				}
				else if (store.GetPlayerAble(4)) {
					CAudio::Instance()->Play(AUDIO_PRESS);
					store.SetCharacter(4);
				}
				else {
					CAudio::Instance()->Play(AUDIO_UNABLE);
				}
			}
			else if ((store.GetProfileNum() == 2)) {
				if (store.GetPlayerAble(4)) {
					CAudio::Instance()->Play(AUDIO_PRESS);
					store.SetCharacter(4);
				}
				else {
					CAudio::Instance()->Play(AUDIO_UNABLE);
				}
			}
			break;
		case KEY_SPACE:
			battlefield.ChangeCharacter(store.GetProfileNum());
			store.SetChoosingCharacter(false);
			CAudio::Instance()->Play(AUDIO_SELECT);
			break;
		default:
			break;
		}
	}
	else if (in_store && store.IsChoosingSkill()) {
		switch (nChar)
		{
		case KEY_RIGHT:
			store.NextSkill();
			CAudio::Instance()->Play(AUDIO_PRESS);
			break;
		case KEY_LEFT:
			store.LastSkill();
			CAudio::Instance()->Play(AUDIO_PRESS);
			break;
		case KEY_SPACE:
			battlefield.ChangeSkill(store.GetSkillNum());
			store.SetChoosingSkill(false);
			CAudio::Instance()->Play(AUDIO_SELECT);
			break;
		default:
			break;
		}
	}

	if (in_store && store.GetOptionNum() == 0 && nChar == KEY_K) {
		for (int i = 0; i < 5; i++)
			store.SetPlayerGet(i);
	}

	if (!in_store && !in_battle && nChar == KEY_K) {
		for (int i = 0; i < 5; i++) {
			if (mapp->GetOpponentAlive(i)) {
				mapp->SetOpponentXY(i, character.GetX1(), character.GetY1());
				break;
			}
		}
	}

	if (in_store && store.GetOptionNum() == 2 && nChar == KEY_SPACE)
		LeaveStore();
	
	if (in_battle && nChar == KEY_Z) {
		if (!player1_attacked && !battlefield.GetWeaponAlive(1) && !battlefield.GetWeaponAlive(2) && !battlefield.GetSkillUsed(1)) {
			battlefield.SetSkillActivated(1);
		}
	}

	if (in_battle && nChar == KEY_SPACE) {
		if (battlefield.GetParalyze(2)) {
			battlefield.SetParalyze(2, false);
		}

		if (!player1_attacked && !battlefield.GetWeaponAlive(1) && !battlefield.GetWeaponAlive(2)) {
			battlefield.SetCharge(1, true);
		}
	}

	if (in_battle && nChar == KEY_UP) {
		if (!player1_attacked) {
			battlefield.SetAngle(battlefield.GetAngle(1) + 5, battlefield.GetAngle(2));
		}
	}
	
	if (in_battle && nChar == KEY_DOWN) {
		if (!player1_attacked) {
			battlefield.SetAngle(battlefield.GetAngle(1) - 5, battlefield.GetAngle(2));
		}
	}

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_SPACE = 0x20; // keyboard空白鍵
	//CheckInStore();
	if (nChar == KEY_LEFT)
		character.SetMovingLeft(false);
	if (nChar == KEY_RIGHT)
		character.SetMovingRight(false);
	if (nChar == KEY_UP)
		character.SetMovingUp(false);
	if (nChar == KEY_DOWN)
		character.SetMovingDown(false);

	if (in_battle && nChar == KEY_SPACE) {
		if (!player1_attacked && !battlefield.GetWeaponAlive(1) && !battlefield.GetWeaponAlive(2)) {
			battlefield.SetCharge(1, false);
			if (battlefield.GetSkillType(1) == 4 && battlefield.GetSkillActivated(1)) {
				battlefield.OnLaserAttack();
				CAudio::Instance()->Play(AUDIO_LASER);
				battlefield.SetSkillActivated(1, false);
			}
			else
				battlefield.OnAttack(1);
			player1_attacked = true;
		}
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	//eraser.SetMovingLeft(true);
	character.SetMovingLeft(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	character.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	character.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	character.SetMovingRight(false);
}

void CGameStateRun::SetPlayer2Angle(UINT nFlags) {
	const char KEY_UP = 0x26; // keyboard上箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭

	if (nFlags == KEY_UP)
		battlefield.SetAngle(battlefield.GetAngle(1), battlefield.GetAngle(2) + 5);
	else if (nFlags == KEY_DOWN)
		battlefield.SetAngle(battlefield.GetAngle(1), battlefield.GetAngle(2) - 5);
}

void CGameStateRun::SetPlayer2Charge(bool flag) {
	battlefield.SetCharge(2, flag);
}

void CGameStateRun::SetPlayer2Attack() {
	battlefield.OnAttack(2);
	player1_attacked = false;
}

void CGameStateRun::OnShow()
{
	//
	//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
	//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
	//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
	//
	//
	//  貼上背景圖、撞擊數、球、擦子、彈跳的球
	//
	gamemap.OnShow();
	character.OnShow(mapp);

	if (in_store) {
		store.OnShow();
	}


	if (in_battle) {
		battlefield.OnShow();
	}
}

void CGameStateRun::CheckInStore() {
	in_store = mapp->EnterHouse(character.GetX2(), character.GetY1());
}

void CGameStateRun::LeaveStore() {
	in_store = false;
	character.SetXY(character.GetX1() - 120, character.GetY1() + 120);
	mapp->SetSX(character.GetX1());
	mapp->SetSY(character.GetY1());
}

void CGameStateRun::CheckInBattle() {
	in_battle = mapp->InBattle(character.GetX1(), character.GetX2(), character.GetY1(), character.GetY2());
	battling_num = mapp->GetBattlingNum();
}

void CGameStateRun::LeaveBattle() {
	in_battle = false;

	if (battlefield.GetHealth(2) <= 0) {
		store.SetPlayerGet(mapp->GetBattlingNum());
		mapp->SetOpponentAlive(false);
	}

	battlefield.ResetSkillAnimation(1);
	battlefield.ResetSkillAnimation(2);

	int nX1 = mapp->GetOpponentX1() - 160;
	int nY1 = mapp->GetOpponentY1() + 160;
	if (nX1 < 0 || !(mapp->IsEmpty(nX1, nY1) && mapp->IsEmpty(nX1+character.GetWidth(), nY1)))
		nX1 = mapp->GetOpponentX2() + 40;
	if (nY1 >= 3480 || !(mapp->IsEmpty(nX1, nY1) && mapp->IsEmpty(nX1, nY1+character.GetHeight())))
		nY1 = mapp->GetOpponentY2() - 40;

	character.SetXY(nX1, nY1);

	mapp->SetSX(character.GetX1());
	mapp->SetSY(character.GetY1());	

	player1_attacked = false;
	battlefield.SetParalyze(2, false);
	SetPlayer2Charge(false);
}
void CGameStateRun::AngleMove() {
	if (!Chargable) {
		
		if (battlefield.GetAngle(2) > angle)
			SetPlayer2Angle(0x28);	//down
		else if (battlefield.GetAngle(2) < angle)
			SetPlayer2Angle(0x26);	//up
		else
			Chargable = true;
	}
	player1_attacked = true;
}

void CGameStateRun::Charge() {
	if (Chargable) {
		if (rand20.GetRand() < 18)
			SetPlayer2Charge(true);
		else {
			SetPlayer2Charge(false);
			SetPlayer2Attack();
			Chargable = false;
			player1_attacked = false;
			angle = rand10.GetRand() * 5;
		}
	}

}
}
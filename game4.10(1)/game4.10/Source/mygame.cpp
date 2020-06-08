
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	logo.LoadBitmap(IDB_BACKGROUND);
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// �K�Wlogo
	//
	logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();
	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}								

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
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
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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
	/*for (int i = 0; i < NUMBALLS; i++) {				// �]�w�y���_�l�y��
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);
	}*/
	//eraser.Initialize();
	character.Initialize();
	//background.SetTopLeft(BACKGROUND_X,0);				// �]�w�I�����_�l�y��
	help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
	hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	//CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	//CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
	CAudio::Instance()->Play(AUDIO_GAME, true);			// ���� MIDI
}

void CGameStateRun::OnMove()							// ���ʹC������
{
	//
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// ���ʭI���Ϫ��y��
	//
	/*if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);*/
	//
	// ���ʲy
	//
	/*int i;
	for (i=0; i < NUMBALLS; i++)
		ball[i].OnMove();*/
	//
	// �������l
	//
	//eraser.OnMove();
	character.OnMove(mapp);
	CheckInBattle();
	//gamemap.OpponentsOnMove();
	if (!in_battle) {
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

	

	//
	// �P�_���l�O�_�I��y
	//
	/*for (i=0; i < NUMBALLS; i++)
		if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
			ball[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(-1);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}*/
	//
	// ���ʼu�����y
	//
	//bball.OnMove();
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
	//
	/*unsigned seed;
	seed = (unsigned)time(NULL); // ���o�ɶ��ǦC
	srand(seed);*/
	gamemap.LoadBitmap();
	store.LoadBitmap();
	battlefield.LoadBitmap();

	/*int i;
	for (i = 0; i < NUMBALLS; i++)	
		ball[i].LoadBitmap();	*/							// ���J��i�Ӳy���ϧ�
	//eraser.LoadBitmap();
	character.LoadBitmap();
	//background.LoadBitmap(IDB_BACKGROUND);					// ���J�I�����ϧ�
	//
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
	//
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// ���J�������ϧ�
	corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�
	//corner.ShowBitmap(background);							// �Ncorner�K��background
	//bball.LoadBitmap();										// ���J�ϧ�
	hits_left.LoadBitmap();									
	//CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	//CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	CAudio::Instance()->Load(AUDIO_GAME,  "sounds\\game.mp3");	// ���J�s��2���n��ntut.mid
	CAudio::Instance()->Load(AUDIO_FIGHT, "sounds\\fight.mp3");
	CAudio::Instance()->Load(AUDIO_STORE, "sounds\\store.mp3");
	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_ESC	 = 0x1B; // keyboard ESC
	const char KEY_SPACE = 0x20; // keyboard�ť���
	const char KEY_ENTER = 0x0D; // keyboard Enter
	CheckInStore();
	if (!in_store && !in_battle) {
		if (nChar == KEY_LEFT)
			character.SetMovingLeft(true);
		//eraser.SetMovingLeft(true);
		if (nChar == KEY_RIGHT)
			character.SetMovingRight(true);
		//eraser.SetMovingRight(true);
		if (nChar == KEY_UP)
			character.SetMovingUp(true);
		//eraser.SetMovingUp(true);
		if (nChar == KEY_DOWN)
			character.SetMovingDown(true);
		//eraser.SetMovingDown(true);
	}
	
	/*if (in_store && nChar == KEY_ESC)
		LeaveStore();*/

	if (in_store && !store.IsChoosingCharacter() && nChar == KEY_RIGHT)
		store.NextOption();

	if (in_store && !store.IsChoosingCharacter()) {
		if (store.GetOptionNum() == 0 && nChar == KEY_SPACE)
			store.SetChoosingCharacter(true);
	}
	else if (in_store && store.IsChoosingCharacter()) {
		switch (nChar)
		{
		case KEY_RIGHT:
			if (store.GetProfileNum() < 4 && store.GetPlayerAble(store.GetProfileNum() + 1))
				store.SetCharacter(store.GetProfileNum() + 1);
			break;
		case KEY_LEFT:
			if (store.GetProfileNum() > 0 && store.GetPlayerAble(store.GetProfileNum() - 1))
				store.SetCharacter(store.GetProfileNum() - 1);
			break;
		case KEY_UP:
			if ((store.GetProfileNum() == 3 && store.GetPlayerAble(0)) || (store.GetProfileNum() == 4 && store.GetPlayerAble(1)))
				store.SetCharacter(store.GetProfileNum() - 3);
			break;
		case KEY_DOWN:
			if ((store.GetProfileNum() == 0 && store.GetPlayerAble(3)) || (store.GetProfileNum() == 1 && store.GetPlayerAble(4)))
				store.SetCharacter(store.GetProfileNum() + 3);
			else if (store.GetProfileNum() == 2 && store.GetPlayerAble(4))
				store.SetCharacter(store.GetProfileNum() + 2);
			break;
		case KEY_SPACE:
			battlefield.ChangeCharacter(store.GetProfileNum());
			store.SetChoosingCharacter(false);
			break;
		default:
			break;
		}
	}

	if (in_store && store.GetOptionNum() == 1 && nChar == KEY_SPACE)
		LeaveStore();

	/*if (in_battle && nChar == KEY_SPACE) {
		if (!player1_attacked && !battlefield.GetWeaponAlive(1) && !battlefield.GetWeaponAlive(2)) {
			battlefield.OnAttack(1);
			player1_attacked = true;
		}
		else if (player1_attacked && !battlefield.GetWeaponAlive(1) && !battlefield.GetWeaponAlive(2)) {
			battlefield.OnAttack(2);
			player1_attacked = false;
		}
	}*/

	if (in_battle && nChar == KEY_SPACE) {
		if (!player1_attacked && !battlefield.GetWeaponAlive(1) && !battlefield.GetWeaponAlive(2)) {
			battlefield.SetCharge(1, true);
		}
		else if (player1_attacked && !battlefield.GetWeaponAlive(1) && !battlefield.GetWeaponAlive(2)) {
			battlefield.SetCharge(2, true);
		}
	}

	if (in_battle && nChar == KEY_UP) {
		if (!player1_attacked) {
			battlefield.SetAngle(battlefield.GetAngle(1) + 5, battlefield.GetAngle(2));
		}
		else if (player1_attacked) {
			battlefield.SetAngle(battlefield.GetAngle(1), battlefield.GetAngle(2) + 5);
		}
	}
	
	if (in_battle && nChar == KEY_DOWN) {
		if (!player1_attacked) {
			battlefield.SetAngle(battlefield.GetAngle(1) - 5, battlefield.GetAngle(2));
		}
		else if (player1_attacked) {
			battlefield.SetAngle(battlefield.GetAngle(1), battlefield.GetAngle(2) - 5);
		}
	}

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_SPACE = 0x20; // keyboard�ť���
	//CheckInStore();
	if (nChar == KEY_LEFT)
		character.SetMovingLeft(false);
		//eraser.SetMovingLeft(false);
	if (nChar == KEY_RIGHT)
		character.SetMovingRight(false);
		//eraser.SetMovingRight(false);
	if (nChar == KEY_UP)
		character.SetMovingUp(false);
		//eraser.SetMovingUp(false);
	if (nChar == KEY_DOWN)
		character.SetMovingDown(false);
		//eraser.SetMovingDown(false);

	if (in_battle && nChar == KEY_SPACE) {
		if (!player1_attacked && !battlefield.GetWeaponAlive(1) && !battlefield.GetWeaponAlive(2)) {
			battlefield.SetCharge(1, false);
			battlefield.OnAttack(1);
			player1_attacked = true;
		}
		else if (player1_attacked && !battlefield.GetWeaponAlive(1) && !battlefield.GetWeaponAlive(2)) {
			battlefield.SetCharge(2, false);
			battlefield.OnAttack(2);
			player1_attacked = false;
		}
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	//eraser.SetMovingLeft(true);
	character.SetMovingLeft(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	//eraser.SetMovingLeft(false);
	character.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	//eraser.SetMovingRight(true);
	character.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	//eraser.SetMovingRight(false);
	character.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{
	//
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	//
	//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
	//
	gamemap.OnShow();
	//background.ShowBitmap();			// �K�W�I����
	//help.ShowBitmap();					// �K�W������
	hits_left.ShowBitmap();
	/*for (int i=0; i < NUMBALLS; i++)
		ball[i].OnShow();			*/	// �K�W��i���y
	//bball.OnShow();						// �K�W�u�����y
	//eraser.OnShow();					// �K�W���l
	character.OnShow(mapp);
	//
	//  �K�W���W�Υk�U��������
	//
	corner.SetTopLeft(0,0);
	corner.ShowBitmap();
	corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	corner.ShowBitmap();

	if (in_store) {
		store.OnShow();
	}

	if (battlefield.GetHealth(1) <= 0 || battlefield.GetHealth(2) <= 0) {
		LeaveBattle();		
		//store.SetPlayerGet(battlefield) = true;
		battlefield.ChangeCharacter(store.GetProfileNum(), 0);

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
	//battling_num = mapp->GetBattlingNum();
}

void CGameStateRun::LeaveBattle() {
	in_battle = false;

	if (battlefield.GetHealth(2) <= 0) {
		store.SetPlayerGet(mapp->GetBattlingNum());
		mapp->SetOpponentAlive(false);
	}

	int nX1 = mapp->GetOpponentX1() - 160;
	int nY1 = mapp->GetOpponentY1() + 160;
	if (nX1 < 0 || !(mapp->IsEmpty(nX1, nY1) && mapp->IsEmpty(nX1+character.GetWidth(), nY1)))
		nX1 = mapp->GetOpponentX2() + 40;
	if (nY1 >= 3480 || !(mapp->IsEmpty(nX1, nY1) && mapp->IsEmpty(nX1, nY1+character.GetHeight())))
		nY1 = mapp->GetOpponentY2() - 40;

	character.SetXY(nX1, nY1);

	mapp->SetSX(character.GetX1());
	mapp->SetSY(character.GetY1());	

	/*if (battlefield.GetHealth(2) <= 0) {
		store.SetPlayerGet(mapp->GetBattlingNum());
		mapp->SetOpponentAlive(false);
	}
	else {
		int nX1 = mapp->GetOpponentX1() - 160;
		int nY1 = mapp->GetOpponentY1() + 160;
		if (nX1 <= 0)
			nX1 = mapp->GetOpponentX2() + 160;
		if (nY1 >= 3480)
			nY1 = mapp->GetOpponentY2() - 160;

		character.SetXY(nX1, nY1);

		mapp->SetSX(character.GetX1());
		mapp->SetSY(character.GetY1());
	}*/

	player1_attacked = false;
}
}
#include "Store.h"
#include "Character.h"
#include "Rock.h"
#include "CEraser.h"
#include "Battlefield.h"
#include "Random.h"
//#include "CBall.h"
//#include "CBouncingBall.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		//AUDIO_DING,				// 0
		//AUDIO_LAKE,				// 1
		AUDIO_GAME,			    // 0
		AUDIO_FIGHT,			// 1
		AUDIO_STORE,			// 2
		AUDIO_PRESS,			// 3
		AUDIO_SELECT,			// 4
		AUDIO_UNABLE,			// 5
		AUDIO_HIT,				// 6
		AUDIO_LASER,			// 7
		AUDIO_PARALYZE,			// 8
		AUDIO_REVIVE			// 9
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo;								// csie的logo
		CMovingBitmap start_page, start_button, quit_button, howTo_button, credit_button, selection_frame;
		CMovingBitmap how_to;
		CMovingBitmap teacher_credit;
		CMovingBitmap yu;
		int selecting = 0;
		bool show_how_to = false, show_teacher_credit = false, show_student_credit = false;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void SetPlayer2Angle(UINT nFlags);
		void SetPlayer2Charge(bool flag);
		void SetPlayer2Attack();
		void CheckInStore();
		void LeaveStore();
		void CheckInBattle();
		void LeaveBattle();
		void AngleMove();
		void Charge();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		const int		NUMBALLS;	// 球的總數
		int				battling_num = -1;
		int				angle = 0;
		bool			in_store = false;
		bool			in_battle = false;
		bool			music_played = true;
		bool			weapon1_in_attack = false;
		bool			weapon2_in_attack = false;
		bool			player1_attacked = false;
		bool			player2_attacked = false;
		bool			Chargable = false;
		Map				gamemap;
		Map *			mapp = &gamemap;
		CMovingBitmap	background;	// 背景圖
		CMovingBitmap	help;		// 說明圖
		//CBall			*ball;		// 球的陣列
		CMovingBitmap	corner;		// 角落圖
		//CEraser			eraser;		// 拍子
		Character		character;
		//Opponent *		opponents;
		Store			store;
		Battlefield		battlefield;
		//Rock			rock;
		CInteger		hits_left;	// 剩下的撞擊數
		//CBouncingBall   bball;		// 反覆彈跳的球
		Random rand20, rand10;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};

}
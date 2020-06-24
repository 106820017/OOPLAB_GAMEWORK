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

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
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
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap logo;								// csie��logo
		CMovingBitmap start_page, start_button, quit_button, howTo_button, credit_button, selection_frame;
		CMovingBitmap how_to;
		CMovingBitmap teacher_credit;
		CMovingBitmap yu;
		int selecting = 0;
		bool show_how_to = false, show_teacher_credit = false, show_student_credit = false;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
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
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		const int		NUMBALLS;	// �y���`��
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
		CMovingBitmap	background;	// �I����
		CMovingBitmap	help;		// ������
		//CBall			*ball;		// �y���}�C
		CMovingBitmap	corner;		// ������
		//CEraser			eraser;		// ��l
		Character		character;
		//Opponent *		opponents;
		Store			store;
		Battlefield		battlefield;
		//Rock			rock;
		CInteger		hits_left;	// �ѤU��������
		//CBouncingBall   bball;		// ���мu�����y
		Random rand20, rand10;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
	};

}
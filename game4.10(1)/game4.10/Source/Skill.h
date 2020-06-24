#pragma once

namespace game_framework {
	class Skill {
	public:
		//Skill();
		Skill(int type = 0);
		virtual void Initialize();
		void LoadBitmap();
		virtual void ReloadBitmap();
		virtual void OnMove();
		virtual void OnShow(int x = 0, int y = 0);
		virtual void ShowBig(int x = 0, int y = 0);
		virtual void ShowAnimation(int x = 0, int y = 0);
		virtual void ShowOnce(int x = 0, int y = 0);
		void SetType(int type);
		void SetActivated(bool activated);
		void SetUsed(bool used);
		void ResetShowed();	//回到第一張圖開始撥放
		void ResetAnimation();	//回到第一張圖不撥放
		int GetType();
		int GetShowedTimes();
		bool IsActivated();
		bool GetUsed();
		virtual bool GetAlive();
	protected:
		CMovingBitmap bitmap[5], bitmap_big[5];
		CAnimation animation;
		int type, showed_times;
		bool activated, used;
	};

	class Paralyze : public Skill {
	public:
		Paralyze(int type = 1);
		void Initialize();
		void ReloadBitmap();
		void ShowAnimation(int x = 0, int y = 0);
	
	};

	class Twice : public Skill {
	public:
		Twice(int type = 2);
		void Initialize();
		void ReloadBitmap();
	};

	class SuckBlood : public Skill {
	public:
		SuckBlood(int type = 3);
		void Initialize();
		void OnMove();
		void ReloadBitmap();
		void ShowAnimation(int x = 0, int y = 0);
		void ShowOnce(int x = 0, int y = 0);
	protected:
		CAnimation animation_self;
	};
	

	class Laser : public Skill {
	public:
		Laser(int type = 4);
		void Initialize();
		void OnMove();
		void ReloadBitmap();
		void ShowAnimation(int x = 0, int y = 0);
		void ShowOnce(int x = 0, int y = 0);
		bool GetAlive();
	protected:
		bool alive;
	};
}

#pragma once

namespace game_framework {
	class Skill {
	public:
		//Skill();
		Skill(int type = 0);
		virtual void Initialize();
		virtual void LoadBitmap();
		virtual void OnMove();
		virtual void OnShow(int x = 0, int y = 0);
		virtual void ShowBig(int x = 0, int y = 0);
		virtual void ShowAnimation(int x = 0, int y = 0);
		void SetType(int type);
		void SetActivated(bool activated);
		void SetUsed(bool used);
		int GetType();
		bool IsActivated();
		bool GetUsed();
	protected:
		CMovingBitmap bitmap, bitmap_big;
		CAnimation animation;
		int type;
		bool activated, used;
		//int x, y;

	};

	class Paralyze : public Skill {
	public:
		Paralyze(int type = 1);
		void Initialize();
		void LoadBitmap();
		//void OnShow();
		void ShowAnimation(int x = 0, int y = 0);
	
	};
	
}

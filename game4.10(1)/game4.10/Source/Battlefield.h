#pragma once
#include "BattlePlayer.h"
#include "Weapon.h"
#include "Energy.h"
#include "Skill.h"

namespace game_framework {
	class Battlefield {
	public:
		Battlefield();
		bool GetWeaponAlive(int num);
		bool GetSkillActivated(int skill_num);
		bool GetSkillUsed(int skill_num);
		bool GetLaserAlive();
		int  GetSkillType(int skill_num);
		int  GetHealth(int player_num);
		int  GetParalyze(int player_num);
		int  GetAngle(int weapon_num);
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		void SetCharge(int num, bool flag);
		void SetSkillActivated(int skill_num, bool flag = true);
		void SetSkillUsed(int skill_num, bool used);
		void SetParalyze(int player_num, bool paralyze);
		void ResetSkillAnimation(int skill_num);
		void OnAttack(int num);
		void OnLaserAttack();
		void ChangeCharacter(int number = 0, int number2 = 0);
		void ChangeWeapon(int number, int number2);
		void ChangeSkill(int type1 = 0, int type2 = 0);
		void SetAngle(int angle1, int angle2);
		void CheckHit();
	protected:
		CAnimation background;
		CMovingBitmap healthbar_background;
		CMovingBitmap healthbar;
		CMovingBitmap test;
		Skill *skill_1, *skill_2;
		BattlePlayer * playerPointer1 = new BattlePlayer(0);
		BattlePlayer * playerPointer2 = new BattlePlayer(0);
		Weapon weapon1, weapon2;
		Energy *energy1 = new Energy(0, 250);
		Energy *energy2 = new Energy(520, 250, true);
		int x, y;
		int s_code, s_code2;
		bool player1_paralyzed, player2_paralyzed, player1_useLaser;
	};
}
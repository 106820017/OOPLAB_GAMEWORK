#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "BattlePlayer.h"

namespace game_framework {
	BattlePlayer::BattlePlayer(int s_code) {
		Initialize(s_code);
	}

	void BattlePlayer::Initialize(int s_code) {
		x = 50;
		y = 300;
		Health = 100;
		aniPointer = animation + s_code;
		aniPointer_under_attack = animation_under_attack + s_code;
		aniPointer_wounded = animation_wounded + s_code;
		this->s_code = s_code;
	}

	/*void BattlePlayer::SetBitmap(int s_code) {
		aniPointer = animation + s_code;
	}*/

	void BattlePlayer::LoadBitmap() {
		//animation[0].AddBitmap();
	}

	void BattlePlayer::UnderAttack() {
		aniPointer_recent = aniPointer_under_attack;
	}

	void BattlePlayer::LowOfHealth() {
		if (Health <= 40) {
			aniPointer_recent = aniPointer_wounded;
		}
		else {
			aniPointer_recent = aniPointer;
		}
	}

	void BattlePlayer::SetPlayer2() {
		aniPointer = rf_animation + s_code;
		aniPointer_wounded = rf_animation_wounded + s_code;
		aniPointer_under_attack = rf_animation_under_attack + s_code;
	}

	void BattlePlayer::OnShow() {
		aniPointer_recent->SetTopLeft(x, y);
		aniPointer_recent->OnShow();
	}

	void BattlePlayer::SetXY(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int BattlePlayer::GetX1()
	{
		return x;
	}

	int BattlePlayer::GetY1()
	{
		return y;
	}

	int BattlePlayer::GetX2()
	{
		return x + aniPointer_recent->Width();
	}

	int BattlePlayer::GetY2()
	{
		return y + aniPointer_recent->Height();
	}

	/*void BattlePlayer::SetHPLow() {
		lowHP = true;
	}*/
}
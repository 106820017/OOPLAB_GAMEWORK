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
		x = 25;
		y = 300;
		Health = 100;
		aniPointer = animation + s_code;
		aniPointer_under_attack = animation_under_attack + s_code;
		aniPointer_wounded = animation_wounded + s_code;
		aniPointer_attack = animation_attack + s_code;
		aniPointer_recent = aniPointer;
		this->s_code = s_code;
	}

	void BattlePlayer::LoadBitmap() {
		//animation[0].AddBitmap();
		animation[0].AddBitmap(IDB_KIRBY, RGB(0, 255, 0));
		animation_wounded[0].AddBitmap(IDB_KIRBY_WOUNDED, RGB(0, 255, 0));
		animation_attack[0].AddBitmap(IDB_KIRBY_ANGRY, RGB(0, 255, 0));

		rf_animation[0].AddBitmap(IDB_RF_KIRBY, RGB(0, 255, 0));
		rf_animation_wounded[0].AddBitmap(IDB_RF_KIRBY_WOUNDED, RGB(0, 255, 0));
		rf_animation_attack[0].AddBitmap(IDB_RF_KIRBY_ANGRY, RGB(0, 255, 0));
	}

	void BattlePlayer::LoadBitmap(int s_code, int * bitmaps, int r, int g, int b) {		//0-animation, 1-wounded, 2-under_attack, 3-attack, 4-rf_animation, 5-rf_wounded, 6-rf_under_attack, 7-rf_attack
		animation[s_code].AddBitmap(bitmaps[0], RGB(r, g, b));
		animation_wounded[s_code].AddBitmap(bitmaps[1], RGB(r, g, b));
		animation_under_attack[s_code].AddBitmap(bitmaps[2], RGB(r, g, b));
		animation_attack[s_code].AddBitmap(bitmaps[3], RGB(r, g, b));
		rf_animation[s_code].AddBitmap(bitmaps[4], RGB(r, g, b));
		rf_animation_wounded[s_code].AddBitmap(bitmaps[5], RGB(r, g, b));
		rf_animation_under_attack[s_code].AddBitmap(bitmaps[6], RGB(r, g, b));
		rf_animation_attack[s_code].AddBitmap(bitmaps[7], RGB(r, g, b));
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

	void BattlePlayer::Attack() {
		aniPointer_recent = aniPointer_attack;
	}

	void BattlePlayer::SetPlayer2() {
		SetXY(495, 300);
		aniPointer = rf_animation + s_code;
		aniPointer_wounded = rf_animation_wounded + s_code;
		aniPointer_under_attack = rf_animation_under_attack + s_code;
		aniPointer_attack = rf_animation_attack + s_code;
		aniPointer_recent = aniPointer;
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
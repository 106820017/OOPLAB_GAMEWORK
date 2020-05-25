#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Alphabet.h"

namespace game_framework {
	Alphabet::Alphabet() {
		x = 0; y = 0;
		current_letter = 0;
		wait = 1;
	}

	void Alphabet::LoadBitmap() {
		/*char capital_a = 'A';
		string source;
		for (int i = 0; i < 26; i++) {
			source.append("res/bmp");
			string s(1, capital_a+i);
			source.append(s);
			source.append(".bmp");
			capitals[i].LoadBitmap("res/A.bmp", RGB(255, 255, 255));
		}*/

		capitals[0].LoadBitmap("res/a.bmp", RGB(255, 255, 255));
		capitals[1].LoadBitmap("res/B.bmp", RGB(255, 255, 255));
		capitals[2].LoadBitmap("res/C.bmp", RGB(255, 255, 255));
		capitals[3].LoadBitmap("res/D.bmp", RGB(255, 255, 255));
		capitals[4].LoadBitmap("res/E.bmp", RGB(255, 255, 255));
		capitals[5].LoadBitmap("res/F.bmp", RGB(255, 255, 255));
		capitals[6].LoadBitmap("res/G.bmp", RGB(255, 255, 255));
		capitals[7].LoadBitmap("res/H.bmp", RGB(255, 255, 255));
		capitals[8].LoadBitmap("res/I.bmp", RGB(255, 255, 255));
		capitals[9].LoadBitmap("res/J.bmp", RGB(255, 255, 255));
		capitals[10].LoadBitmap("res/K.bmp", RGB(255, 255, 255));
		capitals[11].LoadBitmap("res/L.bmp", RGB(255, 255, 255));
		capitals[12].LoadBitmap("res/M.bmp", RGB(255, 255, 255));
		capitals[13].LoadBitmap("res/N.bmp", RGB(255, 255, 255));
		capitals[14].LoadBitmap("res/O.bmp", RGB(255, 255, 255));
		capitals[15].LoadBitmap("res/P.bmp", RGB(255, 255, 255));
		capitals[16].LoadBitmap("res/Q.bmp", RGB(255, 255, 255));
		capitals[17].LoadBitmap("res/R.bmp", RGB(255, 255, 255));
		capitals[18].LoadBitmap("res/S.bmp", RGB(255, 255, 255));
		capitals[19].LoadBitmap("res/T.bmp", RGB(255, 255, 255));
		capitals[20].LoadBitmap(IDB_U, RGB(255, 255, 255));
		capitals[21].LoadBitmap("res/V.bmp", RGB(255, 255, 255));
		capitals[22].LoadBitmap("res/W.bmp", RGB(255, 255, 255));
		capitals[23].LoadBitmap("res/X.bmp", RGB(255, 255, 255));
		capitals[24].LoadBitmap("res/Y.bmp", RGB(255, 255, 255));
		capitals[25].LoadBitmap("res/Z.bmp", RGB(255, 255, 255));

		lowers[0].LoadBitmap("res/lower_a.bmp", RGB(255, 255, 255));
		lowers[1].LoadBitmap("res/lower_b.bmp", RGB(255, 255, 255));
		lowers[2].LoadBitmap("res/lower_c.bmp", RGB(255, 255, 255));
		lowers[3].LoadBitmap("res/lower_d.bmp", RGB(255, 255, 255));
		lowers[4].LoadBitmap("res/lower_e.bmp", RGB(255, 255, 255));
		lowers[5].LoadBitmap("res/lower_f.bmp", RGB(255, 255, 255));
		lowers[6].LoadBitmap("res/lower_g.bmp", RGB(255, 255, 255));
		lowers[7].LoadBitmap("res/lower_h.bmp", RGB(255, 255, 255));
		lowers[8].LoadBitmap("res/lower_i.bmp", RGB(255, 255, 255));
		lowers[9].LoadBitmap("res/lower_j.bmp", RGB(255, 255, 255));
		lowers[10].LoadBitmap("res/lower_k.bmp", RGB(255, 255, 255));
		lowers[11].LoadBitmap("res/lower_l.bmp", RGB(255, 255, 255));
		lowers[12].LoadBitmap("res/lower_m.bmp", RGB(255, 255, 255));
		lowers[13].LoadBitmap("res/lower_n.bmp", RGB(255, 255, 255));
		lowers[14].LoadBitmap("res/lower_o.bmp", RGB(255, 255, 255));
		lowers[15].LoadBitmap("res/lower_p.bmp", RGB(255, 255, 255));
		lowers[16].LoadBitmap("res/lower_q.bmp", RGB(255, 255, 255));
		lowers[17].LoadBitmap("res/lower_r.bmp", RGB(255, 255, 255));
		lowers[18].LoadBitmap("res/lower_s.bmp", RGB(255, 255, 255));
		lowers[19].LoadBitmap("res/lower_t.bmp", RGB(255, 255, 255));
		lowers[20].LoadBitmap("res/lower_u.bmp", RGB(255, 255, 255));
		lowers[21].LoadBitmap("res/lower_v.bmp", RGB(255, 255, 255));
		lowers[22].LoadBitmap("res/lower_w.bmp", RGB(255, 255, 255));
		lowers[23].LoadBitmap("res/lower_x.bmp", RGB(255, 255, 255));
		lowers[24].LoadBitmap("res/lower_y.bmp", RGB(255, 255, 255));
		lowers[25].LoadBitmap("res/lower_z.bmp", RGB(255, 255, 255));

		punctuation[0].LoadBitmap("res/exclamation_mark.bmp", RGB(255, 255, 255));
		punctuation[1].LoadBitmap("res/comma.bmp", RGB(255, 255, 255));
		punctuation[2].LoadBitmap("res/period.bmp", RGB(255, 255, 255));
		punctuation[3].LoadBitmap("res/colon.bmp", RGB(255, 255, 255));
		punctuation[4].LoadBitmap("res/question_mark.bmp", RGB(255, 255, 255));
		
	}

	void Alphabet::OnMove() {		
		if (current_letter < 300) {
			wait--;
			if (wait < 0)
				wait = 1;
			if (wait == 0)
				current_letter++;
		}

	}

	void Alphabet::ShowString(string input, int x, int y) {
		char cstr[300];		
		
		this->x = x, this->y = y;

		int hover = this->x;

		strcpy(cstr, input.c_str());
		/*for (int i = input.size()+1; i < 300; i++) {
			cstr[i] = NULL;
		}*/

		for (int i = 0; i < current_letter; i++) {
			if ((int)cstr[i] >= 65 && (int)cstr[i] <= 90) {		//'A'=65  'Z'=90				
				capitals[(int)cstr[i]-65].SetTopLeft(hover, this->y);
				capitals[(int)cstr[i] - 65].ShowBitmap();
				hover += 25;
			}
			else if ((int)cstr[i] >= 97 && (int)cstr[i] <= 122) {	//'a'=97  'z'=122
				
				lowers[(int)cstr[i] - 97].SetTopLeft(hover, this->y);
				lowers[(int)cstr[i] - 97].ShowBitmap();
				if ((int)cstr[i] == 105 || (int)cstr[i] == 106 || (int)cstr[i] == 108)
					hover += 13;
				else
					hover += 18;
			}
			else if ((int)cstr[i] == 32) {	//ªÅ¥Õ
				hover += 20;
			}
			else if ((int)cstr[i] == 33 || (int)cstr[i] == 44 || (int)cstr[i] == 46 || (int)cstr[i] == 58 || (int)cstr[i] == 63)	// ! , . : ?
			{
				int type = 0;
				switch ((int)cstr[i])
				{
				case 44:
					type = 1;
					break;
				case 46:
					type = 2;
					break;
				case 58:
					type = 3;
					break;
				case 63:
					type = 4;
					break;
				}
				punctuation[type].SetTopLeft(hover, this->y);
				punctuation[type].ShowBitmap();
				hover += 18;
			}
			else if ((int)cstr[i] == 10) {	//\n
				hover = this->x;
				this->y += 40;
			}
			else {
				break;
			}
		}

	}

	void Alphabet::ClearCurrent() {
		current_letter = 0;
	}
}
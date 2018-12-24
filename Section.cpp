#include "Section.h"
#include"DxLib.h"
#include"Singleton.h"
#include<thread>
using namespace std;

void Section::Calculation()
{
	double x, y;
	int code;
	int R, G, B;
	double MAX, MIN;
	double H, S, V;
	double pR, pG, pB, pH, pS, pV;
	int pY;
	for (int i = 0; i < reso; i++) {
		//í≤ç∏ëŒè€Çì¡íË
		x = Ax + ((Bx - Ax)*i / reso);
		y = Ay + ((By - Ay)*i / reso);
		//ÉRÅ[Éhíäèo
		code = GetPixel(x, y);
		//RGBéZèo
		GetColor2(code, &R, &G, &B);
		//HSVéZèoèÄîı
		MAX = R;
		if (MAX < G)MAX = G;
		if (MAX < B)MAX = B;
		MIN = R;
		if (MIN > G)MIN = G;
		if (MIN > B)MIN = B;
		//HéZèo
		H = 360;
		if (MAX != MIN) {
			if (MAX == R)H = 60 * (((double)B - (double)G) / (MAX - MIN));
			if (MAX == G)H = 60 * (2 + ((double)R - (double)B) / (MAX - MIN));
			if (MAX == B)H = 60 * (4 + ((double)G - (double)R) / (MAX - MIN));
			if (H < 0)H += 360;
		}
		//SéZèo
		S = 255 * ((MAX - MIN)/MAX);
		//VéZèo
		V = MAX;
		//Previewç¿ïWéZèo
		pR = pCalculation(detailLX, WIDTH, 255, R);
		pG = pCalculation(detailLX, WIDTH, 255, G);
		pB = pCalculation(detailLX, WIDTH, 255, B);
		pH = pCalculation(detailLX, WIDTH, 360, H);
		pS = pCalculation(detailLX, WIDTH, 255, S);
		pV = pCalculation(detailLX, WIDTH, 255, V);
		pY = pCalculation(0, HEIGHT, reso, i);
		//ë„ì¸
		DATA[i].R = R, DATA[i].G = G, DATA[i].B = B;
		DATA[i].H = H, DATA[i].S = S, DATA[i].V = V;
		DATA[i].pR = pR, DATA[i].pG = pG, DATA[i].pB = pB;
		DATA[i].pH = pH, DATA[i].pS = pS, DATA[i].pV = pV;
		DATA[i].pY = pY;
	}
}

double Section::pCalculation(double left, double right, double maxim, double figure)
{
	return left + (right - left) / maxim*figure;
}

void Section::Prev()
{
	DrawBox(0, 0, WIDTH, HEIGHT, GetColor(255, 255, 255),TRUE);
	DrawFormatStringToHandle(0, 0, GetColor(255, 210, 210), FONT, "A");
	DrawFormatStringToHandle(0, HEIGHT-45, GetColor(210, 255, 210), FONT, "B");

	switch (mode) {
	case RGB:
		DrawFormatStringToHandle(0, 100, GetColor(255, 50, 50), FONT,"R");
		DrawFormatStringToHandle(0, 200, GetColor(50, 255, 50), FONT,"G");
		DrawFormatStringToHandle(0, 300, GetColor(50, 50, 255), FONT,"B");
		break;
	case HSV:
		DrawFormatStringToHandle(0, 100, GetColor(220, 120, 240), FONT, "H");
		DrawFormatStringToHandle(0, 200, GetColor(8, 190, 80), FONT, "S");
		DrawFormatStringToHandle(0, 300, GetColor(210, 100, 60), FONT, "V");
		break;
	}

	for (int i = 0; i < reso; i++) {
		DrawBox(detailLX, DATA[i].pY, WIDTH, HEIGHT, GetColor(DATA[i].R, DATA[i].G, DATA[i].B), TRUE);
		
		if (i == 0)continue;
		
		switch (mode) {
		case RGB:
			DrawLine(DATA[i - 1].pR, DATA[i - 1].pY, DATA[i].pR, DATA[i].pY, GetColor(255, 50, 50), 5);
			DrawLine(DATA[i - 1].pG, DATA[i - 1].pY, DATA[i].pG, DATA[i].pY, GetColor(50, 255, 50), 5);
			DrawLine(DATA[i - 1].pB, DATA[i - 1].pY, DATA[i].pB, DATA[i].pY, GetColor(50, 50, 255), 5);
			break;
		case HSV:
			DrawLine(DATA[i - 1].pH, DATA[i - 1].pY, DATA[i].pH, DATA[i].pY, GetColor(220, 120, 240), 5);
			DrawLine(DATA[i - 1].pS, DATA[i - 1].pY, DATA[i].pS, DATA[i].pY, GetColor(8, 190, 80), 5);
			DrawLine(DATA[i - 1].pV, DATA[i - 1].pY, DATA[i].pV, DATA[i].pY, GetColor(210, 100, 60), 5);
			break;
		}
		
	}
}

Section::Section(int Width, int Height)
{
	WIDTH = Width, HEIGHT = Height;
	FONT = CreateFontToHandle("ÉÅÉCÉäÉI", 40, 5, DX_FONTTYPE_NORMAL);
}

void Section::DO()
{
	if(Mouse::Instance()->GetPressingCount(Mouse::LEFT)==1) {//ç°Ç‹Ç≥Ç…âüÇ≥ÇÍÇΩèuä‘
		Bx = unset, By = unset;
		Ax = Mouse::Instance()->GetX();
		Ay = Mouse::Instance()->GetY();
	}
	if (Mouse::Instance()->GetPressingCount(Mouse::LEFT) > 1) {//âüÇ≥ÇÍÇƒÇ¢ÇÈ
		DrawLine(Ax, Ay, Mouse::Instance()->GetX(), Mouse::Instance()->GetY(), GetColor(0, 0, 0),5);
	}
	if(Mouse::Instance()->GetReleasingCount(Mouse::LEFT)==1&& Ax!=unset&&Ay!=unset){//ç°Ç‹Ç≥Ç…ó£Ç≥ÇÍÇΩèuä‘
		Bx = Mouse::Instance()->GetX();
		By = Mouse::Instance()->GetY();
		Calculation();
	}
	//ê¸Çï\é¶
	if (Ax != unset&&Ay != unset&&Bx != unset&&By != unset) { 
		if (CheckHitKey(KEY_INPUT_SPACE) == 1) Prev();
		DrawLine(Ax, Ay, Bx, By, GetColor(0, 0, 0), 5); 
	}
	//â~Çï\é¶
	if (Ax != unset&&Ay != unset)DrawCircle(Ax, Ay, 7, GetColor(250, 200, 200), TRUE);
	if (Bx != unset&&By != unset)DrawCircle(Bx, By, 7, GetColor(200, 200, 250), TRUE);
}

void Section::ChangeMode(eMode next)
{
	mode = next;
}

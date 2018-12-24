#pragma once

#define reso 100
/*色の情報を保持する。
頭にpの付いた変数には、Section::Prev()にて色彩分布グラフを表示するときの
各プロットの座標
*/
struct eDATA {
	int R;
	int G;
	int B;
	double H;
	double S;
	double V;
	int pR;
	int pG;
	int pB;
	int pH;
	int pS;
	int pV;
	int pY;
};
enum eMode{
	RGB,
	HSV
};

/*ユーザーの線引きの行動を監視し、
ユーザーが引いた線上の色を調べる。
*/
class Section {
private:
	int WIDTH, HEIGHT;
	const int unset = -1;
	const int detailLX = 40;
	eDATA DATA[reso];
	eMode mode;
	int Ax=unset, Ay=unset, Bx=unset, By=unset;
	void Calculation();
	double pCalculation(double left, double right, double maxim, double figure);
	void Prev();
	int FONT;
public:
	Section(int Width, int Height);
	void DO();
	void ChangeMode(eMode next);
};
#pragma once

#define reso 100
/*�F�̏���ێ�����B
����p�̕t�����ϐ��ɂ́ASection::Prev()�ɂĐF�ʕ��z�O���t��\������Ƃ���
�e�v���b�g�̍��W
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

/*���[�U�[�̐������̍s�����Ď����A
���[�U�[������������̐F�𒲂ׂ�B
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
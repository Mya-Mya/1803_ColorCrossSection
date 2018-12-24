#pragma once
#include"Section.h"
/*読み込む画像を指定し、表示する。
Sectionを子に持ち同時に実行する。
*/
class Picture {
private:
	int ImageHandle;
	double ImageLoaded = false;
	double ImageExtend;
	int WIDTH, HEIGHT;
	Section *sec;
public:
	Picture(int Width, int Height);
	void DO();
	void Open();
};
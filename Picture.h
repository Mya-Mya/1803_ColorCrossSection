#pragma once
#include"Section.h"
/*�ǂݍ��މ摜���w�肵�A�\������B
Section���q�Ɏ��������Ɏ��s����B
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
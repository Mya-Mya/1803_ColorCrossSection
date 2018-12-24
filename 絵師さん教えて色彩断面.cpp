// 絵師さん教えて色彩断面.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include"DxLib.h"
#include"Singleton.h"
#include"Picture.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

int main()
{
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	Picture inst(WIDTH, HEIGHT);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		Mouse::Instance()->Update();
		Keyboard::Instance()->Update();
		inst.DO();
	}
	DxLib_End();
	return 0;
    return 0;
}


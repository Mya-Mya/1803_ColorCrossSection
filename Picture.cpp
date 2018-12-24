#include "Picture.h"
#include"DxLib.h"
#include<Windows.h>
#include"Singleton.h"
#include"Section.h"

Picture::Picture(int Width, int Height)
{
	WIDTH = Width, HEIGHT = Height;
	sec = new Section(Width, Height);
}

void Picture::DO()
{
	if (!ImageLoaded) Open();
	DrawRotaGraph(WIDTH / 2, HEIGHT / 2, ImageExtend, 0, ImageHandle, FALSE);
	sec->DO();
	if (Keyboard::Instance()->Get(KEY_INPUT_D) == 1) ImageLoaded = false;
	if (Keyboard::Instance()->Get(KEY_INPUT_H) == 1) sec->ChangeMode(HSV);
	if (Keyboard::Instance()->Get(KEY_INPUT_R) == 1) sec->ChangeMode(RGB);
}

void Picture::Open()
{
	InitGraph();

	{
		TCHAR szPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, szPath);
		TCHAR szFile[MAX_PATH] = "";

		OPENFILENAME ofn;
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = GetMainWindowHandle();
		ofn.lpstrInitialDir = szPath;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFilter = TEXT("画像ファイル(*.jpg,*.png)\0*.jpg;*.png\0")
			TEXT("すべてのファイル(*.*)\0*.*\0");
		ofn.lpstrTitle = TEXT("読み込む画像を選択");
		ofn.Flags = OFN_FILEMUSTEXIST;

		GetOpenFileName(&ofn);
		ImageHandle = LoadGraph(szFile);
	}//ファイルの選択と読み込み

	{
		int PicX, PicY;
		GetGraphSize(ImageHandle, &PicX, &PicY);
		ImageExtend = (double)WIDTH / (double)PicX;
		if ((double)HEIGHT / (double)PicY < ImageExtend) ImageExtend = ((double)HEIGHT / (double)PicY);
	}//画像サイズと拡大率計算

	ImageLoaded = true;
}

#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	if (DxLib_Init() == -1) {	// DXライブラリ初期化処理
		return -1;	// 初期化失敗
	}

	DxLib_End();	// DXライブラリ使用の終了処理

	return 0;		// ソフトの終了
}
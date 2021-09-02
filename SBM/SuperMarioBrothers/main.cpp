#include "DxLib.h"
#include "SceneManager.h"
#include "Mario.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1) {	// DXライブラリ初期化処理
		return -1;				// 初期化失敗
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(640, 480, 30);
	if (SceneMgr_ImgCheck() == -1) {
		return -1;
	}
	SceneMgr_Initialize();			// 初期化

	// TEMP:　マリオを歩かせるための暫定処理
	//T_MARIO player;
	//if (!(isInitSuccess(player))) return 0;
	// TEMP:　ここまで

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){
		SceneMgr_Update();		// 更新
		SceneMgr_Draw();		// 描画

		// TEMP:　マリオを歩かせるための暫定処理
		/*Update(player);
		Draw(player);*/
		// TEMP:　ここまで
	}

	DxLib_End();	// DXライブラリ使用の終了処理

	return 0;		// ソフトの終了
}
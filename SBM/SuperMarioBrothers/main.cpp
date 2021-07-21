#include "DxLib.h"
#include "SceneManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1) {	// DX���C�u��������������
		return -1;				// ���������s
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(640, 480, 30);

	SceneMgr_Initialize();			// ������

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){
		SceneMgr_Update();		// �X�V
		SceneMgr_Draw();		// �`��
	}

	DxLib_End();	// DX���C�u�����g�p�̏I������

	return 0;		// �\�t�g�̏I��
}
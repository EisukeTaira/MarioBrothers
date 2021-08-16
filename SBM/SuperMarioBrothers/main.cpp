#include "DxLib.h"
#include "SceneManager.h"
#include "Mario.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1) {	// DX���C�u��������������
		return -1;				// ���������s
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(640, 480, 30);

	SceneMgr_Initialize();			// ������

	// TEMP:�@�}���I��������邽�߂̎b�菈��
	T_MARIO player;
	if (!(isInitSuccess(player))) return 0;
	// TEMP:�@�����܂�

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){
		SceneMgr_Update();		// �X�V
		SceneMgr_Draw();		// �`��

		// TEMP:�@�}���I��������邽�߂̎b�菈��
		Update(player);
		Draw(player);
		// TEMP:�@�����܂�
	}

	DxLib_End();	// DX���C�u�����g�p�̏I������

	return 0;		// �\�t�g�̏I��
}
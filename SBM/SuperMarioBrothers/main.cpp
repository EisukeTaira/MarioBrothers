#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	if (DxLib_Init() == -1) {	// DX���C�u��������������
		return -1;	// ���������s
	}

	DxLib_End();	// DX���C�u�����g�p�̏I������

	return 0;		// �\�t�g�̏I��
}
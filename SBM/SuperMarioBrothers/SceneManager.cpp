#include "SceneManager.h"

E_Scene scene_mode;

// ������
void SceneMgr_Initialize(void) {
	scene_mode = TITLE;
}
// �X�V
void SceneMgr_Update(void) {
	switch (scene_mode)	{
		case TITLE:
			break;
		case GMAIN:
			break;
		case RESULT:
			break;
		default:
			break;
	}
}
// �`��
void SceneMgr_Draw(void) {
	
}

// �V�[���؂�ւ�
void SceneMgr_SceneChange(E_Scene es) {
	scene_mode = es;
}


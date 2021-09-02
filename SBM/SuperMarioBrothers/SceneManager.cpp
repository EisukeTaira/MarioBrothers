#include "SceneManager.h"
#include "GimmickCtrl.h"
#include "StageCtrl.h"

// �ϐ��錾
int scene_mode;

// ������
void SceneMgr_Initialize(void) {
	SceneMgr_SceneChange(GMAIN);
}
// �X�V
void SceneMgr_Update(void) {
	
}
// �`��
void SceneMgr_Draw(void) {
	
}

// �V�[���؂�ւ�
void SceneMgr_SceneChange(int es) {
	scene_mode = es;
}

//�摜�ǂݍ��݃`�F�b�N
int SceneMgr_ImgCheck(void) {
	int ret = 0;
	if (GimmickCtrl_ImgLoad() == -1) {
		ret = -1;
	}
	if (StageCtrl_ImgLoad() == -1) {
		ret = -1;
	}

	return ret;
}
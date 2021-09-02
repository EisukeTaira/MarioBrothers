#include "SceneManager.h"
#include "GimmickCtrl.h"
#include "StageCtrl.h"

// 変数宣言
int scene_mode;

// 初期化
void SceneMgr_Initialize(void) {
	SceneMgr_SceneChange(GMAIN);
}
// 更新
void SceneMgr_Update(void) {
	
}
// 描画
void SceneMgr_Draw(void) {
	
}

// シーン切り替え
void SceneMgr_SceneChange(int es) {
	scene_mode = es;
}

//画像読み込みチェック
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
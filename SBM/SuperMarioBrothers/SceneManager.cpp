#include "SceneManager.h"
#include "KeyControl.h"
#include "GimmickCtrl.h"
#include "StageCtrl.h"

// 変数宣言
int scene_mode;

// 初期化
void SceneMgr_Initialize(void) {
	SceneMgr_SceneChange(GMAIN);
	StageCtrl_Init();
}
// 更新
void SceneMgr_Update(void) {
	KeyCtrl_Update();
	switch (scene_mode) {
		case TITLE:
			break;
		case GMAIN:
			StageCtrl_Update();
			break;
		case RESULT:
			break;
		default:
			break;
	}
}
// 描画
void SceneMgr_Draw(void) {
	switch (scene_mode) {
	case TITLE:
		break;
	case GMAIN:
		StageCtrl_Draw();
		break;
	case RESULT:
		break;
	default:
		break;
	}
}

// シーン切り替え
void SceneMgr_SceneChange(int es) {
	scene_mode = es;
}

//画像読み込みチェック
int SceneMgr_ImgCheck(void) {
	int ret = 0;
	/*if (GimmickCtrl_ImgLoad() == -1) {
		ret = -1;
	}*/
	if (StageCtrl_ImgLoad() == -1) {
		ret = -1;
	}

	return ret;
}
#include "SceneManager.h"

E_Scene scene_mode;

// 初期化
void SceneMgr_Initialize(void) {
	scene_mode = TITLE;
}
// 更新
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
// 描画
void SceneMgr_Draw(void) {
	
}

// シーン切り替え
void SceneMgr_SceneChange(E_Scene es) {
	scene_mode = es;
}


#ifndef SCENE_MANAGER_H__
#define SCENE_MANAGER_H__

typedef enum {
	TITLE,
	GMAIN,
	RESULT,
	SCENE_MAX
}E_Scene;

void SceneMgr_Initialize(void);
void SceneMgr_Update(void);
void SceneMgr_Draw(void);
void SceneMgr_SceneChange(E_Scene es);

#endif // !SCENE_MANEGER_H__

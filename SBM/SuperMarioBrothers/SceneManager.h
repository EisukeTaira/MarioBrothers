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
void SceneMgr_SceneChange(int es);
int SceneMgr_ImgCheck(void);


#endif // !SCENE_MANEGER_H__

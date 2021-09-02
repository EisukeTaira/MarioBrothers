#ifndef STAGE_CONTROL_H__
#define STAGE_CONTROL_H__

//定数定義

// 構造体宣言
typedef struct {
	int x;
	int y;
	int img;
	int inside;
}T_Stage;


// 関数宣言
void StageCtrl_Init(void);			// ステージ制御：初期化処理
void StageCtrl_Update(void);		// ステージ制御：更新処理
void StageCtrl_Draw(void);			// ステージ制御：描画処理
int StageCtrl_ImgLoad(void);		// ステージ制御：画像読み込み処理
void StageCtrl_MapChange(int wrld);		// ステージ制御：ステージ変更処理
int Get_StageCtrl_world_type(void);
#endif // !STAGE_CONTROL_H__

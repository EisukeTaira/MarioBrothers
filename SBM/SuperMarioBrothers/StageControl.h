#ifndef STAGE_CONTROL_H__
#define STAGE_CONTROL_H__

// 構造体宣言
typedef struct {
	int x;
	int y;
	int img;
	int retention;
	bool flg;
}T_Stage;


// 関数宣言
void StageCtrl_Init(void);			// ステージ制御：初期化処理
void StageCtrl_Update(void);		// ステージ制御：更新処理
void StageCtrl_Draw(void);			// ステージ制御：描画処理

#endif // !STAGE_CONTROL_H__

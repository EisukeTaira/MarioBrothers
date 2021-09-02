#include "DxLib.h"
#include "GimmickCtrl.h"
#include "StageCtrl.h"
#include "EnemyConfig.h"

// 構造体
typedef struct {
	int x;
	int y;
	int img;
	int mode;
	int flg;
}T_Lift;
typedef struct {
	int x;
	int y;
	int img[4];
	int mode;
	int flg;
}T_Firebar;

// 変数宣言
T_GOOMBA	Goomba[GOOMBA_MAX];					// クリボー
T_TROOPER	Trooper[(NKNK_MAX + PTPT_MAX)];		// ノコノコ
T_PLANT		Plant[PIRANHA_PLANT_MAX];			// パックンフラワー
T_BOWSER	Bowser[BOWSER_MAX];					// クッパ
T_BREATH	BowserBreath[2];					// クッパ吐瀉物

// プロトタイプ宣言
static void setting_enemy_position(void);

/* 初期化 */
void GimmickCtrl_Init(void) {

}
/* 更新 */
void GimmickCtrl_Update(void) {

}
/* 描画 */
void GimmickCtrl_Draw(void) {

}
/* 画像読み込み */
int GimmickCtrl_ImgLoad(void) {
	int ret = 0;		// 戻り値(0:正常,	0以外:異常)
	int loop_cnt = 0;	// ループカウンタ

	// 敵画像読み込み
	for (loop_cnt = 0;loop_cnt < GOOMBA_MAX;loop_cnt++) {
		ret = LoadDivGraph("images/kuribo.png", 3, 1, 3, 32, 32, &Goomba->img[0]);
	}
	for (loop_cnt = 0;loop_cnt < (NKNK_MAX + PTPT_MAX);loop_cnt++) {
		ret = LoadDivGraph("images/red_patapata.png", 2, 1, 2, 32, 64, &Trooper->img[0]);
		ret = LoadDivGraph("images/red_nokonoko.png", 2, 1, 2, 32, 64, &Trooper->img[2]);
		ret = LoadDivGraph("images/red_nokonoko_revival.png", 2, 1, 2, 32, 64, &Trooper->img[4]);
	}
	for (loop_cnt = 0;loop_cnt < PIRANHA_PLANT_MAX;loop_cnt++) {
		ret = LoadDivGraph("images/pakkun.png", 2, 2, 1, 32, 64, &Plant->img[0]);
	}
	for (loop_cnt = 0;loop_cnt < BOWSER_MAX;loop_cnt++) {
		ret = LoadDivGraph("images/kuppa.png", 2, 2, 1, 32, 64, &Bowser->img[0]);
	}
	
	// ワールドギミック画像読み込み

	
	return ret;
}



static void setting_enemy_position(void) {
	int wt = Get_StageCtrl_world_type();
}
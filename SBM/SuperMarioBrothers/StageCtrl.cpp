#include <stdio.h>
#include <ctype.h>
#include "DxLib.h"
#include "StageCtrl.h"
#include "StageCtrl_Config.h"

//内部定数
#define BLOCK_SIZE	(32U)
#define LOAD_ERROR	(-1)
#define	CHR_ZERO	('0')
#define	CHR_COMMA	(',')
#define	CHR_NL		('\n')
// 変数
static int world_type;
static T_Stage stage[MAP_HEIGHT][MAP_WIDTH];
static int stage_img[BLOCK_MAX];
static FILE* fp_front = NULL;
// 関数宣言
static void stagectrl_stageload(void);
static const char* get_csv_name(void);
static void stagectrl_world_data_check(void);

// 初期化
void StageCtrl_Init(void) {
	
	StageCtrl_MapChange(ABOVE_GROUND);
	stagectrl_stageload();
}
// 更新
void StageCtrl_Update(void) {
	int i, j;
	for (i = 0;i < MAP_HEIGHT;i++) {
		for (j = 0;j < MAP_WIDTH;j++) {
			stage[i][j].x = j * BLOCK_SIZE;/*(BLOCK_SIZE * 15 * 5) */
			stage[i][j].y = i * BLOCK_SIZE;
		}
	}
}
// 描画
void StageCtrl_Draw(void) {
	int i, j;
	for (i = 0;i < MAP_HEIGHT;i++) {
		for (j = 0;j < MAP_WIDTH;j++) {
			DrawGraph(stage[i][j].x, stage[i][j].y, stage_img[stage[i][j].img], TRUE);
		}
	}
}
// ステージ画像読み込み処理
int StageCtrl_ImgLoad(void) {
	int ret = 0;
	for (int i = 0;i < BLOCK_MAX;i++) {
		stage_img[i] = 0;
	}
	stage_img[SKY] = LoadGraph("images/sora.png");
	stage_img[FLOOR] = LoadGraph("images/floor.png");
	ret = LoadDivGraph("images/hatena.png", 4, 4, 1, 32, 32, &stage_img[HATENA]);
	ret = LoadDivGraph("images/coin.png", 4, 4, 1, 32, 32, &stage_img[COIN]);
	stage_img[BRICK] = LoadGraph("images/block.png");
	stage_img[STAIRS] = LoadGraph("images/sora.png");
	stage_img[BLINK] = LoadGraph("images/sora.png");
	stage_img[ZHUGE_LIANG] = LoadGraph("images/sora.png");

	stage_img[POLE_HEAD] = LoadGraph("images/pole.png");
	stage_img[POLE_DOWN] = LoadGraph("images/pole_down.png");
	stage_img[POLE_FLAG] = LoadGraph("images/flag.png");

	stage_img[VARTCAL_CPIPE] = LoadGraph("images/dokan_left_up.png");
	stage_img[VARTCAL_CPIPE + 1] = LoadGraph("images/dokan_right_up.png");
	stage_img[VARTCAL_CPIPE + 2] = LoadGraph("images/dokan_left_down.png");
	stage_img[VARTCAL_CPIPE + 3] = LoadGraph("images/dokan_right_down.png");
	stage_img[SIDEWAY_CPIPE] = LoadGraph("images/yokodokan_left_up.png");
	stage_img[SIDEWAY_CPIPE + 1] = LoadGraph("images/yokodokan_left_down.png");
	stage_img[SIDEWAY_CPIPE + 2] = LoadGraph("images/yokodokan_middle_up.png");
	stage_img[SIDEWAY_CPIPE + 3] = LoadGraph("images/yokodokan_middle_down.png");
	stage_img[PIPE_JOINT] = LoadGraph("images/yokodokan_right_up.png");
	stage_img[PIPE_JOINT + 1] = LoadGraph("images/yokodokan_right_up.png");

	stage_img[GLASS] = LoadGraph("images/ha0.png");
	stage_img[GLASS + 1] = LoadGraph("images/ha1.png");
	stage_img[GLASS + 2] = LoadGraph("images/ha2.png");

	stage_img[MOUNTAIN] = LoadGraph("images/mountain_up.png");
	stage_img[MOUNTAIN + 1] = LoadGraph("images/mountain_left.png");
	stage_img[MOUNTAIN + 2] = LoadGraph("images/mountain_right.png");
	stage_img[MOUNTAIN + 3] = LoadGraph("images/mountain_surface.png");
	stage_img[MOUNTAIN + 4] = LoadGraph("images/mountain_surface1.png");
	stage_img[MOUNTAIN + 5] = LoadGraph("images/mountain_surface2.png");

	stage_img[MAGMA] = LoadGraph("images/sora.png");
	stage_img[SLIDING_THROUGH] = LoadGraph("images/sora.png");
	stage_img[SLIDING_THROUGH + 1] = LoadGraph("images/sora.png");
	stage_img[SLIDING_THROUGH + 2] = LoadGraph("images/sora.png");
	stage_img[PILLAR] = LoadGraph("images/sora.png");

	for (int i = 0;i < BLOCK_MAX;i++) {
		if (stage_img[i] == LOAD_ERROR) {
			ret = -1;
		}
	}
	return ret;
}
// ステージ切り替え処理
void StageCtrl_MapChange(int wrld) {
	world_type = wrld;
	stagectrl_stageload();
}
int Get_StageCtrl_world_type(void) {
	return world_type;
}
// ステージファイル読み込み処理
static void stagectrl_stageload(void) {
	
	fopen_s(&fp_front, get_csv_name(), "r");

	if(fp_front == NULL){
		DrawFormatString(0, 0, 0xFFFFFFFF, "ファイルを開けませんでした。");
	} else {
		stagectrl_world_data_check();
		fclose(fp_front);							// 読み込んだファイルを閉じる
	}

}

// CSVファイル名の取得
static const char* get_csv_name(void) {
	const char* tmp = NULL;

	if (world_type < WORLD_MAX) {
		tmp = C_StageName[world_type];
	} else {
		tmp = NULL;
	}

	return tmp;
}
// 読み込みデータチェック
static void stagectrl_world_data_check(void) {
	int chr = NULL;
	int digit_flg = FALSE;
	int i = 0, j = 0;
	while (1) {
		chr = fgetc(fp_front);
		if (chr == EOF) {
			break;
		}
		if (isdigit(chr)) {
			if (digit_flg) {
				stage[i][j].img *= 10;
				stage[i][j].img += (chr - CHR_ZERO);
			} else {
				stage[i][j].img = (chr - CHR_ZERO);
			}
			digit_flg = TRUE;									
		}
		if (chr == CHR_COMMA || chr == CHR_NL) {
			digit_flg = FALSE;
			j++;
		}
		if (chr == '\n') {
			i++;
			j = 0;
		}
	}	
}

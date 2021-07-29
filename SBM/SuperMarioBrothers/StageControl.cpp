#include <stdio.h>
#include "DxLib.h"
#include "StageControl.h"
#include "StageControl_Config.h"

//内部定数
#define FRONT		(0x01U)
#define BACK		(0x02U)
#define BLOCK_SIZE	(32U)

// 変数
static int world_type;
static char world_view;
static char* stage_name = NULL;
static T_Stage stage[MAP_HEIGHT][MAP_WIDTH];
static int stage_img[BLOCK_MAX];
// 関数宣言
static void stagectrl_stageload(int wrld);

void StageCtrl_Init(void) {
	world_type = ABOVE_GROUND;
	world_view = FRONT;
	stagectrl_stageload(world_type);
}
void StageCtrl_Update(void) {
	int i, j;
	for (i = 0;i < MAP_HEIGHT;i++) {
		for (j = 0;j < MAP_WIDTH;j++) {
			stage[i][j].x = i * BLOCK_SIZE + 0x0000U;
			stage[i][j].y = i * BLOCK_SIZE;
		}
	}
}
void StageCtrl_Draw(void) {
	int i, j;
	for (i = 0;i < MAP_HEIGHT;i++) {
		for (j = 0;j < MAP_WIDTH;j++) {
			DrawGraph(stage[i][j].x, stage[i][j].y, stage_img[stage[i][j].img], TRUE);
		}
	}
}

// ステージファイル読み込み処理
static void stagectrl_stageload(int wrld) {
	FILE* fp = NULL;
	int i, j;

	if (wrld  == ABOVE_GROUND) {
		char str[] = "stage/world1-1.csv";
		stage_name = str;
	} else if (wrld == UNDER_GROUND) {
		char str[] = "stage/world1-2.csv";
		stage_name = str;
	} else if (wrld == IN_THE_AIR) {
		char str[] = "stage/world1-3.csv";
		stage_name = str;
	} else if (wrld == INSIDE_CASTLE) {
		char str[] = "stage/world1-4.csv";
		stage_name = str;
	} else {
		stage_name = NULL;
	}

	if (stage_name != NULL) {
		fopen_s(&fp, stage_name, "r");	//ステージファイルを読み込み専用で読み込む
	}

	if(fp == NULL){
		DrawFormatString(0, 0, 0xFFFFFFFF, "ファイルを開けませんでした。");
	} else {
		for (i = 0; i < MAP_HEIGHT; i++) {
			for (j = 0; j < MAP_WIDTH; j++)	{
				stage[i][j].img = fgetc(fp);
			}
		}

		fclose(fp);							//　読み込んだファイルを閉じる
	}
	
}


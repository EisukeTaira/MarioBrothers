#include <stdio.h>
#include "DxLib.h"
#include "StageControl.h"
#include "StageControl_Config.h"

//�����萔
#define FRONT		(0x01U)
#define BACK		(0x02U)
#define BLOCK_SIZE	(32U)

// �ϐ�
static int world_type;
static char world_view;
static T_Stage front_stage[MAP_HEIGHT][MAP_WIDTH];
static T_Stage back_stage[MAP_HEIGHT][MAP_WIDTH];
static int stage_img[BLOCK_MAX];
// �֐��錾
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
			if (world_view == FRONT) {
				front_stage[i][j].x = j * BLOCK_SIZE;
				front_stage[i][j].y = i * BLOCK_SIZE;
			} else {
				back_stage[i][j].x = j * BLOCK_SIZE;
				back_stage[i][j].y = i * BLOCK_SIZE;
			}
		}
	}
}
void StageCtrl_Draw(void) {
	int i, j;
	for (i = 0;i < MAP_HEIGHT;i++) {
		for (j = 0;j < MAP_WIDTH;j++) {
			if (world_view == FRONT) {
				DrawGraph(front_stage[i][j].x, front_stage[i][j].y, stage_img[front_stage[i][j].img], TRUE);
			} else {
				DrawGraph(back_stage[i][j].x, back_stage[i][j].y, stage_img[back_stage[i][j].img], TRUE);
			}
		}
	}
}
// �X�e�[�W�摜�ǂݍ��ݏ���
int StageCtrl_ImgLoad(void) {
	int ret = TRUE;
	
	stage_img[0] = LoadGraph("images/dummy.png");

	for (int i = 0; i < BLOCK_MAX; i++) {
		if (stage_img[i] == -1) {
			ret &= FALSE;
		}
	}
	return ret;
}
// �X�e�[�W�t�@�C���ǂݍ��ݏ���
static void stagectrl_stageload(int wrld) {
	FILE* fp_front = NULL;
	FILE* fp_back = NULL;
	int i, j;

	if (wrld  == ABOVE_GROUND) {
		fopen_s(&fp_front, "stage/world1-1.csv", "r");	//�X�e�[�W�t�@�C����ǂݍ��ݐ�p�œǂݍ���
		fopen_s(&fp_back, "stage/world1-1b.csv", "r");	//�X�e�[�W�t�@�C����ǂݍ��ݐ�p�œǂݍ���
	} else if (wrld == UNDER_GROUND) {
		fopen_s(&fp_front, "stage/world1-2.csv", "r");	//�X�e�[�W�t�@�C����ǂݍ��ݐ�p�œǂݍ���
		fopen_s(&fp_back, "stage/world1-2b.csv", "r");	//�X�e�[�W�t�@�C����ǂݍ��ݐ�p�œǂݍ���
	} else if (wrld == IN_THE_AIR) {
		fopen_s(&fp_front, "stage/world1-3.csv", "r");	//�X�e�[�W�t�@�C����ǂݍ��ݐ�p�œǂݍ���
		fopen_s(&fp_back, "stage/world1-3b.csv", "r");	//�X�e�[�W�t�@�C����ǂݍ��ݐ�p�œǂݍ���
	} else if (wrld == INSIDE_CASTLE) {
		fopen_s(&fp_front, "stage/world1-4.csv", "r");	//�X�e�[�W�t�@�C����ǂݍ��ݐ�p�œǂݍ���
		fopen_s(&fp_back, "stage/world1-4b.csv", "r");	//�X�e�[�W�t�@�C����ǂݍ��ݐ�p�œǂݍ���
	} else {
		fp_front = NULL;
		fp_back = NULL;
	}

	if(fp_front == NULL || fp_back == NULL){
		DrawFormatString(0, 0, 0xFFFFFFFF, "�t�@�C�����J���܂���ł����B");
	} else {
		for (i = 0; i < MAP_HEIGHT; i++) {
			for (j = 0; j < MAP_WIDTH; j++)	{
				int tmp = fgetc(fp_front);
				if ((tmp != ',') && (tmp != '\n') && (tmp != -1)) {
					front_stage[i/2][j/2].img = tmp - '0';
				}
				tmp = fgetc(fp_back);
				if ((tmp != ',') && (tmp != '\n') && (tmp != -1)) {
					back_stage[i / 2][j / 2].img = tmp - '0';
				}
			}
		}
		fclose(fp_front);							// �ǂݍ��񂾃t�@�C�������
		fclose(fp_back);							// �ǂݍ��񂾃t�@�C�������
	}
	
}


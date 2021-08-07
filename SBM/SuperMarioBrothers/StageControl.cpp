#include <stdio.h>
#include <ctype.h>
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
static FILE* fp_front = NULL;
static FILE* fp_back = NULL;
// �֐��錾
static void stagectrl_stageload(int wrld);
static void stagectrl_world_data_check(void);

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
	int ret = 0;
	
	stage_img[NONE] = LoadGraph("images/dummy.png");
	stage_img[FLOOR] = LoadGraph("images/floor.png");
	ret += LoadDivGraph("images/hatena.png", 4, 4, 1, 32, 32, &stage_img[HATENA]);


	for (int i = 0; i < BLOCK_MAX; i++) {
		if (stage_img[i] == -1) {
			ret = -1;
		}
	}

	return ret;
}
// �X�e�[�W�t�@�C���ǂݍ��ݏ���
static void stagectrl_stageload(int wrld) {
	
	int i = 0, j = 0;

	//�X�e�[�W�t�@�C����ǂݍ��ݐ�p�œǂݍ���
	if (wrld  == ABOVE_GROUND) {
		fopen_s(&fp_front, "stage/world1-1.csv", "r");
		fopen_s(&fp_back, "stage/world1-1b.csv", "r");
	} else if (wrld == UNDER_GROUND) {
		fopen_s(&fp_front, "stage/world1-2.csv", "r");
		fopen_s(&fp_back, "stage/world1-2b.csv", "r");
	} else if (wrld == IN_THE_AIR) {
		fopen_s(&fp_front, "stage/world1-3.csv", "r");
		fopen_s(&fp_back, "stage/world1-3b.csv", "r");
	} else if (wrld == INSIDE_CASTLE) {
		fopen_s(&fp_front, "stage/world1-4.csv", "r");
		fopen_s(&fp_back, "stage/world1-4b.csv", "r");
	} else {
		fp_front = NULL;
		fp_back = NULL;
	}

	if(fp_front == NULL || fp_back == NULL){
		DrawFormatString(0, 0, 0xFFFFFFFF, "�t�@�C�����J���܂���ł����B");
	} else {
		stagectrl_world_data_check();
		fclose(fp_front);							// �ǂݍ��񂾃t�@�C�������
		fclose(fp_back);							// �ǂݍ��񂾃t�@�C�������
	}
	
}
// �ǂݍ��݃f�[�^�`�F�b�N
static void stagectrl_world_data_check(void) {
	int digit[3] = {}, d = 0;		// �����Ǘ�
	int chr = NULL;					// �o�͕���
	int i = 0, j = 0;				// ���[�v�J�E���^

	// �\�ʂ̃f�[�^�`�F�b�N
	do {
		chr = fgetc(fp_front);
		if (isdigit(chr)) {
			digit[d++] = (chr - '0');
		} else if (chr == ',') {
			int kt = 1;
			for (d -= 1;d >= 0;d--) {
				front_stage[i][j].img += (digit[d] * kt);
				kt *= 10;
			}
			digit[0] = 0;
			digit[1] = 0;
			digit[2] = 0;
			d = 0;
			if (++j >= MAP_WIDTH) {
				j = 0;
				i++;
			}
		}
	} while (chr != EOF);
	i = j = 0;
	// ���ʂ̃f�[�^�`�F�b�N
	do {
		chr = fgetc(fp_back);
		if (isdigit(chr)) {
			digit[d++] = (chr - '0');
		}
		else if (chr == ',') {
			int kt = 1;
			for (d -= 1;d >= 0;d--) {
				back_stage[i][j].img += (digit[d] * kt);
				kt *= 10;
			}
			digit[0] = 0;
			digit[1] = 0;
			digit[2] = 0;
			d = 0;
			if (++j >= MAP_WIDTH) {
				j = 0;
				i++;
			}
		}
	} while (chr != EOF);
}

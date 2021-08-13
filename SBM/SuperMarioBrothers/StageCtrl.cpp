#include <stdio.h>
#include <ctype.h>
#include "DxLib.h"
#include "StageCtrl.h"
#include "StageCtrl_Config.h"

//�����萔
#define BLOCK_SIZE	(32U)

// �ϐ�
static int world_type;
static T_Stage stage[MAP_HEIGHT][MAP_WIDTH];
static int stage_img[BLOCK_MAX];
static FILE* fp_front = NULL;
// �֐��錾
static void stagectrl_stageload(void);
static const char* get_csv_name(void);
static void stagectrl_world_data_check(void);


// ������
void StageCtrl_Init(void) {
	StageCtrl_MapChange(ABOVE_GROUND);
	stagectrl_stageload();
}
// �X�V
void StageCtrl_Update(void) {
	int i, j;
	for (i = 0;i < MAP_HEIGHT;i++) {
		for (j = 0;j < MAP_WIDTH;j++) {
			stage[i][j].x = j * BLOCK_SIZE;
			stage[i][j].y = i * BLOCK_SIZE;
		}
	}
}
// �`��
void StageCtrl_Draw(void) {
	int i, j;
	for (i = 0;i < MAP_HEIGHT;i++) {
		for (j = 0;j < MAP_WIDTH;j++) {
			DrawGraph(stage[i][j].x, stage[i][j].y, stage_img[stage[i][j].img], TRUE);
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
// �X�e�[�W�؂�ւ�����
void StageCtrl_MapChange(int wrld) {
	world_type = wrld;
	stagectrl_stageload();
}
// �X�e�[�W�t�@�C���ǂݍ��ݏ���
static void stagectrl_stageload(void) {
	
	int i = 0, j = 0;
	fopen_s(&fp_front, get_csv_name(), "r");

	if(fp_front == NULL){
		DrawFormatString(0, 0, 0xFFFFFFFF, "�t�@�C�����J���܂���ł����B");
	} else {
		stagectrl_world_data_check();
		fclose(fp_front);							// �ǂݍ��񂾃t�@�C�������
	}
	
}
// CSV�t�@�C�����̎擾
static const char* get_csv_name(void) {
	const char* tmp = NULL;

	if (world_type < WORLD_MAX) {
		tmp = C_StageName[world_type];
	} else {
		tmp = NULL;
	}

	return tmp;
}
// �ǂݍ��݃f�[�^�`�F�b�N
static void stagectrl_world_data_check(void) {
	int digit[2] = {}, d = 0;		// �����Ǘ�
	int chr = NULL;					// �o�͕���
	int i = 0, j = 0;				// ���[�v�J�E���^

	while (1) {
		chr = fgetc(fp_front);
		if (isdigit(chr)) {
			digit[d++] = (chr - '0');
		}
		if (chr == ',' || chr == '\n') {
			int kt = 1;
			for (d = d - 1;d >= 0;d--) {
				stage[i][j].img += (digit[d] * kt);
				kt *= 10;
			}
			for (d = 0;d < 2;d++) {
				digit[d] = 0;
			}
			d = 0;
			j++;
		}
		if (chr == '\n') {
			j = 0;
			i++;
		}
	}
	
}

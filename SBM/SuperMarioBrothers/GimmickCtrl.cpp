#include "DxLib.h"
#include "GimmickCtrl.h"
#include "StageCtrl.h"
#include "EnemyConfig.h"

// �\����
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

// �ϐ��錾
T_GOOMBA	Goomba[GOOMBA_MAX];					// �N���{�[
T_TROOPER	Trooper[(NKNK_MAX + PTPT_MAX)];		// �m�R�m�R
T_PLANT		Plant[PIRANHA_PLANT_MAX];			// �p�b�N���t�����[
T_BOWSER	Bowser[BOWSER_MAX];					// �N�b�p
T_BREATH	BowserBreath[2];					// �N�b�p�f�b��

// �v���g�^�C�v�錾
static void setting_enemy_position(void);

/* ������ */
void GimmickCtrl_Init(void) {

}
/* �X�V */
void GimmickCtrl_Update(void) {

}
/* �`�� */
void GimmickCtrl_Draw(void) {

}
/* �摜�ǂݍ��� */
int GimmickCtrl_ImgLoad(void) {
	int ret = 0;		// �߂�l(0:����,	0�ȊO:�ُ�)
	int loop_cnt = 0;	// ���[�v�J�E���^

	// �G�摜�ǂݍ���
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
	
	// ���[���h�M�~�b�N�摜�ǂݍ���

	
	return ret;
}



static void setting_enemy_position(void) {
	int wt = Get_StageCtrl_world_type();
}
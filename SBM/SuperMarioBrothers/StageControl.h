#ifndef STAGE_CONTROL_H__
#define STAGE_CONTROL_H__

// �\���̐錾
typedef struct {
	int x;
	int y;
	int img;
	int retention;
	bool flg;
}T_Stage;


// �֐��錾
void StageCtrl_Init(void);			// �X�e�[�W����F����������
void StageCtrl_Update(void);		// �X�e�[�W����F�X�V����
void StageCtrl_Draw(void);			// �X�e�[�W����F�`�揈��

#endif // !STAGE_CONTROL_H__
#ifndef STAGE_CONTROL_H__
#define STAGE_CONTROL_H__

//�萔��`

// �\���̐錾
typedef struct {
	int x;
	int y;
	int img;
	int inside;
}T_Stage;


// �֐��錾
void StageCtrl_Init(void);			// �X�e�[�W����F����������
void StageCtrl_Update(void);		// �X�e�[�W����F�X�V����
void StageCtrl_Draw(void);			// �X�e�[�W����F�`�揈��
int StageCtrl_ImgLoad(void);		// �X�e�[�W����F�摜�ǂݍ��ݏ���
void StageCtrl_MapChange(int wrld);		// �X�e�[�W����F�X�e�[�W�ύX����
int Get_StageCtrl_world_type(void);
#endif // !STAGE_CONTROL_H__

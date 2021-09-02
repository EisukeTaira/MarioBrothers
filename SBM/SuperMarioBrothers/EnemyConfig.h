#ifndef ENEMY_CONFIG_H__
#define ENEMY_CONFIG_H__

// �}�N����`
#define GOOMBA_MAX			(32U)	// �N���{�[�ő吔
#define GOOMBA_ANIM_SIZE	(3U)	// �N���{�[�A�j���[�V�����T�C�Y
#define NKNK_MAX			(8U)	// �m�R�m�R�ő吔
#define PTPT_MAX			(2U)	// �p�^�p�^�ő吔
#define TROOPER_ANIM_SIZE	(6U)	// �T�A�j���[�V�����T�C�Y
#define PIRANHA_PLANT_MAX	(4U)	// �p�b�N���t�����[�ő吔
#define PLANT_ANIME_SIZE	(4U)	// �p�b�N���t�����[�A�j���[�V�����T�C�Y
#define BOWSER_MAX			(1U)	// �N�b�p�ő吔
#define BOWSER_ANIM_SIZE	(4U)	// �N�b�p�A�j���[�V�����T�C�Y
#define	FLAME_ANIME_SIZE	(2U)	// ���A�j���[�V�����T�C�Y


// �\���̐錾
typedef struct {
	int		x;
	int		y;
}T_Pos;
typedef struct {
	T_Pos	pos;
	int		hp;
	int		flg;
	int		dir;
}T_ENEMY;
typedef struct {
	T_ENEMY	e_info;
	int		img[GOOMBA_ANIM_SIZE];
}T_GOOMBA;
typedef struct {
	T_ENEMY	e_info;
	int		img[TROOPER_ANIM_SIZE];
}T_TROOPER;
typedef struct {
	T_ENEMY	e_info;
	int		img[PLANT_ANIME_SIZE];
}T_PLANT;
typedef struct {
	T_ENEMY	e_info;
	T_Pos	fire_pos;
	int		img[PLANT_ANIME_SIZE];
}T_BOWSER;
typedef struct {
	T_Pos	pos;
	int img[FLAME_ANIME_SIZE];
}T_BREATH;

/************************************
*�@�G�̏����ʒu�e�[�u���ݒ�			*
*************************************/
// ���[���h�G���e�[�u��
const int Enemy_Table[8][4] = {
	/* 	�G��	�T		��		�� */
	{	15,		1,		0,		0	},
	{	0,		0,		0,		0	},
	{	14,		4,		3,		0	},
	{	0,		0,		0,		0	},
	{	0,		0,		0,		0	},
	{	0,		0,		1,		0	},
	{	3,		5,		0,		0	},
	{	0,		0,		0,		1	},
};

// �N���{�[�����ʒu
const T_Pos C_Enemy_Goomba_Pos_Table[GOOMBA_MAX] = {
	/* world 1-1 (15��) */
	{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
	{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
	/* world 1-2 (14��) */
	{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
	{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
	/* world 1-3 ( 3��) */
	{0,0},{0,0},{0,0},
};
// �m�R�m�R���p�^�p�^�����ʒu
const T_Pos C_Enemy_Trooper_Pos_Table[(NKNK_MAX + PTPT_MAX)] = {
	/* world 1-1 ( 1��) */
	{0,0},
	/* world 1-2 ( 4��) */
	{0,0},{0,0},{0,0},{0,0},
	/* world 1-3 ( 5��) */
	{0,0},{0,0},{0,0},{0,0},{0,0}
};
// �p�b�N���t�����[�����ʒu
const T_Pos C_Enemy_Plant_Pos_Table[PIRANHA_PLANT_MAX] = {
	/* world 1-2 ( 4��) */
	{0,0},{0,0},{0,0},{0,0},
};
// �N�b�p�����ʒu
const T_Pos C_Enemy_Bowser_Pos_Table[(NKNK_MAX + PTPT_MAX)] = {
	/* world 1-4 ( 1��) */
	{0,0},
};



#endif // !ENEMY_CONFIG_H__
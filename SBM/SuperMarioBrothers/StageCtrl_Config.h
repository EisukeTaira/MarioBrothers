#ifndef STAGE_CONTROL_CONFIG_H__
#define STAGE_CONTROL_CONFIG_H__

#define MAP_HEIGHT		(0x0FU)		// �}�b�v����
#define MAP_WIDTH		(0xFFU)		// �}�b�v��
#define ANIM_SIZE		(0x04U)		// �A�j���[�V�����T�C�Y

// ���[���h���
enum {
	ABOVE_GROUND,		// ���[���h1-1
	ABOVE_BACK,			// �y�ǂ̒�
	UNDER_GROUND,		// ���[���h1-2
	UNDER_START,		// �X�^�[�g�n�_
	UNDER_BACK,			// �y�ǂ̒�
	UNDER_GOAL,			// �S�[���n�_
	IN_THE_AIR,			// ���[���h1-3
	INSIDE_CASTLE,		// ���[���h1-4
	WORLD_MAX
};

// �e�u���b�N
enum {
	SKY = 0,								// ���蓖�Ė���
	FLOOR,									// ��
	FLOOR_UNDER,							// ��(�n��)
	HATENA,									// �n�e�i
	HATENA_UNDER,							// �n�e�i(�n��)
	COIN = HATENA + ANIM_SIZE,				// �R�C��
	COIN_UNDER = COIN + ANIM_SIZE,			// �R�C��(�n��)
	BRICK = COIN_UNDER + ANIM_SIZE,			// �����K
	BRICK_UNDER,							// �����K(�n��)
	STAIRS,									// �K�i
	STAIRS_UNDER,							// �K�i(�n��)
	BLINK,									// ��u���b�N
	BLINK_UNDER,							// ��u���b�N(�n��)
	ZHUGE_LIANG,							// �E��
	POLE_HEAD,								// �|�[���̐擪
	POLE_DOWN,								// �|�[���̎x��
	POLE_FLAG,								// �|�[���̊�
	VARTCAL_CPIPE,							// �c�����y��
	SIDEWAY_CPIPE = VARTCAL_CPIPE + 4,		// �������y��
	PIPE_JOINT = SIDEWAY_CPIPE + 4,			// �y�ǂȂ���
	GLASS = PIPE_JOINT + 2,					// ��(���i)
	MOUNTAIN = GLASS + 3,					// �R(���i)
	CLOUD = MOUNTAIN + 6,					// �_(���i)
	MISSING = CLOUD + 6,					// 
	MAGMA,
	CASTLE_WALL = MAGMA + 2,				// �}�O�}
	BRIDGE,									// �}�O�}
	SLIDING_THROUGH,						// ���蔲���u���b�N
	PILLAR = SLIDING_THROUGH + 3,			// ��
	BLOCK_MAX
};

const char C_StageName[][25] = {
	"stage/world1-1.csv",
	"stage/world1-1b.csv",
	"stage/world1-2.csv",
	"stage/world1-2s.csv",
	"stage/world1-2b.csv",
	"stage/world1-2g.csv",
	"stage/world1-3.csv",
	"stage/world1-4.csv",
};

#endif
#ifndef STAGE_CONTROL_CONFIG_H__
#define STAGE_CONTROL_CONFIG_H__

#define MAP_HEIGHT			(0x0FU)						// �}�b�v����
#define MAP_WIDTH			(0xFFU)						// �}�b�v��
#define BLOCK_SIZE			(32U)						// �u���b�N�T�C�Y
#define ANIM_SIZE			(4U)						// �A�j���[�V�����T�C�Y

#define SKY					(0U)						// ���蓖�Ė���
#define FLOOR				(1U)						// ��
#define FLOOR_UNDER			(2U)						// ��(�n��)
#define HATENA				(3U)						// �n�e�i
#define HATENA_UNDER		(7U)						// �n�e�i(�n��)
#define COIN				(11U)						// �R�C��
#define COIN_UNDER			(15U)						// �R�C��(�n��)
#define BRICK				(19U)						// �����K
#define BRICK_UNDER			(20U)						// �����K(�n��)
#define STAIRS				(21U)						// �K�i
#define STAIRS_UNDER		(22U)						// �K�i(�n��)
#define BLINK				(23U)						// ��u���b�N
#define BLINK_UNDER			(24U)						// ��u���b�N(�n��)
#define ZHUGE_LIANG			(25U)						// �E��
#define POLE_HEAD			(26U)						// �|�[���̐擪
#define POLE_DOWN			(27U)						// �|�[���̎x��
#define POLE_FLAG			(28U)						// �|�[���̊�
#define VARTCAL_CPIPE		(29U)						// �c�����y��
#define SIDEWAY_CPIPE		(33U)						// �������y��
#define PIPE_JOINT			(37U)						// �y�ǂȂ���
#define GLASS				(39U)						// ��(���i)
#define MOUNTAIN			(42U)						// �R(���i)
#define CLOUD				(48U)						// �_(���i)
#define BRIDGE				(56U)						// �V��
#define MAGMA				(57U)						// �}�O�}
#define CASTLE_WALL			(59U)						// �ǁE�n��
#define SLIDING_THROUGH		(60U)						// ���蔲���u���b�N
#define PILLAR				(63U)						// ��
#define BLOCK_MAX			(64U)

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
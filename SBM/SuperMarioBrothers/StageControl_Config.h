#ifndef STAGE_CONTROL_CONFIG_H__
#define STAGE_CONTROL_CONFIG_H__

#define MAP_HEIGHT		(0x0FU)		// �}�b�v����
#define MAP_WIDTH		(0xFFU)		// �}�b�v��
#define ANIM_SIZE		(0x04U)		// �A�j���[�V�����T�C�Y

// ���[���h���
enum {
	ABOVE_GROUND,
	ABOVE_BACK,
	UNDER_GROUND,
	UNDER_START,
	UNDER_BACK,
	UNDER_GOAL,
	IN_THE_AIR,
	INSIDE_CASTLE,
	WORLD_MAX
};

// �e�u���b�N
enum {
	NONE = 0,					// ���蓖�Ė���
	FLOOR,						// ��
	HATENA,						// �n�e�i
	COIN = HATENA + ANIM_SIZE,	// �R�C��
	BRICK = COIN + ANIM_SIZE,	// �����K
	STAIRS,						// �K�i
	BLINK_,						// ��u���b�N
	ZHUGE_LIANG,				// �E��
	VARTCAL_CPIPE,				// �c�����y��
	SIDEWAY_CPIPE = VARTCAL_CPIPE + 4,		// �������y��
	PIPE_JOINT = SIDEWAY_CPIPE + 4,			// �y�ǂȂ���
	BLOCK_MAX = PIPE_JOINT + 2
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
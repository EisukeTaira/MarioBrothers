#ifndef STAGE_CONTROL_CONFIG_H__
#define STAGE_CONTROL_CONFIG_H__

#define MAP_HEIGHT		(0x0FU)		// �}�b�v����
#define MAP_WIDTH		(0xFFU)		// �}�b�v��
#define ANIM_SIZE		(0x04U)

enum {
	ABOVE_GROUND,					// �X�e�[�W 1-1
	UNDER_GROUND,					// �X�e�[�W 1-2
	IN_THE_AIR,						// �X�e�[�W 1-3
	INSIDE_CASTLE,					// �X�e�[�W 1-4
	WORLD_MAX
};

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

#endif
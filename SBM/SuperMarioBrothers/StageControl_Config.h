#ifndef STAGE_CONTROL_CONFIG_H__
#define STAGE_CONTROL_CONFIG_H__

#define MAP_HEIGHT		(0x0FU)		// �}�b�v����
#define MAP_WIDTH		(0xFFU)		// �}�b�v��

enum {
	ABOVE_GROUND,					// �X�e�[�W 1-1
	UNDER_GROUND,					// �X�e�[�W 1-2
	IN_THE_AIR,						// �X�e�[�W 1-3
	INSIDE_CASTLE,					// �X�e�[�W 1-4
	WORLD_MAX
};

enum {
	NONE = 0,
	BRICK_NORMAL,					// �����K�u���b�N(��)
	BRICK_COIN,						// �����K�u���b�N(�R�C��)
	HATENA_MUSH_PW,					// �n�e�i�u���b�N(PW�L�m�R)
	HATENA_MUSH_1UP,				// �n�e�i�u���b�N(1UP�L�m�R)
	HATENA_STAR,					// �n�e�i�u���b�N(�X�^�[)
	HATENA_COIN,					// �n�e�i�u���b�N(�R�C��)
	HATENA_LVY,						// �n�e�i�u���b�N(�c�^)
	ZHUGE_LIANG,					// �E���u���b�N
	FIRE_BAR,						// �t�@�C�A�o�[
	FLOOR,							// ��
	PIPE_ENTRANCE_L,				// �y��(��������p����)
	PIPE_ENTRANCE_R,				// �y��(������E�p����)
	PIPE_ENTRANCE_U,				// �y��(��������p����)
	PIPE_ENTRANCE_D,				// �y��(���������p����)
	PIPE_EARTHEN_L,					// �y��(��������p)
	PIPE_EARTHEN_R,					// �y��(������E�p)
	PIPE_EARTHEN_U,					// �y��(��������p)
	PIPE_EARTHEN_D,					// �y��(���������p)
	PIPE_SEAM_U,					// �y��(�Ȃ��ڏ�)
	PIPE_SEAM_D,					// �y��(�Ȃ��ډ�)
	STAIRS,							// �i���u���b�N
	POLE_HEAD,						// �|�[���擪
	POLE_SEAM,						// �|�[���Ȃ���
	EXIT_GATEWAY,					// �X�e�[�W�̏o��
	BLOCK_MAX
};

#endif
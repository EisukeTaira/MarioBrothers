#pragma once

// �摜���
#define MARIO_WIDTH_HEIGHT		(32)			// �摜�̕�
#define MARIO_IMAGE_MAX			(9)				// �摜�̕�����
// �摜�̓Y����
#define IDOL_IMG				(0)				// �_����
#define MOVE_IMG_START			(1)				// �ŏ��̈ړ��摜
#define MOVE_IMG_END			(3)				// �Ō�̈ړ��摜
#define TURN_IMG				(4)				// �^�[��
#define JUMP_IMG				(5)				// �W�����v

// �ړ���Ԃ�\���t���O�萔
#define STATE_IDOL				(0b0000U)		// �_����
#define STATE_MOVE				(0b0001U)		// �ړ�
#define STATE_DASH				(0b0010U)		// �_�b�V��
#define STATE_TURN				(0b0100U)		// �^�[��
#define STATE_JUMP				(0b1000U)		// �W�����v

// �X�e�[�^�X
#define WALK_ACCELERATION		(0.2f)			// �ړ��̉����x
#define MAX_WALK_SPEED			(3.0f)			// �ʏ펞�̍ō����x
#define MAX_DASH_SPEED			(5.0f)			// �_�b�V�����̍ō����x
#define FRICTION_POWER			(0.2f)			// ���C
#define IDOL_JUMP_POWER			(10.0f)			// �ʏ펞�̃W�����v��
#define DASH_JUMP_POWER			(13.0f)			// �_�b�V�����̃W�����v��
#define GRAVITY_POWER			(1.0f)			// �d��
#define MAX_FALL_SPEED			(8.0f)			// �����̍ō����x

// �Q�b�^�[
#define GET_MAX_SPEED(DASH_FLG) (DASH_FLG ? MAX_DASH_SPEED : MAX_WALK_SPEED)		// �ō����x�擾
#define GET_JUMP_POWER(DASH_FLG) (DASH_FLG ? -IDOL_JUMP_POWER : -DASH_JUMP_POWER)		// �W�����v�͎擾

// �����w��̗�
typedef enum {
	LEFT_DIR = -1,
	RIGHT_DIR = 1
}E_MARIO_DIR;

// ���W�̍\����
typedef struct {
	float x;
	float y;
}T_COORDINATE;

// �}���I�̍\����
typedef struct {
	int images[MARIO_IMAGE_MAX];	// �}���I�̉摜
	E_MARIO_DIR direction;			// ���E�̌���
	T_COORDINATE oldPosition;		// 1�t���[���O�̍��W
	T_COORDINATE nowPosition;		// ���ݍ��W
	T_COORDINATE speed;				// ���x�@���W�ɉ��Z����l
	unsigned char moveStateFlag;	// �ړ����
	int animationFreamTime;			// �A�j���[�V�����p�t���[���J�E���g
	bool isJumpPush;				// �W�����v�{�^���������Ă��邩�ǂ���
	bool isStageClear;				// �X�e�[�W�N���A�̃t���O
	bool isDeath;					// GameOver�̃t���O
}T_MARIO;

// �v���g�^�C�v�錾
bool Mario_Init();					// �}���I�̏�����
void Mario_Update();				// �}���I�̍X�V����
void Mario_Draw();					// �}���I�̕`�揈��
const T_MARIO* getMarioInfo();		// �}���I�̏��擾

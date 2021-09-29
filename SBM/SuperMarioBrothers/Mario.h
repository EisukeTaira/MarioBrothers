#pragma once

// �摜�n�萔
#define MARIO_WIDTH_HEIGHT__ 32	// �摜�̕�
#define MARIO_IMAGE_MAX__ 9		// �摜�̕�����

// �摜�̓Y����
#define IDOL_IMG__ 0			// �_����
#define MOVE_IMG_START__ 1		// �ŏ��̈ړ��摜
#define MOVE_IMG_END__ 3		// �Ō�̈ړ��摜
#define TURN_IMG__ 4			// �^�[��
#define JUMP_IMG__ 5			// �W�����v

// �ړ���Ԃ�\���萔
#define IDOL__ 0x00U			// �_����
#define MOVE__ 0x01U			// �ړ�
#define DASH__ 0x02U			// �_�b�V��
#define TURN__ 0x04U			// �^�[��
#define JUMP__ 0x08U			// �W�����v

// �X�e�[�^�X
#define MAX_WALK_SPEED__ 3		// �ʏ펞�̍ō����x
#define MAX_DASH_SPEED__ 5		// �_�b�V�����̍ō����x
#define JUMP_POWER__ 10			// �ʏ펞�̃W�����v��
#define DASH_JUMP_POWER__ 13	// �_�b�V�����̃W�����v��

// �^�U
#define SUCCESS__ 1	// ����
#define ERROR__ -1	// ���s

// �����w��̗�
typedef enum {
	LEFT_DIR = -1,
	RIGHT_DIR = 1
}E_MARIO_DIRECTION;

// ���W�̍\����
typedef struct {
	float x;
	float y;
}T_COORDINATE;

// �}���I�̍\����
typedef struct {
	T_COORDINATE oldPosition;		// 1�t���[���O�̍��W
	T_COORDINATE nowPosition;		// ���ݍ��W
	T_COORDINATE speed;				// ���x�@���W�ɉ��Z����l
	T_COORDINATE maxSpeed;			// �ő呬�x�@�X�s�[�h�̏���l
	T_COORDINATE acc;				// �����x�@�X�s�[�h�ɉ��Z����l
	float jumpPower;				// �W�����v��
	
	bool isJumpPush;				// �W�����v�{�^���������Ă��邩�ǂ���
	bool isStageClear;				// �X�e�[�W�N���A�̃t���O
	bool isDeath;					// GameOver�̃t���O

	unsigned char moveFlag;		// �ړ����
	E_MARIO_DIRECTION direction;	// ���E�̌���

	int animationFreamTime;			// �A�j���[�V�����p�t���[���J�E���g
	int images[MARIO_IMAGE_MAX__];	// �}���I�̉摜

	
}T_MARIO;

// ���������\�b�h
inline bool isMarioInitSuccess() {
	int marioInit();
	return (marioInit() == SUCCESS__);
}

// �X�V����
void Update();

// �`�揈��
void Draw();

const T_MARIO getMarioInfo();
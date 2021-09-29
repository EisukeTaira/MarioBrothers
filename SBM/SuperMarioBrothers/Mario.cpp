#include "DxLib.h"
#include "KeyControl.h"
#include "Mario.h"

// �v���C���[�ϐ�
T_MARIO mario;

// �֐��̃v���g�^�C�v�錾
void Input();
void Move();
void Jump();
int getImageNum();
void updateDirection();

/******************************************
* ���ӂ̃t���O�ɉE�ӂ̃t���O��ǉ�
*
* �����F	leftFlag ���ӂ̃t���O
*			rightFlag �E�ӂ̃t���O
* �߂�l�F	�Ȃ�
******************************************/
inline void addFlag(unsigned char& leftFlag, unsigned char rightFlag) {
	leftFlag |= rightFlag;
}

/******************************************
* ���ӂ̃t���O����E�ӂ̃t���O���폜
*
* �����F	leftFlag ���ӂ̃t���O
*			rightFlag �E�ӂ̃t���O
* �߂�l�F	�Ȃ�
******************************************/
inline void subFlag(unsigned char& leftFlag, unsigned char rightFlag) {
	leftFlag &= ~rightFlag;
}

/******************************************
* ���ӂ̃t���O�ɉE�ӂ̃t���O���܂܂�Ă��邩�ǂ���
*
* �����F	leftFlag ���ӂ̃t���O
*			rightFlag �E�ӂ̃t���O
* �߂�l�F	TRUE �܂܂�Ă���
*			FALSE �܂܂�Ă��Ȃ�
******************************************/
inline bool containFlag(unsigned char leftFlag, unsigned char rightFlag) {
	return leftFlag & rightFlag;
}

/******************************************
* ���ӂ̃t���O�ƉE�ӂ̃t���O�����S��v
*
* �����F	leftFlag ���ӂ̃t���O
*			rightFlag �E�ӂ̃t���O
* �߂�l�F	TRUE ���S��v
*			FALSE ���S��v�ȊO
******************************************/
inline bool equalFlag(unsigned char leftFlag, unsigned char rightFlag) {
	return leftFlag == rightFlag;
}

/******************************************
* �}���I�̎��S�t���O��ON�ɂ���
*
* �����F	�Ȃ�
* �߂�l�F	�Ȃ�
******************************************/
inline void marioDie() {
	mario.isDeath = true;
}

/******************************************
* �}���I�̎��S�t���O���擾����
*
* �����F	�Ȃ�
* �߂�l�F	�}���I�̎��S�t���O
******************************************/
inline const bool getMarioDeathFlag() {
	return mario.isDeath;
}

/******************************************
* �}���I�̃X�e�[�W�N���A�t���O���擾����
*
* �����F	�Ȃ�
* �߂�l�F	�}���I�̃X�e�[�W�N���A�t���O
******************************************/
inline const bool getMarioStageClearFlag() {
	return mario.isStageClear;
}

/******************************************
* �}���I�̃_�b�V���t���O���I���ɂ���
*
* �����F	�Ȃ�
* �߂�l�F	�Ȃ�
******************************************/
inline void setDashFlagOn() {
	addFlag(mario.moveFlag, DASH__);
	mario.maxSpeed.x = MAX_DASH_SPEED__;
	mario.jumpPower = DASH_JUMP_POWER__;
}

/******************************************
* �}���I�̃_�b�V���t���O���I�t�ɂ���
*
* �����F	�Ȃ�
* �߂�l�F	�Ȃ�
******************************************/
inline void setDashFlagOff() {
	subFlag(mario.moveFlag, DASH__);
	mario.maxSpeed.x = MAX_WALK_SPEED__;
	mario.jumpPower = JUMP_POWER__;
}

/******************************************
* �}���I���W�����v�����ǂ����擾����
*
* �����F	�Ȃ�
* �߂�l�F	TRUE(�W�����v��)�AFALSE(�n�ʂɂ���)
******************************************/
inline bool isJump() {
	return (mario.oldPosition.y != mario.nowPosition.y);
}

/******************************************
* T_MARIO �̏��������\�b�h
*
* �����F	�Ȃ�
* �߂�l�F	TRUE(����I��)�AFALSE(�ُ�I��)
******************************************/
int marioInit() {
	// TODO : �}���I�e�X�g�p
	KeyCtrl_Init();

	// �}���I�̉摜�ǂݍ���
	if(mario.images[0] == 0) {
		if (LoadDivGraph("images/mario.png", MARIO_IMAGE_MAX__, MARIO_IMAGE_MAX__, 1, MARIO_WIDTH_HEIGHT__, MARIO_WIDTH_HEIGHT__, mario.images) == ERROR__) {
			// �ǂݍ��ݎ��s
			return ERROR__;
		}
	}

	// �������W
	mario.nowPosition.x = 0;	// ���ݍ��W X
	mario.nowPosition.y = 200;	// ���ݍ��W Y
	mario.oldPosition.x = mario.nowPosition.x;	// 1�t���[���O���W X
	mario.oldPosition.y = mario.nowPosition.y;	// 1�t���[���O���W Y

	mario.speed.x = 0;	// X���W�̈ړ��X�s�[�h
	mario.speed.y = 0;	// Y���W�̈ړ��X�s�[�h
	mario.maxSpeed.x = 5;	// X���W�̍ő�X�s�[�h
	mario.maxSpeed.y = 8;	// Y���W�̍ő�X�s�[�h

	mario.acc.x = 0.2f;	// �����xX
	mario.acc.y = 1.0f;	// �����xY
	mario.jumpPower = JUMP_POWER__;

	mario.moveFlag = IDOL__;	// ���݂̃��[�h
	mario.direction = RIGHT_DIR;	// ����

	// �e�t���O�̓I�t
	mario.isJumpPush = false;	// �W�����v�{�^����������Ă��邩
	mario.isDeath = false;	// ���S�t���O
	mario.isStageClear = false;	// �X�e�[�W�N���A�t���O

	mario.animationFreamTime = 0;	// �A�j���[�V�����p�t���[���J�E���g
	

	return SUCCESS__;
}

/******************************************
* T_MARIO �̍X�V���\�b�h
*
* �����F	�Ȃ�
* �߂�l�F	�Ȃ�
******************************************/
void Update() {

	KeyCtrl_Update();
	
	if (!getMarioDeathFlag()) {
		if (!getMarioStageClearFlag()) {
			Input();
			Move();
			Jump();
		}
		else {
			// �X�e�[�W�N���A����
		}
	}
	else {
		// ���S����
	}
}

/******************************************
* T_MARIO �̕`�惁�\�b�h
*
* �����F	�Ȃ�
* �߂�l�F	�Ȃ�
******************************************/
void Draw() {
	// ���E�̌�������
	updateDirection();


	// �\���摜�̌���
	int displayImageNum = getImageNum();
		//mario.imageNum;
	//if (mario.moveFlag & MOVE__ && (~mario.moveFlag & JUMP__) && (~mario.moveFlag & TURN__)) {
	//	// MOVE__�̎������A�j���[�V�����ɂ���
	//	displayImageNum += mario.animationWalkAddNum;
	//}

	// �`����W X
	int x = (int)mario.nowPosition.x + (MARIO_WIDTH_HEIGHT__ / 2);
	// �`����W Y
	int y = (int)mario.nowPosition.y + (MARIO_WIDTH_HEIGHT__ / 2);
	// ���� (�� = TRUE, �E = FALSE)
	bool isLeftDir = (mario.direction == LEFT_DIR);

	// �}���I��`��
	DrawRotaGraph(x, y, 1.0, 0.0, mario.images[displayImageNum], TRUE, isLeftDir);

}

/******************************************
* �}���I�̓��͔��胁�\�b�h
*
* �����F	�Ȃ�
* �߂�l�F	�Ȃ�
******************************************/
void Input() {
	if (Get_Key().key_flg & PAD_INPUT_B) {	// �_�b�V���t���O���I��
		setDashFlagOn();

	} else if (containFlag(mario.moveFlag, DASH__) && !(Get_Key().now_key & PAD_INPUT_B)) {	// �_�b�V���t���O���I�t
		setDashFlagOff();
	}
	
	// ���L�[��������Ă���
	if(Get_Key().now_key & PAD_INPUT_LEFT) {

		// ���L�[���������u��
		if (Get_Key().key_flg & PAD_INPUT_LEFT) {
			addFlag(mario.moveFlag, MOVE__);
			subFlag(mario.moveFlag, TURN__);

			mario.animationFreamTime = 0;

			// �X�s�[�h���E�����̎��^�[��������
			if (1.0f <= mario.speed.x && !isJump()) {
				addFlag(mario.moveFlag, TURN__);
			}

		}	// �^�[���̎��ɕ����摜�ɕύX
		else if(containFlag(mario.moveFlag, TURN__) && mario.speed.x <= 0.5f){
			subFlag(mario.moveFlag, TURN__);
			mario.speed.x = 0;
		}

		// ���ֈړ�
		mario.speed.x -= mario.acc.x;
		if (mario.speed.x < -mario.maxSpeed.x) {
			mario.speed.x = -mario.maxSpeed.x;
		}

	}	// �E�L�[��������Ă���
	else if (Get_Key().now_key & PAD_INPUT_RIGHT) {
		
		// �E�L�[�������ꂽ�u��
		if (Get_Key().key_flg & PAD_INPUT_RIGHT) {
			addFlag(mario.moveFlag, MOVE__);
			subFlag(mario.moveFlag, TURN__);

			mario.animationFreamTime = 0;

			// �X�s�[�h���������̎��^�[��������
			if (mario.speed.x  <= -1.0f && !isJump()) {
				addFlag(mario.moveFlag, TURN__);
			}

		}	// �^�[���̎��ɕ����摜�ɕύX
		else if (containFlag(mario.moveFlag, TURN__) && -0.5f <= mario.speed.x) {
			subFlag(mario.moveFlag, TURN__);
			mario.speed.x = 0;
		}

		// �E�ֈړ�
		mario.speed.x += mario.acc.x;
		if (mario.maxSpeed.x < mario.speed.x) {
			mario.speed.x = mario.maxSpeed.x;
		}

	}	// �ړ��L�[��������Ă��Ȃ�
	else {
		subFlag(mario.moveFlag, MOVE__);
	}

	
	// �W�����v�{�^���������ꂽ�u�ԂɃW�����v�t���OON
	if (!isJump() && Get_Key().key_flg & PAD_INPUT_A) {
		subFlag(mario.moveFlag, TURN__);
		addFlag(mario.moveFlag, JUMP__);
		mario.isJumpPush = true;
		mario.speed.y = -mario.jumpPower;

	}	// �W�����v�{�^���������Ă��Ȃ��t���O�ɕύX
	else  if (mario.isJumpPush && !(Get_Key().now_key & PAD_INPUT_A)) {
		mario.isJumpPush = false;
	}
}

/******************************************
* �}���I�̉��ړ�
*
* �����F	�Ȃ�
* �߂�l�F	�Ȃ�
******************************************/
void Move() {
	const float STOP_SPEED__ = 0.3f;
	if(equalFlag(mario.moveFlag, IDOL__) || (!containFlag(mario.moveFlag, MOVE__) && mario.speed.x != 0)) {
		// ���Ɉړ����Ă���ꍇ�͏��X�ɒ�~����
		if (mario.speed.x != 0) {

			// �E�ړ���
			if (0 < mario.speed.x) {
				mario.speed.x -= mario.acc.x;
				if (mario.speed.x <= STOP_SPEED__) {
					mario.speed.x = 0;
				}

			}	// ���ړ���
			else {
				mario.speed.x += mario.acc.x;
				if (-STOP_SPEED__ <= mario.speed.x) {
					mario.speed.x = 0;
				}
			}
		}
	}

	// ���ݍ��W�w�̕ۑ�
	mario.oldPosition.x = mario.nowPosition.x;
	// ���ݍ��W�w�̍X�V
	mario.nowPosition.x += mario.speed.x;
}

/******************************************
* �}���I�̃W�����v�Ɨ����ړ�
*
* �����F	�Ȃ�
* �߂�l�F	�Ȃ�
******************************************/
void Jump() {
	if (isJump() || containFlag(mario.moveFlag, JUMP__)) {

		// �W�����v�t���O��ON�ɂ���
		if (!containFlag(mario.moveFlag, JUMP__)) {
			addFlag(mario.moveFlag, JUMP__);
		}

		// �d�͂ŃW�����v�X�s�[�h������
		if (mario.speed.y < 0 && mario.isJumpPush) {
			mario.speed.y += (mario.acc.y / 2.0);
		}
		else {
			mario.speed.y += mario.acc.y;
		}

		// ������maxSpeed�ȏ�ɂȂ�Ȃ�
		if (mario.maxSpeed.y < mario.speed.y) {
			mario.speed.y = mario.maxSpeed.y;
		}

		// ���ݍ��W�x�̕ۑ�
		mario.oldPosition.y = mario.nowPosition.y;
		// ���ݍ��W�x�̍X�V
		mario.nowPosition.y += mario.speed.y;

		// ���n����
		if (mario.nowPosition.y > 200) {
			// �߂荞�܂Ȃ����W�ɏC��
			mario.nowPosition.y = 200;
			
			// �ړ����~����
			mario.speed.y = 0;

			// �t���O���I�t�ɂ���
			subFlag(mario.moveFlag, JUMP__);
			mario.isJumpPush = false;
		}
	}
}

/******************************************
* �}���I�̌����Ă���������X�V����
*
* �����F	�Ȃ�
* �߂�l�F	�Ȃ�
******************************************/
void updateDirection() {
	if (mario.speed.x != 0) {
		if (mario.speed.x < 0) {
			mario.direction = LEFT_DIR;

		}
		else {
			mario.direction = RIGHT_DIR;
		}
	}
}

/******************************************
* �}���I�̕\���摜�̔z��ԍ����擾
*
* �����F	�Ȃ�
* �߂�l�F	�Ȃ�
******************************************/
int getImageNum() {
	if (equalFlag(mario.moveFlag, IDOL__)) {
		return IDOL_IMG__;
	}

	if (containFlag(mario.moveFlag, TURN__)) {
		return TURN_IMG__;
	}

	if (containFlag(mario.moveFlag, JUMP__)) {
		return JUMP_IMG__;
	}

	if (containFlag(mario.moveFlag, MOVE__)) {
		mario.animationFreamTime++;
		int freamNum = 5;	// �A���ŕ\������t���[����
		if (containFlag(mario.moveFlag, DASH__)) {
			freamNum = 3;
		}
		return MOVE_IMG_START__ + mario.animationFreamTime % ((MOVE_IMG_END__ - MOVE_IMG_START__ + 1) * freamNum) / freamNum;
	}
}

/******************************************
* �v���C���[���擾
*
* �����F	�Ȃ�
* �߂�l�F	�萔�̃v���C���[���
******************************************/
const T_MARIO getMarioInfo() {
	return mario;
}
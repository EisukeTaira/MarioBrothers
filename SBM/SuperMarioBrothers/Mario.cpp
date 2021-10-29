#include "DxLib.h"
#include "KeyControl.h"
#include "Mario.h"

// �֐��̃v���g�^�C�v�錾
void Mario_Input();
void Mario_Move();
void Mario_Jump();
int getMarioImageNum();
void updateDirection();
inline bool isJump();
inline void Mario_Die();

static inline void addFlag(unsigned char& leftFlag, unsigned char rightFlag);
static inline void subFlag(unsigned char& leftFlag, unsigned char rightFlag);
static inline bool containFlag(unsigned char leftFlag, unsigned char rightFlag);
static inline bool equalFlag(unsigned char leftFlag, unsigned char rightFlag);

// �v���C���[�ϐ�
static T_MARIO mario;

/******************************************
* T_MARIO �̏��������\�b�h
*
* �����F	�Ȃ�
* �߂�l�F	TRUE(����I��)�AFALSE(�ُ�I��)
******************************************/
bool Mario_Init() {
    // TODO : �}���I�e�X�g�p
    KeyCtrl_Init();

    // �}���I�̉摜�ǂݍ���
    if (mario.images[0] == 0) {
        if (LoadDivGraph("images/mario.png", MARIO_IMAGE_MAX, MARIO_IMAGE_MAX, 1, MARIO_WIDTH_HEIGHT, MARIO_WIDTH_HEIGHT, mario.images) == -1) {
            // �ǂݍ��ݎ��s
            return false;
        }
    }

    // �������W
    mario.direction = RIGHT_DIR;				// ����
    mario.nowPosition.x = 0.0f;					// ���ݍ��W X
    mario.nowPosition.y = 200.0f;				// ���ݍ��W Y
    mario.oldPosition.x = mario.nowPosition.x;	// 1�t���[���O���W X
    mario.oldPosition.y = mario.nowPosition.y;	// 1�t���[���O���W Y
    mario.speed.x = 0.0f;						// X���W�̈ړ��X�s�[�h
    mario.speed.y = 0.0f;						// Y���W�̈ړ��X�s�[�h
    mario.moveStateFlag = STATE_IDOL;			// ���݂̈ړ����
    mario.animationFreamTime = 0;				// �A�j���[�V�����p�t���[���J�E���g
    mario.isJumpPush = false;					// �W�����v�{�^����������Ă��邩
    mario.isDeath = false;						// ���S�t���O
    mario.isStageClear = false;					// �X�e�[�W�N���A�t���O

    return true;
}

/******************************************
* T_MARIO �̍X�V���\�b�h
*
* �����F	�Ȃ�
* �߂�l�F	�Ȃ�
******************************************/
void Mario_Update() {

    KeyCtrl_Update();

    if (!mario.isDeath) {
        if (!mario.isStageClear) {
            Mario_Input();
            Mario_Move();
            Mario_Jump();
            updateDirection();
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
void Mario_Draw() {
    // �\���摜�̌���
    int displayImageNum = getMarioImageNum();

    // �`����W X
    int x = (int)mario.nowPosition.x + (MARIO_WIDTH_HEIGHT / 2);

    // �`����W Y
    int y = (int)mario.nowPosition.y + (MARIO_WIDTH_HEIGHT / 2);

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
void Mario_Input() {
    if (Get_Key().key_flg & PAD_INPUT_B) {	// �_�b�V���t���O���I��
        addFlag(mario.moveStateFlag, STATE_DASH);

    }
    else if (containFlag(mario.moveStateFlag, STATE_DASH) && !(Get_Key().now_key & PAD_INPUT_B)) {	// �_�b�V���t���O���I�t
        subFlag(mario.moveStateFlag, STATE_DASH);
    }

    // ���L�[��������Ă���
    if (Get_Key().now_key & PAD_INPUT_LEFT) {

        // ���L�[���������u��
        if (Get_Key().key_flg & PAD_INPUT_LEFT) {
            addFlag(mario.moveStateFlag, STATE_MOVE);
            subFlag(mario.moveStateFlag, STATE_TURN);

            // �����A�j���[�V�����̃t���[���^�C����������
            mario.animationFreamTime = 0;

            // �X�s�[�h���E�����̎��^�[��������
            if (1.0f <= mario.speed.x && !isJump()) {
                addFlag(mario.moveStateFlag, STATE_TURN);
            }

        }	// �^�[���̎��ɕ����摜�ɕύX
        else if (containFlag(mario.moveStateFlag, STATE_TURN) && mario.speed.x <= 0.5f) {
            subFlag(mario.moveStateFlag, STATE_TURN);
            mario.speed.x = 0;
        }

        // ���ֈړ�
        mario.speed.x -= WALK_ACCELERATION;

        // �ő呬�x�͒��߂��Ȃ�
        float maxSpeed = -GET_MAX_SPEED(containFlag(mario.moveStateFlag, STATE_DASH));
        if (mario.speed.x < maxSpeed) {
            mario.speed.x = maxSpeed;
        }

    }	// �E�L�[��������Ă���
    else if (Get_Key().now_key & PAD_INPUT_RIGHT) {

        // �E�L�[�������ꂽ�u��
        if (Get_Key().key_flg & PAD_INPUT_RIGHT) {
            addFlag(mario.moveStateFlag, STATE_MOVE);
            subFlag(mario.moveStateFlag, STATE_TURN);

            // �����A�j���[�V�����̃t���[���^�C����������
            mario.animationFreamTime = 0;

            // �X�s�[�h���������̎��^�[��������
            if (mario.speed.x <= -1.0f && !isJump()) {
                addFlag(mario.moveStateFlag, STATE_TURN);
            }

        }	// �^�[���̎��ɕ����摜�ɕύX
        else if (containFlag(mario.moveStateFlag, STATE_TURN) && -0.5f <= mario.speed.x) {
            subFlag(mario.moveStateFlag, STATE_TURN);
            mario.speed.x = 0;
        }

        // �E�ֈړ�
        mario.speed.x += WALK_ACCELERATION;

        // �ő呬�x�͒��߂��Ȃ�
        float maxSpeed = GET_MAX_SPEED(containFlag(mario.moveStateFlag, STATE_DASH));
        if (maxSpeed < mario.speed.x) {
            mario.speed.x = maxSpeed;
        }

    }	// �ړ��L�[��������Ă��Ȃ�
    else {
        subFlag(mario.moveStateFlag, STATE_MOVE);
    }


    // �W�����v�{�^���������ꂽ�u�ԂɃW�����v�t���OON
    if (!isJump() && Get_Key().key_flg & PAD_INPUT_A) {
        subFlag(mario.moveStateFlag, STATE_TURN);
        addFlag(mario.moveStateFlag, STATE_JUMP);
        mario.isJumpPush = true;
        mario.speed.y = GET_JUMP_POWER(containFlag(mario.moveStateFlag, STATE_JUMP));

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
void Mario_Move() {
    if (equalFlag(mario.moveStateFlag, STATE_IDOL) || (!containFlag(mario.moveStateFlag, STATE_MOVE) && mario.speed.x != 0)) {
        // ���Ɉړ����Ă���ꍇ�͏��X�ɒ�~����
        if (mario.speed.x != 0) {

            // �E�ړ���
            if (0 < mario.speed.x) {
                mario.speed.x -= FRICTION_POWER;
                if (mario.speed.x <= 0) {
                    mario.speed.x = 0;
                }

            }	// ���ړ���
            else {
                mario.speed.x += FRICTION_POWER;
                if (0 <= mario.speed.x) {
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
void Mario_Jump() {
    if (isJump() || containFlag(mario.moveStateFlag, STATE_JUMP)) {

        // �W�����v�t���O��ON�ɂ���
        if (!containFlag(mario.moveStateFlag, STATE_JUMP)) {
            addFlag(mario.moveStateFlag, STATE_JUMP);
        }

        // �W�����v�X�s�[�h���d�͂Ō�������
        if (mario.speed.y < 0 && mario.isJumpPush) {
            mario.speed.y += (GRAVITY_POWER / 2.0f);
        }
        else {
            mario.speed.y += GRAVITY_POWER;
        }

        // �����̍ō����x�ȏ�ɂȂ�Ȃ�
        if (MAX_FALL_SPEED < mario.speed.y) {
            mario.speed.y = MAX_FALL_SPEED;
        }

        // ���ݍ��W�x�̕ۑ�
        mario.oldPosition.y = mario.nowPosition.y;
        // ���ݍ��W�x�̍X�V
        mario.nowPosition.y += mario.speed.y;

        // ���n����
        if (mario.nowPosition.y > 200.0f) {
            // �߂荞�܂Ȃ����W�ɏC��
            mario.nowPosition.y = 200.0f;

            // �ړ����~����
            mario.speed.y = 0;

            // �t���O���I�t�ɂ���
            subFlag(mario.moveStateFlag, STATE_JUMP);
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
int getMarioImageNum() {
    if (equalFlag(mario.moveStateFlag, STATE_IDOL)) {
        return IDOL_IMG;
    }

    if (containFlag(mario.moveStateFlag, STATE_TURN)) {
        return TURN_IMG;
    }

    if (containFlag(mario.moveStateFlag, STATE_JUMP)) {
        return JUMP_IMG;
    }

    if (containFlag(mario.moveStateFlag, STATE_MOVE)) {
        mario.animationFreamTime++;
        int freamNum = 5;	// �A���ŕ\������t���[����

        if (containFlag(mario.moveStateFlag, STATE_DASH)) {
            freamNum = 3;
        }

        return MOVE_IMG_START + mario.animationFreamTime % ((MOVE_IMG_END - MOVE_IMG_START + 1) * freamNum) / freamNum;
    }
}

/******************************************
* �v���C���[�Ɏ擾�A�C�e����ʒm����
*
* �����F	�擾�A�C�e��
* �߂�l�F	�Ȃ�
******************************************/
void checkHitItem() {

}

/******************************************
* �v���C���[�Ɏ擾�A�C�e����ʒm����
*
* �����F	�擾�A�C�e��
* �߂�l�F	�Ȃ�
******************************************/
void getItemNotify(E_FIELD_ITEM item) {
    switch (item) {
        case SIZE_UP_MUSH:
            break;
        case LIFE_UP_MUSH:
            break;
        case FIRE_FROWER:
            break;
        case COIN:
            break;
        case ENEMY:
            break;
    }
}

/******************************************
* �v���C���[���擾
*
* �����F	�Ȃ�
* �߂�l�F	�萔�̃v���C���[���
******************************************/
const T_MARIO* getMarioInfo() {
    return &mario;
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
* �}���I�̎��S�t���O��ON�ɂ���
*
* �����F	�Ȃ�
* �߂�l�F	�Ȃ�
******************************************/
inline void Mario_Die() {
    mario.isDeath = true;
}

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
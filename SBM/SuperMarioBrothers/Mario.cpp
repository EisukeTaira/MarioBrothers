#include "DxLib.h"
#include "KeyControl.h"
#include "Mario.h"
#define SUCCESS__ 1	// ����
#define ERROR__ -1	// ���s
#define MAX_SPEED__ 5	// ���x
#define MARIO_IMAGE_MAX__ 9	//�摜�̕�����

int images[MARIO_IMAGE_MAX__];
bool leftFlag;

int Init(T_MARIO&);
void Move(T_MARIO&);
void Jump(T_MARIO&);
void changeStatus(T_MARIO&, E_MARIO_STATUS);

/******************************************
* T_MARIO �̏��������\�b�h
*
* �����FT_MARIO�@�̃C���X�^���X
* �߂�l�FTRUE(����I��)�AFALSE(�ُ�I��)
******************************************/
int Init(T_MARIO& mario) {
	if (LoadDivGraph("images/mario.png", MARIO_IMAGE_MAX__, MARIO_IMAGE_MAX__, 1, MARIO_WIDTH_HEIGHT__, MARIO_WIDTH_HEIGHT__, images) == ERROR__) {
		return ERROR__;
	}

	mario.x = 0;
	mario.y = 200;
	mario.speed = 0;
	mario.acc = 1 / (60 * 1);
	mario.status = IDOL;
	return SUCCESS__;
}

bool isInitSuccess(T_MARIO& mario) {
	KeyCtrl_Init();

	return Init(mario) == SUCCESS__;
}

void Update(T_MARIO& mario) {
	KeyCtrl_Update();
	
	switch (mario.status) {
	case IDOL:
	case MOVE:
	case JUMP:
		Move(mario);
		Jump(mario);
		break;

	case GAME_OVER:
		break;

	case GAME_CLEAR:
		break;
	}
}

void Draw(T_MARIO& mario) {
	static int animspeed = 4;
	static int animFreamCount = 0;

	
	switch (mario.status) {
	case MOVE:
		DrawRotaGraph(mario.x + (MARIO_WIDTH_HEIGHT__ / 2), mario.y + (MARIO_WIDTH_HEIGHT__ / 2), 1.0, 0.0, images[animFreamCount / animspeed % 3 + mario.status], TRUE, (mario.direction == LEFT));
		animFreamCount++;
		break;

	case GAME_CLEAR:
		DrawRotaGraph(mario.x + (MARIO_WIDTH_HEIGHT__ / 2), mario.y + (MARIO_WIDTH_HEIGHT__ / 2), 1.0, 0.0, images[animFreamCount / animspeed % 2 + mario.status], TRUE, (mario.direction == LEFT));
		animFreamCount++;
		break;

	default:
		animFreamCount = 0;
		DrawRotaGraph(mario.x + (MARIO_WIDTH_HEIGHT__ / 2), mario.y + (MARIO_WIDTH_HEIGHT__ / 2), 1.0, 0.0, images[mario.status], TRUE, (mario.direction == LEFT));

	}
	

	
}

void Input(T_MARIO& mario) {
	if (Get_Key().now_key & PAD_INPUT_LEFT || CheckHitKey(KEY_INPUT_A)) {
		mario.status = MOVE;
		mario.direction = LEFT;
		if (0 < mario.acc) {
			mario.acc = -mario.acc;
		}
	} else if (Get_Key().now_key & PAD_INPUT_RIGHT || CheckHitKey(KEY_INPUT_D)) {
		mario.status = MOVE;	// �X�e�[�^�X�ύX
		mario.direction = RIGHT;	// ��������
		if (mario.acc < 0) {
			mario.acc = -mario.acc;
		}
	} else {
		if(!(Get_Key().old_key & Get_Key().now_key)){
			if (mario.speed < 0 && mario.acc < 0) {
				mario.acc = -mario.acc;
			} else if(0 < mario.speed && 0 < mario.acc) {
				mario.acc = -mario.acc;
			}
		}
		if (mario.status != IDOL && mario.status != JUMP) {
			if (mario.speed == 0.0f) {
				mario.status = IDOL;
			} else {
				mario.speed += mario.acc;
			}
		}
	}

	if (Get_Key().key_flg & PAD_INPUT_A || CheckHitKey(KEY_INPUT_SPACE)) {
		mario.status = JUMP;
	}
}

/******************************************
* T_MARIO �̈ړ�
*
* �����FT_MARIO�@�̃C���X�^���X
* �߂�l�FTRUE(����I��)�AFALSE(�ُ�I��)
******************************************/
void Move(T_MARIO& mario) {
	if (mario.direction == RIGHT) {
		if (mario.status != TURN) {
			// ���֐i��ł����Astatus��TURN�ɂ���
			if(mario.speed < 0.0f) {
				mario.status = TURN;
			}
		} else {
			if (0.0f <= mario.speed) {
				// �E�֐i�ݎn�߂���status��TURN����MOVE�ɕύX
				mario.status = MOVE;
			}
		}
	} else {
		if (mario.status != TURN) {
			// �E�֐i��ł����Astatus��TURN�ɂ���
			if (0.0f < mario.speed) {
				mario.status = TURN;
			}
		}
		else {
			if (mario.speed <= 0.0f) {
				// ���֐i�ݎn�߂���status��TURN����MOVE�ɕύX
				mario.status = MOVE;
			}
		}
	}

	mario.speed += mario.acc;
	if (0 < mario.speed) {
		if (1.0f < mario.speed) {
			mario.speed = 1.0f;
		}
	}
	else {
		if (mario.speed < -1.0f) {
			mario.speed = -1.0f;
		}
	}
}

void Jump(T_MARIO& mario) {
	static int jumpFreamCount = 0;
	
  	if (mario.status == JUMP || (Get_Key().key_flg & PAD_INPUT_A) || CheckHitKey(KEY_INPUT_SPACE)) {
		if (jumpFreamCount++ < 15) {
			mario.y -= MAX_SPEED__;
		}
		else {
			mario.y += MAX_SPEED__;

			// �W�����v�I�������ԂŐ���B
			// �{���͒n�ʂɂ�����W�����v�I��
			if (jumpFreamCount == 30) {
				jumpFreamCount = 0;
				mario.status = IDOL;
			}
		}
	}
}


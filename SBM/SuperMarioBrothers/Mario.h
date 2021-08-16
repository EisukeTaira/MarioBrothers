#pragma once
#define MARIO_WIDTH_HEIGHT__ 32

typedef enum {
	IDOL = 0,
	MOVE,
	MOVE_END = 3,
	TURN,
	JUMP,
	GAME_OVER,
	GAME_CLEAR,
	GAME_CLEAR_END
}E_MARIO_STATUS;

typedef enum {
	LEFT = -1,
	RIGHT = 1
}E_MARIO_DIRECTION;

typedef struct {
	int x;	// ���WX
	int y;	// ���WY
	float acc;	// �����x
	float speed;	// ���x
	E_MARIO_DIRECTION direction;
	E_MARIO_STATUS status;
}T_MARIO;

bool isInitSuccess(T_MARIO&);
void Update(T_MARIO&);
void Draw(T_MARIO&);
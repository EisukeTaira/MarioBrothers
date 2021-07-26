#include "DxLib.h"
#include "KeyControl.h"

T_KEY_CTRL key_ctrl;

void KeyCtrl_Init(void) {
	key_ctrl.key_flg = 0x00U;
	key_ctrl.now_key = 0x00U;
	key_ctrl.old_key = 0x00U;
	for (unsigned char i = 0; i < INPUT_KEY_MAX; i++){
		key_ctrl.key[i] = 0x00;
	}
}
void KeyCtrl_Update(void) {
	key_ctrl.old_key = key_ctrl.now_key;
	key_ctrl.now_key = GetJoypadInputState(DX_INPUT_PAD1);
	key_ctrl.key_flg = key_ctrl.now_key & ~key_ctrl.old_key;
}

T_KEY_CTRL Get_Key(void) {
	return key_ctrl;
}
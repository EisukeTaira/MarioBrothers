#ifndef KEY_CONTROL_H__
#define KEY_CONTROL_H__

#define INPUT_KEY_MAX (0x100U)

typedef struct {
	int old_key;
	int now_key;
	int key_flg;
	char key[INPUT_KEY_MAX];
}T_KEY_CTRL;

void KeyCtrl_Init(void);
void KeyCtrl_Update(void);
T_KEY_CTRL Get_Key(void);

#endif // !KEY_CONTROL_H__

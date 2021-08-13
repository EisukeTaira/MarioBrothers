#ifndef GIMMICK_CTRL_H__
#define GIMMICK_CTRL_H__

// ç\ë¢ëÃ
typedef struct {
	int x;
	int y;
	int img;
	int mode;
	int flg;
}T_Lift;
typedef struct {
	int x;
	int y;
	int img;
	int mode;
	int flg;
}T_Firebar;
typedef struct {
	int x;
	int y;
	int img;
	int hp;
	int flg;
}T_Enemy;

void GimmickCtrl_Init(void);
void GimmickCtrl_Update(void);
void GimmickCtrl_Draw(void);
int GimmickCtrl_ImgLoad(void);

#endif // !GIMMICK_CTRL_H__

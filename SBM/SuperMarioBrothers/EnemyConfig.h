#ifndef ENEMY_CONFIG_H__
#define ENEMY_CONFIG_H__

// マクロ定義
#define GOOMBA_MAX			(32U)	// クリボー最大数
#define GOOMBA_ANIM_SIZE	(3U)	// クリボーアニメーションサイズ
#define NKNK_MAX			(8U)	// ノコノコ最大数
#define PTPT_MAX			(2U)	// パタパタ最大数
#define TROOPER_ANIM_SIZE	(6U)	// 亀アニメーションサイズ
#define PIRANHA_PLANT_MAX	(4U)	// パックンフラワー最大数
#define PLANT_ANIME_SIZE	(4U)	// パックンフラワーアニメーションサイズ
#define BOWSER_MAX			(1U)	// クッパ最大数
#define BOWSER_ANIM_SIZE	(4U)	// クッパアニメーションサイズ
#define	FLAME_ANIME_SIZE	(2U)	// 炎アニメーションサイズ


// 構造体宣言
typedef struct {
	int		x;
	int		y;
}T_Pos;
typedef struct {
	T_Pos	pos;
	int		hp;
	int		flg;
	int		dir;
}T_ENEMY;
typedef struct {
	T_ENEMY	e_info;
	int		img[GOOMBA_ANIM_SIZE];
}T_GOOMBA;
typedef struct {
	T_ENEMY	e_info;
	int		img[TROOPER_ANIM_SIZE];
}T_TROOPER;
typedef struct {
	T_ENEMY	e_info;
	int		img[PLANT_ANIME_SIZE];
}T_PLANT;
typedef struct {
	T_ENEMY	e_info;
	T_Pos	fire_pos;
	int		img[PLANT_ANIME_SIZE];
}T_BOWSER;
typedef struct {
	T_Pos	pos;
	int img[FLAME_ANIME_SIZE];
}T_BREATH;

/************************************
*　敵の初期位置テーブル設定			*
*************************************/
// ワールド敵数テーブル
const int Enemy_Table[8][4] = {
	/* 	雑魚	亀		花		王 */
	{	15,		1,		0,		0	},
	{	0,		0,		0,		0	},
	{	14,		4,		3,		0	},
	{	0,		0,		0,		0	},
	{	0,		0,		0,		0	},
	{	0,		0,		1,		0	},
	{	3,		5,		0,		0	},
	{	0,		0,		0,		1	},
};

// クリボー初期位置
const T_Pos C_Enemy_Goomba_Pos_Table[GOOMBA_MAX] = {
	/* world 1-1 (15体) */
	{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
	{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
	/* world 1-2 (14体) */
	{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
	{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
	/* world 1-3 ( 3体) */
	{0,0},{0,0},{0,0},
};
// ノコノコ＆パタパタ初期位置
const T_Pos C_Enemy_Trooper_Pos_Table[(NKNK_MAX + PTPT_MAX)] = {
	/* world 1-1 ( 1体) */
	{0,0},
	/* world 1-2 ( 4体) */
	{0,0},{0,0},{0,0},{0,0},
	/* world 1-3 ( 5体) */
	{0,0},{0,0},{0,0},{0,0},{0,0}
};
// パックンフラワー初期位置
const T_Pos C_Enemy_Plant_Pos_Table[PIRANHA_PLANT_MAX] = {
	/* world 1-2 ( 4体) */
	{0,0},{0,0},{0,0},{0,0},
};
// クッパ初期位置
const T_Pos C_Enemy_Bowser_Pos_Table[(NKNK_MAX + PTPT_MAX)] = {
	/* world 1-4 ( 1体) */
	{0,0},
};



#endif // !ENEMY_CONFIG_H__
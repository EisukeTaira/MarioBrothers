#ifndef STAGE_CONTROL_CONFIG_H__
#define STAGE_CONTROL_CONFIG_H__

#define MAP_HEIGHT		(0x0FU)		// マップ高さ
#define MAP_WIDTH		(0xFFU)		// マップ幅

enum {
	ABOVE_GROUND,					// ステージ 1-1
	UNDER_GROUND,					// ステージ 1-2
	IN_THE_AIR,						// ステージ 1-3
	INSIDE_CASTLE,					// ステージ 1-4
	WORLD_MAX
};

enum {
	NONE = 0,
	BRICK_NORMAL,					// レンガブロック(無)
	BRICK_COIN,						// レンガブロック(コイン)
	HATENA_MUSH_PW,					// ハテナブロック(PWキノコ)
	HATENA_MUSH_1UP,				// ハテナブロック(1UPキノコ)
	HATENA_STAR,					// ハテナブロック(スター)
	HATENA_COIN,					// ハテナブロック(コイン)
	HATENA_LVY,						// ハテナブロック(ツタ)
	ZHUGE_LIANG,					// 孔明ブロック
	FIRE_BAR,						// ファイアバー
	FLOOR,							// 床
	PIPE_ENTRANCE_L,				// 土管(上向き左用入口)
	PIPE_ENTRANCE_R,				// 土管(上向き右用入口)
	PIPE_ENTRANCE_U,				// 土管(左向き上用入口)
	PIPE_ENTRANCE_D,				// 土管(左向き下用入口)
	PIPE_EARTHEN_L,					// 土管(上向き左用)
	PIPE_EARTHEN_R,					// 土管(上向き右用)
	PIPE_EARTHEN_U,					// 土管(左向き上用)
	PIPE_EARTHEN_D,					// 土管(左向き下用)
	PIPE_SEAM_U,					// 土管(つなぎ目上)
	PIPE_SEAM_D,					// 土管(つなぎ目下)
	STAIRS,							// 段差ブロック
	POLE_HEAD,						// ポール先頭
	POLE_SEAM,						// ポールつなぎ目
	EXIT_GATEWAY,					// ステージの出口
	BLOCK_MAX
};

#endif
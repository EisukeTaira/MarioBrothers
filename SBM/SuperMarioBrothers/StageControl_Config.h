#ifndef STAGE_CONTROL_CONFIG_H__
#define STAGE_CONTROL_CONFIG_H__

#define MAP_HEIGHT		(0x0FU)		// マップ高さ
#define MAP_WIDTH		(0xFFU)		// マップ幅
#define ANIM_SIZE		(0x04U)

enum {
	ABOVE_GROUND,					// ステージ 1-1
	UNDER_GROUND,					// ステージ 1-2
	IN_THE_AIR,						// ステージ 1-3
	INSIDE_CASTLE,					// ステージ 1-4
	WORLD_MAX
};

enum {
	NONE = 0,					// 割り当て無し
	FLOOR,						// 床
	HATENA,						// ハテナ
	COIN = HATENA + ANIM_SIZE,	// コイン
	BRICK = COIN + ANIM_SIZE,	// レンガ
	STAIRS,						// 階段
	BLINK_,						// 空ブロック
	ZHUGE_LIANG,				// 孔明
	VARTCAL_CPIPE,				// 縦向き土管
	SIDEWAY_CPIPE = VARTCAL_CPIPE + 4,		// 横向き土管
	PIPE_JOINT = SIDEWAY_CPIPE + 4,			// 土管つなぎ目
	BLOCK_MAX = PIPE_JOINT + 2
};

#endif
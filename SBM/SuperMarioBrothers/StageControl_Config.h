#ifndef STAGE_CONTROL_CONFIG_H__
#define STAGE_CONTROL_CONFIG_H__

#define MAP_HEIGHT		(0x0FU)		// マップ高さ
#define MAP_WIDTH		(0xFFU)		// マップ幅
#define ANIM_SIZE		(0x04U)		// アニメーションサイズ

// ワールド情報
enum {
	ABOVE_GROUND,
	ABOVE_BACK,
	UNDER_GROUND,
	UNDER_START,
	UNDER_BACK,
	UNDER_GOAL,
	IN_THE_AIR,
	INSIDE_CASTLE,
	WORLD_MAX
};

// 各ブロック
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

const char C_StageName[][25] = {
	"stage/world1-1.csv",
	"stage/world1-1b.csv",
	"stage/world1-2.csv",
	"stage/world1-2s.csv",
	"stage/world1-2b.csv",
	"stage/world1-2g.csv",
	"stage/world1-3.csv",
	"stage/world1-4.csv",
};

#endif
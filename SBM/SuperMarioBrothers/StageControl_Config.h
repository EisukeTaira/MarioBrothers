#ifndef STAGE_CONTROL_CONFIG_H__
#define STAGE_CONTROL_CONFIG_H__

#define MAP_HEIGHT		(0x0FU)		// マップ高さ
#define MAP_WIDTH		(0xFFU)		// マップ幅
#define ANIM_SIZE		(0x04U)		// アニメーションサイズ

// ワールド情報
enum {
	ABOVE_GROUND,		// ワールド1-1
	ABOVE_BACK,			// 土管の中
	UNDER_GROUND,		// ワールド1-2
	UNDER_START,		// スタート地点
	UNDER_BACK,			// 土管の中
	UNDER_GOAL,			// ゴール地点
	IN_THE_AIR,			// ワールド1-3
	INSIDE_CASTLE,		// ワールド1-4
	WORLD_MAX
};

// 各ブロック
enum {
	NONE = 0,								// 割り当て無し
	FLOOR,									// 床
	HATENA,									// ハテナ
	COIN = HATENA + ANIM_SIZE,				// コイン
	BRICK = COIN + ANIM_SIZE,				// レンガ
	STAIRS,									// 階段
	BLINK_,									// 空ブロック
	ZHUGE_LIANG,							// 孔明
	VARTCAL_CPIPE,							// 縦向き土管
	SIDEWAY_CPIPE = VARTCAL_CPIPE + 4,		// 横向き土管
	PIPE_JOINT = SIDEWAY_CPIPE + 4,			// 土管つなぎ目
	MAGMA = PIPE_JOINT + 2,					// マグマ
	SLIDING_THROUGH,						// すり抜けブロック
	PILLAR = SLIDING_THROUGH + 3,			// 柱
	BLOCK_MAX
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
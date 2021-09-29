#ifndef STAGE_CONTROL_CONFIG_H__
#define STAGE_CONTROL_CONFIG_H__

#define MAP_HEIGHT			(0x0FU)						// マップ高さ
#define MAP_WIDTH			(0xFFU)						// マップ幅
#define BLOCK_SIZE			(32U)						// ブロックサイズ
#define ANIM_SIZE			(4U)						// アニメーションサイズ

#define SKY					(0U)						// 割り当て無し
#define FLOOR				(1U)						// 床
#define FLOOR_UNDER			(2U)						// 床(地下)
#define HATENA				(3U)						// ハテナ
#define HATENA_UNDER		(7U)						// ハテナ(地下)
#define COIN				(11U)						// コイン
#define COIN_UNDER			(15U)						// コイン(地下)
#define BRICK				(19U)						// レンガ
#define BRICK_UNDER			(20U)						// レンガ(地下)
#define STAIRS				(21U)						// 階段
#define STAIRS_UNDER		(22U)						// 階段(地下)
#define BLINK				(23U)						// 空ブロック
#define BLINK_UNDER			(24U)						// 空ブロック(地下)
#define ZHUGE_LIANG			(25U)						// 孔明
#define POLE_HEAD			(26U)						// ポールの先頭
#define POLE_DOWN			(27U)						// ポールの支柱
#define POLE_FLAG			(28U)						// ポールの旗
#define VARTCAL_CPIPE		(29U)						// 縦向き土管
#define SIDEWAY_CPIPE		(33U)						// 横向き土管
#define PIPE_JOINT			(37U)						// 土管つなぎ目
#define GLASS				(39U)						// 草(風景)
#define MOUNTAIN			(42U)						// 山(風景)
#define CLOUD				(48U)						// 雲(風景)
#define BRIDGE				(56U)						// 桟橋
#define MAGMA				(57U)						// マグマ
#define CASTLE_WALL			(59U)						// 壁・地面
#define SLIDING_THROUGH		(60U)						// すり抜けブロック
#define PILLAR				(63U)						// 柱
#define BLOCK_MAX			(64U)

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
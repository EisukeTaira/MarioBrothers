#pragma once

// 画像情報
#define MARIO_WIDTH_HEIGHT		(32)			// 画像の幅
#define MARIO_IMAGE_MAX			(9)				// 画像の分割数
// 画像の添え字
#define IDOL_IMG				(0)				// 棒立ち
#define MOVE_IMG_START			(1)				// 最初の移動画像
#define MOVE_IMG_END			(3)				// 最後の移動画像
#define TURN_IMG				(4)				// ターン
#define JUMP_IMG				(5)				// ジャンプ

// 移動状態を表すフラグ定数
#define STATE_IDOL				(0b0000U)		// 棒立ち
#define STATE_MOVE				(0b0001U)		// 移動
#define STATE_DASH				(0b0010U)		// ダッシュ
#define STATE_TURN				(0b0100U)		// ターン
#define STATE_JUMP				(0b1000U)		// ジャンプ

// ステータス
#define WALK_ACCELERATION		(0.2f)			// 移動の加速度
#define MAX_WALK_SPEED			(3.0f)			// 通常時の最高速度
#define MAX_DASH_SPEED			(5.0f)			// ダッシュ時の最高速度
#define FRICTION_POWER			(0.2f)			// 摩擦
#define IDOL_JUMP_POWER			(10.0f)			// 通常時のジャンプ力
#define DASH_JUMP_POWER			(13.0f)			// ダッシュ時のジャンプ力
#define GRAVITY_POWER			(1.0f)			// 重力
#define MAX_FALL_SPEED			(8.0f)			// 落下の最高速度

// ゲッター
#define GET_MAX_SPEED(DASH_FLG) (DASH_FLG ? MAX_DASH_SPEED : MAX_WALK_SPEED)		// 最高速度取得
#define GET_JUMP_POWER(DASH_FLG) (DASH_FLG ? -IDOL_JUMP_POWER : -DASH_JUMP_POWER)		// ジャンプ力取得

// 方向指定の列挙
typedef enum {
	LEFT_DIR = -1,
	RIGHT_DIR = 1
}E_MARIO_DIR;

// 座標の構造体
typedef struct {
	float x;
	float y;
}T_COORDINATE;

// マリオの構造体
typedef struct {
	int images[MARIO_IMAGE_MAX];	// マリオの画像
	E_MARIO_DIR direction;			// 左右の向き
	T_COORDINATE oldPosition;		// 1フレーム前の座標
	T_COORDINATE nowPosition;		// 現在座標
	T_COORDINATE speed;				// 速度　座標に加算する値
	unsigned char moveStateFlag;	// 移動状態
	int animationFreamTime;			// アニメーション用フレームカウント
	bool isJumpPush;				// ジャンプボタンを押しているかどうか
	bool isStageClear;				// ステージクリアのフラグ
	bool isDeath;					// GameOverのフラグ
}T_MARIO;

// プロトタイプ宣言
bool Mario_Init();					// マリオの初期化
void Mario_Update();				// マリオの更新処理
void Mario_Draw();					// マリオの描画処理
const T_MARIO* getMarioInfo();		// マリオの情報取得

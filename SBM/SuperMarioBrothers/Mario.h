#pragma once

// 画像系定数
#define MARIO_WIDTH_HEIGHT__ 32	// 画像の幅
#define MARIO_IMAGE_MAX__ 9		// 画像の分割数

// 画像の添え字
#define IDOL_IMG__ 0			// 棒立ち
#define MOVE_IMG_START__ 1		// 最初の移動画像
#define MOVE_IMG_END__ 3		// 最後の移動画像
#define TURN_IMG__ 4			// ターン
#define JUMP_IMG__ 5			// ジャンプ

// 移動状態を表す定数
#define IDOL__ 0x00U			// 棒立ち
#define MOVE__ 0x01U			// 移動
#define DASH__ 0x02U			// ダッシュ
#define TURN__ 0x04U			// ターン
#define JUMP__ 0x08U			// ジャンプ

// ステータス
#define MAX_WALK_SPEED__ 3		// 通常時の最高速度
#define MAX_DASH_SPEED__ 5		// ダッシュ時の最高速度
#define JUMP_POWER__ 10			// 通常時のジャンプ力
#define DASH_JUMP_POWER__ 13	// ダッシュ時のジャンプ力

// 真偽
#define SUCCESS__ 1	// 成功
#define ERROR__ -1	// 失敗

// 方向指定の列挙
typedef enum {
	LEFT_DIR = -1,
	RIGHT_DIR = 1
}E_MARIO_DIRECTION;

// 座標の構造体
typedef struct {
	float x;
	float y;
}T_COORDINATE;

// マリオの構造体
typedef struct {
	T_COORDINATE oldPosition;		// 1フレーム前の座標
	T_COORDINATE nowPosition;		// 現在座標
	T_COORDINATE speed;				// 速度　座標に加算する値
	T_COORDINATE maxSpeed;			// 最大速度　スピードの上限値
	T_COORDINATE acc;				// 加速度　スピードに加算する値
	float jumpPower;				// ジャンプ力
	
	bool isJumpPush;				// ジャンプボタンを押しているかどうか
	bool isStageClear;				// ステージクリアのフラグ
	bool isDeath;					// GameOverのフラグ

	unsigned char moveFlag;		// 移動状態
	E_MARIO_DIRECTION direction;	// 左右の向き

	int animationFreamTime;			// アニメーション用フレームカウント
	int images[MARIO_IMAGE_MAX__];	// マリオの画像

	
}T_MARIO;

// 初期化メソッド
inline bool isMarioInitSuccess() {
	int marioInit();
	return (marioInit() == SUCCESS__);
}

// 更新処理
void Update();

// 描画処理
void Draw();

const T_MARIO getMarioInfo();
#include "DxLib.h"
#include "KeyControl.h"
#include "Mario.h"

// プレイヤー変数
T_MARIO mario;

// 関数のプロトタイプ宣言
void Input();
void Move();
void Jump();
int getImageNum();
void updateDirection();

/******************************************
* 左辺のフラグに右辺のフラグを追加
*
* 引数：	leftFlag 左辺のフラグ
*			rightFlag 右辺のフラグ
* 戻り値：	なし
******************************************/
inline void addFlag(unsigned char& leftFlag, unsigned char rightFlag) {
	leftFlag |= rightFlag;
}

/******************************************
* 左辺のフラグから右辺のフラグを削除
*
* 引数：	leftFlag 左辺のフラグ
*			rightFlag 右辺のフラグ
* 戻り値：	なし
******************************************/
inline void subFlag(unsigned char& leftFlag, unsigned char rightFlag) {
	leftFlag &= ~rightFlag;
}

/******************************************
* 左辺のフラグに右辺のフラグが含まれているかどうか
*
* 引数：	leftFlag 左辺のフラグ
*			rightFlag 右辺のフラグ
* 戻り値：	TRUE 含まれている
*			FALSE 含まれていない
******************************************/
inline bool containFlag(unsigned char leftFlag, unsigned char rightFlag) {
	return leftFlag & rightFlag;
}

/******************************************
* 左辺のフラグと右辺のフラグが完全一致
*
* 引数：	leftFlag 左辺のフラグ
*			rightFlag 右辺のフラグ
* 戻り値：	TRUE 完全一致
*			FALSE 完全一致以外
******************************************/
inline bool equalFlag(unsigned char leftFlag, unsigned char rightFlag) {
	return leftFlag == rightFlag;
}

/******************************************
* マリオの死亡フラグをONにする
*
* 引数：	なし
* 戻り値：	なし
******************************************/
inline void marioDie() {
	mario.isDeath = true;
}

/******************************************
* マリオの死亡フラグを取得する
*
* 引数：	なし
* 戻り値：	マリオの死亡フラグ
******************************************/
inline const bool getMarioDeathFlag() {
	return mario.isDeath;
}

/******************************************
* マリオのステージクリアフラグを取得する
*
* 引数：	なし
* 戻り値：	マリオのステージクリアフラグ
******************************************/
inline const bool getMarioStageClearFlag() {
	return mario.isStageClear;
}

/******************************************
* マリオのダッシュフラグをオンにする
*
* 引数：	なし
* 戻り値：	なし
******************************************/
inline void setDashFlagOn() {
	addFlag(mario.moveFlag, DASH__);
	mario.maxSpeed.x = MAX_DASH_SPEED__;
	mario.jumpPower = DASH_JUMP_POWER__;
}

/******************************************
* マリオのダッシュフラグをオフにする
*
* 引数：	なし
* 戻り値：	なし
******************************************/
inline void setDashFlagOff() {
	subFlag(mario.moveFlag, DASH__);
	mario.maxSpeed.x = MAX_WALK_SPEED__;
	mario.jumpPower = JUMP_POWER__;
}

/******************************************
* マリオがジャンプ中かどうか取得する
*
* 引数：	なし
* 戻り値：	TRUE(ジャンプ中)、FALSE(地面にいる)
******************************************/
inline bool isJump() {
	return (mario.oldPosition.y != mario.nowPosition.y);
}

/******************************************
* T_MARIO の初期化メソッド
*
* 引数：	なし
* 戻り値：	TRUE(正常終了)、FALSE(異常終了)
******************************************/
int marioInit() {
	// TODO : マリオテスト用
	KeyCtrl_Init();

	// マリオの画像読み込み
	if(mario.images[0] == 0) {
		if (LoadDivGraph("images/mario.png", MARIO_IMAGE_MAX__, MARIO_IMAGE_MAX__, 1, MARIO_WIDTH_HEIGHT__, MARIO_WIDTH_HEIGHT__, mario.images) == ERROR__) {
			// 読み込み失敗
			return ERROR__;
		}
	}

	// 初期座標
	mario.nowPosition.x = 0;	// 現在座標 X
	mario.nowPosition.y = 200;	// 現在座標 Y
	mario.oldPosition.x = mario.nowPosition.x;	// 1フレーム前座標 X
	mario.oldPosition.y = mario.nowPosition.y;	// 1フレーム前座標 Y

	mario.speed.x = 0;	// X座標の移動スピード
	mario.speed.y = 0;	// Y座標の移動スピード
	mario.maxSpeed.x = 5;	// X座標の最大スピード
	mario.maxSpeed.y = 8;	// Y座標の最大スピード

	mario.acc.x = 0.2f;	// 加速度X
	mario.acc.y = 1.0f;	// 加速度Y
	mario.jumpPower = JUMP_POWER__;

	mario.moveFlag = IDOL__;	// 現在のモード
	mario.direction = RIGHT_DIR;	// 向き

	// 各フラグはオフ
	mario.isJumpPush = false;	// ジャンプボタンが押されているか
	mario.isDeath = false;	// 死亡フラグ
	mario.isStageClear = false;	// ステージクリアフラグ

	mario.animationFreamTime = 0;	// アニメーション用フレームカウント
	

	return SUCCESS__;
}

/******************************************
* T_MARIO の更新メソッド
*
* 引数：	なし
* 戻り値：	なし
******************************************/
void Update() {

	KeyCtrl_Update();
	
	if (!getMarioDeathFlag()) {
		if (!getMarioStageClearFlag()) {
			Input();
			Move();
			Jump();
		}
		else {
			// ステージクリア処理
		}
	}
	else {
		// 死亡処理
	}
}

/******************************************
* T_MARIO の描画メソッド
*
* 引数：	なし
* 戻り値：	なし
******************************************/
void Draw() {
	// 左右の向き決定
	updateDirection();


	// 表示画像の決定
	int displayImageNum = getImageNum();
		//mario.imageNum;
	//if (mario.moveFlag & MOVE__ && (~mario.moveFlag & JUMP__) && (~mario.moveFlag & TURN__)) {
	//	// MOVE__の時だけアニメーションにする
	//	displayImageNum += mario.animationWalkAddNum;
	//}

	// 描画座標 X
	int x = (int)mario.nowPosition.x + (MARIO_WIDTH_HEIGHT__ / 2);
	// 描画座標 Y
	int y = (int)mario.nowPosition.y + (MARIO_WIDTH_HEIGHT__ / 2);
	// 向き (左 = TRUE, 右 = FALSE)
	bool isLeftDir = (mario.direction == LEFT_DIR);

	// マリオを描画
	DrawRotaGraph(x, y, 1.0, 0.0, mario.images[displayImageNum], TRUE, isLeftDir);

}

/******************************************
* マリオの入力判定メソッド
*
* 引数：	なし
* 戻り値：	なし
******************************************/
void Input() {
	if (Get_Key().key_flg & PAD_INPUT_B) {	// ダッシュフラグをオン
		setDashFlagOn();

	} else if (containFlag(mario.moveFlag, DASH__) && !(Get_Key().now_key & PAD_INPUT_B)) {	// ダッシュフラグをオフ
		setDashFlagOff();
	}
	
	// 左キーが押されている
	if(Get_Key().now_key & PAD_INPUT_LEFT) {

		// 左キーを押した瞬間
		if (Get_Key().key_flg & PAD_INPUT_LEFT) {
			addFlag(mario.moveFlag, MOVE__);
			subFlag(mario.moveFlag, TURN__);

			mario.animationFreamTime = 0;

			// スピードが右方向の時ターンさせる
			if (1.0f <= mario.speed.x && !isJump()) {
				addFlag(mario.moveFlag, TURN__);
			}

		}	// ターンの時に歩く画像に変更
		else if(containFlag(mario.moveFlag, TURN__) && mario.speed.x <= 0.5f){
			subFlag(mario.moveFlag, TURN__);
			mario.speed.x = 0;
		}

		// 左へ移動
		mario.speed.x -= mario.acc.x;
		if (mario.speed.x < -mario.maxSpeed.x) {
			mario.speed.x = -mario.maxSpeed.x;
		}

	}	// 右キーが押されている
	else if (Get_Key().now_key & PAD_INPUT_RIGHT) {
		
		// 右キーが押された瞬間
		if (Get_Key().key_flg & PAD_INPUT_RIGHT) {
			addFlag(mario.moveFlag, MOVE__);
			subFlag(mario.moveFlag, TURN__);

			mario.animationFreamTime = 0;

			// スピードが左方向の時ターンさせる
			if (mario.speed.x  <= -1.0f && !isJump()) {
				addFlag(mario.moveFlag, TURN__);
			}

		}	// ターンの時に歩く画像に変更
		else if (containFlag(mario.moveFlag, TURN__) && -0.5f <= mario.speed.x) {
			subFlag(mario.moveFlag, TURN__);
			mario.speed.x = 0;
		}

		// 右へ移動
		mario.speed.x += mario.acc.x;
		if (mario.maxSpeed.x < mario.speed.x) {
			mario.speed.x = mario.maxSpeed.x;
		}

	}	// 移動キーが押されていない
	else {
		subFlag(mario.moveFlag, MOVE__);
	}

	
	// ジャンプボタンが押された瞬間にジャンプフラグON
	if (!isJump() && Get_Key().key_flg & PAD_INPUT_A) {
		subFlag(mario.moveFlag, TURN__);
		addFlag(mario.moveFlag, JUMP__);
		mario.isJumpPush = true;
		mario.speed.y = -mario.jumpPower;

	}	// ジャンプボタンが押していないフラグに変更
	else  if (mario.isJumpPush && !(Get_Key().now_key & PAD_INPUT_A)) {
		mario.isJumpPush = false;
	}
}

/******************************************
* マリオの横移動
*
* 引数：	なし
* 戻り値：	なし
******************************************/
void Move() {
	const float STOP_SPEED__ = 0.3f;
	if(equalFlag(mario.moveFlag, IDOL__) || (!containFlag(mario.moveFlag, MOVE__) && mario.speed.x != 0)) {
		// 横に移動している場合は徐々に停止する
		if (mario.speed.x != 0) {

			// 右移動中
			if (0 < mario.speed.x) {
				mario.speed.x -= mario.acc.x;
				if (mario.speed.x <= STOP_SPEED__) {
					mario.speed.x = 0;
				}

			}	// 左移動中
			else {
				mario.speed.x += mario.acc.x;
				if (-STOP_SPEED__ <= mario.speed.x) {
					mario.speed.x = 0;
				}
			}
		}
	}

	// 現在座標Ｘの保存
	mario.oldPosition.x = mario.nowPosition.x;
	// 現在座標Ｘの更新
	mario.nowPosition.x += mario.speed.x;
}

/******************************************
* マリオのジャンプと落下移動
*
* 引数：	なし
* 戻り値：	なし
******************************************/
void Jump() {
	if (isJump() || containFlag(mario.moveFlag, JUMP__)) {

		// ジャンプフラグをONにする
		if (!containFlag(mario.moveFlag, JUMP__)) {
			addFlag(mario.moveFlag, JUMP__);
		}

		// 重力でジャンプスピードを減衰
		if (mario.speed.y < 0 && mario.isJumpPush) {
			mario.speed.y += (mario.acc.y / 2.0);
		}
		else {
			mario.speed.y += mario.acc.y;
		}

		// 落下がmaxSpeed以上にならない
		if (mario.maxSpeed.y < mario.speed.y) {
			mario.speed.y = mario.maxSpeed.y;
		}

		// 現在座標Ｙの保存
		mario.oldPosition.y = mario.nowPosition.y;
		// 現在座標Ｙの更新
		mario.nowPosition.y += mario.speed.y;

		// 着地処理
		if (mario.nowPosition.y > 200) {
			// めり込まない座標に修正
			mario.nowPosition.y = 200;
			
			// 移動を停止する
			mario.speed.y = 0;

			// フラグをオフにする
			subFlag(mario.moveFlag, JUMP__);
			mario.isJumpPush = false;
		}
	}
}

/******************************************
* マリオの向いている方向を更新する
*
* 引数：	なし
* 戻り値：	なし
******************************************/
void updateDirection() {
	if (mario.speed.x != 0) {
		if (mario.speed.x < 0) {
			mario.direction = LEFT_DIR;

		}
		else {
			mario.direction = RIGHT_DIR;
		}
	}
}

/******************************************
* マリオの表示画像の配列番号を取得
*
* 引数：	なし
* 戻り値：	なし
******************************************/
int getImageNum() {
	if (equalFlag(mario.moveFlag, IDOL__)) {
		return IDOL_IMG__;
	}

	if (containFlag(mario.moveFlag, TURN__)) {
		return TURN_IMG__;
	}

	if (containFlag(mario.moveFlag, JUMP__)) {
		return JUMP_IMG__;
	}

	if (containFlag(mario.moveFlag, MOVE__)) {
		mario.animationFreamTime++;
		int freamNum = 5;	// 連続で表示するフレーム数
		if (containFlag(mario.moveFlag, DASH__)) {
			freamNum = 3;
		}
		return MOVE_IMG_START__ + mario.animationFreamTime % ((MOVE_IMG_END__ - MOVE_IMG_START__ + 1) * freamNum) / freamNum;
	}
}

/******************************************
* プレイヤー情報取得
*
* 引数：	なし
* 戻り値：	定数のプレイヤー情報
******************************************/
const T_MARIO getMarioInfo() {
	return mario;
}
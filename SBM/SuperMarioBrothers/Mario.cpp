#include "DxLib.h"
#include "KeyControl.h"
#include "Mario.h"

// 関数のプロトタイプ宣言
void Mario_Input();
void Mario_Move();
void Mario_Jump();
int getMarioImageNum();
void updateDirection();
inline bool isJump();
inline void Mario_Die();

static inline void addFlag(unsigned char& leftFlag, unsigned char rightFlag);
static inline void subFlag(unsigned char& leftFlag, unsigned char rightFlag);
static inline bool containFlag(unsigned char leftFlag, unsigned char rightFlag);
static inline bool equalFlag(unsigned char leftFlag, unsigned char rightFlag);

// プレイヤー変数
static T_MARIO mario;

/******************************************
* T_MARIO の初期化メソッド
*
* 引数：	なし
* 戻り値：	TRUE(正常終了)、FALSE(異常終了)
******************************************/
bool Mario_Init() {
    // TODO : マリオテスト用
    KeyCtrl_Init();

    // マリオの画像読み込み
    if (mario.images[0] == 0) {
        if (LoadDivGraph("images/mario.png", MARIO_IMAGE_MAX, MARIO_IMAGE_MAX, 1, MARIO_WIDTH_HEIGHT, MARIO_WIDTH_HEIGHT, mario.images) == -1) {
            // 読み込み失敗
            return false;
        }
    }

    // 初期座標
    mario.direction = RIGHT_DIR;				// 向き
    mario.nowPosition.x = 0.0f;					// 現在座標 X
    mario.nowPosition.y = 200.0f;				// 現在座標 Y
    mario.oldPosition.x = mario.nowPosition.x;	// 1フレーム前座標 X
    mario.oldPosition.y = mario.nowPosition.y;	// 1フレーム前座標 Y
    mario.speed.x = 0.0f;						// X座標の移動スピード
    mario.speed.y = 0.0f;						// Y座標の移動スピード
    mario.moveStateFlag = STATE_IDOL;			// 現在の移動状態
    mario.animationFreamTime = 0;				// アニメーション用フレームカウント
    mario.isJumpPush = false;					// ジャンプボタンが押されているか
    mario.isDeath = false;						// 死亡フラグ
    mario.isStageClear = false;					// ステージクリアフラグ

    return true;
}

/******************************************
* T_MARIO の更新メソッド
*
* 引数：	なし
* 戻り値：	なし
******************************************/
void Mario_Update() {

    KeyCtrl_Update();

    if (!mario.isDeath) {
        if (!mario.isStageClear) {
            Mario_Input();
            Mario_Move();
            Mario_Jump();
            updateDirection();
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
void Mario_Draw() {
    // 表示画像の決定
    int displayImageNum = getMarioImageNum();

    // 描画座標 X
    int x = (int)mario.nowPosition.x + (MARIO_WIDTH_HEIGHT / 2);

    // 描画座標 Y
    int y = (int)mario.nowPosition.y + (MARIO_WIDTH_HEIGHT / 2);

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
void Mario_Input() {
    if (Get_Key().key_flg & PAD_INPUT_B) {	// ダッシュフラグをオン
        addFlag(mario.moveStateFlag, STATE_DASH);

    }
    else if (containFlag(mario.moveStateFlag, STATE_DASH) && !(Get_Key().now_key & PAD_INPUT_B)) {	// ダッシュフラグをオフ
        subFlag(mario.moveStateFlag, STATE_DASH);
    }

    // 左キーが押されている
    if (Get_Key().now_key & PAD_INPUT_LEFT) {

        // 左キーを押した瞬間
        if (Get_Key().key_flg & PAD_INPUT_LEFT) {
            addFlag(mario.moveStateFlag, STATE_MOVE);
            subFlag(mario.moveStateFlag, STATE_TURN);

            // 歩くアニメーションのフレームタイムを初期化
            mario.animationFreamTime = 0;

            // スピードが右方向の時ターンさせる
            if (1.0f <= mario.speed.x && !isJump()) {
                addFlag(mario.moveStateFlag, STATE_TURN);
            }

        }	// ターンの時に歩く画像に変更
        else if (containFlag(mario.moveStateFlag, STATE_TURN) && mario.speed.x <= 0.5f) {
            subFlag(mario.moveStateFlag, STATE_TURN);
            mario.speed.x = 0;
        }

        // 左へ移動
        mario.speed.x -= WALK_ACCELERATION;

        // 最大速度は超過しない
        float maxSpeed = -GET_MAX_SPEED(containFlag(mario.moveStateFlag, STATE_DASH));
        if (mario.speed.x < maxSpeed) {
            mario.speed.x = maxSpeed;
        }

    }	// 右キーが押されている
    else if (Get_Key().now_key & PAD_INPUT_RIGHT) {

        // 右キーが押された瞬間
        if (Get_Key().key_flg & PAD_INPUT_RIGHT) {
            addFlag(mario.moveStateFlag, STATE_MOVE);
            subFlag(mario.moveStateFlag, STATE_TURN);

            // 歩くアニメーションのフレームタイムを初期化
            mario.animationFreamTime = 0;

            // スピードが左方向の時ターンさせる
            if (mario.speed.x <= -1.0f && !isJump()) {
                addFlag(mario.moveStateFlag, STATE_TURN);
            }

        }	// ターンの時に歩く画像に変更
        else if (containFlag(mario.moveStateFlag, STATE_TURN) && -0.5f <= mario.speed.x) {
            subFlag(mario.moveStateFlag, STATE_TURN);
            mario.speed.x = 0;
        }

        // 右へ移動
        mario.speed.x += WALK_ACCELERATION;

        // 最大速度は超過しない
        float maxSpeed = GET_MAX_SPEED(containFlag(mario.moveStateFlag, STATE_DASH));
        if (maxSpeed < mario.speed.x) {
            mario.speed.x = maxSpeed;
        }

    }	// 移動キーが押されていない
    else {
        subFlag(mario.moveStateFlag, STATE_MOVE);
    }


    // ジャンプボタンが押された瞬間にジャンプフラグON
    if (!isJump() && Get_Key().key_flg & PAD_INPUT_A) {
        subFlag(mario.moveStateFlag, STATE_TURN);
        addFlag(mario.moveStateFlag, STATE_JUMP);
        mario.isJumpPush = true;
        mario.speed.y = GET_JUMP_POWER(containFlag(mario.moveStateFlag, STATE_JUMP));

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
void Mario_Move() {
    if (equalFlag(mario.moveStateFlag, STATE_IDOL) || (!containFlag(mario.moveStateFlag, STATE_MOVE) && mario.speed.x != 0)) {
        // 横に移動している場合は徐々に停止する
        if (mario.speed.x != 0) {

            // 右移動中
            if (0 < mario.speed.x) {
                mario.speed.x -= FRICTION_POWER;
                if (mario.speed.x <= 0) {
                    mario.speed.x = 0;
                }

            }	// 左移動中
            else {
                mario.speed.x += FRICTION_POWER;
                if (0 <= mario.speed.x) {
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
void Mario_Jump() {
    if (isJump() || containFlag(mario.moveStateFlag, STATE_JUMP)) {

        // ジャンプフラグをONにする
        if (!containFlag(mario.moveStateFlag, STATE_JUMP)) {
            addFlag(mario.moveStateFlag, STATE_JUMP);
        }

        // ジャンプスピードを重力で減衰する
        if (mario.speed.y < 0 && mario.isJumpPush) {
            mario.speed.y += (GRAVITY_POWER / 2.0f);
        }
        else {
            mario.speed.y += GRAVITY_POWER;
        }

        // 落下の最高速度以上にならない
        if (MAX_FALL_SPEED < mario.speed.y) {
            mario.speed.y = MAX_FALL_SPEED;
        }

        // 現在座標Ｙの保存
        mario.oldPosition.y = mario.nowPosition.y;
        // 現在座標Ｙの更新
        mario.nowPosition.y += mario.speed.y;

        // 着地処理
        if (mario.nowPosition.y > 200.0f) {
            // めり込まない座標に修正
            mario.nowPosition.y = 200.0f;

            // 移動を停止する
            mario.speed.y = 0;

            // フラグをオフにする
            subFlag(mario.moveStateFlag, STATE_JUMP);
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
int getMarioImageNum() {
    if (equalFlag(mario.moveStateFlag, STATE_IDOL)) {
        return IDOL_IMG;
    }

    if (containFlag(mario.moveStateFlag, STATE_TURN)) {
        return TURN_IMG;
    }

    if (containFlag(mario.moveStateFlag, STATE_JUMP)) {
        return JUMP_IMG;
    }

    if (containFlag(mario.moveStateFlag, STATE_MOVE)) {
        mario.animationFreamTime++;
        int freamNum = 5;	// 連続で表示するフレーム数

        if (containFlag(mario.moveStateFlag, STATE_DASH)) {
            freamNum = 3;
        }

        return MOVE_IMG_START + mario.animationFreamTime % ((MOVE_IMG_END - MOVE_IMG_START + 1) * freamNum) / freamNum;
    }
}

/******************************************
* プレイヤーに取得アイテムを通知する
*
* 引数：	取得アイテム
* 戻り値：	なし
******************************************/
void checkHitItem() {

}

/******************************************
* プレイヤーに取得アイテムを通知する
*
* 引数：	取得アイテム
* 戻り値：	なし
******************************************/
void getItemNotify(E_FIELD_ITEM item) {
    switch (item) {
        case SIZE_UP_MUSH:
            break;
        case LIFE_UP_MUSH:
            break;
        case FIRE_FROWER:
            break;
        case COIN:
            break;
        case ENEMY:
            break;
    }
}

/******************************************
* プレイヤー情報取得
*
* 引数：	なし
* 戻り値：	定数のプレイヤー情報
******************************************/
const T_MARIO* getMarioInfo() {
    return &mario;
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
* マリオの死亡フラグをONにする
*
* 引数：	なし
* 戻り値：	なし
******************************************/
inline void Mario_Die() {
    mario.isDeath = true;
}

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
/* 2024.12.26 駒沢風助 ファイル作成 */
/* 2025.01.10 菊池雅道 初期化処理追加  */
/* 2025.01.22 菊池雅道 初期化処理追加  */
/* 2025.02.10 菊池雅道 初期化処理追加 */
/* 2025.02.11 菊池雅道 初期化処理追加 */
/* 2025.02.22 菊池雅道 初期化処理追加 */

#include "DataList_PlayerStatus.h"

/* プレイヤーステータス管理クラスの定義 */

// コンストラクタ
DataList_PlayerStatus::DataList_PlayerStatus() : DataListBase("DataList_PlayerStatus")
{
	/* 初期化(仮) */
	/* プレイヤー状態関連 */
	this->iPlayerMoveState					= PLAYER_MOVESTATUS_FREE;			// プレイヤーの移動状態
	this->iPlayerAttackState				= PLAYER_ATTACKSTATUS_FREE;			// プレイヤーの攻撃状態
	this->bPlayerLandingFlg					= false;							// プレイヤーが着地しているか
	this->fPlayerNowMoveSpeed				= 0;								// プレイヤーの現在の移動速度
	this->fPlayerAngleX						= 0;								// プレイヤーのX軸回転量(ラジアン)
	this->fPlayerTurnSpeed					= PLAYER_TURN_SPEED;				// プレイヤーの方向転換の速度										/* 2025.02.10 菊池雅道 初期化処理追加 */
	this->fPlayerNowFallSpeed				= 0;								// プレイヤーの現在の落下速度
	this->iPlayerNowJumpCount				= 0;								// プレイヤーのジャンプ回数(現在数)
	this->iPlayerNormalDashFlameCount		= 0;								//通常ダッシュ時経過フレーム数（高速ダッシュへの移行に使用			/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->bPlayerJumpingFlag				= false;							//プレイヤーがジャンプ中かのフラグ									/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->iPlayerJumpCount					= 0;								//プレイヤーの現在のジャンプ回数									/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->fPlayerDodgeProgress				= 0.0f;								//プレイヤー回避モーション進行度									/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->vecPlayerDodgeDirection			= { 0, 0, 0 };						//プレイヤー回避方向												/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->iPlayerDodgeWhileJumpingCount		= 0;								//プレイヤージャンプ中の回避回数									/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->fPlayerJumpSpeed					= 0;								//プレイヤージャンプ速度											/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->iPlayerNowDodgeFlame				= 0;								//プレイヤーの現在の回避フレーム数									/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->fPlayerDodgeSpeed					= 0;								//プレイヤー回避速度												/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->bPlayerAfterDodgeFlag				= false;							//プレイヤーの回避後フラグ											/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->bPlayerKickWallFlg				= false;							//プレイヤーが壁を蹴ったかのフラグ									/* 2025.02.22 菊池雅道 初期化処理追加 */
	this->iPlayerAfterKickWallCount			= 0;								//プレイヤーが壁を蹴った後のカウント								/* 2025.02.22 菊池雅道 初期化処理追加 */
	this->bPlayerAfterKickWallFlg			= false;							//プレイヤーが壁を蹴った後のフラグ									/* 2025.02.22 菊池雅道 初期化処理追加 */
	this->iPlayerNowAttakChargeFlame		= 0;								//現在のプレイヤー溜め攻撃チャージフレーム数						/* 2025.01.22 菊池雅道 初期化処理追加 */
	this->vecPlayerChargeAttakTargetMove	= { 0, 0, 0 };						//プレイヤー溜め攻撃の目的地										/* 2025.01.22 菊池雅道 初期化処理追加 */
	this->iPlayerChargeAttackCount			= 0;								// 近接攻撃(強)のカウント
	this->pLockOnEnemy						= nullptr;							// ロックオン対象のエネミー
	this->iPlayerNowHp						= INIT_ATTRIBUTES_HP_MAX;			// プレイヤーの現在のHP
	this->iPlayerNowInvincibleTime			= 0;								// プレイヤーの現在の残り無敵時間
	this->iPlayerComboNowCount				= 0;								// プレイヤーの現在のコンボ数
	this->iPlayerComboMaxCount				= 0;								// プレイヤーの最大コンボ数
	this->iPlayerComboDuration				= 0;								// プレイヤーのコンボの残り持続時間
	this->bPlayerAimCancelledFlg			= false;							// 遠距離攻撃(構え)がキャンセルされたかのフラグ		/* 2025.02.11 菊池雅道 初期化処理追加 */
	this->bPlayerDeadFlg					= false;							// プレイヤー死亡フラグ

	/* プレイヤーモーション関連 */
	this->iPlayerMotion_Move				= MOTION_ID_MOVE_WAIT;				// プレイヤーモーション(移動系)
	this->iPlayerMotion_Move_Old			= -1;								// 変更前プレイヤーモーション(移動系)
	this->iPlayerMotion_Attack				= MOTION_ID_ATTACK_NONE;			// プレイヤーモーション(攻撃系)
	this->iPlayerMotion_Attack_Old			= -1;								// 変更前プレイヤーモーション(攻撃系)
	
	this->fMotionTimer_Move					= 0;								// モーションカウント(移動系)
	this->fMotionTimer_Move_End				= 1;								// モーションカウント(移動系/終了時間)(※初期化時の不具合防止のため1に設定)
	this->fMotionTimer_Attack				= 0;								// モーションカウント(攻撃系)
	this->fMotionTimer_Attack_End			= 1;								// モーションカウント(攻撃系/終了時間)(※初期化時の不具合防止のため1に設定)

	/* 判定処理用コリジョン */
	this->bMeleeSearchCollisionUseFlg		= false;
	
	/* 能力値関連 */
	this->fPlayerMoveAcceleration			= INIT_ATTRIBUTES_MOVE_ACCELERATION;	// プレイヤーの移動加速度
	this->fPlayerMaxMoveSpeed				= INIT_ATTRIBUTES_MOVE_SPEED_MAX;		// プレイヤーの最大移動速度
	this->fPlayerFallAcceleration			= INIT_ATTRIBUTES_FALL_ACCELERATION;	// プレイヤーの落下加速度
	this->fPlayerMaxFallSpeed				= INIT_ATTRIBUTES_FALL_SPEED_MAX;		// プレイヤーの最大落下速度
	this->iPlayerMaxJumpCount				= INIT_ATTRIBUTES_JUMP_COUNT_MAX;		// プレイヤーのジャンプ回数(最大数)
	this->fPlayerRockOnRadius				= INIT_ATTRIBUTES_ROCK_ON_RADIUS;		// ロックオン範囲の半径
	this->iPlayerMaxHp						= INIT_ATTRIBUTES_HP_MAX;				// プレイヤーの最大HP
	this->iPlayerMaxInvincibleTime			= INIT_ATTRIBUTES_INVINCIBLE_TIME_MAX;	// プレイヤーの最大無敵時間
}

// デストラクタ
DataList_PlayerStatus::~DataList_PlayerStatus()
{

}

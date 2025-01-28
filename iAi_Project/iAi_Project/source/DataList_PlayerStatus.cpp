/* 2024.12.26 駒沢風助 ファイル作成 */
/* 2025.01.10 菊池雅道 初期化処理追加  */
/* 2025.01.22 菊池雅道 初期化処理追加  */
#include "DataList_PlayerStatus.h"

/* プレイヤーステータス管理クラスの定義 */

// コンストラクタ
DataList_PlayerStatus::DataList_PlayerStatus() : DataListBase("DataList_PlayerStatus")
{
	/* 初期化(仮) */
	/* プレイヤー状態関連 */
	this->iPlayerState						= PLAYER_STATUS_FREE;	// プレイヤーの状態
	this->iPlayerMotion						= PLAYER_MOTION_IDLE;	// プレイヤーのモーション
	this->bPlayerLandingFlg					= false;				// プレイヤーが着地しているか
	this->fPlayerNowMoveSpeed				= 0;					// プレイヤーの現在の移動速度
	this->fPlayerAngleX						= 0;					// プレイヤーのX軸回転量(ラジアン)
	this->fPlayerNowFallSpeed				= 0;					// プレイヤーの現在の落下速度
	this->iPlayerNowJumpCount				= 0;					// プレイヤーのジャンプ回数(現在数)
	/* 2025.01.10 菊池雅道 初期化処理追加 開始 */
	this->iPlayerNormalDashFlameCount		= 0;			//通常ダッシュ時経過フレーム数（高速ダッシュへの移行に使用）
	this->bPlayerJumpingFlag				= false;		//プレイヤーがジャンプ中かのフラグ
	this->iPlayerJumpCount					= 0;			//プレイヤーの現在のジャンプ回数
	this->fPlayerDodgeProgress				= 0.0f;			//プレイヤー回避モーション進行度
	this->vecPlayerDodgeDirection			= { 0, 0, 0 };	//プレイヤー回避方向
	this->iPlayerDodgeWhileJumpingCount		= 0;			//プレイヤージャンプ中の回避回数
	this->fPlayerJumpSpeed					= 0;			//プレイヤージャンプ速度
	this->iPlayerNowDodgeFlame				= 0;			// プレイヤーの現在の回避フレーム数
	this->fPlayerDodgeSpeed					= 0;			//プレイヤー回避速度
	this->bPlayerAfterDodgeFlag				= false;		//プレイヤーの回避後フラグ
	/* 2025.01.10 菊池雅道 初期化処理追加 終了 */
	/* 2025.01.22 菊池雅道 初期化処理追加 開始 */
	this->iPlayerNowAttakChargeFlame		= 0;			//現在のプレイヤー溜め攻撃チャージフレーム数  2025.01.22 菊池雅道 初期化処理追加
	this->vecPlayerChargeAttakTargetMove	= { 0, 0, 0 };	//プレイヤー溜め攻撃の目的地
	/* 2025.01.22 菊池雅道 初期化処理追加 終了 */
	this->iPlayerChargeAttackCount			= 0;			// 近接攻撃(強)のカウント
	this->pLockOnEnemy						= nullptr;		// ロックオン対象のエネミー

	/* 能力値関連 */
	this->fPlayerMoveAcceleration	= INIT_ATTRIBUTES_MOVE_ACCELERATION;	// プレイヤーの移動加速度
	this->fPlayerMaxMoveSpeed		= INIT_ATTRIBUTES_MOVE_SPEED_MAX;		// プレイヤーの最大移動速度
	this->fPlayerFallAcceleration	= INIT_ATTRIBUTES_FALL_ACCELERATION;	// プレイヤーの落下加速度
	this->fPlayerMaxFallSpeed		= INIT_ATTRIBUTES_FALL_SPEED_MAX;		// プレイヤーの最大落下速度
	this->iPlayerMaxJumpCount		= INIT_ATTRIBUTES_JUMP_COUNT_MAX;		// プレイヤーのジャンプ回数(最大数)
	this->fPlayerRockOnRadius		= INIT_ATTRIBUTES_ROCK_ON_RADIUS;		// ロックオン範囲の半径

	/* カメラ関連 */
	this->iCameraMode						= CAMERA_MODE_FREE;							// カメラモード
	this->vecCameraUp						= VGet(0, 1, 0);							// カメラの上方向(Y+方向で固定)
	this->vecCameraPosition					= VGet(0, 0, 0);							// カメラの座標
	this->vecCameraTarget					= VGet(0, 0, 0);							// カメラの注視点
	this->fCameraRadius						= INIT_CAMERA_RADIUS;						// カメラの中心点からの距離
	this->fCameraAngleX						= 0;										// カメラのX軸回転量
	this->fCameraAngleY						= 0;										// カメラのY軸回転量
	this->fCameraRotationalSpeed_Controller	= INIT_CAMERA_ROTATIONAL_SPEED_CONTROLLER;	// カメラの回転速度(コントローラー)
	this->fCameraRotationalSpeed_Mouse		= INIT_CAMERA_ROTATIONAL_SPEED_MOUSE;		// カメラの回転速度(マウス)
	this->fCameraAngleLimitUp				= INIT_CAMERA_ANGLE_LIMIT_UP;				// カメラの回転角度制限(上)
	this->fCameraAngleLimitDown				= INIT_CAMERA_ANGLE_LIMIT_DOWN;				// カメラの回転角度制限(下)
}

// デストラクタ
DataList_PlayerStatus::~DataList_PlayerStatus()
{

}

/* 2024.12.26 駒沢風助 ファイル作成 */
/* 2025.01.10 菊池雅道 初期化処理追加 */
#include "DataList_PlayerStatus.h"

/* プレイヤーステータス管理クラスの定義 */

// コンストラクタ
DataList_PlayerStatus::DataList_PlayerStatus() : DataListBase("DataList_PlayerStatus")
{
	/* 初期化(仮) */
	/* プレイヤー状態関連 */
	this->fPlayerNowMoveSpeed		= 0;		// プレイヤーの現在の移動速度
	this->fPlayerAngleX				= 0;		// プレイヤーのX軸回転量(ラジアン)
	this->fPlayerNowFallSpeed		= 0;		// プレイヤーの現在の落下速度

	/* 2025.01.10 菊池雅道 初期化処理追加 開始 */
	this->vecPlayerOldVector = { 0,0,0 };
	this->fPlayerOldRadian = 0;
	this->iPlayerNormalDashFlameCount = 0;
	this->bPlayerJumpingFlag = false;
	this->iPlayerJumpCount = 0;
	this->bPlayerDodgingFlag = false;
	this->fPlayerDodgeProgress = 0.0f;
	this->vecPlayerDodgeDirection = VGet(0, 0, 0);
	this->iPlayerDodgeWhileJumpingCount = 0;
	this->bPlayerAfterDodgeFlag = false;
	/* 2025.01.10 菊池雅道 初期化処理追加 終了 */

	/* 能力値関連 */
	this->fPlayerMoveAcceleration	= INIT_ATTRIBUTES_MOVE_ACCELERATION;	// プレイヤーの移動加速度
	this->fPlayerMaxMoveSpeed		= INIT_ATTRIBUTES_MOVE_SPEED_MAX;		// プレイヤーの最大移動速度
	this->fPlayerFallAcceleration	= INIT_ATTRIBUTES_FALL_ACCELERATION;	// プレイヤーの落下加速度
	this->fPlayerMaxFallSpeed		= INIT_ATTRIBUTES_FALL_SPEED_MAX;		// プレイヤーの最大落下速度
	/* 2025.01.10 菊池雅道 初期化処理追加 開始 */
	this->fPlayerMoveSpeed = PLAYER_WALK_MOVE_SPEED;
	float fPlayerJumpSpeed = PLAYER_JUMP_SPEED; //プレイヤージャンプ速度
	float fPlayerDodgeTime = PLAYER_DODGE_TIME; // プレイヤー回避時間
	float fPlayerDodgeSpeed = PLAYER_DODGE_SPEED; //プレイヤー回避速度
	/* 2025.01.10 菊池雅道 初期化処理追加 終了 */

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

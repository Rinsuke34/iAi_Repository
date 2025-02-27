/* 2025.01.22 駒沢風助 ファイル作成 */

#include "DataList_StageStatus.h"

/* ステージ状態管理クラスの定義 */

// コンストラクタ
DataList_StageStatus::DataList_StageStatus() : DataListBase("DataList_StageStatus")
{
	/* 初期化 */
	{
		this->iGameStatus	= GAMESTATUS_PLAY_GAME;
		this->iNowStageNo	= 0;
		this->iEndStageNo	= 0;
		this->bAddUiFlg		= false;

		/* カメラ関連 */
		this->iCameraMode						= CAMERA_MODE_FREE;							// カメラモード
		this->iCameraMode_Old					= CAMERA_MODE_FREE;							// カメラモード(変更前)
		this->vecCameraUp						= VGet(0, 1, 0);							// カメラの上方向(Y+方向で固定)
		this->vecCameraPosition					= VGet(0, 0, 0);							// カメラの座標(現在地点)
		this->vecCameraPosition_Start			= VGet(0, 0, 0);							// カメラの座標(変更前地点)
		this->vecCameraPosition_Target			= VGet(0, 0, 0);							// カメラの座標(変更後地点)
		this->iCameraPositionLeapCount			= CAMERA_POSITION_LEAP_COUNT_MAX;			// カメラ座標の線形保管用カウント
		this->vecCameraTarget					= VGet(0, 0, 0);							// カメラの注視点
		this->fCameraRadius						= INIT_CAMERA_RADIUS;						// カメラの中心点からの距離
		this->fCameraAngleX						= 0;										// カメラのX軸回転量
		this->fCameraAngleY						= 0;										// カメラのY軸回転量
		this->fCameraRotationalSpeed_Controller	= INIT_CAMERA_ROTATIONAL_SPEED_CONTROLLER;	// カメラの回転速度(コントローラー)
		this->fCameraRotationalSpeed_Mouse		= INIT_CAMERA_ROTATIONAL_SPEED_MOUSE;		// カメラの回転速度(マウス)
		this->fCameraAngleLimitUp				= INIT_CAMERA_ANGLE_LIMIT_UP;				// カメラの回転角度制限(上)
		this->fCameraAngleLimitDown				= INIT_CAMERA_ANGLE_LIMIT_DOWN;				// カメラの回転角度制限(下)
	}
}

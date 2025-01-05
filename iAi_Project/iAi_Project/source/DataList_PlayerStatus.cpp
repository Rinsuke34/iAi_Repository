/* 2024.12.26 駒沢風助 ファイル作成 */

#include "DataList_PlayerStatus.h"

/* プレイヤーステータス管理クラスの定義 */

// コンストラクタ
DataList_PlayerStatus::DataList_PlayerStatus() : DataListBase("DataList_PlayerStatus")
{
	/* 初期化 */
	this->vecCameraUp				= VGet(0, 1, 0);				// カメラの上方向(Y+方向で固定)
	this->vecCameraPosition			= VGet(0, 0, 0);				// カメラの座標
	this->vecCameraTarget			= VGet(0, 0, 0);				// カメラの注視点
	this->fCameraRadius				= INIT_CAMERA_RADIUS;			// カメラの中心点からの距離
	this->fCameraAngleX				= 0;							// カメラのX軸回転量
	this->fCameraAngleY				= 0;							// カメラのY軸回転量
	this->fCameraRotationalSpeed	= INIT_CAMERA_ROTATIONAL_SPEED;	// カメラの回転速度
	this->fCameraAngleLimitUp		= INIT_CAMERA_ANGLE_LIMIT_UP;	// カメラの回転角度制限(上)
	this->fCameraAngleLimitDown		= INIT_CAMERA_ANGLE_LIMIT_DOWN;	// カメラの回転角度制限(下)
}

// デストラクタ
DataList_PlayerStatus::~DataList_PlayerStatus()
{

}

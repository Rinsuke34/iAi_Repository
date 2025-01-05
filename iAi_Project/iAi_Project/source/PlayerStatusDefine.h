#pragma once
/* 2024.12.26 駒沢風助 ファイル作成 */

#pragma once
#include <string>

/* プレイヤー状態管理の構造体や定数の宣言を行う */

/* 初期化用の定数(仮) */
// 今後Jsonから読み込めるようにする予定
/* カメラ関連 */
static const float	INIT_CAMERA_RADIUS				= 300;				// カメラの中心点からの距離
static const float	INIT_CAMERA_ROTATIONAL_SPEED	= 0.01f;			// カメラの回転速度
static const float	INIT_CAMERA_ANGLE_LIMIT_UP		= DX_PI_F / +2.f;	// カメラの回転角度制限(上)
static const float	INIT_CAMERA_ANGLE_LIMIT_DOWN	= DX_PI_F / -2.f;	// カメラの回転角度制限(下)

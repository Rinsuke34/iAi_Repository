#pragma once
/* 2024.12.26 駒沢風助 ファイル作成 */

#pragma once
#include <string>

/* プレイヤー状態管理の構造体や定数の宣言を行う */

/* 初期化用の定数(仮) */
// 今後Jsonから読み込めるようにする予定
/* 能力値関連 */
static const float	INIT_ATTRIBUTES_MOVE_ACCELERATION	= 0.5f;			// プレイヤーの移動加速度
static const float	INIT_ATTRIBUTES_MOVE_SPEED_MAX		= 10.f;			// プレイヤーの最大移動速度
static const float	INIT_ATTRIBUTES_FALL_ACCELERATION	= 0.5f;			// プレイヤーの落下加速度
static const float	INIT_ATTRIBUTES_FALL_SPEED_MAX		= 10.f;			// プレイヤーの最大落下速度
static const int	INIT_ATTRIBUTES_JUMP_COUNT_MAX		= 2;			// プレイヤーのジャンプ回数(最大数)

/* カメラ関連 */
static const float	INIT_CAMERA_RADIUS						= 300;				// カメラの中心点からの距離
static const float	INIT_CAMERA_ROTATIONAL_SPEED_CONTROLLER	= 0.02f;			// カメラの回転速度(コントローラー)
static const float	INIT_CAMERA_ROTATIONAL_SPEED_MOUSE		= 0.005f;			// カメラの回転速度(マウス)
static const float	INIT_CAMERA_ANGLE_LIMIT_UP				= DX_PI_F / +2.f;	// カメラの回転角度制限(上)(ラジアン)
static const float	INIT_CAMERA_ANGLE_LIMIT_DOWN			= DX_PI_F / -2.f;	// カメラの回転角度制限(下)(ラジアン)

/* プレイヤー状態 */
static const int	PLAYER_STATE_IDLE					= 0;	// 待機
static const int	PLAYER_STATE_WALK					= 1;	// 歩行
static const int	PLAYER_STATE_RUN_LOW				= 2;	// 走行(低速)
static const int	PLAYER_STATE_RUN_HIGH				= 3;	// 走行(高速)
static const int	PLAYER_STATE_DRAW_SWORD_CHARGE		= 4;	// 居合(溜め)
static const int	PLAYER_STATE_DRAW_SWORD_WEAK		= 5;	// 居合(弱)
static const int	PLAYER_STATE_DRAW_SWORD_STRONG		= 6;	// 居合(強)
static const int	PLAYER_STATE_THROW_KUNAI_AIM		= 7;	// クナイ(構え)
static const int	PLAYER_STATE_THROW_KUNAI_THROW		= 8;	// クナイ(投げ)
static const int	PLAYER_STATE_DODGE					= 9;	// 回避
static const int	PLAYER_STATE_JUMP_UP				= 10;	// 空中(上昇)
static const int	PLAYER_STATE_JUMP_DOWN				= 11;	// 空中(下降)

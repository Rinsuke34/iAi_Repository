/* 2024.12.26 駒沢風助 ファイル作成 */
/* 2025.01.09菊池雅道 移動関連の変数・関数追加 */

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

/* 2025.01.09 菊池雅道 移動関連の定数追加開始 */
//移動関係
static const float PLAYER_WALK_MOVE_SPEED = 1.0f; //プレイヤーの歩きの移動速度
static const float PLAER_DASH_NOMAL_SPEED = 5.0f; //プレイヤーの走り（通常）の移動速度
static const float PLAER_DASH_MAX_SPEED = 10.0f; //プレイヤーの走り（最大）の移動速度
static const int FLAME_COUNT_TO_MAX_SPEED = 180; //プレイヤーの走りの通常→最大になるフレーム数
static const float STICK_TILT_PLAER_DASH = 0.8f; //プレイヤーが走り状態になるスティックの傾き（範囲：最大1）

//ジャンプ関係
static const float PLAYER_JUMP_SPEED = 50.0f; //プレイヤーのジャンプの速度
static const float GRAVITY_SREED = -9.8f; //重力の速度　Y軸の下方向なのでマイナスとする
static const float GRAVITY_BUFFER = 0.1f; //キャラクターにかかる重力調整　１より大きいと重くなる　１より小さいと軽くなる
static const int PLAYER_JUMPING_IN_AIR_LIMIT = 1;//プレイヤーが空中ジャンプできる回数
//回避関係
static const float PLAYER_DODGE_SPEED = 100.0f;//プレイヤーの回避速度
static const int PLAYER_DODGE_FLAME = 30.0f; //プレイヤーの回避フレーム数
static const int PLAYER_DODGE_IN_AIR_LIMIT = 1;//プレイヤーが空中で回避できる回数
/* 2025.01.09 菊池雅道 移動関連の定数追加終了 */

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

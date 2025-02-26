/* 2024.12.26 駒沢風助 ファイル作成 */

#pragma once
#include <string>

/* ゲームの状態管理の構造体や定数の宣言を行う */

/* ゲーム状態 */
static const int	GAMESTATUS_PLAY_GAME	= 0;	// ゲーム実行
static const int	GAMESTATUS_RESULT		= 1;	// リザルト実行
static const int	GAMESTATUS_EDIT			= 2;	// エディット実行
static const int	GAMESTATUS_NEXTSTAGE	= 3;	// 次のステージへ遷移
static const int	GAMESTATUS_GAMEOVER		= 4;	// ゲームオーバー

/* カメラ関連 */
// 基本情報
static const float	INIT_CAMERA_RADIUS						= 400;				// カメラの中心点からの距離
static const float	INIT_CAMERA_ROTATIONAL_SPEED_CONTROLLER	= 0.02f;			// カメラの回転速度(コントローラー)
static const float	INIT_CAMERA_ROTATIONAL_SPEED_MOUSE		= 0.005f;			// カメラの回転速度(マウス)
static const float	INIT_CAMERA_ANGLE_LIMIT_UP				= DX_PI_F / +2.f;	// カメラの回転角度制限(上)(ラジアン)
static const float	INIT_CAMERA_ANGLE_LIMIT_DOWN			= DX_PI_F / -2.f;	// カメラの回転角度制限(下)(ラジアン)
// カメラ状態
static const int	CAMERA_MODE_FREE						= 0;				// フリーモード(通常の三人称視点)
static const int    CAMERA_MODE_LOCK						= 1;				// 固定
static const int	CAMERA_MODE_AIM_MELEE					= 2;				// 構え(近接攻撃構え)
static const int	CAMERA_MODE_AIM_KUNAI					= 3;				// 構え(クナイ構え)
static const int	CAMERA_MODE_TITLE						= 4;				// タイトル
// 線形補間
static const int	CAMERA_POSITION_LEAP_COUNT_MAX			= 60 * 2;			// カメラ座標の線形保管用カウントの最大値

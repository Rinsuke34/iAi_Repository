/* 2024.12.26 駒沢風助 ファイル作成 */
/* 2025.03.06 菊池雅道 定数追加 */

#pragma once
#include <string>

/* ゲームの状態管理の構造体や定数の宣言を行う */

/* ゲーム状態 */
static const int	GAMESTATUS_PLAY_GAME			= 0;	// ゲーム実行
static const int	GAMESTATUS_STAGE_CLEAR_SETUP	= 1;	// ステージクリア準備
static const int	GAMESTATUS_STAGE_CLEAR			= 2;	// ステージクリア
static const int	GAMESTATUS_RESULT				= 3;	// リザルト実行
static const int	GAMESTATUS_EDIT					= 4;	// エディット実行
static const int	GAMESTATUS_NEXTSTAGE			= 5;	// 次のステージへ遷移
static const int	GAMESTATUS_GAMEOVER				= 6;	// ゲームオーバー
static const int	GAMESTATUS_RESET				= 7;	// リセット
static const int	GAMESTATUS_START				= 8;	// ゲーム開始
static const int	GAMESTATUS_STAGE_JUMP			= 9;	// ステージジャンプ

/* ゲームクリア時のカウントに応じた処理 */
static const int	STAGECLEAR_COUNT_START				= 0;	// ステージクリア処理開始
static const int	STAGECLEAR_COUNT_CAMERA_STOP		= 30;	// カメラ停止
static const int	STAGECLEAR_COUNT_CAMERA_TRUN_FAST	= 60;	// カメラ回転
static const int	STAGECLEAR_COUNT_CAMERA_TRUN_LAST	= 90;	// カメラ回転
static const int	STAGECLEAR_COUNT_START_FADEIN		= 120;	// フェードイン開始
static const int	STAGECLEAR_COUNT_START_RESULT		= 240;	// リザルト開始

/* カメラ関連 */
// 基本情報
static const float	INIT_CAMERA_RADIUS						= 400;				// カメラの中心点からの距離
static const float	INIT_CAMERA_ROTATIONAL_SPEED_CONTROLLER	= 0.02f;			// カメラの回転速度(コントローラー)
static const float	INIT_CAMERA_ROTATIONAL_SPEED_MOUSE		= 0.005f;			// カメラの回転速度(マウス)
static const float	INIT_CAMERA_ANGLE_LIMIT_UP				= DX_PI_F / +2.f;	// カメラの回転角度制限(上)(ラジアン)
static const float	INIT_CAMERA_ANGLE_LIMIT_DOWN			= DX_PI_F / -2.f;	// カメラの回転角度制限(下)(ラジアン)
static const float	INIT_CAMERA_NEAR						= 100.f;			// カメラの前方クリップ距離
static const float	INIT_CAMERA_FAR							= 30000.f;			// カメラの後方クリップ距離
static const float	INIT_CAMERA_FOG_START					= 20000.f;			// カメラのフォグ開始距離
static const float	INIT_CAMERA_FOG_END						= 26000.f;			// カメラのフォグ終了距離
// カメラ状態
static const int	CAMERA_MODE_NORMAL						= 0;				// フリーモード(通常の三人称視点)
static const int    CAMERA_MODE_LOCK						= 1;				// 固定
static const int	CAMERA_MODE_AIM_MELEE					= 2;				// 構え(近接攻撃構え)
static const int	CAMERA_MODE_AIM_KUNAI					= 3;				// 構え(クナイ構え)
static const int	CAMERA_MODE_TITLE						= 4;				// タイトル
static const int	CAMERA_MODE_STAGECLEAR					= 5;				// ステージクリア
static const int	CAMERA_MODE_STAGESTART					= 6;				// ステージ開始
static const int	CAMERA_MODE_STAGESTART_CLOSE_UP			= 7;				// ステージ開始(プレイヤークローズアップ)
static const int	CAMERA_MODE_FALL						= 8;				// 落下
// 線形補間
static const int	CAMERA_POSITION_LEAP_COUNT_MAX_NORMAL		= 30 * 1;		// カメラ座標の線形保管用カウントの最大値(フリー)				/* 2025.03.06 菊池雅道 定数追加 */
static const int	CAMERA_POSITION_LEAP_CONT_MAX_TITLE			= 60 * 1;		// カメラ座標の線形保管用カウントの最大値(タイトル)				/* 2025.03.06 菊池雅道 定数追加 */
static const int	CAMERA_POSITION_LEAP_COUNT_MAX_MELEE		= 40 * 1;		// カメラ座標の線形保管用カウントの最大値(近距離攻撃(強))		/* 2025.03.06 菊池雅道 定数追加 */
static const int	CAMERA_POSITION_LEAP_COUNT_MAX_PROJECTILE	= 30 * 1;		// カメラ座標の線形保管用カウントの最大値(遠距離攻撃)			/* 2025.03.06 菊池雅道 定数追加 */
static const int	CAMERA_POSITION_LEAP_COUNT_MAX_STAGECLEAR	= 60 * 2;		// カメラ座標の線形保管用カウントの最大値(ステージクリア)		/* 2025.03.06 菊池雅道 定数追加 */
static const int	CAMERA_POSITION_LEAP_COUNT_MAX_STAGESTART	= 60 * 4;		// カメラ座標の線形保管用カウントの最大値(ステージ開始/区間)
// カメラ固定座標
static const int	CAMERA_FIXED_POSITION_START				= 0;				// カメラ固定座標(開始地点)
static const int	CAMERA_FIXED_POSITION_A					= 1;				// カメラ固定座標(A地点)
static const int	CAMERA_FIXED_POSITION_B					= 2;				// カメラ固定座標(B地点)
static const int	CAMERA_FIXED_POSITION_C					= 3;				// カメラ固定座標(C地点)
static const int	CAMERA_FIXED_POSITION_D					= 4;				// カメラ固定座標(D地点)
static const int	CAMERA_FIXED_POSITION_E					= 5;				// カメラ固定座標(E地点)
static const int	CAMERA_FIXED_POSITION_MAX				= 6;				// カメラ固定座標の最大数
// クローズアップ関連定数
static const int	CAMERA_CLOSEUP_COUNT_MAX				= 180;				// クローズアップカウントの最大値
static const int	CAMERA_CLOSEUP_POSITION_HEIGHT			= 100;				// クローズアップ時のカメラの高さ(プレイヤーを基準に)

/* カメラ固定座標情報 */
struct CAMERA_FIXED_POSITION_INFO
{
	int		iNo;			// カメラ固定座標番号
	bool	bUseFlg;		// 使用するか
	VECTOR	vecPosition;	// カメラ固定座標
	VECTOR	vecTarget;		// カメラ固定注視点
};

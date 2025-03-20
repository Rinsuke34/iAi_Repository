/* 2024.01.06 駒沢風助 ファイル作成 */
/* 2025.03.03 菊池雅道 ロックオン関連の定数追加 */
/* 2025.03.03 菊池雅道 プレイヤー関連の定数追加 */
#pragma once

#include <string>
#include "StructDefine.h"

/* プロジェクトで使用する定数の宣言 */

/* 計算用マクロ */
#define	PI					(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )
#define	ACCELERATION(x)		( (x) / 60.0f * 60.0f )
#define GRAVITY				( -9.8f )

/* ステージ情報 */
// ステージ数
static const int	STAGE_MAX       = 10;
// ステージ番号
static const int	STAGE_NO_1_1    = 0;
static const int	STAGE_NO_1_2    = 1;
static const int	STAGE_NO_1_3    = 2;
static const int	STAGE_NO_2_1    = 3;
static const int	STAGE_NO_2_2    = 4;
static const int	STAGE_NO_2_3    = 5;
static const int	STAGE_NO_3_1    = 6;
static const int	STAGE_NO_3_2    = 7;
static const int	STAGE_NO_3_3    = 8;
// タイトル、ホーム
static const int	STAGE_NO_TITLE  = 9;
// 開始/終了ステージ番号
static const int    STAGE_START     = STAGE_NO_1_1;     // 開始
static const int    STAGE_END       = STAGE_NO_3_3;     // 終了
// ステージ名
static const std::string STAGE_NAME[STAGE_MAX] =
{
    "Stage_1_1", "Stage_1_2", "Stage_1_3",
    "Stage_2_1", "Stage_2_2", "Stage_2_3",
    "Stage_3_1", "Stage_3_2", "Stage_3_3",
    "Stage_Title"
};

/* 描写関連 */
static const int    SHADOWMAP_SIZE_ACTOR        = 4096;     // シャドウマップ(アクタ)のサイズ
static const int    SHADOWMAP_SIZE_PLATFORM     = 4096 * 2;		// シャドウマップ(プラットフォーム)のサイズ

static const int    SHADOWMAP_RANGE_ACTOR_HEIGHT      = 2048;		// シャドウマップ(アクタ)の高さ
static const int    SHADOWMAP_RANGE_ACTOR_WIDTH       = 2048;		// シャドウマップ(アクタ)の横幅
static const int    SHADOWMAP_RANGE_PLATFORM_HEIGHT   = 2048 * 3;	// シャドウマップ(プラットフォーム)の高さ
static const int    SHADOWMAP_RANGE_PLATFORM_WIDTH    = 2048 * 3;	// シャドウマップ(プラットフォーム)の横幅

static const int	LIGHTMAP_DOWNSCALE		= 8;		// ライトマップの縮小倍率
static const int	LIGHTMAP_GAUSS_WIDTH	= 16;		// ぼかしの強さ(8, 16, 32のいずれか)
static const int	LIGHTMAP_GAUSS_RATIO	= 100;		// ぼかしパラメータ(100につき約1ピクセル分の幅)

static const int    ALPHA_MAX               = 255;		// アルファ値の最大値
static const int    FADE_ALPHA_CHANGE_SPEED = 3;		// フェードイン/アウトの速度

/* デバッグ関連 */
static const int    DEBUG_MAP_HEIGHT	    = 256;	// デバッグ描写の高さ
static const int    DEBUG_MAP_WIDTH         = 256;	// デバッグ描写の横幅
// デバッグモード
static const int	DEBUG_MODE_OPTION       = 0;	// デバッグオプション
static const int	DEBUG_MODE_OPERATION    = 1;	// デバッグ操作
static const int	DEBUG_MODE_MAX          = 2;	// デバッグモードの総数
// デバッグ操作名
static const int    DEBUG_OPERATION_STAGEJUMP   = 0;	// ステージジャンプ
static const int    DEBUG_OPERATION_STATUSSETUP = 1;	// ステータス調整
static const int    DEBUG_OPERATION_MAX         = 2;    // デバッグ操作の総数

/* ロックオン関係 */
// エネミーのプレイヤーからのロックオン状態
static const int PLAYER_LOCKON_NONE     = 0;    // ロックオンされていない
static const int PLAYER_LOCKON_RANGE    = 1;    // ロックオン範囲内である
static const int PLAYER_LOCKON_TARGET   = 2;    // ロックオンされている
// ロックオン関連の設定値
static const float PLAYER_LOCKON_RADIUS = 5000.0f;    // ロックオン範囲の半径       /* 2025.03.03 菊池雅道 ロックオン関連の定数追加 */

/* 評価ランク */
static const int	RESULT_EVALUATION_S     = 0;	// S(最高ランク)
static const int	RESULT_EVALUATION_A     = 1;	// A
static const int	RESULT_EVALUATION_B     = 2;	// B
static const int	RESULT_EVALUATION_C     = 3;	// C
static const int	RESULT_EVALUATION_D     = 4;	// D(最低ランク)
static const int    RESULT_EVALUATION_MAX   = 5;    // 評価ランクの総数

/* 画面エフェクト関連 */
// ダメージエフェクト関連
static const int	DAMAGE_EFFECT_TIME              = 30;	// ダメージエフェクトの持続時間(フレーム数)
static const int    DAMAGE_EFFECT_SHIFT_CHANGE      = 10;	// ダメージエフェクトのシフト量変更カウント
static const int	DAMAGE_EFFECT_ALPHA             = 50;	// ダメージエフェクトのアルファ値(0～100)
static const int	DAMAGE_EFFECT_SHIFT             = 50;	// ダメージエフェクトの最初のシフト量(ピクセル数)
// 集中線エフェクト関連
static const int    CONCENTRATIONLINE_EFFECT_CHANGE = 5;    // 集中線エフェクトの変更間隔(フレーム数)
static const int	CONCENTRATIONLINE_EFFECT_ALPHA  = 30;	// ダメージエフェクトのアルファ値(0～100)
static const int    CONCENTRATIONLINE_EFFECT_TYPE   = 2;    // 集中線エフェクトの種類の数

/* コンボ関連 */
// コンボランク
static const int    COMBO_RANK_S        = 0;    // Sランク
static const int    COMBO_RANK_A        = 1;    // Aランク
static const int    COMBO_RANK_B        = 2;    // Bランク
static const int    COMBO_RANK_C        = 3;    // Cランク
static const int    COMBO_RANK_D        = 4;    // Dランク
static const int    COMBO_RANK_MAX      = 5;	// コンボランクの総数
static const int    COMBO_RANK_NONE     = -1;   // 無し

/* スロー関連 */
static const int	SLOW_SPEED = 1;				// スロー状態での速度(何フレームに一度実行されるか)

/* プレイヤー関連 */
static const int	PLAYER_STRONG_MELEE_AFTER_COUNT_MAX = 120 * 1 / (SLOW_SPEED + 1);	// 近接攻撃(強)後で敵を倒した後のカウントの最大値(※第一項にスローモーションを考慮しないフレーム数を書く)	/* 2025.03.03 菊池雅道 攻撃関連の定数追加 */

/* プレイヤー入力タイプ */
static const int    INPUT_TYPE_CONTROLLER   = 0;    // コントローラ
static const int    INPUT_TYPE_MOUSE        = 1;    // マウス
static const int    INPUT_TYPE_MAX          = 2;    // 入力タイプの総数

/* カメラ関連 */
// カメラ移動タイプ
static const int	INPUT_CAMERA_NORMAL     = 0;	// 通常
static const int	INPUT_CAMERA_AIM        = 1;	// エイム(構え/クナイ構え)
static const int	INPUT_CAMERA_NONE       = 2;	// 無し(入力受付なし)
static const int	INPUT_CAMERA_MAX        = 3;	// カメラ移動タイプの総数

/* 入力オプション関連 */
// 軸
static const int    AXIS_X                  = 0;	// X軸
static const int    AXIS_Y                  = 1;	// Y軸
static const int    AXIS_MAX                = 2;	// 軸の総数
// カメラ状態
static const int    INPUT_CAMERA_MODE_NORMAL      = 0;	// 通常状態
static const int    INPUT_CAMERA_MODE_AIM         = 1;	// エイム状態
static const int    INPUT_CAMERA_MODE_MAX         = 2;	// カメラ状態の総数

/* データ型名称 */
static const std::string DATA_TYPE_BOOL     = "bool";	// ブール型
static const std::string DATA_TYPE_INT      = "int";	// 整数型
static const std::string DATA_TYPE_FLOAT    = "float";	// 浮動小数点型

/* ギミック関連 */
static const int	GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_SHORT  = 0;		// 移動床の移動距離タイプ(短)
static const int	GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_NORMAL = 1;		// 移動床の移動距離タイプ(中)
static const int	GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_LONG   = 2;		// 移動床の移動距離タイプ(長)

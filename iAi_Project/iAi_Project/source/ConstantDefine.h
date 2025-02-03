/* 2024.01.06 駒沢風助 ファイル作成 */

#pragma once

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
static const int	STAGE_MAX   = 12;
// ステージ番号
static const int	STAGE_NO_0_1 = 0;
static const int	STAGE_NO_0_2 = 1;
static const int	STAGE_NO_0_3 = 2;
static const int	STAGE_NO_1_1 = 3;
static const int	STAGE_NO_1_2 = 4;
static const int	STAGE_NO_1_3 = 5;
static const int	STAGE_NO_2_1 = 6;
static const int	STAGE_NO_2_2 = 7;
static const int	STAGE_NO_2_3 = 8;
static const int	STAGE_NO_3_1 = 9;
static const int	STAGE_NO_3_2 = 10;
static const int	STAGE_NO_3_3 = 11;
// 開始/終了ステージ番号
static const int    STAGE_NO_TUTORIAL_START    = STAGE_NO_0_1;     // チュートリアル開始
static const int    STAGE_NO_TUTORIAL_END      = STAGE_NO_0_3;     // チュートリアル終了
static const int    STAGE_NO_PRACTICE_START    = STAGE_NO_1_1;     // 実践開始
static const int    STAGE_NO_PRACTICE_END      = STAGE_NO_3_3;     // 実践終了
// ステージ名
static const std::string STAGE_NAME[STAGE_MAX] =
{
    "Stage_0_1", "Stage_0_2", "Stage_0_3",
    "Stage_1_1", "Stage_1_2", "Stage_1_3",
    "Stage_2_1", "Stage_2_2", "Stage_2_3",
    "Stage_3_1", "Stage_3_2", "Stage_3_3"
};

/* 描写関連 */
static const int	SHADOWMAP_SIZE			= 2048;		// シャドウマップのサイズ
static const float	SHADOWMAP_RANGE			= 1024;		// シャドウマップの描写範囲
static const int	LIGHTMAP_DOWNSCALE		= 8;		// ライトマップの縮小倍率
static const int	LIGHTMAP_GAUSS_WIDTH	= 16;		// ぼかしの強さ(8, 16, 32のいずれか)
static const int	LIGHTMAP_GAUSS_RATIO	= 100;		// ぼかしパラメータ(100につき約1ピクセル分の幅)

/* デバッグ関連 */
static const int DEBUG_MAP_HEIGHT	= 256;	// デバッグ描写の高さ
static const int DEBUG_MAP_WIDTH	= 256;	// デバッグ描写の横幅

// Effekseer関連
static const int EFFECT_MAX_PARTICLE	= 8000;		// エフェクトの最大パーティクル数

/* ロックオン関係 */
// エネミーのプレイヤーからのロックオン状態
static const int PLAYER_LOCKON_NONE     = 0;    // ロックオンされていない
static const int PLAYER_LOCKON_RANGE    = 1;    // ロックオン範囲内である
static const int PLAYER_LOCKON_TARGET   = 2;    // ロックオンされている

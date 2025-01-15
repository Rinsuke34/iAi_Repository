/* 2024.01.06 駒沢風助 ファイル作成 */

#pragma once

/* プロジェクトで使用する定数の宣言 */

/* 計算用マクロ */
#define	PI					(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )
#define	ACCELERATION(x)		( (x) / 60.0f * 60.0f )
#define GRAVITY				( -9.8f )

/* ステージ関連 */
static const int STAGE_0_1	= 0;	// ステージ0-1
static const int STAGE_0_2	= 1;	// ステージ0-2
static const int STAGE_0_3	= 2;	// ステージ0-3
static const int STAGE_1_1	= 3;	// ステージ1-1
static const int STAGE_1_2	= 4;	// ステージ1-2
static const int STAGE_1_3	= 5;	// ステージ1-3
static const int STAGE_2_1	= 6;	// ステージ2-1
static const int STAGE_2_2	= 7;	// ステージ2-2
static const int STAGE_2_3	= 8;	// ステージ2-3
static const int STAGE_3_1	= 9;	// ステージ0-1
static const int STAGE_3_2	= 10;	// ステージ0-2
static const int STAGE_3_3	= 11;	// ステージ0-3

/* カメラ関連 */
static const int CAMERA_MODE_FREE	= 0;	// フリーモード(通常の三人称視点)

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

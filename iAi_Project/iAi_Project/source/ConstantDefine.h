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
static const int	SHADOWMAP_SIZE_PLATFORM     = 2048;		// シャドウマップのサイズ

static const float	SHADOWMAP_RANGE			= 1024;		// シャドウマップの描写範囲
static const int	LIGHTMAP_DOWNSCALE		= 8;		// ライトマップの縮小倍率
static const int	LIGHTMAP_GAUSS_WIDTH	= 16;		// ぼかしの強さ(8, 16, 32のいずれか)
static const int	LIGHTMAP_GAUSS_RATIO	= 100;		// ぼかしパラメータ(100につき約1ピクセル分の幅)

static const int    ALPHA_MAX               = 255;		// アルファ値の最大値
static const int    FADE_ALPHA_CHANGE_SPEED = 3;		// フェードイン/アウトの速度

/* デバッグ関連 */
static const int DEBUG_MAP_HEIGHT	= 256;	// デバッグ描写の高さ
static const int DEBUG_MAP_WIDTH	= 256;	// デバッグ描写の横幅

/* ロックオン関係 */
// エネミーのプレイヤーからのロックオン状態
static const int PLAYER_LOCKON_NONE     = 0;    // ロックオンされていない
static const int PLAYER_LOCKON_RANGE    = 1;    // ロックオン範囲内である
static const int PLAYER_LOCKON_TARGET   = 2;    // ロックオンされている

/* 評価ランク */
static const int	RESULT_EVALUATION_S     = 0;	// S(最高ランク)
static const int	RESULT_EVALUATION_A     = 1;	// A
static const int	RESULT_EVALUATION_B     = 2;	// B
static const int	RESULT_EVALUATION_C     = 3;	// C
static const int	RESULT_EVALUATION_D     = 4;	// D(最低ランク)
static const int    RESULT_EVALUATION_MAX   = 5;    // 評価ランクの総数

/* 画面エフェクト関連 */
// ダメージエフェクト関連
static const int	DAMAGE_EFFECT_TIME          = 30;	// ダメージエフェクトの持続時間(フレーム数)
static const int    DAMAGE_EFFECT_SHIFT_CHANGE  = 10;	// ダメージエフェクトのシフト量変更カウント
static const int	DAMAGE_EFFECT_ALPHA         = 50;	// ダメージエフェクトのアルファ値(0～100)
static const int	DAMAGE_EFFECT_SHIFT         = 50;	// ダメージエフェクトの最初のシフト量(ピクセル数)

/* コンボ関連 */
// コンボランク
static const int    COMBO_RANK_S        = 0;    // Sランク
static const int    COMBO_RANK_A        = 1;    // Aランク
static const int    COMBO_RANK_B        = 2;    // Bランク
static const int    COMBO_RANK_C        = 3;    // Cランク
static const int    COMBO_RANK_D        = 4;    // Dランク
static const int    COMBO_RANK_NONE     = -1;   // 無し
// ボーダーライン
// ※コンボ数がこの値を超えていればそのコンボランク
static const int    COMBO_RANK_BORDER_S = 21;   // Sランク
static const int    COMBO_RANK_BORDER_A = 11;   // Aランク
static const int    COMBO_RANK_BORDER_B = 5;    // Bランク
static const int    COMBO_RANK_BORDER_C = 2;    // Cランク

/* 2025.03.05 ファイル作成 駒沢風助 */

#pragma once

/* リザルト画面用の構造体や定数の宣言を行う */
// 座標系
static const int RESULT_BACKGROUND_POSITION_REDUCTION	= 26;	// 背景縮小量
static const int RESULT_STRING_RESULT_POSITION_X		= 80;	// リザルト文字列のX座標
static const int RESULT_STRING_RESULT_POSITION_Y		= 40;	// リザルト文字列のY座標
static const int RESULT_STRING_RANK_POSITION_X			= 1290;	// ランク文字列のX座標
static const int RESULT_STRING_RANK_POSITION_Y			= 820;	// ランク文字列のY座標

static const int RESULT_STRING_RESULT_LINE_LU	= 65;	// リザルト文字列の線(左上)
static const int RESULT_STRING_RESULT_LINE_LD	= 160;	// リザルト文字列の線(左下)
static const int RESULT_STRING_RESULT_LINE_RU	= 1810;	// リザルト文字列の線(右上)
static const int RESULT_STRING_RESULT_LINE_RD	= 165;	// リザルト文字列の線(右下)
static const int RESULT_STRING_RANK_LINE_LU		= 1260;	// ランク文字列の線(左上)
static const int RESULT_STRING_RANK_LINE_LD		= 940;	// ランク文字列の線(左下)
static const int RESULT_STRING_RANK_LINE_RU		= 1810;	// ランク文字列の線(右上)
static const int RESULT_STRING_RANK_LINE_RD		= 945;	// ランク文字列の線(右下)

// 描写フェーズ
static const int RESULT_DRAW_FAZE_CLEAR_TIME			= 0;	// クリアタイム描写
static const int RESULT_DRAW_FAZE_CREAR_TIME_EVALUATION	= 1;	// クリアタイム評価描写
static const int RESULT_DRAW_FAZE_COMBO					= 2;	// コンボ描写
static const int RESULT_DRAW_FAZE_COMBO_EVALUATION		= 3;	// コンボ評価描写
static const int RESULT_DRAW_FAZE_DAMAGE				= 4;	// ダメージ描写
static const int RESULT_DRAW_FAZE_DAMAGE_EVALUATION		= 5;	// ダメージ評価描写
static const int RESULT_DRAW_FAZE_GETBLOOD				= 6;	// 取得ブラッド描写
static const int RESULT_DRAW_FAZE_TOTAL_EVALUATION		= 7;	// 総合評価描写

static const int RESULT_DRAW_FAZE_DELAY_TIME			= 30;	// 
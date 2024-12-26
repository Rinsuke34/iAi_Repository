/* 2024.12.08 駒沢風助 ファイル作成 */

#pragma once

/* AppFrameで使用する定数の宣言 */

// 画面サイズ
namespace SCREEN_SIZE
{
	static const int WIDE	= 1920;
	static const int HEIGHT	= 1080;
}

// フレームレート
namespace FRAME_RATE
{
	static const int FPS_RATE	= 60;	// フレームレート設定値
}

/* 入力タイプ */
static const int INPUT_HOLD	= 0;	// ホールド入力
static const int INPUT_TRG	= 1;	// トリガ入力
static const int INPUT_REL	= 2;	// リリース入力

/* 2025.03.05 ファイル作成 駒沢風助 */

#pragma once

/* 一時停止画面用の構造体や定数の宣言を行う */

static const int	PAUSE_MANU_CONTINUE	= 0;	// 続ける
static const int	PAUSE_MANU_RESTART	= 1;	// 最初から
static const int	PAUSE_MANU_OPTION	= 2;	// オプション
static const int	PAUSE_MANU_TITLE	= 3;	// タイトルへ
static const int	PAUSE_MANU_MAX		= 4;	// メニューの最大数

static const int	PAUSE_BLACK_ALPHA	= 100;	// ポーズ時の画面の暗さ(0～255)

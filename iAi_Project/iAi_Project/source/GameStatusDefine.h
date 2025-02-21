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

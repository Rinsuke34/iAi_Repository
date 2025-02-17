/* 2025.02.11 駒沢風助 ファイル作成 */

#pragma once

/* エディット画面用の構造体や定数の宣言を行う */

static const int	SELECT_ITEM_MAX			= 13;	// 選択項目数
static const int	SELECT_ITEM_KEEP		= 0;	// 選択項目(キープ中のエディット)
static const int	SELECT_ITEM_NEW_EDIT	= 5;	// 選択項目(新規のエディット)(ここまで)
static const int	SELECT_ITEM_DELETE		= 6;	// 選択項目(削除)
static const int	SELECT_ITEM_NOW_EDIT	= 11;	// 選択項目(現在のエディット)(ここまで)
static const int	SELECT_ITEM_NEXT		= 12;	// 選択項目(次へ)

static const int	SELECT_TYPE_NEW			= 0;	// 選択項目の種類(新規のエディット)
static const int	SELECT_TYPE_NOW			= 1;	// 選択項目の種類(現在のエディット)
static const int	SELECT_TYPE_MAX			= 2;	// 選択項目の種類の最大数


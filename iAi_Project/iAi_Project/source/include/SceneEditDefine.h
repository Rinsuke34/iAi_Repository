/* 2025.02.11 駒沢風助 ファイル作成 */

#pragma once
#include "PublicInclude.h"
#include "EditDefine.h"

/* エディット画面用の構造体や定数の宣言を行う */

/* 選択項目の種類 */
static const int	SELECT_TYPE_NONE		= -1;	// 選択項目無し
static const int	SELECT_TYPE_KEEP_EDIT	= 0;	// キープ中のエディット
static const int	SELECT_TYPE_NEW_EDIT	= 1;	// 新規のエディット
static const int	SELECT_TYPE_DELETE_EDIT	= 2;	// 削除
static const int	SELECT_TYPE_NOW_EDIT	= 3;	// 現在のエディット
static const int	SELECT_TYPE_NEXT		= 4;	// 次へ
static const int	SELECT_TYPE_MAX			= 5;	// 選択項目の種類の総数

/* 選択項目の番号 */
static const int	SELECT_ITEM_KEEP			= 0;	// キープ中のエディット
static const int	SELECT_ITEM_NEW_EDIT_START	= 1;	// 新規のエディット(ここから)
static const int	SELECT_ITEM_NEW_EDIT_END	= 5;	// 新規のエディット(ここまで)
static const int	SELECT_ITEM_DELETE			= 6;	// 削除
static const int	SELECT_ITEM_NOW_EDIT_START	= 7;	// 現在のエディット(ここから)
static const int	SELECT_ITEM_NOW_EDIT_END	= 11;	// 現在のエディット(ここまで)
static const int	SELECT_ITEM_NEXT			= 12;	// 次へ
static const int	SELECT_ITEM_MAX				= 13;	// 選択項目の総数

/* 選択項目の状態 */
static const int	SELECT_STATUS_NONE				= -1;	// 状態無し
static const int	SELECT_STATUS_POSSIBLE_SET		= 0;	// セット可能
static const int	SELECT_STATUS_POSSIBLE_UPGRADE	= 1;	// 強化可能
static const int	SELECT_STATUS_INTERCHANGEABLE	= 2;	// 交換可能
static const int	SELECT_STATUS_IMPOSSIBLE		= 3;	// 選択不可
static const int	SELECT_STATUS_MAX				= 4;	// 選択項目の状態の総数

/* ランクに応じた新規エディット数 */
static const int	NEW_EDIT_NO_RANK_S				= 5;	// 新規エディット数(Sランク時)
static const int	NEW_EDIT_NO_RANK_A				= 5;	// 新規エディット数(Aランク時)
static const int	NEW_EDIT_NO_RANK_B				= 4;	// 新規エディット数(Bランク時)
static const int	NEW_EDIT_NO_RANK_C				= 3;	// 新規エディット数(Cランク時)
static const int	NEW_EDIT_NO_RANK_D				= 3;	// 新規エディット数(Dランク時)


/* 選択項目の管理用構造体 */
struct EDIT_SELECT_ITEM
{
	EDIT_DATA*		pstEditData;		// エディット情報
	int				iSelectItemType;	// 選択項目の種類
	st2DPosition	stDrawPos;			// 描写座標
	int				iSelectStatus;		// 選択状態
};

/* エディット抽選用の構造体 */
struct EDIT_LOTTERY
{
	int			iEffect;		// エディットの効果
	int			iRank;			// エディットのランク
	int			iIncidenceRate;	// 出現率
	int			iCost;			// 価格
	std::string	aText;			// テキスト
};

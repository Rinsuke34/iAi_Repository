/* 2025.01.22 駒沢風助 ファイル作成 */

#include "DataList_GameStatus.h"

/* ゲーム状態管理クラスの定義 */

// コンストラクタ
DataList_GameStatus::DataList_GameStatus() : DataListBase("DataList_GameStatus")
{
	/* 初期化 */
	this->iGameStatus	= GAMESTATUS_NORMAL;
}

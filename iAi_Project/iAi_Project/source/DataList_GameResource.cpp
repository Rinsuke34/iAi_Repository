/* 2025.02.11 駒沢風助 ファイル作成 */

#include "DataList_GameResource.h"

/* ゲーム内リソース管理クラスの定義 */
// コンストラクタ
DataList_GameResource::DataList_GameResource() : DataListBase("DataList_GameResource")
{
	/* 初期化 */
	this->iHaveBlood	= 0;
}

// デストラクタ
DataList_GameResource::~DataList_GameResource()
{

}

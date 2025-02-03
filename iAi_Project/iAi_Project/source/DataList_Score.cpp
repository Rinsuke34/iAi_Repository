/* 2025.01.30 駒沢風助 ファイル作成 */

#include "DataList_Score.h"

/* スコア関連管理データリストの定義 */

// コンストラクタ
DataList_Score::DataList_Score() : DataListBase("DataList_Score")
{
	/* 初期化 */
	this->iPlayerComboNowCount = 0;			// プレイヤーの現在のコンボ数
	this->iPlayerComboMaxCount = 0;			// プレイヤーの最大コンボ数
	this->iPlayerComboDuration = 0;			// プレイヤーのコンボの残り持続時間
}

// デストラクタ
DataList_Score::~DataList_Score()
{

}

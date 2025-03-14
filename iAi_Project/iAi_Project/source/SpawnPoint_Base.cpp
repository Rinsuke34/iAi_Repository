/* 2025.03.08 駒沢風助 ファイル作成 */

#include "SpawnPoint_Base.h"

/* エネミースポナーベースクラスの定義 */
// コンストラクタ
SpawnPoint_Base::SpawnPoint_Base() : PlatformBase()
{
	/* データリストを取得 */
	{
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}
}

// リセット処理
void SpawnPoint_Base::Reset()
{
	/* このオブジェクトの初期化処理を実行する */
	Initialization();
}

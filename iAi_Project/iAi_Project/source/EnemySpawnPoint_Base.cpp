/* 2025.03.08 駒沢風助 ファイル作成 */

#include "EnemySpawnPoint_Base.h"

/* エネミースポナーベースクラスの定義 */
// コンストラクタ
EnemySpawnPoint_Base::EnemySpawnPoint_Base() : PlatformBase()
{
	/* データリストを取得 */
	{
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}
}

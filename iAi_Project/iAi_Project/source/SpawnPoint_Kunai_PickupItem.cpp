/* 2025.03.22 駒沢風助 ファイル作成 */

#include "SpawnPoint_Kunai_PickupItem.h"

/* クナイ(ピックアップアイテム)スポナークラスの定義 */
// コンストラクタ
SpawnPoint_Kunai_PickupItem::SpawnPoint_Kunai_PickupItem() : SpawnPoint_Base()
{

}

// 初期化
void SpawnPoint_Kunai_PickupItem::Initialization()
{
	/* クナイ(ピックアップアイテム)生成処理 */
	{
		/* クナイ(ピックアップアイテム)を作成 */
		PickUpItemBase* AddPickUpItem = new PickUpItem_Kunai();

		/* 生成したクナイ(ピックアップアイテム)をリストに追加 */
		this->ObjectList->SetPickUpItem(AddPickUpItem);

		/* 生成したクナイ(ピックアップアイテム)の座標を設定 */
		AddPickUpItem->SetPosition(this->vecPosition);

		/* 生成したクナイ(ピックアップアイテム)の回転量を設定 */
		AddPickUpItem->SetRotation(this->vecRotation);

		/* 生成したクナイ(ピックアップアイテム)の初期化処理 */
		AddPickUpItem->Initialization();
	}
}

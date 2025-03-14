/* 2025.03.14 駒沢風助 ファイル作成 */

#include "SpawnPoint_Blood_PickupItem.h"

/* ブラッド(ピックアップアイテム)スポナークラスの定義 */
// コンストラクタ
SpawnPoint_Blood_PickupItem::SpawnPoint_Blood_PickupItem() : SpawnPoint_Base()
{

}

// 初期化
void SpawnPoint_Blood_PickupItem::Initialization()
{
	/* ブラッド(ピックアップアイテム)生成処理 */
	{
		/* ブラッド(ピックアップアイテム)を作成 */
		PickUpItemBase* AddPickUpItem = new PickUpItem_Blood();

		/* 生成したブラッド(ピックアップアイテム)をリストに追加 */
		this->ObjectList->SetPickUpItem(AddPickUpItem);

		/* 生成したブラッド(ピックアップアイテム)の座標を設定 */
		AddPickUpItem->SetPosition(this->vecPosition);

		/* 生成したブラッド(ピックアップアイテム)の回転量を設定 */
		AddPickUpItem->SetRotation(this->vecRotation);

		/* 生成したブラッド(ピックアップアイテム)の初期化処理 */
		AddPickUpItem->Initialization();
	}
}

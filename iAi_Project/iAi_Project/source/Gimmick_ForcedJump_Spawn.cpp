/* 2025.02.12 駒沢風助 ファイル作成 */

#include "Gimmick_ForcedJump_Spawn.h"

/* 強制ジャンプギミックスポナークラスの定義 */
// コンストラクタ
Gimmick_ForcedJump_Spawn::Gimmick_ForcedJump_Spawn() : PlatformBasic()
{
	/* データリストを取得 */
	{
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* 初期化 */
	{
		this->bSpawnObjectFlg	= true;
		this->iSpawnCoolTime	= 0;
	}
}

// デストラクタ
Gimmick_ForcedJump_Spawn::~Gimmick_ForcedJump_Spawn()
{

}

// 更新
void Gimmick_ForcedJump_Spawn::Update()
{
	/* オブジェクトのスポーンフラグが有効かつ、クールタイムが終了しているか確認 */
	if (this->bSpawnObjectFlg == true && this->iSpawnCoolTime <= 0)
	{
		// 有効かつクールタイムが終了しているならば
		/* アイテム"強制ジャンプ(ギミック)"生成処理" */
		{
			/* アイテム"強制ジャンプ(ギミック)"を作成 */
			PickUpItemBase* AddItem = new PickUpItem_ForcedJump();

			/* 生成したアイテムをリストに追加 */
			this->ObjectList->SetPickUpItem(AddItem);

			/* 生成したアイテムの生成元にこのオブジェクトを追加*/
			dynamic_cast<PickUpItem_ForcedJump*>(AddItem)->SetGimmick_ForcedJump_Spawn(this);

			/* 生成したアイテムの座標を設定 */
			AddItem->SetPosition(this->vecPosition);

			/* 生成したアイテムの回転量を設定 */
			AddItem->SetRotation(this->vecRotation);

			/* 生成したアイテムの初期化処理 */
			AddItem->Initialization();
		}

		/* オブジェクトのスポーンフラグを無効に設定 */
		this->bSpawnObjectFlg = false;

		/* クールタイムを設定 */
		this->iSpawnCoolTime = 60 * 3;
	}

	/* スポーンのクールタイムが0より大きいか確認 */
	if (this->iSpawnCoolTime > 0)
	{
		// 0より大きいならば
		/* クールタイムを減少 */
		this->iSpawnCoolTime--;
	}
}

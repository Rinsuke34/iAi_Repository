/* 2025.03.04 駒沢風助 ファイル作成 */

#include "Gimmick_FallJudgment.h"

/* 落下判定クラスの定義 */
// コンストラクタ
Gimmick_FallJudgment::Gimmick_FallJudgment() : PlatformBase()
{
	/* データリストを取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "プレイヤー状態管理"を取得 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Gimmick/FallJudgment/FallJudgment");
	}	
}

// 更新
void Gimmick_FallJudgment::Update()
{
	/* プレイヤーを取得 */
	CharacterBase* pPlayer = ObjectList->GetCharacterPlayer();

	/* プレイヤーが存在しているか確認 */
	if (pPlayer != nullptr)
	{
		//プレイヤーが存在している場合
		/* プレイヤーと接触しているか確認 */
		if (pPlayer->HitCheck(this->iModelHandle, this->iCollisionFrameNo))
		{
			// 接触している場合
			/* プレイヤーの落下判定を有効にする */
			this->PlayerStatusList->SetFallFlg(true);
		}
	}
	

	/* エネミーと接触しているか確認 */
	for (auto& enemy : this->ObjectList->GetEnemyList())
	{
		if (enemy->HitCheck(this->iModelHandle, this->iCollisionFrameNo))
		{
			// 接触している場合
			/* エネミーの削除フラグを有効にする */
			enemy->SetDeleteFlg(true);
		}
	}
}

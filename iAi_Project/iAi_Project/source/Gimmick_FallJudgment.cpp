/* 2025.03.04 駒沢風助 ファイル作成 */

#include "Gimmick_FallJudgment.h"

/* 落下判定クラスの定義 */
// コンストラクタ
Gimmick_FallJudgment::Gimmick_FallJudgment() : PlatformBasic()
{
	/* データリストを取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "プレイヤー状態管理"を取得 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}
}

// 更新
void Gimmick_FallJudgment::Update()
{
	/* プレイヤーと接触しているか確認 */
	if (this->ObjectList->GetCharacterPlayer()->HitCheck(this->iModelHandle, this->iCollisionFrameNo))
	{
		// 接触している場合
		/* プレイヤーの落下判定を有効にする */
		this->PlayerStatusList->SetFallFlg(true);
	}
}

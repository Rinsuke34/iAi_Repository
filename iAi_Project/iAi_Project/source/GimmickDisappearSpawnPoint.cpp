/* 2025.03.19 石川智也 ファイル作成 */

#include "GimmickDisappearSpawnPoint.h"

/* エネミー(ノーマル)スポナークラスの定義 */
// コンストラクタ
GimmickDisappearSpawnPoint::GimmickDisappearSpawnPoint() : SpawnPoint_Base()
{
	/* 変数初期化 */
	this->bAddObjectFlg = false;

	/* リスポーンカウント */
	this->iRespawnDelay = 0;
}

// 初期化
void GimmickDisappearSpawnPoint::Initialization()
{
	Update();
}

// 更新
void GimmickDisappearSpawnPoint::Update()
{
	/* オブジェクト生成フラグが無効であるか確認 */
	if (this->bAddObjectFlg == false)
	{
		// 無効である場合
		/* リスポーン待機時間中であるか確認 */
		if (this->iRespawnDelay <= 0)
		{
			// 0以下(待機時間が完了している)場合
			/* エネミー(ノーマル)生成処理 */
			{
				/* "オブジェクト管理"に床消失を追加 */
				GimmickDisappear* pPlatform = new GimmickDisappear();
				this->ObjectList->SetPlatform(pPlatform);

				/* 座標 */
				pPlatform->SetPosition(vecPosition);

				/* 回転量 */
				pPlatform->SetRotation(vecRotation);

				/* 拡大率 */
				pPlatform->SetScale(vecScale);

				pPlatform->Initialization();

				pPlatform->SetSpawnPoint(this);

				this->bAddObjectFlg = true;

				this->iRespawnDelay = 60 * 3;
			}
		}
		else
		{
			// 待機時間中である場合
			/* 待機時間を減算 */
			this->iRespawnDelay--;
		}
	}
}
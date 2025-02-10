/* 2025.02.10 石川智也 ファイル作成 */
#include "GimmickDisappear.h"

// コンストラクタ
GimmickDisappear::GimmickDisappear() : PlatformBasic()
{
	/* データリスト */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}
	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));
		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Gimmick/cube");
	}
	this->pPlayer = ObjectList->GetCharacterPlayer();

	//ギミックの消滅時間
	this->iDisappearTime = GIMMICK_DISAPPEAR_TIME;

	//ギミックテクスチャ変更カウント
	this->iTextureChangeCount = GIMMICK_TEXTURE_CHANGE_COUNT;

	this->textureHandle = LoadGraph("resource/ModelData/Gimmick/本家.mp4");
}

// デストラクタ
GimmickDisappear::~GimmickDisappear()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
}

//ギミックの処理
void GimmickDisappear::ProcessGimmick()
{
	//プレイヤーの座標を取得
	VECTOR playerPos = pPlayer->vecGetPosition();

	//プレイヤーがギミックの上に乗っているか確認
	if (playerPos.x > this->vecPosition.x - 50 && playerPos.x < this->vecPosition.x + 50 &&
		playerPos.y > this->vecPosition.y - 50 && playerPos.y < this->vecPosition.y + 50 &&
		playerPos.z > this->vecPosition.z - 50 && playerPos.z < this->vecPosition.z + 50)
	{
		//プレイヤーがギミックの上に乗っている場合
		//180フレーム後にギミックを消滅させる
		iTextureChangeCount--;
		if (iTextureChangeCount <= 0)
		{
			iDisappearTimeCount++;
			PlayMovieToGraph(textureHandle); // 再生開始

			// 新しいテクスチャを設定
			MV1SetTextureGraphHandle(iModelHandle, 0, textureHandle, true);
			
			if (iDisappearTimeCount == GIMMICK_DISAPPEAR_TIME)
			{
				//再生終了
				PauseMovieToGraph(textureHandle);
				
				//ギミックを消滅させる
				this->SetDeleteFlg(true);
			}
		}
	}
}

// 更新
void GimmickDisappear::Update()
{
	ProcessGimmick();
}

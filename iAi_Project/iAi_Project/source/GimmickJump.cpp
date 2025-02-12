/* 2025.02.10 石川智也 ファイル作成 */
#include "GimmickJump.h"

// コンストラクタ
GimmickJump::GimmickJump() : PlatformBasic()
{
	/* データリスト */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
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
GimmickJump::~GimmickJump()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
}

//ギミックの処理
void GimmickJump::ProcessGimmick()
{
	//プレイヤーの座標を取得
	VECTOR playerPos = pPlayer->vecGetPosition();

	//プレイヤーがギミックの上に乗っているか確認
	if (playerPos.x > this->vecPosition.x - 50 && playerPos.x < this->vecPosition.x + 50 &&
		playerPos.y > this->vecPosition.y - 50 && playerPos.y < this->vecPosition.y + 50 &&
		playerPos.z > this->vecPosition.z - 50 && playerPos.z < this->vecPosition.z + 50)
	{
		//プレイヤーがギミックの上に乗っている場合
		//プレイヤーのジャンプ回数を1に設定
		this->PlayerStatusList->SetPlayerJumpCount(1);
		this->PlayerStatusList->SetPlayerNowFallSpeed(-30.0f);
		
		//プレイヤーがギミックの上に乗っている場合
		//180フレーム後にギミックを消滅させる
		iTextureChangeCount--;
		if (iTextureChangeCount <= 0)
		{
			iDisappearTimeCount++;
			PlayMovieToGraph(textureHandle); // 再生開始

			// 新しいテクスチャを設定
			MV1SetTextureGraphHandle(iModelHandle, 0, textureHandle, true);
			

		}
	}
}

// 更新
void GimmickJump::Update()
{
	ProcessGimmick();
}

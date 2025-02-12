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

	//プレイヤーの情報を取得
	this->pPlayer = ObjectList->GetCharacterPlayer();

	//ギミックの消滅時間
	this->iDisappearTime = GIMMICK_DISAPPEAR_TIME;

	//ギミックテクスチャ変更カウント
	this->iTextureChangeCount = GIMMICK_TEXTURE_CHANGE_FIRST_COUNT;
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

		//プレイヤーを吹き飛ばす
		this->PlayerStatusList->SetPlayerNowFallSpeed(-30.0f);

		//プレイヤーのジャンプ回数を1に設定
		this->PlayerStatusList->SetPlayerNowJumpCount(1);
	}
}

// 更新
void GimmickJump::Update()
{
	//ギミックの処理
	ProcessGimmick();
}

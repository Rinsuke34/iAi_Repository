/* 2025.02.10 石川智也 ファイル作成 */
#include "GimmickDisappear.h"

// コンストラクタ
GimmickDisappear::GimmickDisappear() : PlatformBase()
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
		this->iModelHandle = ModelListHandle->iGetModel("Object/DisappearFloor/DisappearFloor");
	}

	//プレイヤーの情報を取得
	this->pPlayer = ObjectList->GetCharacterPlayer();

	//ギミックの消滅時間
	this->iDisappearTime = GIMMICK_DISAPPEAR_TIME;

	//ギミックテクスチャ変更カウント
	this->iTextureFirstChangeCount = GIMMICK_TEXTURE_CHANGE_FIRST_COUNT;

	//ギミックテクスチャ変更カウント
	this->iTextureSecondChangeCount = GIMMICK_TEXTURE_CHANGE_SECOND_COUNT;

	// テクスチャの読み込み
	this->textureOrangeHandle = LoadGraph("resource/ModelData/Gimmick/Orange.png");

	// テクスチャの読み込み
	this->textureRedHandle = LoadGraph("resource/ModelData/Gimmick/aka.png");
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
		/* エフェクト追加 */

		/*爆発エフェクトを生成 */
		this->pEffectSine = new EffectManualDelete();

		/* エフェクトの読み込み */
		this->pEffectSine->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_g_mine_sine/FX_g_mine_sine")));

		/* エフェクトの座標設定 */
		this->pEffectSine->SetPosition(this->vecPosition);

		/* エフェクトの回転量設定 */
		this->pEffectSine->SetRotation(this->vecRotation);

		/* エフェクトの初期化 */
		this->pEffectSine->Initialization();

		/* エフェクトをリストに登録 */
		{
			/* "オブジェクト管理"データリストを取得 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* エフェクトをリストに登録 */
			ObjectListHandle->SetEffect(this->pEffectSine);
		}
		//テクスチャの変更カウントを減らす
		iTextureFirstChangeCount--;

		//テクスチャの変更カウントが0以下になったか確認
		if (iTextureFirstChangeCount <= 0)
		{
			//テクスチャの変更カウントが0以下になった場合
			// 0番のテクスチャをオレンジテクスチャに変更
			MV1SetTextureGraphHandle(iModelHandle, 0, textureOrangeHandle, true);

			//セカンドテクスチャの変更カウントを減らす
			iTextureSecondChangeCount--;

			//セカンドテクスチャの変更カウントが0以下になったか確認
			if (iTextureSecondChangeCount <= 0)
		{
				//セカンドテクスチャの変更カウントが0以下になった場合

				//ギミックの消滅時間カウントを増やす
			iDisappearTimeCount++;

				// 0番のテクスチャを赤テクスチャに変更
				MV1SetTextureGraphHandle(iModelHandle, 0, textureRedHandle, true);
			
				//PlayMovieToGraph(textureHandle); // 再生開始

				//ギミックの消滅時間カウントが一定数になったか確認
			if (iDisappearTimeCount == GIMMICK_DISAPPEAR_TIME)
			{
				//ギミックの消滅時間カウントが一定数になった場合
				//再生終了
				//	PauseMovieToGraph(textureHandle);
				
				//ギミックを消滅させる
				this->SetDeleteFlg(true);
			}
		}
	}
}
}

// 更新
void GimmickDisappear::Update()
{
	//ギミックの処理
	ProcessGimmick();
}

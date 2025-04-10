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
		this->iModelHandle = ModelListHandle->iGetModel("Gimmick/DisappearFloor/DisappearFloor");
	}

	//プレイヤーの情報を取得
	this->pPlayer = ObjectList->GetCharacterPlayer();

	//ギミックの消滅時間
	this->iDisappearTime = GIMMICK_DISAPPEAR_TIME;

	//ギミックテクスチャ変更カウント
	this->iTextureFirstChangeCount = GIMMICK_TEXTURE_CHANGE_FIRST_COUNT;

	//ギミックテクスチャ変更カウント
	this->iTextureSecondChangeCount = GIMMICK_TEXTURE_CHANGE_SECOND_COUNT;

	//ギミックのスポーンカウント
	this->iSpawnCount = GIMMICK_SPAWN_COUNT;

	//ギミックの消滅時間カウント
	this->iDisappearTimeCount = GIMMICK_BLINK_TIME;

	this->bRidePlayerFlg = false;

	/* データリスト"画像ハンドル管理"を取得 */
	DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));
	// テクスチャの読み込み
	this->iTextureOrangeHandle = *ImageList->piGetImage("DisappearFloor/Orange");

	// テクスチャの読み込み
	this->iTextureRedHandle = *ImageList->piGetImage("DisappearFloor/Red");

	this->iTextureYellowHandle = *ImageList->piGetImage("DisappearFloor/Yellow");

	MV1SetTextureGraphHandle(iModelHandle, 0, iTextureYellowHandle, true);
	MV1SetTextureGraphHandle(iModelHandle, 1, iTextureYellowHandle, true);
}
 
// デストラクタ
GimmickDisappear::~GimmickDisappear()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
	this->pGimmickDisappearSpawnPoint->SetAddobjectFlg(false);
}

//ギミックの処理
void GimmickDisappear::ProcessGimmick()
{
	//プレイヤーの座標を取得
	VECTOR playerPos = pPlayer->vecGetPosition();
		if (this->bRidePlayerFlg == true)
	{
		//プレイヤーがギミックの上に乗っている場合
		//テクスチャの変更カウントを減らす
		iTextureFirstChangeCount = 0;
;

		//テクスチャの変更カウントが0以下になったか確認
		if (iTextureFirstChangeCount <= 0)
		{
			//テクスチャの変更カウントが0以下になった場合
			// 0番のテクスチャをオレンジテクスチャに変更
			MV1SetTextureGraphHandle(iModelHandle, 0, iTextureOrangeHandle, true);
			MV1SetTextureGraphHandle(iModelHandle, 1, iTextureOrangeHandle, true);

			//セカンドテクスチャの変更カウントを減らす
			iTextureSecondChangeCount--;

			//セカンドテクスチャの変更カウントが0以下になったか確認
			if (iTextureSecondChangeCount <= 0)
			{
				//セカンドテクスチャの変更カウントが0以下になった場合

				//ギミックの消滅時間カウントを増やす
				iDisappearTimeCount++;

				// 0番のテクスチャを赤テクスチャに変更
				MV1SetTextureGraphHandle(iModelHandle, 0, iTextureRedHandle, true);
				MV1SetTextureGraphHandle(iModelHandle, 1, iTextureRedHandle, true);

				
			

				//ギミックの消滅時間カウントが一定数になったか確認
				if (iDisappearTimeCount >= GIMMICK_DISAPPEAR_TIME)
				{
					//ギミックの消滅時間カウントが一定数になった場合
				
					//ギミックを消す
					MV1SetVisible(this->iModelHandle, FALSE);

					//コリジョンを削除
					this->bDeleteFlg = true;

					//スポーンカウントを減らす
					this->iSpawnCount--;


				}
				else if (iDisappearTimeCount <= GIMMICK_DISAPPEAR_TIME && iDisappearTimeCount >= GIMMICK_DISAPPEAR_TIME/2)
				{
					//点滅処理
					this->iBlinkTime--;
					if (this->iBlinkTime <= 4)
					{
						//点滅時間が0以下になった場合
						//ギミックを点滅させる
						MV1SetVisible(this->iModelHandle, FALSE);
						this->iBlinkTime = GIMMICK_BLINK_TIME;
					}
					else
					{
						//点滅時間が0以下になっていない場合
						//ギミックを点滅させない
						MV1SetVisible(this->iModelHandle, TRUE);
					}
				}
			}
		}
	}

		//スポーンカウントが0以下になったか確認
		if (this->iSpawnCount <= 0)
		{
			//this->bDeleteFlg = true;
		}
}

// 更新
void GimmickDisappear::Update()
{
	//ギミックの処理
	ProcessGimmick();
}

// リセット処理
void GimmickDisappear::Reset()
{
	//ギミックの消滅時間
	this->iDisappearTime = GIMMICK_DISAPPEAR_TIME;

	//ギミックテクスチャ変更カウント
	this->iTextureFirstChangeCount = GIMMICK_TEXTURE_CHANGE_FIRST_COUNT;

	//ギミックテクスチャ変更カウント
	this->iTextureSecondChangeCount = GIMMICK_TEXTURE_CHANGE_SECOND_COUNT;

	//ギミックのスポーンカウント
	this->iSpawnCount = GIMMICK_SPAWN_COUNT;

	//ギミックの消滅時間カウント
	this->iDisappearTimeCount = GIMMICK_BLINK_TIME;

	this->bRidePlayerFlg = false;

	

	MV1SetTextureGraphHandle(iModelHandle, 0, iTextureYellowHandle, true);
	MV1SetTextureGraphHandle(iModelHandle, 1, iTextureYellowHandle, true);
}

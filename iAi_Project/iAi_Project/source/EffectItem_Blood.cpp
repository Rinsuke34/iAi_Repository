/* 2025.02.11 駒沢風助 ファイル作成 */

#include "EffectItem_Blood.h"

/* ブラッド(ゲーム内通貨)クラスの定義 */
// コンストラクタ
EffectItem_Blood::EffectItem_Blood() : EffectItemBase()
{
	/* データリストを取得 */
	{
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* 初期化 */
	{
		this->iMoveCount = 30;
		this->iMoveFaze = MOVE_FAZE_RUNDOM;
	}

	/* 移動方向をランダム方向に設定 */
	{
		this->vecMoveDirection = VGet((float)(GetRand(100) - 50) / 100.0f, (float)(GetRand(100) - 50) / 100.0f, (float)(GetRand(100) - 50) / 100.0f);
	}

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Item/Blood/Blood");

		/* モデル縮小 */
		MV1SetScale(this->iModelHandle, VGet(0.2f, 0.2f, 0.2f));

		UpdataLightFrame();
	}
}

// 更新
void EffectItem_Blood::Update()
{
	/* 現在のフェーズに応じて処理を変更する */
	switch (this->iMoveFaze)
	{
		/* ランダム方向へ移動 */
		case MOVE_FAZE_RUNDOM:
			/* 移動方向に設定された方向へ移動 */
			this->vecPosition = VAdd(this->vecPosition, VScale(this->vecMoveDirection, MOVE_SPEED_RUNDOM));

			/* 移動カウントが以下になった場合 */
			if (this->iMoveCount < 0)
			{
				/* プレイヤーに向かって移動するフェーズへ移行 */
				this->iMoveFaze = MOVE_FAZE_PLAYER;
			}
			break;

		/* プレイヤーに向かって移動 */
		case MOVE_FAZE_PLAYER:
			/* プレイヤーの中心座標を取得 */
			VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();
			vecPlayerPos.y += PLAYER_HEIGHT / 2;

			/* プレイヤーの座標に向かって移動 */
			this->vecPosition = VAdd(this->vecPosition, VScale(VNorm(VSub(vecPlayerPos, this->vecPosition)), MOVE_SPEED_PLAYER));

			/* プレイヤーの座標に到達した場合 */
			if (VSize(VSub(vecPlayerPos, this->vecPosition)) <= MOVE_SPEED_PLAYER * 1.5f)
			{
				/* 削除フラグを有効化 */
				this->bDeleteFlg = true;

				/* ブラッドをプレイヤーに加算 */
				{
					/* データリスト取得 */
					DataList_GameResource* GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));

					/* ブラッドをプレイヤーに加算 */
					int iNowBlood = GameResourceList->iGetHaveBlood();
					GameResourceList->SetHaveBlood(iNowBlood + 1);
				}

				/* "ブラッド取得"のSEを再生 */
				gpDataList_Sound->SE_PlaySound(SE_PLAYER_GET_BLOOD);
			}
			break;
	}
	
	/* カウントを進める */
	this->iMoveCount -= 1;
}

// リセット処理
void EffectItem_Blood::Reset()
{
	/* このオブジェクトの削除フラグを有効にする */
	this->bDeleteFlg = true;
}

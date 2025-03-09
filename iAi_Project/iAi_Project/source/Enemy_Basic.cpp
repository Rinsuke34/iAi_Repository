/* 2025.01.27 駒沢風助 ファイル作成 */

#include "Enemy_Basic.h"

/* 基本エネミークラスの定義 */

// コンストラクタ
Enemy_Basic::Enemy_Basic() : EnemyBase()
{
	/* データリストを取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "オプション設定管理"を取得 */
		this->OptionList = dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));
	}

	/* 初期化 */
	this->iPlayerLockOnType	= PLAYER_LOCKON_NONE;	// ロックオンされていない状態にする
	this->iCoreFrameNo		= -1;					// コアフレーム番号を初期化
}

// 発光描写
void Enemy_Basic::BloomDraw()
{
	/* カメラ位置からの距離を取得 */
	float fDistance = VSize(VSub(this->vecPosition, this->StageStatusList->vecGetCameraPosition()));

	/* カメラからの距離との距離がエネミー描写距離の範囲内であるか */
	if (fDistance < OptionList->fGetEnemyDrawDistance())
	{
		/* 発光部分の描写 */
		CharacterBase::BloomDraw();
	}
}

// 当たり判定描写
void Enemy_Basic::CollisionDraw()
{
	/* カメラ位置からの距離を取得 */
	float fDistance = VSize(VSub(this->vecPosition, this->StageStatusList->vecGetCameraPosition()));

	/* カメラからの距離との距離がエネミー描写距離の範囲内であるか */
	if (fDistance < OptionList->fGetEnemyDrawDistance())
	{
		/* 当たり判定の描写 */
		CharacterBase::CollisionDraw();
	}
}

// 描写
void Enemy_Basic::Draw()
{
	/* カメラ位置からの距離を取得 */
	float fDistance = VSize(VSub(this->vecPosition, this->StageStatusList->vecGetCameraPosition()));

	/* カメラからの距離との距離がエネミー描写距離の範囲内であるか */
	if (fDistance < OptionList->fGetEnemyDrawDistance())
	{
		/* 描写 */
		CharacterBase::Draw();
	}
}

// リセット処理
void Enemy_Basic::Reset()
{
	/* このオブジェクトの削除フラグを有効にする */
	this->bDeleteFlg = true;
}

// 敵撃破時の処理
void Enemy_Basic::Defeat()
{
	/* プレイヤーのコンボ数加算＆継続時間リセット */
	{
		/* データリスト取得 */
		DataList_PlayerStatus* PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* データリストが存在しない(強制終了された)場合は処理を終了する */
		if (PlayerStatusList == nullptr)
		{
			return;
		}

		/* プレイヤーのコンボ数加算 */
		PlayerStatusList->SetPlayerComboNowCount(PlayerStatusList->iGetPlayerComboNowCount() + 1);

		/* プレイヤーのコンボ継続時間リセット */
		PlayerStatusList->SetPlayerComboDuration(INIT_ATTRIBUTES_COMBO_DURATION);
	}

	/* 爆発エフェクト生成 */
	{
		/* 時間経過で削除されるエフェクトを追加 */
		EffectSelfDelete* AddEffect = new EffectSelfDelete();

		/* エフェクト読み込み */
		AddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_die/FX_e_die")));

		/* エフェクトの座標設定 */
		AddEffect->SetPosition(this->vecPosition);

		/* エフェクトの回転量設定 */
		AddEffect->SetRotation(this->vecRotation);

		/* エフェクトの削除されるまでの時間を設定 */
		AddEffect->SetDeleteCount(30);

		/* エフェクトの初期化 */
		AddEffect->Initialization();

		/* リストに登録 */
		{
			/* "オブジェクト管理"データリストを取得 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* エフェクトをリストに登録 */
			ObjectListHandle->SetEffect(AddEffect);
		}
	}

	/* ブラッド(ゲーム内通貨)を作成 */
	{
		/* "オブジェクト管理"データリストを取得 */
		DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		for (int i = 0; i < 10; i++)
		{
			/* 時間経過で削除されるアイテムを追加 */
			EffectItemBase* AddItem = new EffectItem_Blood();

			/* エフェクトの座標設定 */
			AddItem->SetPosition(this->vecPosition);

			/* エフェクトをリストに登録 */
			ObjectListHandle->SetEffectItem(AddItem);
		}
	}

	/* エネミーの削除フラグを有効にする */
	this->bDeleteFlg = true;
}

// コアフレーム番号取得
void Enemy_Basic::LoadCoreFrameNo()
{
	/* コアフレーム番号を取得 */
	this->iCoreFrameNo = MV1SearchFrame(this->iModelHandle, "Core");
}

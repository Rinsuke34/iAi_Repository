/* 2025.01.27 駒沢風助 ファイル作成 */

#include "EnemyBasic.h"

/* 基本エネミークラスの定義 */

// コンストラクタ
EnemyBasic::EnemyBasic() : EnemyBase()
{
	/* 初期化 */
	this->iPlayerLockOnType	= PLAYER_LOCKON_NONE;	// ロックオンされていない状態にする
	this->iCoreFrameNo		= -1;					// コアフレーム番号を初期化
}

// デストラクタ
EnemyBasic::~EnemyBasic()
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

	/* 仮処理 */
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
}

// コアフレーム番号取得
void EnemyBasic::LoadCoreFrameNo()
{
	/* コアフレーム番号を取得 */
	this->iCoreFrameNo = MV1SearchFrame(this->iModelHandle, "Core");
}

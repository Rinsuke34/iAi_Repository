/* 2025.02.10 石川智也 ファイル作成 */

#include "PickUpItem_ForcedJump.h"

/* 強制ジャンプアイテム(ギミック)クラスの定義 */
// コンストラクタ
PickUpItem_ForcedJump::PickUpItem_ForcedJump() : PickUpItemBase()
{
	/* データリスト取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}

	/* オブジェクト取得 */
	{
		/* プレイヤーを取得 */
		this->pPlayer = dynamic_cast<CharacterPlayer*>(ObjectList->GetCharacterPlayer());
	}

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Gimmick/ForcedJump/ForcedJump");

		// ３Ｄモデルのスケールを調整
		MV1SetScale(this->iModelHandle, VGet(0.25f, 0.25f, 0.25f));
	}
}

// 初期化
void PickUpItem_ForcedJump::Initialization()
{
	/* 発光するフレームを取得 */
	UpdataLightFrame();

	/* コリジョン設定 */
	{
		this->stCollisionCapsule.fCapsuleRadius		= 65.0f;
		this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0.0f, 100.0f, 0.0f));
		this->stCollisionCapsule.vecCapsuleBottom	= VAdd(this->vecPosition, VGet(0.0f, 25.0f, 0.0f));
	}

	//光エフェクトを生成
	this->pEffectLight = new EffectManualDelete();

	/* エフェクトの読み込み */
	this->pEffectLight->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_g_mine_sine/FX_g_mine_sine")));

	/* エフェクトの座標設定 */
	this->pEffectLight->SetPosition(VGet(this->vecPosition.x, this->vecPosition.y + 118.0f, this->vecPosition.z));

	/* エフェクトの回転量設定 */
	this->pEffectLight->SetRotation(this->vecRotation);

	/*エフェクトの拡大率設定*/
	this->pEffectLight->SetScale(VGet(6.0f, 6.0f, 6.0f));

	/* エフェクトの初期化 */
	this->pEffectLight->Initialization();

	/* エフェクトをリストに登録 */
	{
		/* "オブジェクト管理"データリストを取得 */
		DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
		/* エフェクトをリストに登録 */
		ObjectListHandle->SetEffect(this->pEffectLight);
	}
}

// 更新
void PickUpItem_ForcedJump::Update()
{
	/* プレイヤーとこのギミックが接触しているか確認 */
	if (this->pPlayer->HitCheck(this->stCollisionCapsule))
	{
		/* エフェクト追加 */

		/*爆発エフェクトを生成 */
		this->pEffectExplosion = new EffectManualDelete();

		/* エフェクトの読み込み */
		this->pEffectExplosion->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_g_mine_explosion/FX_g_mine_explosion")));

		/* エフェクトの座標設定 */
		this->pEffectExplosion->SetPosition(this->vecPosition);

		/* エフェクトの回転量設定 */
		this->pEffectExplosion->SetRotation(this->vecRotation);

		/*エフェクトの拡大率設定*/
		this->pEffectExplosion->SetScale(VGet(4.5f, 4.5f, 4.5f));

		/* エフェクトの初期化 */
		this->pEffectExplosion->Initialization();

		/* エフェクトをリストに登録 */
		{
			/* "オブジェクト管理"データリストを取得 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* エフェクトをリストに登録 */
			ObjectListHandle->SetEffect(this->pEffectExplosion);
		}

		/* "ジャンプギミック爆発"のSEを再生 */
		gpDataList_Sound->SE_PlaySound_3D(SE_GIMMIC_JUMPEXPLP, this->vecPosition, SE_3D_SOUND_RADIUS);

		/* プレイヤーが接触している場合 */
		//プレイヤーを吹き飛ばす
		this->PlayerStatusList->SetPlayerNowFallSpeed(-40.0f);

		//プレイヤーのジャンプ回数を1に設定
		this->PlayerStatusList->SetPlayerNowJumpCount(1);

		/* このオブジェクトの削除フラグを有効にする */
		this->bDeleteFlg = true;

		/* 生成元のスポーンフラグを有効にする */
		this->pGimmick_ForcedJump_Spawn->SetSpawnObjectFlg(true);

		//光エフェクトを削除
		this->pEffectLight->SetDeleteFlg(true);
	}
}

// リセット処理
void PickUpItem_ForcedJump::Reset()
{
	/* このオブジェクトの削除フラグを有効にする */
	this->bDeleteFlg = true;
}

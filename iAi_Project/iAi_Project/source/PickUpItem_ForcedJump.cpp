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

	/* コリジョン設定 */
	{
		this->stCollisionCapsule.fCapsuleRadius		= 50.0f;
		this->stCollisionCapsule.vecCapsuleTop		= VGet(0.0f, 50.0f, 0.0f);
		this->stCollisionCapsule.vecCapsuleBottom	= VGet(0.0f, -50.0f, 0.0f);
	}
}

// デストラクタ
PickUpItem_ForcedJump::~PickUpItem_ForcedJump()
{

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

		/* エフェクトの初期化 */
		this->pEffectExplosion->Initialization();

		/* エフェクトをリストに登録 */
		{
			/* "オブジェクト管理"データリストを取得 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* エフェクトをリストに登録 */
			ObjectListHandle->SetEffect(this->pEffectExplosion);
		}

		/* プレイヤーが接触している場合 */
		//プレイヤーを吹き飛ばす
		this->PlayerStatusList->SetPlayerNowFallSpeed(-30.0f);

		//プレイヤーのジャンプ回数を1に設定
		this->PlayerStatusList->SetPlayerNowJumpCount(1);

		/* このオブジェクトの削除フラグを有効にする */
		this->bDeleteFlg = true;

		/* 生成元のスポーンフラグを有効にする */
		this->pGimmick_ForcedJump_Spawn->SetSpawnObjectFlg(true);
	}
}

// 描写
void PickUpItem_ForcedJump::Draw()
{
	/* 仮描写(本番ではモデル) */
	int iColor = GetColor(255, 255, 0);
	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius, 16, iColor, iColor, FALSE);
}

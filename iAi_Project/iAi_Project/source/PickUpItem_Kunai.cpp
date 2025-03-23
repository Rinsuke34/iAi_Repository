/* 2025.03.22 駒沢風助 ファイル作成 */

#include "PickUpItem_Kunai.h"

/* クナイ(ピックアップアイテム)クラスの定義 */
// コンストラクタ
PickUpItem_Kunai::PickUpItem_Kunai() : PickUpItemBase()
{
	/* データリスト取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "プレイヤー状態管理"を取得 */
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
		this->iModelHandle = ModelListHandle->iGetModel("Item/Kunai/Kunai");

		/* モデル縮小 */
		MV1SetScale(this->iModelHandle, VGet(0.2f, 0.2f, 0.2f));
	}

	/* 初期化 */
	this->iAddEffectDelay = 0;			// エフェクト追加待機時間
}

// 初期化
void PickUpItem_Kunai::Initialization()
{
	/* 発光するフレームを取得 */
	UpdataLightFrame();

	/* コリジョン設定 */
	{
		this->stCollisionCapsule.fCapsuleRadius = 100.0f;
		this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0.0f, 400.0f, 0.0f));
		this->stCollisionCapsule.vecCapsuleBottom = VAdd(this->vecPosition, VGet(0.0f, 100.0f, 0.0f));
	}
}

// 更新
void PickUpItem_Kunai::Update()
{
	/* プレイヤーとこのオブジェクトが接触しているか確認 */
	if (this->pPlayer->HitCheck(this->stCollisionCapsule))
	{
		/* このオブジェクトの削除フラグを有効にする */
		this->bDeleteFlg = true;

		/* プレイヤーの最大クナイ所持本数を取得 */
		int iMaxKunai = this->PlayerStatusList->iGetMaxHaveKunai();

		/* プレイヤーの所持クナイ数を取得 */
		int iHaveKunai = this->PlayerStatusList->iGetNowHaveKunai();

		/* プレイヤーの所持クナイ数を加算 */
		iHaveKunai += 1;

		/* プレイヤーの所持クナイ数が最大所持数を超えているか確認 */
		if (iHaveKunai > iMaxKunai)
		{
			// 超えている場合
			/* プレイヤーの所持クナイ数を最大所持数に設定 */
			iHaveKunai = iMaxKunai;
		}

		/* プレイヤーの所持クナイ数を設定 */
		this->PlayerStatusList->SetNowHaveKunai(iHaveKunai);

		/* クナイ取得のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_PLAYER_KUNAI_GET);
	}

	/* エフェクト待機時間を更新 */
	this->iAddEffectDelay -= 1;

	/* エフェクト待機時間が0以下であるか確認 */
	if (this->iAddEffectDelay <= 0)
	{
		// 0以下である場合
		/* エフェクトを生成 */
		EffectSelfDelete* pAddEffect = new EffectSelfDelete();

		/* エフェクトの読み込み */
		pAddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_glitter/FX_e_glitter")));

		/* エフェクトの座標設定 */
		pAddEffect->SetPosition(this->vecPosition);

		/* エフェクトの回転量設定 */
		pAddEffect->SetRotation(this->vecRotation);

		/* エフェクトの削除時間を設定 */
		pAddEffect->SetDeleteCount(30);

		/* エフェクトの初期化 */
		pAddEffect->Initialization();

		/* エフェクトをリストに登録 */
		this->ObjectList->SetEffect(pAddEffect);

		/* エフェクト待機時間をリセット */
		this->iAddEffectDelay = 10;
	}
}

// リセット処理
void PickUpItem_Kunai::Reset()
{
	/* このオブジェクトの削除フラグを有効にする */
	this->bDeleteFlg = true;
}


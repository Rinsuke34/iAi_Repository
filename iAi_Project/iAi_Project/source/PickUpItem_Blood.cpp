/* 2025.03.14 駒沢風助 ファイル作成 */

#include "PickUpItem_Blood.h"

/* ブラッド(ゲーム内通貨/ピックアップアイテム)クラスの定義 */
// コンストラクタ
PickUpItem_Blood::PickUpItem_Blood() : PickUpItemBase()
{
	/* データリスト取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "ゲームリソース管理"を取得 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
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
		this->iModelHandle = ModelListHandle->iGetModel("Item/Blood/Blood");

		/* モデル縮小 */
		MV1SetScale(this->iModelHandle, VGet(0.2f, 0.2f, 0.2f));
	}

	/* 初期化 */
	this->iAddEffectDelay	= 0;			// エフェクト追加待機時間
}

// 初期化
void PickUpItem_Blood::Initialization()
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
void PickUpItem_Blood::Update()
{
	/* プレイヤーとこのオブジェクトが接触しているか確認 */
	if (this->pPlayer->HitCheck(this->stCollisionCapsule))
	{
		/* このオブジェクトの削除フラグを有効にする */
		this->bDeleteFlg = true;

		/* プレイヤーの所持ブラッドを取得 */
		int iHaveBlood = this->GameResourceList->iGetHaveBlood();

		/* プレイヤーの所持ブラッドを加算 */
		iHaveBlood += 10;

		/* プレイヤーの所持ブラッドを設定 */
		this->GameResourceList->SetHaveBlood(iHaveBlood);

		/* "ブラッド取得"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_PLAYER_GET_BLOOD);
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
		this->iAddEffectDelay = 100;
	}
}

// リセット処理
void PickUpItem_Blood::Reset()
{
	/* このオブジェクトの削除フラグを有効にする */
	this->bDeleteFlg = true;
}

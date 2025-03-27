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
		this->stCollisionCapsule.fCapsuleRadius		= 200.0f;
		this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0.0f, +50.0f, 0.0f));
		this->stCollisionCapsule.vecCapsuleBottom	= VAdd(this->vecPosition, VGet(0.0f, -50.0f, 0.0f));
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

		/* "ブラッド取得"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_PLAYER_GET_BLOOD);

		/* ダメージ発生時エフェクト */
		{
			/* "エフェクトリソース管理"データリストを取得 */
			DataList_Effect* EffectList = dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"));

			/* 被ダメージの瞬間に発生するエフェクトを追加 */
			EffectSelfDelete* pDamageEffect = new EffectSelfDelete();

			/* 座標を設定 */
			pDamageEffect->SetPosition(this->vecPosition);

			/* エフェクトを取得 */
			pDamageEffect->SetEffectHandle(EffectList->iGetEffect("FX_damaged/FX_damaged"));

			/* 拡大率を設定 */
			pDamageEffect->SetScale(VGet(1.f, 1.f, 1.f));

			/* 削除カウントを設定 */
			// ※仮で1秒間
			pDamageEffect->SetDeleteCount(60);

			/* エフェクト初期化処理 */
			pDamageEffect->Initialization();

			/* オブジェクトリストに登録 */
			this->ObjectList->SetEffect(pDamageEffect);
		}

		/* ブラッド(ゲーム内通貨)を作成 */
		{
			/* "オブジェクト管理"データリストを取得 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

			/* ブラッドの生成 */
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

		/* コンボ継続時間を延長 */
		// デフォルトの継続時間の半分の時間を加算
		{
			/* プレイヤーのコンボ継続時間を取得 */
			int iComboDuration		= PlayerStatusList->iGetPlayerComboDuration();

			/* プレイヤーの最大コンボ継続時間を取得 */
			int iMaxComboDuration	= INIT_ATTRIBUTES_COMBO_DURATION + PlayerStatusList->iGetAddComboTime();

			/* プレイヤーのコンボ継続時間を加算 */
			iComboDuration			+= INIT_ATTRIBUTES_COMBO_DURATION / 2;

			/* プレイヤーのコンボ継続時間が最大コンボ継続時間を超えているか確認 */
 			if (iComboDuration > iMaxComboDuration)
			{
				// 超えている場合
				/* プレイヤーのコンボ継続時間を最大コンボ継続時間に設定 */
				iComboDuration = iMaxComboDuration;
			}

			/* プレイヤーのコンボ継続時間を設定 */
			PlayerStatusList->SetPlayerComboDuration(iComboDuration);
		}
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

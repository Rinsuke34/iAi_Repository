/* 2025.01.21 駒沢風助 ファイル作成 */

#include "Enemy_GoalObject.h"

/* ゴールオブジェクトクラスの定義 */

// コンストラクタ
Enemy_GoalObject::Enemy_GoalObject() : Enemy_Basic()
{
	/* 初期化 */
	this->iMaxHp			= 1;
	this->iNowHp			= 1;
	this->iObjectType		= OBJECT_TYPE_ENEMY;	// オブジェクトの種類
	this->bStageChangeFlg	= false;
	this->pEffect_Glory		= nullptr;		// 発光エフェクト
	this->pEffect_Clear		= nullptr;		// 撃破時エフェクト
	this->bPlayeSeFlg		= false;		// SEを再生開始したかのフラグ(ゲーム開始後に実行しないと他のシーン中に再生されるため)


	/* データリスト取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "ゲーム状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Goal_Object/Goal_Object");
	}
}

// デストラクタ
Enemy_GoalObject::~Enemy_GoalObject()
{
	/* エフェクトを削除する */
	{
		if (this->pEffect_Glory != nullptr)	{ this->pEffect_Glory->SetDeleteFlg(true); }
		if (this->pEffect_Clear != nullptr) { this->pEffect_Clear->SetDeleteFlg(true); }
	}

	/* ループする恐れのあるSEを停止する */
	gpDataList_Sound->SE_PlaySound_Stop(SE_GOAL);
}

// 初期化
void Enemy_GoalObject::Initialization()
{
	Enemy_Basic::Initialization();

	/* コリジョンセット */
	this->stCollisionCapsule.vecCapsuleBottom	= this->vecPosition;
	this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0.f, ENEMY_GOAL_OBJECT_HEIGHT, 0.f));
	this->stCollisionCapsule.fCapsuleRadius		= 100.0f;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();

	/* エフェクト(発光)生成 */
	{
		/* エフェクト(発光)を生成 */
		this->pEffect_Glory = new EffectManualDelete();

		/* エフェクトの読み込み */
		this->pEffect_Glory->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_o_goal/FX_o_goal")));

		/* エフェクトの座標設定 */
		this->pEffect_Glory->SetPosition(VAdd(this->vecPosition, VGet(0.f, ENEMY_GOAL_OBJECT_HEIGHT / 2.f, 0.f)));

		// エフェクトの初期化
		this->pEffect_Glory->Initialization();

		/* エフェクトをリストに登録 */
		{
			/* "オブジェクト管理"データリストを取得 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

			/* エフェクトをリストに登録 */
			ObjectListHandle->SetEffect(pEffect_Glory);
		}
	}
}

// 更新
void Enemy_GoalObject::Update()
{
	/* SEを再生開始したかの確認 */
	if (this->bPlayeSeFlg == false)
	{
		// 再生していない場合
		/* "ゴールが発する音"のSEをループ再生 */
		gpDataList_Sound->SE_PlaySound_Loop_3D(SE_GOAL, this->vecPosition, SE_3D_SOUND_RADIUS);

		/* 再生フラグを有効にする */
		this->bPlayeSeFlg = true;
	}

	/* バレットリストを取得 */
	auto& BulletList = ObjectList->GetBulletList();

	/* プレイヤーの攻撃と接触するか確認 */
	for (auto* bullet : BulletList)
	{
		/* オブジェクトタイプが"近接攻撃(プレイヤー)"であるか確認 */
		if (bullet->iGetObjectType() == OBJECT_TYPE_MELEE_PLAYER)
		{
			// 近接攻撃(プレイヤー)の場合
			/* 近接攻撃との接触判定 */
			if (bullet->HitCheck(this->stCollisionCapsule) == true)
			{
				// 接触している場合
				/* ダメージ処理 */
				this->iNowHp -= 1;
			}
		}
	}

	/* HPが0になっているか確認 */
	if (this->iGetNowHP() <= 0)
	{
		// HPが0以下の場合
		/* ゲーム状態を"ステージクリア"に変更する */
		this->StageStatusList->SetGameStatus(GAMESTATUS_STAGE_CLEAR_SETUP);

		/* エフェクト(撃破時)生成 */
		{
			/* エフェクト(撃破時)を生成 */
			this->pEffect_Clear = new EffectManualDelete();

			/* エフェクトの読み込み */
			this->pEffect_Clear->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_suicide_light/FX_e_suicide_light")));

			/* エフェクトの座標設定 */
			this->pEffect_Clear->SetPosition(VAdd(this->vecPosition, VGet(0.f, ENEMY_GOAL_OBJECT_HEIGHT / 2.f, 0.f)));

			// エフェクトの初期化
			this->pEffect_Clear->Initialization();

			/* エフェクトをリストに登録 */
			{
				/* "オブジェクト管理"データリストを取得 */
				DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

				/* エフェクトをリストに登録 */
				ObjectListHandle->SetEffect(pEffect_Clear);
			}
		}

		/* "ゴールが発する音"のSEを停止 */
		gpDataList_Sound->SE_PlaySound_Stop(SE_GOAL);

		/* "ゴール演出(光あふれる)"のSEを再生 */
		gpDataList_Sound->SE_PlaySound_3D(SE_GOAL_SHINE, this->vecPosition, SE_3D_SOUND_RADIUS);
	}
}

/* 2025.01.21 駒沢風助 ファイル作成 */

#include "EnemyGoalObject.h"

/* ゴールオブジェクトクラスの定義 */

// コンストラクタ
EnemyGoalObject::EnemyGoalObject() : EnemyBasic()
{
	/* 初期化 */
	this->iMaxHp			= 1;
	this->iNowHp			= 1;
	this->iObjectType		= OBJECT_TYPE_ENEMY;	// オブジェクトの種類
	this->bStageChangeFlg	= false;
	this->pEffect_Glory		= nullptr;		// 発光エフェクト
	this->pEffect_Clear		= nullptr;		// 撃破時エフェクト

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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/GoalObject/GoalObject/Goal_Object");
	}
}

// デストラクタ
EnemyGoalObject::~EnemyGoalObject()
{
	/* エフェクトを削除する */
	{
		if (this->pEffect_Glory != nullptr)	{ this->pEffect_Glory->SetDeleteFlg(true); }
		if (this->pEffect_Clear != nullptr) { this->pEffect_Clear->SetDeleteFlg(true); }
	}
}

// 初期化
void EnemyGoalObject::Initialization()
{
	EnemyBasic::Initialization();

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
void EnemyGoalObject::Update()
{
	/* バレットリストを取得 */
	auto& BulletList = ObjectList->GetBulletList();

	/* プレイヤーの攻撃と接触するか確認 */
	for (auto* bullet : BulletList)
	{
		/* オブジェクトタイプが"弾(プレイヤー)"であるか確認 */
		if (bullet->iGetObjectType() == OBJECT_TYPE_BULLET_PLAYER)
		{
			// 弾(プレイヤー)の場合
			/* 弾との接触判定 */
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
		this->StageStatusList->SetGameStatus(GAMESTATUS_STAGE_CLEAR);

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
	}
}

// 発光描写
void EnemyGoalObject::BloomDraw()
{
	/* 元の色を保存 */
	int iBackUpFrames = MV1GetFrameNum(this->iModelHandle);
	std::vector<COLOR_F> vecOriginalDifColor(iBackUpFrames);
	std::vector<COLOR_F> vecOriginalSpcColor(iBackUpFrames);
	std::vector<COLOR_F> vecOriginalEmiColor(iBackUpFrames);
	std::vector<COLOR_F> vecOriginalAmbColor(iBackUpFrames);

	for (int i = 0; i < iBackUpFrames; i++)
	{
		vecOriginalDifColor[i] = MV1GetFrameDifColorScale(this->iModelHandle, i);
		vecOriginalSpcColor[i] = MV1GetFrameSpcColorScale(this->iModelHandle, i);
		vecOriginalEmiColor[i] = MV1GetFrameEmiColorScale(this->iModelHandle, i);
		vecOriginalAmbColor[i] = MV1GetFrameAmbColorScale(this->iModelHandle, i);
	}

	/* ライトフレームNoに設定された番号以外を黒色でに設定 */
	for (int i = 0; i < iBackUpFrames; i++)
	{
		/* 発光フレームであるか確認 */
		if (std::find(aiLightFrameNo.begin(), aiLightFrameNo.end(), i) != aiLightFrameNo.end())
		{
			// 発光フレームである場合
			/* 対象フレームを赤色で描写 */
			MV1SetFrameDifColorScale(this->iModelHandle, i, GetColorF(1.f, 0.f, 0.f, 1.f));
		}
		else
		{
			// 発光フレームでない場合
			/* 対象フレームを黒色で描写 */
			MV1SetFrameDifColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
			MV1SetFrameSpcColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
			MV1SetFrameEmiColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
			MV1SetFrameAmbColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
		}
	}

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);

	/* 元の色に戻す */
	for (int i = 0; i < iBackUpFrames; i++)
	{
		MV1SetFrameDifColorScale(this->iModelHandle, i, vecOriginalDifColor[i]);
		MV1SetFrameSpcColorScale(this->iModelHandle, i, vecOriginalSpcColor[i]);
		MV1SetFrameEmiColorScale(this->iModelHandle, i, vecOriginalEmiColor[i]);
		MV1SetFrameAmbColorScale(this->iModelHandle, i, vecOriginalAmbColor[i]);
	}
}
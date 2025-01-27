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

	/* データリスト取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "ゲーム状態管理"を取得 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
	}

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Goal_Object_Kari");
	}
}

// デストラクタ
EnemyGoalObject::~EnemyGoalObject()
{

}

// 初期化
void EnemyGoalObject::Initialization()
{
	/* コリジョンセット */
	this->stCollisionCapsule.vecCapsuleBottom	= this->vecPosition;
	this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0.f, 100.f, 0.f));
	this->stCollisionCapsule.fCapsuleRadius		= 100.0f;
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
		/* ゲーム状態を"エディット"に変更する */
		this->GameStatusList->SetGameStatus(GAMESTATUS_EDIT);
	}
}

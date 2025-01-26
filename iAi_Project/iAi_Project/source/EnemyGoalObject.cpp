/* 2025.01.21 駒沢風助 ファイル作成 */

#include "EnemyGoalObject.h"

/* ゴールオブジェクトクラスの定義 */

// コンストラクタ
EnemyGoalObject::EnemyGoalObject() : EnemyBase()
{
	/* 初期化 */
	this->iMaxHp = 1;
	this->iNowHp = 1;
	this->iObjectType = OBJECT_TYPE_ENEMY;	// オブジェクトの種類

	/* データリスト取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Player");
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
	/* 仮ダメージ処理 */
	if (this->iNowHp <= 0)
	{
		// ダメージを受けた場合
	}
}

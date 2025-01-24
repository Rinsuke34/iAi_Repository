/* 2025.01.21 駒沢風助 ファイル作成 */

#include "EnemyGoalObject.h"

/* ゴールオブジェクトクラスの定義 */

// コンストラクタ
EnemyGoalObject::EnemyGoalObject() : EnemyBase()
{
	/* HPを設定(仮) */
	this->iMaxHp = 1;
	this->iNowHp = 1;

	/* 初期化 */
	/* データリスト取得 */
	this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
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

// 描写
void EnemyGoalObject::Draw()
{
	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.fCapsuleRadius, 40, 8, GetColor(255, 0, 0), GetColor(255, 0, 0));
}

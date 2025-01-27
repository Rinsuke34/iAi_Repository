
#include "Enemy_Test.h"

// コンストラクタ
TestEnemy::TestEnemy() : EnemyBasic()
{
	// HPを設定
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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy_Kari");
	}
}

// デストラクタ
TestEnemy::~TestEnemy()
{

}

// 初期化
void TestEnemy::Initialization()
{
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition,VGet(0,100,0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}

// 更新
void TestEnemy::Update()
{
	/* バレットリストを取得 */
	auto& BulletList = ObjectList->GetBulletList();

	/* プレイヤー攻撃と接触するか確認 */
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

	if (this->iGetNowHP() <= 0)
	{
		// 削除フラグを有効にする
		this->SetDeleteFlg(true);
	}
}

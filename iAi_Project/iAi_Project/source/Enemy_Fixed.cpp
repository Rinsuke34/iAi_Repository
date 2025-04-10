/* 2025.03.17 石川智也 ファイル作成 */
#include "Enemy_Fixed.h"

// コンストラクタ
Enemy_Fixed::Enemy_Fixed() : Enemy_Basic()
{

	/* オブジェクトのハンドル */
	// HPを設定
	this->iMaxHp = 1;
	this->iNowHp = 1;
	//　オブジェクトの種類をTypeEnemyに設定
	this->iObjectType = OBJECT_TYPE_ENEMY;

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
		this->iModelHandle = this->iModelscaffoldHandle = ModelListHandle->iGetModel("Enemy/Enemy_Fixed/Enemy_Fixed");

	}
}

// デストラクタ
Enemy_Fixed::~Enemy_Fixed()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
}

// 初期化
void Enemy_Fixed::Initialization()
{
	/* コリジョンセット */
	//エネミーのカプセル半径
	this->stCollisionCapsule.fCapsuleRadius = 100;

	//カプセルコリジョンの上の座標
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));

	//カプセルコリジョンの下の座標
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();

	//発光するフレームの処理
	UpdataLightFrame();
}

// 敵を移動させる
void Enemy_Fixed::MoveEnemy()
{
	// 重力処理
	this->vecMove.y -= ENEMY_GRAVITY_SREED;

	// エネミーの座標を更新
	this->vecPosition.y += this->vecMove.y;

}


// 更新
void Enemy_Fixed::Update()
{
	/* バレットリストを取得 */
	auto& BulletList = ObjectList->GetBulletList();

	/* プレイヤー攻撃と接触するか確認 */
	for (auto* bullet : BulletList)
	{
		/* オブジェクトタイプが"弾(プレイヤー)"あるいは"近接攻撃(プレイヤー)"であるか確認 */
		if ((bullet->iGetObjectType() == OBJECT_TYPE_BULLET_PLAYER) || (bullet->iGetObjectType() == OBJECT_TYPE_MELEE_PLAYER))
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
	// エネミーを移動させる
	MoveEnemy();

	//重力処理
	Enemy_Gravity();

	/* HPが0以下であるか確認 */
	if (this->iNowHp <= 0)
	{
		// HPが0以下である場合

		//削除フラグを有効にする
		this->bDeleteFlg = true;
	}
}

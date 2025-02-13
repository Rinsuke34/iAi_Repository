/* 2025.01.29 石川智也 ファイル作成 */

#include "BulletEnemyRangeNormal.h"

/* ノーマル弾クラスの定義 */

// コンストラクタ
BulletEnemyRangeNormal::BulletEnemyRangeNormal() : BulletBase()
{
	/* 初期化 */
	this->iObjectType = OBJECT_TYPE_BULLET_ENEMY;	// オブジェクトの種類を"弾(エネミー)"に設定
	this->pEffect = nullptr;

	this->iDurationCount = ENEMY_NORMAL_DURATION_COUNT;		// 弾の持続カウント
	this->iBulletCount = ENEMY_NORMAL_BULLET_COUNT;			// 弾発射カウント

	this->iEnemyNormalDurationCount = ENEMY_NORMAL_DURATION_COUNT;	//ノーマル弾の持続カウント
}

// デストラクタ
BulletEnemyRangeNormal::~BulletEnemyRangeNormal()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
	this->pEffect->SetDeleteFlg(true);
}

// 初期化
void BulletEnemyRangeNormal::Initialization()
{
	/* 当たり判定設定 */
	{
		this->stCollisionSqhere.vecSqhere = this->vecPosition;
		this->stCollisionSqhere.fSqhereRadius = 50.0f;
	}

	/* エフェクト追加 */
	{
		/* ノーマル弾エフェクトを生成 */
		this->pEffect = new EffectManualDelete();

		/* エフェクトの読み込み */
		this->pEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_bullet")));

		/* エフェクトの座標設定 */
		this->pEffect->SetPosition(this->vecPosition);

		/* エフェクトの回転量設定 */
		this->pEffect->SetRotation(this->vecRotation);

		/* エフェクトの初期化 */
		this->pEffect->Initialization();

		/* エフェクトをリストに登録 */
		{
			/* "オブジェクト管理"データリストを取得 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* エフェクトをリストに登録 */
			ObjectListHandle->SetEffect(this->pEffect);
		}
	}
}

// ノーマル弾の移動処理
void BulletEnemyRangeNormal::BulletEnemyRangeNormalMove()
{
	/* プレイヤーの座標を取得 */
	CharacterBase* player = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	// 持続カウントが発射カウントを超えているか確認
	if (iEnemyNormalDurationCount >= ENEMY_NORMAL_BULLET_COUNT)
	{
		//持続カウントが発射カウントを超えている場合
		// プレイヤーのy座標を取得
		playerPos.y += PLAYER_HEIGHT / 2.f;

		// プレイヤーの方向を向くようにエネミーの向きを定義
		this->vecDirection = VNorm(VSub(playerPos, this->vecPosition));
	}

	// ノーマル弾の移動座標と向きと速度を更新
	this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 18));

	// ノーマル弾のコリジョン座標を更新
	this->stCollisionSqhere.vecSqhere = this->vecPosition;

	// ノーマル弾のエフェクト座標を更新
	this->pEffect->SetPosition(this->vecPosition);

}

// 更新
void BulletEnemyRangeNormal::Update()
{

	// 持続カウントが0より大きいか確認
	if (iEnemyNormalDurationCount > 0)
	{
		// 持続カウントが0より大きい場合
		// 持続カウントを減算
		iEnemyNormalDurationCount--;
	}
	else
	{
		// 持続カウントが0以下の場合
		// 削除フラグを有効化
		this->bDeleteFlg = true;
	}

	// ノーマル弾の移動処理
	BulletEnemyRangeNormalMove();
}

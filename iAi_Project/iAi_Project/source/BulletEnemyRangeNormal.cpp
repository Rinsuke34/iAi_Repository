/* 2025.01.29 石川智也 ファイル作成 */

#include "BulletEnemyRangeNormal.h"

/* 近接攻撃(弱)クラスの定義 */

// コンストラクタ
BulletEnemyRangeNormal::BulletEnemyRangeNormal() : BulletBase()
{
	/* 初期化 */
	this->iObjectType = OBJECT_TYPE_BULLET_ENEMY;	// オブジェクトの種類を"弾(プレイヤー)"に設定
	this->eEffect = nullptr;

	/* 仮追加 */
	iDeleteCount = 130;
}

// デストラクタ
BulletEnemyRangeNormal::~BulletEnemyRangeNormal()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
	this->eEffect->SetDeleteFlg(true);
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
		/* 近接攻撃(弱)のエフェクトを生成 */
		this->eEffect = new EffectManualDelete();

		/* エフェクトの読み込み */
		this->eEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_bullet")));

		/* エフェクトの座標設定 */
		this->eEffect->SetPosition(this->vecPosition);

		/* エフェクトの回転量設定 */
		this->eEffect->SetRotation(this->vecRotation);

		/* エフェクトの初期化 */
		this->eEffect->Initialization();

		/* エフェクトをリストに登録 */
		{
			/* "オブジェクト管理"データリストを取得 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* エフェクトをリストに登録 */
			ObjectListHandle->SetEffect(this->eEffect);
		}
	}
}

void BulletEnemyRangeNormal::BulletEnemyRangeNormalMove()
{
	CharacterBase* player = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();
	if (iDeleteCount >= 120)
	{
		playerPos.y += 60; // y座標を60増加させる
		this->vecDirection = VNorm(VSub(playerPos, this->vecPosition)); // プレイヤーの位置に向かう方向を更新
	}

	this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 18));
	this->stCollisionSqhere.vecSqhere = this->vecPosition;
	this->eEffect->SetPosition(this->vecPosition);
}

// 更新
void BulletEnemyRangeNormal::Update()
{
	/* 仮処理 */
	// 本来はプレイヤー側で削除フラグを設定する予定
	if (iDeleteCount > 0)
	{
		iDeleteCount--;
	}
	else
	{
		this->bDeleteFlg = true;
	}
	BulletEnemyRangeNormalMove();
}

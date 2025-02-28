/* 2025.01.30 石川智也 ファイル作成 */

#include "BulletEnemyRangeMissile.h"

/* ミサイル弾クラスの定義 */

// コンストラクタ
BulletEnemyRangeMissile::BulletEnemyRangeMissile() : BulletBase()
{
	/* 初期化 */
	this->iObjectType = OBJECT_TYPE_BULLET_ENEMY;	// オブジェクトの種類を"弾(エネミー)"に設定
	this->pEffect = nullptr;
	this->pEffectGuidance = nullptr;

	this->iDurationCount = ENEMY_MISSILE_DURATION_COUNT;				// ミサイル弾の持続カウント
	this->iBulletUPCount = ENEMY_MISSILE_BULLET_UP_COUNT;				// ミサイル弾打ち上げカウント
	this->iBulletDownCount = ENEMY_MISSILE_BULLET_DOWN_COUNT;			// ミサイル弾打ち下げカウント
	this->iBulletGuidanceCount = ENEMY_MISSILE_BULLET_GUIDANCE_COUNT;	// ミサイル誘導カウント
	this->iEnemyMissileDurationCount = ENEMY_MISSILE_DURATION_COUNT;	// ミサイル弾の持続カウント

	this->iTextureHandle = LoadGraph("resource/ImageData/Test/a.png");

	this->bPredictedLandingFlg = false;

	/* データリスト取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}
}

// デストラクタ
BulletEnemyRangeMissile::~BulletEnemyRangeMissile()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
	this->pEffect->SetDeleteFlg(true);
	this->pEffectGuidance->SetDeleteFlg(true);
}

// 初期化
void BulletEnemyRangeMissile::Initialization()
{
	/* 当たり判定設定 */
	{
		this->stCollisionSqhere.vecSqhere = this->vecPosition;
		this->stCollisionSqhere.fSqhereRadius = 50.0f;
	}
	/* エフェクト追加 */
	{
		/* ミサイルエフェクトを生成 */
		this->pEffect = new EffectManualDelete();

		/* エフェクトの読み込み */
		this->pEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_bullet/FX_e_bullet")));

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
		/* エフェクト追加 */
	{
		/* ミサイル誘導エフェクトを生成 */
		this->pEffectGuidance = new EffectManualDelete();

		/* エフェクトの読み込み */
		this->pEffectGuidance->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_missile_contrail/FX_e_missile_contrail")));

		/* エフェクトの座標設定 */
		this->pEffectGuidance->SetPosition(this->vecPosition);

		/* エフェクトの回転量設定 */
		this->pEffectGuidance->SetRotation(this->vecRotation);

		/* エフェクトの初期化 */
		this->pEffectGuidance->Initialization();

		/* エフェクトをリストに登録 */
		{
			/* "オブジェクト管理"データリストを取得 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* エフェクトをリストに登録 */
			ObjectListHandle->SetEffect(this->pEffectGuidance);
		}
	}
}
// ミサイル弾の移動処理
void BulletEnemyRangeMissile::BulletEnemyRangeMissileMove()
{
	/* プレイヤーの座標を取得 */
	CharacterBase* player = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	iEnemyMissileDurationCount--;	// ミサイル弾の持続カウントを減算


	// 持続カウントが打ち上げカウントを超えているか確認
	if (iEnemyMissileDurationCount >= ENEMY_MISSILE_BULLET_UP_COUNT)
	{
		// 持続カウントが打ち上げカウントを超えている場合

		// プレイヤーの高さの半分のy座標を取得
		playerPos.y += PLAYER_HEIGHT / 2.f;

		// ミサイルの移動方向をプレイヤーがいる方向に更新
		this->vecDirection = VNorm(VSub(playerPos, this->vecPosition));

		// ミサイルの移動座標と移動速度を更新
		this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 18));

	}
	// 持続カウントが打ち下げカウントを超えているか確認
	else if (iEnemyMissileDurationCount >= ENEMY_MISSILE_BULLET_DOWN_COUNT)
	{
		// 持続カウントが打ち下げカウントを超えている場合

		// ミサイルの移動方向を上方向に設定
		this->vecDirection = VGet(0, 1, 0);

		// 再度ミサイルの移動速度を更新
		//this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 30));
	}
	// 持続カウントが誘導カウントを超えているか確認
	else if (iEnemyMissileDurationCount >= ENEMY_MISSILE_BULLET_GUIDANCE_COUNT)
	{
		// 持続カウントが誘導カウントを超えている場合

		// プレイヤーの高さの半分のy座標を取得
		playerPos.y += PLAYER_HEIGHT / 2.f;

		// ミサイルの移動方向をプレイヤーがいる方向に更新
		this->vecDirection = VNorm(VSub(playerPos, this->vecPosition));

		// ミサイルの移動座標と移動速度を更新
		this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 25));
	}

	// ミサイルの座標を更新
	this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 50));

	// ミサイルのコリジョン座標を更新
	this->stCollisionSqhere.vecSqhere = this->vecPosition;

	// ミサイルのエフェクト座標を更新
	this->pEffect->SetPosition(this->vecPosition);

	// ミサイルの誘導エフェクト座標をミサイルエフェクトの座標の少し後ろに設定
	this->pEffectGuidance->SetPosition(this->vecPosition);

	// ミサイルの誘導エフェクト座標をミサイルエフェクトの数秒後に設定
	static const float delayTime = 10.0f; // 数秒後の時間
	VECTOR delayedPosition = VAdd(this->vecPosition, VScale(this->vecDirection, -this->fMoveSpeed * delayTime));
	this->pEffectGuidance->SetPosition(delayedPosition);

	// ミサイルの誘導エフェクトの向きを設定
	VECTOR rotation = VGet(atan2(this->vecDirection.y, this->vecDirection.z), atan2(this->vecDirection.x, this->vecDirection.z), 0);

	this->pEffectGuidance->SetRotation(rotation);

	// 移動後の座標を取得(垂直方向)
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x;
	vecNextPosition.y = this->vecPosition.y;
	vecNextPosition.z = this->vecPosition.z;

	// 主人公の上部分の当たり判定から下方向へ向けた線分を作成
	this->stVerticalCollision.vecLineStart = this->vecPosition;
	this->stVerticalCollision.vecLineStart.y += 25;
	this->stVerticalCollision.vecLineEnd = stVerticalCollision.vecLineStart;
	this->stVerticalCollision.vecLineEnd.y -= 60;

	// 足場を取得
	auto& PlatformList = ObjectList->GetCollisionList();





	// 足場と接触するか確認
	for (auto* platform : PlatformList)
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stVerticalCollision);

		// 接触しているか確認
		if (stHitPolyDim.HitFlag == 1)
		{
			// 接触している場合
		// ミサイルの削除フラグを有効化
		this->bDeleteFlg = true;
			this->bPredictedLandingFlg = false;

		/* エフェクト追加 */

		/*爆発エフェクトを生成 */
		this->pEffectExplosion = new EffectManualDelete();

		/* エフェクトの読み込み */
		this->pEffectExplosion->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_missile_explosion/FX_e_missile_explosion")));

		/* エフェクトの座標設定 */
		this->pEffectExplosion->SetPosition(this->vecPosition);

		/* エフェクトの回転量設定 */
		this->pEffectExplosion->SetRotation(this->vecRotation);

		/* エフェクトの初期化 */
		this->pEffectExplosion->Initialization();

		/* エフェクトをリストに登録 */
		{
			/* "オブジェクト管理"データリストを取得 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* エフェクトをリストに登録 */
			ObjectListHandle->SetEffect(this->pEffectExplosion);
		}
			break;
		}
	}
	}

//コリジョン描写
void BulletEnemyRangeMissile::CollisionDraw()
{
	DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, GetColor(255, 0, 0));
}

// 更新
void BulletEnemyRangeMissile::Update()
{
	/* 仮処理 */


	// 本来はプレイヤー側で削除フラグを設定する予定

	// 持続カウントが0より大きいか確認
	if (iEnemyMissileDurationCount > 0)
	{
		// 持続カウントが0より大きい場合

		// 持続カウントを減算
		iEnemyMissileDurationCount--;
	}
	else
	{
		// 持続カウントが0以下の場合

		// 削除フラグを有効化
		this->bDeleteFlg = true;
	}

	// ミサイルの移動処理
	BulletEnemyRangeMissileMove();
}

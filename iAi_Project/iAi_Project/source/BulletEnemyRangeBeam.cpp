/* 2025.01.29 石川智也 ファイル作成 */

#include "BulletEnemyRangeBeam.h"

/* ビームクラスの定義 */

// コンストラクタ
BulletEnemyRangeBeam::BulletEnemyRangeBeam() : BulletBase()
{
	/* 初期化 */
	this->iObjectType = OBJECT_TYPE_BULLET_ENEMY;	// オブジェクトの種類を"弾(エネミー)"に設定
	this->pEffect = nullptr;

	this->iChargeCount = ENEMY_BEAM_CHARGE_COUNT;		// ビームチャージカウント

	this->iBulletCount = ENEMY_BEAM_BULLET_COUNT;			// ビーム発射カウント

	this->iEnemyBeamDurationCount = ENEMY_BEAM_DURATION_COUNT;	//ビームの持続カウント
	// エネミーの位置を初期化
	this->vecEnemyPosition = VGet(0, 0, 0);
}

// デストラクタ
BulletEnemyRangeBeam::~BulletEnemyRangeBeam()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
	this->pEffect->SetDeleteFlg(true);
}

// 初期化
void BulletEnemyRangeBeam::Initialization()
{
	/* 当たり判定設定 */
	{
		this->stCollisionCapsule.fCapsuleRadius = 50.0f;
		this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(100, 0, 0)); // 横に設定
		this->stCollisionCapsule.vecCapsuleBottom = VGet(0, 0, 0); // 初期化
	}

	/* エフェクト追加 */
	{
		/* ビームエフェクトを生成 */
		this->pEffect = new EffectManualDelete();

		/* エフェクトの読み込み */
		this->pEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_beam/FX_e_beam")));

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

	//エネミーの位置を設定
	this->vecEnemyPosition = this->vecPosition;
}

// ビームの移動処理
void BulletEnemyRangeBeam::BulletEnemyRangeBeamMove()
{
	/* プレイヤーの座標を取得 */
	CharacterBase* player = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	iChargeCount--;	// チャージカウントを減算
	if (iChargeCount <= 0)
	{
	// 持続カウントが発射カウントを超えているか確認
	if (iEnemyBeamDurationCount >= ENEMY_NORMAL_BULLET_COUNT)
	{
		//持続カウントが発射カウントを超えている場合
		// プレイヤーのy座標を取得
		playerPos.y += PLAYER_HEIGHT / 2.f;

		// プレイヤーの方向を向くようにエネミーの向きを定義
		this->vecDirection = VNorm(VSub(playerPos, this->vecPosition));

			//チャージカウントを初期化
			iChargeCount = ENEMY_BEAM_CHARGE_COUNT;
		}
	}

	// ビームの移動座標と向きと速度を更新
	this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 35));

	// エネミーのリストを取得
	auto& enemyList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetEnemyList();

	// ビームのコリジョン座標を更新
	this->stCollisionCapsule.vecCapsuleTop = this->vecPosition; // 開始地点を更新
	this->stCollisionCapsule.vecCapsuleBottom = this->vecEnemyPosition; // 終了地点をエネミーの位置に固定

	// ビームのエフェクトの向きを設定
	VECTOR rotation = VGet(atan2(this->vecDirection.y, this->vecDirection.z), atan2(this->vecDirection.x, this->vecDirection.z), 0);
	this->pEffect->SetRotation(rotation);
}

// 更新
void BulletEnemyRangeBeam::Update()
{

	// 持続カウントが0より大きいか確認
	if (iEnemyBeamDurationCount > 0)
	{
		// 持続カウントが0より大きい場合
		// 持続カウントを減算
		iEnemyBeamDurationCount--;
	}
	else
	{
		// 持続カウントが0以下の場合
		// 削除フラグを有効化
		this->bDeleteFlg = true;
	}

	// ビームの移動処理
	BulletEnemyRangeBeamMove();
}

// コリジョン描写
void BulletEnemyRangeBeam::CollisionDraw()
{
	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius, 12, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
}
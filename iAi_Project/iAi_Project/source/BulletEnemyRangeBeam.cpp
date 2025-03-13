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
        // エフェクトが再生中かどうか確認
        if (IsEffekseer3DEffectPlaying(this->pEffect->iGetEffectHandle()))
        {
            // エフェクトが再生終了している場合
            // エネミーの削除フラグを有効にする
            this->bDeleteFlg = true;
        }
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
    this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 30));

	// エネミーのリストを取得
	auto& enemyList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetEnemyList();

	// ビームのコリジョン座標を更新
    this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition; // 終了地点を更新

    // コリジョンの長さを計算
    float collisionLength = VSize(VSub(this->stCollisionCapsule.vecCapsuleBottom, this->vecEnemyPosition));
    const float maxCollisionLength = 2200.0f; // 最大コリジョン長さ

    // コリジョンの長さが最大長さを超えないように調整
    if (collisionLength > maxCollisionLength)
    {
        VECTOR direction = VNorm(VSub(this->stCollisionCapsule.vecCapsuleBottom, this->vecEnemyPosition));
        this->stCollisionCapsule.vecCapsuleBottom = VAdd(this->vecEnemyPosition, VScale(direction, maxCollisionLength));
    }

    this->stCollisionCapsule.vecCapsuleTop = this->vecEnemyPosition; // 開始地点をエネミーの位置に固定

	// ビームのエフェクトの向きを設定
	VECTOR rotation = VGet(atan2(this->vecDirection.y, this->vecDirection.z), atan2(this->vecDirection.x, this->vecDirection.z), 0);

    // ビームのエフェクトの反対向きを設定
    VECTOR rotation2 = VGet(rotation.x, rotation.y + DX_PI_F, rotation.z);

	// エフェクトの向きを設定する前に、必要な回転軸がどれかを確認
    if (this->vecDirection.z > 0)
    {
        // 正面を向いている場合
        this->pEffect->SetRotation(rotation2);
    }
    else
    {
        // 正面を向いていない場合
	this->pEffect->SetRotation(rotation);
}
}

/* 接触判定(簡易) */
// カプセル - カプセル
bool BulletEnemyRangeBeam::HitCheck(COLLISION_CAPSULE	stCapsule)
{
	// 引数
	// stCapsule	: 判定するカプセルコリジョン
	// 戻り値
	// bool : 接触している(true) / 接触していない(false)

	/* カプセル同士が接触しているか確認 */
	if (HitCheck_Capsule_Capsule
		/* 判定するオブジェクトのコリジョン */
		(stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius,
			/* このオブジェクトのコリジョン */
			this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius))
	{
		// 接触している場合
		return true;
	}
	// 接触していない場合
	return false;
}

// カプセル - 球体
bool BulletEnemyRangeBeam::HitCheck(COLLISION_SQHERE	stSqhere)
{
	// 引数
	// stCapsule	: 判定する球体コリジョン
	// 戻り値
	// bool			: 接触している(true) / 接触していない(false)

	/* カプセルと球体が接触しているか確認 */
	if (HitCheck_Sphere_Capsule(
		/* 判定するオブジェクトのコリジョン */
		stSqhere.vecSqhere, stSqhere.fSqhereRadius,
		/* このオブジェクトのコリジョン */
		this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius))
	{
		// 接触している場合
		return true;
	}
	// 接触していない場合
	return false;
}

// カプセル - モデル
bool BulletEnemyRangeBeam::HitCheck(int iModelHandle, int iFrameIndex)
{
	// 引数
	// iModelHandle	: 判定するモデルのハンドル
	// iFrameIndex	: 判定するモデルのフレーム番号
	// 戻り値
	// bool			: 接触している(true) / 接触していない(false)

	// ポリゴンとの接触情報
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* プレイヤーと対象のモデルが接触しているかの情報取得 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* 判定するオブジェクトのコリジョン */
		iModelHandle, iFrameIndex,
		/* このオブジェクトのコリジョン */
		this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius);

	/* 接触数を取得 */
	if (stHitPolyDim.HitNum > 0)
	{
		// 接触している場合
		return true;
	}
	// 接触していない場合
	return false;
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
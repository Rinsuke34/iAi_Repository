/* 2025.01.29 石川智也 ファイル作成 */
#include "Enemy_Normal.h"

// コンストラクタ
Enemy_Normal::Enemy_Normal() : Enemy_Basic()
{

	/* オブジェクトのハンドル */
	this->pBulletRangeNormal = nullptr;	// 近接攻撃(弱)の弾
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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy");
	}

	this->pPlayer = ObjectList->GetCharacterPlayer();// プレイヤー

	this->iFiringCount = ENEMY_NORMAL_BULLET_INTERVAL;	// 発射カウント
	this->iGuidanceCount = ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL;	// 誘導カウント

	this->pEffectWarning = nullptr;	// 警告エフェクト
}

// デストラクタ
Enemy_Normal::~Enemy_Normal()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
}

// 初期化
void Enemy_Normal::Initialization()
{
	/* コリジョンセット */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();
}

// 敵を移動させる
void Enemy_Normal::MoveEnemy()
{
	// プレイヤーの座標を取得
	VECTOR playerPos = pPlayer->vecGetPosition();

	//エネミーの向きを初期化する
	VECTOR VRot = VGet(0, 0, 0);

	//プレイヤーの方向を向くようにエネミーの向きを定義
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//エネミーの向きを設定
	this->vecRotation = VRot;

	//エネミーの縦向きを取得
	MV1SetRotationXYZ(iModelHandle, VRot);

	//プレイヤーとエネミーのXZ軸の距離を取得
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);


	//プレイヤーが探知範囲内にいるか確認
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE)  // x軸とz軸の距離が1000未満の場合
	{
		// プレイヤーが探知範囲内にいる場合
		iFiringCount--;	// 発射カウントを減少

		//誘導カウントが発射カウントより大きいか確認
		if (iFiringCount <= ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL)
		{
			// 誘導カウントが発射カウントより大きい場合
			/* 攻撃予告エフェクト追加 */
			{
				/* 攻撃予告エフェクトを生成 */
				this->pEffectWarning = new EffectManualDelete();

				/* エフェクトの読み込み */
				this->pEffectWarning->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_bullet_warning/FX_e_bullet_warning")));

				/* エフェクトの座標設定 */
				this->pEffectWarning->SetPosition(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT, vecPosition.z));

				/* エフェクトの回転量設定 */
				this->pEffectWarning->SetRotation(this->vecRotation);

				/* エフェクトの初期化 */
				this->pEffectWarning->Initialization();

				/* エフェクトをリストに登録 */
				{
					/* "オブジェクト管理"データリストを取得 */
					DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
					/* エフェクトをリストに登録 */
					ObjectListHandle->SetEffect(this->pEffectWarning);
				}
			}
		}
		//発射カウントが0以下か確認
		if (iFiringCount <= 0)
		{

			// モデルのフレーム０番を表示
			MV1SetFrameVisible(iModelHandle, 0, TRUE);

			// モデルのフレーム２番を表示
			MV1SetFrameVisible(iModelHandle, 2, TRUE);
			// 発射カウントが0以下の場合
			// ノーマル弾を発射する
			Player_Range_Normal_Shot();

			// 発射カウントを初期化
			this->iFiringCount = ENEMY_NORMAL_BULLET_INTERVAL;
		}
	}


}

// ノーマル弾の発射
void Enemy_Normal::Player_Range_Normal_Shot()
{
	// プレイヤーの座標を取得
	VECTOR playerPos = pPlayer->vecGetPosition();

	// ノーマル弾を生成
	this->pBulletRangeNormal = new BulletEnemyRangeNormal;
	/* 攻撃の生成方向の設定 */
	/* 攻撃座標を算出 */

	//エネミーの向きを初期化
	VECTOR vecAdd = VGet(0, 0, 0);

	// 発射させる方向を設定
	vecAdd = VNorm(vecAdd);

	// 発射させる高さと幅を設定
	vecAdd.y = PLAYER_HEIGHT / 2.f;
	vecAdd.x = PLAYER_WIDE / 2.f;

	// 攻撃生成座標をエネミーが向いている方向に設定
	this->pBulletRangeNormal->SetPosition(VAdd(this->vecPosition, vecAdd));

	// 移動する弾の向きを設定
	this->pBulletRangeNormal->SetRotation(VGet(0.0f, -(this->vecRotation.y), 0.0f));
	
	//初期化
	this->pBulletRangeNormal->Initialization();

	//バレットリストに追加
	ObjectList->SetBullet(this->pBulletRangeNormal);


	
}

// 更新
void Enemy_Normal::Update()
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

	/* HPが0以下であるか確認 */
	if (this->iNowHp <= 0)
	{
		// HPが0以下である場合
		/* 撃破時の処理を実行 */
		Defeat();

		return;
	}

	// エネミーを移動させる
	MoveEnemy();

	// コリジョンセット
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}

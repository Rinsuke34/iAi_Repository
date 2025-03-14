/* 2025.03.13 石川智也 ファイル作成 */
#include "Enemy_Missile_Air.h"

// コンストラクタ
Enemy_Missile_Air::Enemy_Missile_Air() : Enemy_Basic()
{

	/* オブジェクトのハンドル */
	this->pBulletRangeMissile = nullptr;	// ミサイルの弾
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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Missile/Enemy_Missile");
	}


	this->pPlayer = ObjectList->GetCharacterPlayer();
	this->bHitEffectGenerated = false;	// ヒットエフェクト生成フラグ
	this->iFiringCount = ENEMY_MISSILE_INTERVAL;	// 発射カウント
	/*モーション関連*/
	// エネミーモデルに空中のアニメーションをアタッチする
	this->iMissileAirAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, FALSE);
	// アタッチした空中アニメーションの総再生時間を取得する
	this->iMissileAirAttachIndex = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iMissileAirAttachIndex);
	this->bDirectionFlg = true;					// 向き固定フラグ
}

// デストラクタ
Enemy_Missile_Air::~Enemy_Missile_Air()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
}

// 初期化
void Enemy_Missile_Air::Initialization()
{
	/* コリジョンセット */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();
}

// 敵を移動させる
void Enemy_Missile_Air::MoveEnemy()
{

	// プレイヤーの座標を取得
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	//エネミーの向きを初期化する
	VECTOR VRot = VGet(0, 0, 0);

	//プレイヤーの方向を向くようにエネミーの向きを定義
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	if (this->bDirectionFlg == true)
	{
		//エネミーの向きを設定
		this->vecRotation = VRot;
		//エネミーの向きを取得
		MV1SetRotationXYZ(iModelHandle, VRot);
	}

	//プレイヤーとエネミーのXZ軸の距離を取得
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerY = fabs(this->vecPosition.y - playerPos.y);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);


	//プレイヤーが探知範囲内にいるか確認
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerY < ENEMY_Y_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE)  // x軸とz軸の距離が1000未満の場合
	{
		// プレイヤーが探知範囲内にいる場合
		// ミサイル発射カウントを減算
		iFiringCount--;

		//発射カウントが0以下か確認
		if (iFiringCount <= 0)
		{
			// 発射カウントが0以下の場合

		// ミサイルを発射する
			Player_Range_Missile_Shot();

			// 発射カウントを初期化
			this->iFiringCount = ENEMY_MISSILE_INTERVAL;
		}
	}
}

// ミサイル弾の発射
void Enemy_Missile_Air::Player_Range_Missile_Shot()
{

	// ミサイルを生成
	this->pBulletRangeMissile = new BulletEnemyRangeMissile;

	//効果音再生
	gpDataList_Sound->SE_PlaySound(SE_ENEMY_IKURA_ATTACK);

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
	this->pBulletRangeMissile->SetPosition(VAdd(this->vecPosition, vecAdd));

	// 移動する弾の向きを設定
	this->pBulletRangeMissile->SetRotation(VGet(0.0f, -(this->vecRotation.y), 0.0f));

	//初期化
	this->pBulletRangeMissile->Initialization();

	//バレットリストに追加
	ObjectList->SetBullet(this->pBulletRangeMissile);
}

// 更新
void Enemy_Missile_Air::Update()
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


	// エネミーを移動させる
	MoveEnemy();


	/* HPが0以下であるか確認 */
	if (this->iNowHp <= 0)
	{
		/* 死亡フラグを有効化 */
		this->bDeadFlg = true;

		// HPが0以下である場合
		if (this->bHitEffectGenerated == FALSE)
		{
			/* Hitエフェクト追加 */
			{
				/* 時間経過で削除されるエフェクトを追加 */
				EffectManualDelete* AddEffect = new EffectManualDelete();

				/* エフェクト読み込み */
				AddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_hit/FX_hit")));

				/* エフェクトの座標設定 */
				AddEffect->SetPosition(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z));

				/* エフェクトの回転量設定 */
				AddEffect->SetRotation(this->vecRotation);

				/* エフェクトの初期化 */
				AddEffect->Initialization();

				/* リストに登録 */
				{
					/* "オブジェクト管理"データリストを取得 */
					DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
					/* エフェクトをリストに登録 */
					ObjectListHandle->SetEffect(AddEffect);
				}


				this->bHitEffectGenerated = TRUE;
			}
		}
		this->bDirectionFlg = false;
		//死亡モーション以外のモーションをデタッチ
		MV1DetachAnim(this->iModelHandle, this->iMissileAirAttachIndex);

		//死亡モーションの再生時間を加算
		this->fDiePlayTime += 2.5f;

		// 死亡モーションをアタッチ
		this->iDieAttachIndex = MV1AttachAnim(this->iModelHandle, 6, -1, FALSE);

		//アタッチした死亡モーションの再生時間をセット
		MV1SetAttachAnimTime(this->iModelHandle, this->iDieAttachIndex, this->fDiePlayTime);

		// 死亡モーションの総再生時間を取得
		this->fDieTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iDieAttachIndex);

		// 死亡モーションの再生時間が総再生時間に達したか確認
		if (this->fDiePlayTime >= this->fDieTotalTime)
		{
			/* 撃破時の処理を実行 */
			Defeat();

			//爆発SE再生
			gpDataList_Sound->SE_PlaySound(SE_ENEMY_DAMAGE);
		}
		return;
	}

	// コリジョンセット
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}

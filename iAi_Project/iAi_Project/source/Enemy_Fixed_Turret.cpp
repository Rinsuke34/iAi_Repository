/* 2025.03.17 石川智也 ファイル作成 */
#include "Enemy_Fixed_Turret.h"

// コンストラクタ
Enemy_Fixed_Turret::Enemy_Fixed_Turret() : Enemy_Basic()
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
		this->iModelHandle = this->iModelturretHandle = ModelListHandle->iGetModel("Enemy/Enemy_EyeBall/Enemy_EyeBall");

	}

	this->pPlayer = ObjectList->GetCharacterPlayer();// プレイヤー

	this->iFiringCount = ENEMY_NORMAL_BULLET_INTERVAL;	// 発射カウント
	this->iGuidanceCount = ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL;	// 誘導カウント
	this->bHitEffectGenerated = false;	// ヒットエフェクト生成フラグ
	this->bWarningEffectFlg = true;				// 警告エフェクトフラグ
	this->bShotFlg = false;						// ショットフラグ

	this->bDirectionFlg = true;					// 向き固定フラグ
	this->bUpFlg = false;						// 上フラグ
	this->bDownFlg = false;						// 下フラグ
	this->bMissile = false;						// ミサイルフラグ

	//維持カウントを初期化
	this->iMaintainCount = 60;
}

// デストラクタ
Enemy_Fixed_Turret::~Enemy_Fixed_Turret()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
}

// 初期化
void Enemy_Fixed_Turret::Initialization()
{
	/* コリジョンセット */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();
	
	UpdataLightFrame();
}



// 敵を移動させる
void Enemy_Fixed_Turret::MoveEnemy()
{

	// プレイヤーの座標を取得
	VECTOR playerPos = pPlayer->vecGetPosition();

	//エネミーの向きを初期化する
	VECTOR VRot = VGet(0, 0, 0);
	VECTOR VYRot = VGet(0, 0, 0);

	// プレイヤーの方向を向くようにエネミーの向きを定義
	VECTOR centerPos = VGet(playerPos.x, playerPos.y, playerPos.z);
	float deltaX = this->vecPosition.x - centerPos.x;
	float deltaZ = this->vecPosition.z - centerPos.z;


	VRot.y = atan2f(deltaX, deltaZ);
	VYRot.y = atan2f(deltaX, deltaZ);
	//現在向ている方向を取得
	VECTOR vecRot = MV1GetRotationXYZ(iModelHandle);
	if (vecPosition.z > centerPos.z)
	{
		VRot.x = atan2f(this->vecPosition.y - centerPos.y, this->vecPosition.z - centerPos.z) * -1;
	}
	else if (vecPosition.z < centerPos.z)
	{
		VRot.x = atan2f(centerPos.y - this->vecPosition.y, centerPos.z - this->vecPosition.z);
	}

	if (this->bShotFlg == false)
	{
		if (VRot.x >= -0.5)
		{
			this->vecRotation = VRot;
			MV1SetRotationXYZ(iModelHandle, VRot);
		}
		if (VRot.x <= 0.9)
		{
			this->vecRotation = VRot;
			MV1SetRotationXYZ(iModelHandle, VRot);
		}
		if (VRot.x > 0.9 && VRot.x > 0)
		{
			//現在のVRot.xの値を保存
			float fVRotX = VRot.x;
			this->vecRotation = VGet(1, VYRot.y, VYRot.z);
		}
		if (VRot.x < -0.5 && VRot.x < 0)
		{
			//現在のVRot.xの値を保存
			float fVRotX = VRot.x;
			this->vecRotation = VGet(-0.5,VYRot.y,VYRot.z);
		}
		
	}

	//プレイヤーとエネミーのXZ軸の距離を取得
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerY = fabs(this->vecPosition.y - playerPos.y);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);


	//プレイヤーが探知範囲内にいるか確認
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerY < ENEMY_Y_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE)  // x軸とz軸の距離が1000未満の場合
	{
		// プレイヤーが探知範囲内にいる場合
		iFiringCount--;	// 発射カウントを減少

		//誘導カウントが発射カウントより大きいか確認
		if (iFiringCount <= ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL)
		{
			// 誘導カウントが発射カウントより大きい場合
			if (this->bWarningEffectFlg == true)	// 警告エフェクトフラグが有効の場合
			{
				this->bWarningEffectFlg = false;




			

				/* 攻撃予告エフェクト追加 */
				{
					/* 攻撃予告エフェクトを生成 */
					this->pEffectWarning = new EffectManualDelete();

					/* エフェクトの読み込み */
					this->pEffectWarning->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_bullet_warning/FX_e_bullet_warning")));

					this->vecEffectPos = MV1GetFramePosition(this->iModelHandle, 2);

					/* エフェクトの座標設定 */
					this->pEffectWarning->SetPosition(VGet(vecEffectPos.x, vecEffectPos.y, vecEffectPos.z));

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
				//維持カウントを減算
				this->iMaintainCount--;

				if (iMaintainCount <= 0)
			{
					this->bShotFlg = true;

					this->bUpFlg = true;

					this->bTestFlg = false;

					this->iMaintainCount = 60;
				}
			}
		}

	if (bUpFlg == true)
	{
		this->vecRotation = VGet(vecRotation.x+0.1, vecRotation.y, vecRotation.z);

		if (vecRotation.x >= 1.5)
		{
			this->vecRotation = VGet(1.5, vecRotation.y, vecRotation.z);

			this->bMissile = true;
			if (this->bMissile == true && iMaintainCount == 60)
			{
				// ミサイルを生成
				this->pBulletRangeMissile = new BulletEnemyRangeMissile;

				// 効果音再生
				gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_IKURA_ATTACK, this->vecPosition, SE_3D_SOUND_RADIUS);

				/* 攻撃の生成方向の設定 */
				/* 攻撃座標を算出 */

				//エネミーの向きを初期化
				VECTOR vecAdd = VGet(0, 0, 0);

				// 発射させる方向を設定
				vecAdd = VNorm(vecAdd);

				//モデルの２番目のフレームの位置を取得
				VECTOR vecFramePos = MV1GetFramePosition(iModelHandle, 2);

				// 発射させる高さと幅を設定
				vecAdd.y += PLAYER_HEIGHT / 2.f;
				//vecAdd.x = PLAYER_WIDE / 2.f;

				// 攻撃生成座標をエネミーが向いている方向に設定
				this->pBulletRangeMissile->SetPosition(VAdd(vecFramePos, vecAdd));

				// 移動する弾の向きを設定
				this->pBulletRangeMissile->SetRotation(VGet(0.0f, -(this->vecRotation.y), 0.0f));

				//初期化
				this->pBulletRangeMissile->Initialization();

				//バレットリストに追加
				ObjectList->SetBullet(this->pBulletRangeMissile);

				this->bMissile = false;

				this->bUpFlg = false;

				this->bTestFlg2 = true;
			}
		}
	}

	if (this->bTestFlg2 == true)
	{
		this->vecRotation = VGet(vecRotation.x - 0.1, vecRotation.y, vecRotation.z);

		//エネミーのｘ向きがプレイヤーのｘ向きが誤差が0.1以上または0.1以下か確認
		if (vecRotation.x < VRot.x)
		{
			this->vecRotation = VGet(VRot.x, vecRotation.y, vecRotation.z);

			this->bTestFlg3 = true;

			this->bTestFlg2 = false;

		}
		}

	if (this->bTestFlg3 == true)
		{
		// プレイヤーの座標を取得
		VECTOR playerPos = pPlayer->vecGetPosition();

		// プレイヤーの方向を向くための角度を計算
		this->fTargetAngle = atan2f(playerPos.x - this->vecPosition.x, playerPos.z - this->vecPosition.z);

		// 180度反対を向くように角度を調整
		this->fTargetAngle += DX_PI_F;

		// 現在のエネミーの向き
		this->fCurrentAngle = this->vecRotation.y;
		
		// 回転方向を決定
		this->fAngleDifference = this->fTargetAngle - this->fCurrentAngle;
		if (this->fAngleDifference > DX_PI_F) this->fAngleDifference -= 2 * DX_PI_F;
		if (this->fAngleDifference < -DX_PI_F) this->fAngleDifference += 2 * DX_PI_F;

		// 右回りか左回りかを判断して回転
		if (this->fAngleDifference > 0)
		{
			this->vecRotation.y += 0.1f; // 右回り
}
		else
		{
			this->vecRotation.y -= 0.1f; // 左回り
		}

		// エネミーがプレイヤーの方向を完全に向いたか確認
		if (fabs(this->fAngleDifference) < 0.1f)
{
			this->vecRotation.y = fTargetAngle;
			this->bTestFlg3 = false;
	this->bWarningEffectFlg = true;
			this->bShotFlg = false;
		}
}
}


// 更新
void Enemy_Fixed_Turret::Update()
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

	Enemy_Gravity();

	/* HPが0以下であるか確認 */
	if (this->iNowHp <= 0)
	{
		// HPが0以下である場合
		/* 死亡フラグを有効化 */
		this->bDeadFlg = true;

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
		/* 撃破時の処理を実行 */
		Defeat();

		//爆発SE再生
		gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_DAMAGE, this->vecPosition, SE_3D_SOUND_RADIUS);
	}


	// コリジョンセット
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}

// 描写
void Enemy_Fixed_Turret::Draw()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転 */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotation);

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);
}
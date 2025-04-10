/* 2025.01.30 石川智也 ファイル作成 */
#include "Enemy_Missile.h"

// コンストラクタ
Enemy_Missile::Enemy_Missile() : Enemy_Basic()
{

	/* オブジェクトのハンドル */
	this->pBulletRangeMissile = nullptr;	// ミサイルの弾
	// HPを設定
	this->iMaxHp = 1;
	this->iNowHp = 1;

	// オブジェクトの種類をTypeEnemyに設定
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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Missile/Enemy_Missile");
	}


	/* オブジェクト取得 */

	// プレイヤーを取得
	this->pPlayer = ObjectList->GetCharacterPlayer();


	// 初期化
	// 
	//ヒットエフェクト生成終了確認フラグ
	this->bHitEffectGenerated = false;

	// ミサイルショットフラグ
	this->bShotFlg = true;

	// 警告エフェクトフラグ
	this->bWarningEffectFlg = true;

	// 発射カウント
	this->iFiringCount = ENEMY_MISSILE_INTERVAL;


	/*モーション関連*/

	// エネミーモデルに攻撃のアニメーションをアタッチする
	this->iMissileAttackAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, FALSE);

	// アタッチした攻撃アニメーションの総再生時間を取得する
	this->fMissileAttackTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iMissileAttackAttachIndex);

	// 攻撃モーションフラグ
	this->bMissileAttackMotionFlg = false;

	// 攻撃中モーションフラグ
	this->bMissileAttackNowMotionFlg = false;

	// 攻撃終了モーションフラグ
	this->bMissileAttackEndMotionFlg = false;

	// 攻撃終了ループモーションフラグ
	this->bMissileAttackEndLoopMotionFlg = false;

	// 向き固定フラグ
	this->bDirectionFlg = true;
}

// デストラクタ
Enemy_Missile::~Enemy_Missile()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
}

// 初期化
void Enemy_Missile::Initialization()
{
	/* コリジョンセット */

	// エネミーのコリジョンの半径
	this->stCollisionCapsule.fCapsuleRadius = 100;

	// エネミーのカプセルコリジョンの上座標
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));

	// エネミーのカプセルコリジョンの下座標
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();

	// 発光フレームの処理
	UpdataLightFrame();
}

// 敵を移動させる
void Enemy_Missile::MoveEnemy()
{
	// 重力処理
	this->vecMove.y -= ENEMY_GRAVITY_SREED;

	// エネミーの座標を更新
	this->vecPosition.y += this->vecMove.y;

	// プレイヤーの座標を取得
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();

	//プレイヤーの座標を取得
	VECTOR playerPos = player->vecGetPosition();

	//エネミーの向きを初期化する
	VECTOR VRot = VGet(0, 0, 0);

	//プレイヤーの方向を向くようにエネミーの向きを定義
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//エネミーの向き固定フラグが有効か確認
	if (this->bDirectionFlg == true)
	{
		//エネミーの向き固定フラグが有効の場合
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
			// 攻撃予告エフェクトフラグが有効か確認
			if (this->bWarningEffectFlg == true)
			{
				// 攻撃予告エフェクトフラグが有効の場合
				// 攻撃予告エフェクトフラグを無効化
				this->bWarningEffectFlg = false;

				// ショットフラグを有効化
				this->bShotFlg = true;

				/* 攻撃予告エフェクト追加 */
				{
					/* 攻撃予告エフェクトを生成 */
					this->pEffectWarning = new EffectManualDelete();

					/* エフェクトの読み込み */
					this->pEffectWarning->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_bullet_warning/FX_e_bullet_warning")));

					/* エフェクトの座標設定 */
					this->pEffectWarning->SetPosition(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT - 20, vecPosition.z));

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

					// ショットフラグが有効か確認
					if (this->bShotFlg == true)
					{
						// ショットフラグが有効の場合
						// ミサイルを発射する
						Player_Range_Missile_Shot();

						// 発射カウントを初期化
						this->iFiringCount = ENEMY_MISSILE_INTERVAL;

						// 攻撃予告エフェクトフラグを有効化
						this->bWarningEffectFlg = true;
					}

					// ショットフラグを無効化
					this->bShotFlg = false;
				}
			}

		}
	}
}


// ミサイル弾の発射
void Enemy_Missile::Player_Range_Missile_Shot()
{
	//攻撃終了ループモーションフラグを無効化
	this->bMissileAttackEndLoopMotionFlg = false;

	//攻撃モーションフラグを有効化
	this->bMissileAttackMotionFlg = true;

	
}

// エネミーモデルアニメーション
void Enemy_Missile::Enemy_Model_Animation()
{
	// 攻撃モーションフラグが有効か確認
	if (this->bMissileAttackMotionFlg)
	{
		// 攻撃モーションフラグが有効の場合
		// 攻撃の再生時間を加算する
		this->fMissileAttackPlayTime += 0.5f;

		// 再生時間をセットする
		MV1SetAttachAnimTime(this->iModelHandle, this->iMissileAttackAttachIndex, this->fMissileAttackPlayTime);

		// 再生時間がアニメーションの総再生時間に達したか確認
		if (this->fMissileAttackPlayTime >= this->fMissileAttackTotalTime)
		{
			// アニメーションの再生時間が総再生時間に達した場合
			// ミサイルを生成
			this->pBulletRangeMissile = new BulletEnemyRangeMissile;

			//効果音再生
			gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_MISSILE_SHOT, this->vecPosition, SE_3D_SOUND_RADIUS);

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

			// アタッチした攻撃アニメーションをデタッチする
			MV1DetachAnim(this->iModelHandle, iMissileAttackAttachIndex);

			// 再生時間を初期化する
			this->fMissileAttackPlayTime = 0.0f;

			// エネミーモデルに攻撃のアニメーションをアタッチする
			this->iMissileAttackNowAttachIndex = MV1AttachAnim(this->iModelHandle, 1, -1, FALSE);

			// アタッチした攻撃アニメーションの総再生時間を取得する
			this->fMissileAttackNowTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iMissileAttackNowAttachIndex);

			// 攻撃中モーションフラグを有効化
			this->bMissileAttackNowMotionFlg = true;

			// 攻撃モーションフラグを無効化
			this->bMissileAttackMotionFlg = false;
		}
	}

	// 攻撃中モーションフラグが有効か確認
	if (this->bMissileAttackNowMotionFlg == true)
	{
		// 攻撃中モーションフラグが有効の場合
		// 攻撃中の再生時間を加算する
		this->fMissileAttackNowPlayTime += 0.5f;

		// 再生時間をセットする
		MV1SetAttachAnimTime(this->iModelHandle, this->iMissileAttackNowAttachIndex, this->fMissileAttackNowPlayTime);

		// 再生時間がアニメーションの総再生時間に達したか確認
		if (this->fMissileAttackNowPlayTime >= this->fMissileAttackNowTotalTime)
		{
			// アニメーションの再生時間が総再生時間に達した場合
			// アタッチしたアニメーションをデタッチする
			MV1DetachAnim(this->iModelHandle, iMissileAttackNowAttachIndex);

			// 再生時間を初期化する
			this->fMissileAttackNowPlayTime = 0.0f;

			// エネミーモデルに攻撃のアニメーションをアタッチする
			this->iMissileAttackEndAttachIndex = MV1AttachAnim(this->iModelHandle, 4, -1, FALSE);

			// アタッチした攻撃アニメーションの総再生時間を取得する
			this->fMissileAttackEndTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iMissileAttackEndAttachIndex);

			// 攻撃中モーションフラグを無効化
			this->bMissileAttackNowMotionFlg = false;

			// 攻撃終了モーションフラグを有効化
			this->bMissileAttackEndMotionFlg = true;
		}
	}

	// 攻撃終了モーションフラグが有効か確認
	if (this->bMissileAttackEndMotionFlg)
	{
		// 攻撃終了モーションフラグが有効の場合
		// 攻撃終了の再生時間を加算する
		this->fMissileAttackEndPlayTime += 0.5f;

		// 再生時間をセットする
		MV1SetAttachAnimTime(this->iModelHandle, this->iMissileAttackEndAttachIndex, this->fMissileAttackEndPlayTime);

		// 再生時間がアニメーションの総再生時間に達したか確認
		if (this->fMissileAttackEndPlayTime >= this->fMissileAttackEndTotalTime)
		{
			// アニメーションの再生時間が総再生時間に達した場合
			// アタッチしたアニメーションをデタッチする
			MV1DetachAnim(this->iModelHandle, iMissileAttackEndAttachIndex);

			// 再生時間を初期化する
			this->fMissileAttackEndPlayTime = 0.0f;

			// エネミーモデルに攻撃のアニメーションをアタッチする
			this->iMissileAttackEndLoopAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, TRUE);

			// アタッチした攻撃アニメーションの総再生時間を取得する
			this->fMissileAttackEndLoopTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iMissileAttackEndLoopAttachIndex);

			// 攻撃終了モーションフラグを無効化
			this->bMissileAttackEndMotionFlg = false;

			// 攻撃終了ループモーションフラグを有効化
			this->bMissileAttackEndLoopMotionFlg = true;
		}
	}

	// 攻撃終了ループモーションフラグが有効か確認
	if (this->bMissileAttackEndLoopMotionFlg)
	{
		// 攻撃終了ループモーションフラグが有効の場合
		// 攻撃終了ループの再生時間を加算する
		this->fMissileAttackEndLoopPlayTime += 0.5f;

		// 再生時間をセットする
		MV1SetAttachAnimTime(this->iModelHandle, this->iMissileAttackEndLoopAttachIndex, this->fMissileAttackEndPlayTime);

		// 再生時間がアニメーションの総再生時間に達したか確認
		if (this->fMissileAttackEndPlayTime >= this->fMissileAttackEndLoopTotalTime)
		{
			// アニメーションの再生時間が総再生時間に達した場合
			// 再生時間を初期化する
			this->fMissileAttackEndLoopPlayTime = 0.0f;

			// 攻撃終了ループモーションフラグを無効化
			this->bMissileAttackEndLoopMotionFlg = false;

			// アニメーションのループが終了したら、最初の攻撃モーションフラグを再度有効化
			this->bMissileAttackMotionFlg = true;
		}
	}
}

// 更新
void Enemy_Missile::Update()
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

	// エネミーモデルアニメーション
	Enemy_Model_Animation();

	// 重力処理
	Enemy_Gravity();

	/* HPが0以下であるか確認 */
	if (this->iNowHp <= 0)
	{
		// HPが0以下である場合
		/* 死亡フラグを有効化 */
		this->bDeadFlg = true;

		// HPが0以下である場合
		// ヒットエフェクト生成終了確認フラグが無効か確認
		if (this->bHitEffectGenerated == FALSE)
		{
			//ヒットエフェクト生成終了確認フラグが無効の場合
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

				//ヒットエフェクト生成終了確認フラグを有効化
				this->bHitEffectGenerated = TRUE;
			}
		}

		// 向き固定フラグを無効化
		this->bDirectionFlg = false;
		//死亡モーション以外のモーションをデタッチ
		MV1DetachAnim(this->iModelHandle, this->iMissileAttackAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iMissileAttackNowAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iMissileAttackEndAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iMissileAttackEndLoopAttachIndex);

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
			// 死亡モーションの再生時間が総再生時間に達した場合
			/* 撃破時の処理を実行 */
			Defeat();

			//爆発SE再生
			gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_DAMAGE, this->vecPosition, SE_3D_SOUND_RADIUS);
		}
		return;
	}
}

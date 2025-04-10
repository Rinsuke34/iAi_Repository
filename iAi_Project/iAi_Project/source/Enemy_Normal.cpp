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

	/* オブジェクトの設定 */

	//オブジェクトの種類をTypeEnemyに設定
	this->iObjectType = OBJECT_TYPE_ENEMY;

	//出現するブラッド量を設定
	this->iBloodAmount = 10;

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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Normal/Enemy_Normal");
	}

	/* オブジェクト取得 */
	// プレイヤーを取得
	this->pPlayer = ObjectList->GetCharacterPlayer();


	/* 初期化 */

	// 発射カウント
	this->iFiringCount = 0;

	// 誘導カウント
	this->iGuidanceCount = ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL;

	// プレイヤー攻撃ヒットエフェクト生成フラグ
	this->bHitEffectGenerated = false;

	//エネミー警告エフェクトフラグ
	this->bWarningEffectFlg = true;

	// ショットフラグ
	this->bShotFlg = false;



	/*モーション関連*/

	// エネミーモデルに攻撃のアニメーションをアタッチする
	this->iNormalAttackAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, FALSE);

	// アタッチした攻撃アニメーションの総再生時間を取得する
	this->fNormalAttackTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iNormalAttackAttachIndex);

	/*モーション関連初期化*/

	//攻撃モーションフラグ
	this->bNormalAttackMotionFlg = false;

	//攻撃中モーションフラグ
	this->bNormalAttackNowMotionFlg = false;

	//攻撃終了モーションフラグ
	this->bNormalAttackEndMotionFlg = false;

	//攻撃終了ループモーションフラグ
	this->bNormalAttackEndLoopMotionFlg = false;

	//向き固定フラグ
	this->bDirectionFlg = true;
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

	//エネミーのカプセルコリジョンの半径を設定
	this->stCollisionCapsule.fCapsuleRadius = 100;

	//エネミーのカプセルコリジョンの上の座標を設定
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));

	//エネミーのカプセルコリジョンの下の座標を設定
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();

	//発光フレーム処理
	UpdataLightFrame();
}

// 敵を移動させる
void Enemy_Normal::MoveEnemy()
{
	// 重力処理
	this->vecMove.y -= ENEMY_GRAVITY_SREED;

	// エネミーのy座標を更新
	this->vecPosition.y += this->vecMove.y;

	// プレイヤーの座標を取得
	VECTOR playerPos = pPlayer->vecGetPosition();

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

	//プレイヤーとエネミーの軸の距離を取得
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerY = fabs(this->vecPosition.y - playerPos.y);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//エネミーが撃破されていないか確認
	if (this->iNowHp > 0)
	{
		//エネミーが撃破されていない場合
		// プレイヤーとエネミーの距離の平方を計算
		float distanceToPlayerSquared = (this->vecPosition.x - playerPos.x) * (this->vecPosition.x - playerPos.x) +
			(this->vecPosition.y - playerPos.y) * (this->vecPosition.y - playerPos.y) +
			(this->vecPosition.z - playerPos.z) * (this->vecPosition.z - playerPos.z);

		// 索敵範囲の半径の平方
		float detectionRadiusSquared = ENEMY_Y_DISTANCE * ENEMY_Y_DISTANCE;

		// 発射カウントを減少
		iFiringCount--;

		// プレイヤーが索敵範囲内にいるか確認
		if (distanceToPlayerSquared < detectionRadiusSquared)
		{
			// プレイヤーが索敵範囲内にいる場合の処理
			//誘導カウントが発射カウントより大きいか確認
			if (iFiringCount <= ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL)
			{
				// 誘導カウントが発射カウントより大きい場合
				//エネミー攻撃予告エフェクトフラグが有効か確認
				if (this->bWarningEffectFlg == true)
				{
					//エネミー攻撃予告エフェクトフラグが有効の場合
					//エネミー攻撃予告エフェクトフラグを無効化
					this->bWarningEffectFlg = false;

					//ショットフラグを有効化
					this->bShotFlg = true;

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

						//攻撃予告SE再生
						gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_WARNING, this->vecPosition, SE_3D_SOUND_RADIUS);

						//攻撃予告エフェクトフラグが有効の場合
						if (this->bShotFlg == true)
						{
							//攻撃予告エフェクトフラグが有効の場合
							// ノーマル弾を発射する
							Player_Range_Normal_Shot();

							// 発射カウントを初期化
							this->iFiringCount = ENEMY_NORMAL_BULLET_INTERVAL;
						}

						//ショットフラグを無効化
						this->bShotFlg = false;
					}
				}
			}
		}
	}
}

// ノーマル弾の発射
void Enemy_Normal::Player_Range_Normal_Shot()
{
	//エネミーが撃破されていないか確認
	if (this->iNowHp > 0)
	{
		//エネミーが撃破されていない場合
		// プレイヤーの座標を取得
		VECTOR playerPos = pPlayer->vecGetPosition();

		//攻撃終了ループモーションフラグを無効化
		this->bNormalAttackEndLoopMotionFlg = false;

		//攻撃モーションフラグを有効化
		this->bNormalAttackMotionFlg = true;

		this->bWarningEffectFlg = true;
	}
}

// エネミーモデルアニメーション
void Enemy_Normal::Enemy_Model_Animation()
{
	//エネミーが撃破されていないか確認
	if (this->iNowHp > 0)
	{
		//エネミーが撃破されていない場合
		// 攻撃モーションフラグが有効か確認
		if (this->bNormalAttackMotionFlg)
		{
			// 攻撃モーションフラグが有効の場合
			// 再生時間を加算する
			this->fNormalAttackPlayTime += 0.5f;
			// 再生時間をセットする
			MV1SetAttachAnimTime(this->iModelHandle, this->iNormalAttackAttachIndex, this->fNormalAttackPlayTime);

			// 再生時間がアニメーションの総再生時間に達したか確認
			if (this->fNormalAttackPlayTime >= this->fNormalAttackTotalTime)
			{
				// アニメーションの再生時間が総再生時間に達した場合
				// ノーマル弾を生成
				this->pBulletRangeNormal = new BulletEnemyRangeNormal;
				//効果音再生
				gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_IKURA_ATTACK, this->vecPosition, SE_3D_SOUND_RADIUS);

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

				// アタッチした攻撃アニメーションをデタッチする
				MV1DetachAnim(this->iModelHandle, iNormalAttackAttachIndex);

				// 再生時間を初期化する
				this->fNormalAttackPlayTime = 0.0f;

				// エネミーモデルに攻撃のアニメーションをアタッチする
				this->iNormalAttackNowAttachIndex = MV1AttachAnim(this->iModelHandle, 1, -1, FALSE);

				// アタッチした攻撃アニメーションの総再生時間を取得する
				this->fNormalAttackNowTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iNormalAttackNowAttachIndex);

				// 攻撃中モーションフラグを有効化
				this->bNormalAttackNowMotionFlg = true;

				// 攻撃モーションフラグを無効化
				this->bNormalAttackMotionFlg = false;
			}
		}

		// 攻撃中モーションフラグが有効か確認
		if (this->bNormalAttackNowMotionFlg)
		{
			// 攻撃中モーションフラグが有効の場合
			// 攻撃中のアニメーション再生時間を加算する
			this->fNormalAttackNowPlayTime += 0.5f;

			// 攻撃中のアニメーション再生時間をセットする
			MV1SetAttachAnimTime(this->iModelHandle, this->iNormalAttackNowAttachIndex, this->fNormalAttackNowPlayTime);

			// 攻撃中のアニメーション再生時間が総再生時間に達したか確認
			if (this->fNormalAttackNowPlayTime >= this->fNormalAttackNowTotalTime)
			{
				// 攻撃中のアニメーション再生時間が総再生時間に達した場合
				// アタッチしたアニメーションをデタッチする
				MV1DetachAnim(this->iModelHandle, iNormalAttackNowAttachIndex);

				// 再生時間を初期化する
				this->fNormalAttackNowPlayTime = 0.0f;

				// エネミーモデルに攻撃のアニメーションをアタッチする
				this->iNormalAttackEndAttachIndex = MV1AttachAnim(this->iModelHandle, 4, -1, FALSE);

				// アタッチした攻撃アニメーションの総再生時間を取得する
				this->fNormalAttackEndTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iNormalAttackEndAttachIndex);

				// 攻撃終了モーションフラグを有効化
				this->bNormalAttackNowMotionFlg = false;

				// 攻撃終了モーションフラグを有効化
				this->bNormalAttackEndMotionFlg = true;
			}
		}

		// 攻撃終了モーションフラグが有効か確認
		if (this->bNormalAttackEndMotionFlg)
		{
			// 攻撃終了モーションフラグが有効の場合
			// 攻撃終了のアニメーション再生時間を加算する
			this->fNormalAttackEndPlayTime += 0.5f;

			// 攻撃終了のアニメーション再生時間をセットする
			MV1SetAttachAnimTime(this->iModelHandle, this->iNormalAttackEndAttachIndex, this->fNormalAttackEndPlayTime);

			// 攻撃終了のアニメーション再生時間が総再生時間に達したか確認
			if (this->fNormalAttackEndPlayTime >= this->fNormalAttackEndTotalTime)
			{
				// 攻撃終了のアニメーション再生時間が総再生時間に達した場合
				// アタッチしたアニメーションをデタッチする
				MV1DetachAnim(this->iModelHandle, iNormalAttackEndAttachIndex);

				// 再生時間を初期化する
				this->fNormalAttackEndPlayTime = 0.0f;

				// エネミーモデルに攻撃のアニメーションをアタッチする
				this->iNormalAttackEndLoopAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, TRUE);

				// アタッチした攻撃アニメーションの総再生時間を取得する
				this->fNormalAttackEndLoopTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iNormalAttackEndLoopAttachIndex);

				// 攻撃終了ループモーションフラグを有効化
				this->bNormalAttackEndMotionFlg = false;

				// 攻撃終了ループモーションフラグを有効化
				this->bNormalAttackEndLoopMotionFlg = true;
			}
		}

		// 攻撃終了ループモーションフラグが有効か確認
		if (this->bNormalAttackEndLoopMotionFlg)
		{
			// 攻撃終了ループモーションフラグが有効の場合
			// 攻撃終了ループのアニメーション再生時間を加算する
			this->fNormalAttackEndLoopPlayTime += 0.5f;

			// 攻撃終了ループのアニメーション再生時間をセットする
			MV1SetAttachAnimTime(this->iModelHandle, this->iNormalAttackEndLoopAttachIndex, this->fNormalAttackEndPlayTime);

			// 攻撃終了ループのアニメーション再生時間が総再生時間に達したか確認
			if (this->fNormalAttackEndPlayTime >= this->fNormalAttackEndLoopTotalTime)
			{
				// 攻撃終了ループのアニメーション再生時間が総再生時間に達した場合
				// アタッチしたアニメーションをデタッチする
				this->fNormalAttackEndLoopPlayTime = 0.0f;

				// 攻撃終了ループモーションフラグを無効化
				this->bNormalAttackEndLoopMotionFlg = false;

				// アニメーションのループが終了したら、最初の攻撃モーションフラグを再度有効化
				this->bNormalAttackMotionFlg = true;
			}
		}
	}
}

// 更新
void Enemy_Normal::Update()
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

				/* 攻撃ヒットのSEを再生 */
				gpDataList_Sound->SE_PlaySound(SE_PLAYER_SLASH_HIT);

				// エネミー被弾時の処理を実行
				DefeatAttack();

				// プレイヤー攻撃ヒットエフェクト生成フラグを有効化
				this->bHitEffectGenerated = TRUE;
			}
		}

		//エネミーの向き固定フラグを無効化
		this->bDirectionFlg = false;


		//死亡モーション以外のモーションをデタッチ
		MV1DetachAnim(this->iModelHandle, this->iNormalAttackAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iNormalAttackNowAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iNormalAttackEndAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iNormalAttackEndLoopAttachIndex);

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
		gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_DAMAGE, this->vecPosition, SE_3D_SOUND_RADIUS);
		}
		return;
	}
}

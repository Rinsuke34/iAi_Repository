/* 2025.01.29 石川智也 ファイル作成 */
#include "Enemy_Beam.h"

// コンストラクタ
Enemy_Beam::Enemy_Beam() : Enemy_Basic()
{

	/* オブジェクトのハンドル */
	this->pBulletRangeBeam = nullptr;	// ビームの弾
	// HPを設定
	this->iMaxHp = 1;
	this->iNowHp = 1;

	// オブジェクトの種類をTypeEnemyに設定
	this->iObjectType = OBJECT_TYPE_ENEMY;

	// 出現するブラッド量を設定
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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Beam/Enemy_Beam");
	}

	/* オブジェクト取得 */

	// プレイヤーを取得
	this->pPlayer = ObjectList->GetCharacterPlayer();

	/* 初期化 */

	// 発射カウント
	this->iFiringCount = 0;

	//ビームチャージカウント
	this->iChargeCount = ENEMY_BEAM_CHARGE_COUNT;

	//ビーム持続カウント
	this->iBeamDurationCount = ENEMY_BEAM_DURATION_COUNT;

	//ヒットエフェクト生成フラグ
	this->bHitEffectGenerated = false;

	// チャージフラグ
	this->bChargeFlg = false;

	// 発射フラグ
	this->bFiringFlg = false;

	// 向き固定フラグ
	this->bDirectionFlg = true;

	// ビームSEフラグ
	this->bBeamSEFlg = false;

	// ショットフラグ
	this->bShotFlg = true;

	// 警告エフェクトフラグ
	this->bWarningEffectFlg = true;					// 警告エフェクトフラグ

	/*モーション関連*/

	// エネミーモデルに攻撃のアニメーションをアタッチする
	this->iBeamAttackAttachIndex = MV1AttachAnim(this->iModelHandle, 5, -1, FALSE);

	// アタッチした攻撃アニメーションの総再生時間を取得する
	this->fBeamAttackTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iBeamAttackAttachIndex);

	// 攻撃モーションフラグ
	this->bBeamAttackMotionFlg = false;

	// 攻撃中モーションフラグ
	this->bBeamAttackNowMotionFlg = false;

	// 攻撃終了モーションフラグ
	this->bBeamAttackEndMotionFlg = false;

	// 攻撃終了ループモーションフラグ
	this->bBeamAttackEndLoopMotionFlg = false;
}

// デストラクタ
Enemy_Beam::~Enemy_Beam()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
}

// 初期化
void Enemy_Beam::Initialization()
{
	/* コリジョンセット */
	//エネミーのコリジョン半径を設定
	this->stCollisionCapsule.fCapsuleRadius = 100;

	//エネミーのカプセルコリジョンの上座標を設定
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));

	//エネミーのカプセルコリジョンの下座標を設定
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();

	// 発光するフレームの処理
	UpdataLightFrame();
}

// 敵を移動させる
void Enemy_Beam::MoveEnemy()
{
	// プレイヤーの座標を取得
	VECTOR playerPos = pPlayer->vecGetPosition();

	//エネミーの向きを初期化する
	VECTOR VRot = VGet(0, 0, 0);

	//プレイヤーの方向を向くようにエネミーの向きを定義
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//攻撃予告エフェクトの座標を設定
	VECTOR vecWarning = VGet(vecPosition.x, vecPosition.y + vecPosition.y / 2, vecPosition.z);


	//エネミーの向き固定フラグが有効か確認
	if (this->bDirectionFlg == true)
	{
		//エネミーの向きを設定
		this->vecRotation = VRot;
		//エネミーの向きを取得
		MV1SetRotationXYZ(iModelHandle, VRot);
	}

	//プレイヤーとエネミー軸の距離を取得
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
			// プレイヤーが探知範囲内にいる場合

			//誘導カウントが発射カウントより大きいか確認
			if (iFiringCount <= ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL)
			{
				// 誘導カウントが発射カウントより大きい場合
				//攻撃予告エフェクトフラグが有効か確認
				if (this->bWarningEffectFlg == true)
				{
					// 攻撃予告エフェクトフラグが有効の場合
					//攻撃予告エフェクトフラグを無効化
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
			}
		}
		//エフェクトがnullptrでないか確認
		if (this->pEffectWarning != nullptr)
		{
			//エフェクトがnullptrでない場合
			// エフェクトが再生中かどうか確認
			if (IsEffekseer3DEffectPlaying(this->pEffectWarning->iGetEffectHandle()))
			{
				// エフェクトが再生中の場合
				//ショットフラグが有効か確認
				if (this->bShotFlg == true)
				{
					// ショットフラグが有効の場合
					// ビームを発射する
					Player_Range_Beam_Shot();

					// 発射カウントを初期化
					this->iFiringCount = ENEMY_BEAM_INTERVAL;

					//攻撃予告エフェクトフラグを有効化
					this->bWarningEffectFlg = true;
				}

				//ショットフラグが無効か確認
				this->bShotFlg = false;
			}
		}

	}
}

// ビームの発射
void Enemy_Beam::Player_Range_Beam_Shot()
{
	//エネミーが撃破されていないか確認
	if (this->iNowHp > 0)
	{
		//エネミーが撃破されていない場合
	// プレイヤーの座標を取得
		VECTOR playerPos = pPlayer->vecGetPosition();

		// ビームを生成
		this->pBulletRangeBeam = new BulletEnemyRangeBeam;

		//効果音再生
		gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_BEAM_CHARGE, this->vecPosition, SE_3D_SOUND_RADIUS);

		//チャージフラグを有効化
		this->bChargeFlg = true;

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
		this->pBulletRangeBeam->SetPosition(VAdd(this->vecPosition, vecAdd));

		// 移動する弾の向きを設定
		this->pBulletRangeBeam->SetRotation(VGet(0.0f, -(this->vecRotation.y), 0.0f));

		//初期化
		this->pBulletRangeBeam->Initialization();

		//バレットリストに追加
		ObjectList->SetBullet(this->pBulletRangeBeam);
	}

}

//チャージ
void Enemy_Beam::Charge()
{
	//エネミーが撃破されていないか確認
	if (this->iNowHp > 0)
	{
		//エネミーが撃破されていない場合
		//チャージフラグが有効か確認
		if (this->bChargeFlg == TRUE)
		{
			// チャージフラグが有効の場合
			// チャージカウントを減算
			iChargeCount--;

			//向き固定フラグを有効化
			this->bDirectionFlg = true;

			// チャージカウントが0以下か確認
			if (this->iChargeCount <= 0)
			{
				// チャージカウントが0以下の場合
				//攻撃終了ループモーションフラグを無効化
				this->bBeamAttackEndLoopMotionFlg = false;

				//攻撃モーションフラグを有効化
				this->bBeamAttackMotionFlg = true;

				// チャージカウントを初期化
				this->iChargeCount = ENEMY_BEAM_CHARGE_COUNT;

				//チャージフラグを無効化
				this->bChargeFlg = false;

				//発射フラグを有効化
				this->bFiringFlg = true;

				//向き固定フラグを無効化
				this->bDirectionFlg = false;

				//ビームSEフラグを有効化
				this->bBeamSEFlg = true;
			}
		}

		//発射フラグが有効か確認
		if (this->bFiringFlg == TRUE)
		{
			// 発射フラグが有効の場合
			//ビームSEフラグが有効か確認
			if (this->bBeamSEFlg == TRUE)
			{
				// ビームSEフラグが有効の場合
				//効果音再生
				gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_BEAM_SHOT, this->vecPosition, SE_3D_SOUND_RADIUS);

				//ビームSEフラグを無効化
				this->bBeamSEFlg = false;
			}

			// ビームの持続カウントを減算
			this->iBeamDurationCount--;
			// ビームの持続カウントが0以下か確認
			if (this->iBeamDurationCount <= 0)
			{
				// ビームの持続カウントが0以下の場合
				this->bFiringFlg = false;

				//ビームの持続カウントを初期化
				this->iBeamDurationCount = ENEMY_BEAM_DURATION_COUNT;
			}
		}
	}
}

// エネミーモデルアニメーション
void Enemy_Beam::Enemy_Model_Animation()
{
	//エネミーが撃破されていないか確認
	if (this->iNowHp > 0)
	{
		//エネミーが撃破されていない場合
		//攻撃モーションフラグが有効か確認
		if (this->bBeamAttackNowMotionFlg == true)
		{
			// 攻撃モーションフラグが有効の場合
			// アタッチしたアニメーションを再生時間を加算する
			this->fBeamAttackNowPlayTime += 1.0f;

			// アタッチしたアニメーションの再生時間をセットする
			MV1SetAttachAnimTime(this->iModelHandle, this->iBeamAttackNowAttachIndex, this->fBeamAttackNowPlayTime);

			// アタッチしたアニメーションの再生時間が総再生時間に達したか確認
			if (this->fBeamAttackNowPlayTime >= this->fBeamAttackNowTotalTime)
			{
				// アタッチしたアニメーションの再生時間が総再生時間に達した場合
				//　ビームの持続カウントがビームのチャージカウント以下か確認
				if (this->iBeamDurationCount <= this->iChargeCount)
				{
					// ビームの持続カウントがビームのチャージカウント以下の場合
					// アタッチしたアニメーションをデタッチする
					MV1DetachAnim(this->iModelHandle, iBeamAttackNowAttachIndex);

					//ビーム攻撃中再生時間を初期化
					this->fBeamAttackNowPlayTime = 0.0f;

					// エネミーモデルに攻撃のアニメーションをアタッチする
					this->iBeamAttackEndAttachIndex = MV1AttachAnim(this->iModelHandle, 4, -1, FALSE);

					// アタッチした攻撃アニメーションの総再生時間を取得する
					this->fBeamAttackEndTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iBeamAttackEndAttachIndex);

					//攻撃中モーションフラグを無効化
					this->bBeamAttackNowMotionFlg = false;

					//攻撃終了モーションフラグを有効化
					this->bBeamAttackEndMotionFlg = true;


				}
			}
		}
	}
}

// 更新
void Enemy_Beam::Update()
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

	// チャージ
	Charge();

	/* HPが0以下であるか確認 */
	if (this->iNowHp <= 0)
	{
		// HPが0以下である場合
		/* 死亡フラグを有効化 */
		this->bDeadFlg = true;

		//ヒットエフェクト生成終了確認フラグが無効か確認
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

				//被弾時の処理を実行
				DefeatAttack();

				//ヒットエフェクト生成終了確認フラグを有効化
				this->bHitEffectGenerated = TRUE;
			}
		}

		//向き固定フラグを無効化
		this->bDirectionFlg = false;


		//死亡モーション以外のモーションをデタッチ
		MV1DetachAnim(this->iModelHandle, this->iBeamAttackAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iBeamAttackNowAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iBeamAttackEndAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iBeamAttackEndLoopAttachIndex);

		//ビームエフェクトを削除
		if (this->pBulletRangeBeam != nullptr)
		{
			//ビームエフェクトを削除
			this->pBulletRangeBeam->SetDeleteFlg(true);
		}

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

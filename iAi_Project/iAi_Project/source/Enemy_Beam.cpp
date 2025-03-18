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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Beam/Enemy_Beam");
	}

	this->pPlayer = ObjectList->GetCharacterPlayer();// プレイヤー
	this->iFiringCount = ENEMY_BEAM_INTERVAL;	// 発射カウント
	this->iChargeCount = ENEMY_BEAM_CHARGE_COUNT;			// ビームチャージカウント
	this->iBeamDurationCount = ENEMY_BEAM_DURATION_COUNT;	//ビームの持続カウント
	this->bEffectGenerated		 = false;					// 警告エフェクト生成フラグ
	this->bHitEffectGenerated	 = false;					// ヒットエフェクト生成フラグ
	this->bChargeFlg			 = false;					// チャージフラグ
	this->bFiringFlg			 = false;					// 発射フラグ
	this->bDirectionFlg			 = true;					// 向き固定フラグ
	this->bBeamSEFlg			 = false;					// ビームSEフラグ
	this->bShotFlg				 = true;					// ショットフラグ
	this->bWarningEffectFlg		 = true;					// 警告エフェクトフラグ

	/*モーション関連*/
// エネミーモデルに攻撃のアニメーションをアタッチする
	this->iBeamAttackAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, FALSE);
	// アタッチした攻撃アニメーションの総再生時間を取得する
	this->fBeamAttackTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iBeamAttackAttachIndex);

	this->bBeamAttackMotionFlg			= false;			// 攻撃モーションフラグ
	this->bBeamAttackNowMotionFlg		= false;			// 攻撃中モーションフラグ
	this->bBeamAttackEndMotionFlg		= false;			// 攻撃終了モーションフラグ
	this->bBeamAttackEndLoopMotionFlg	= false;			// 攻撃終了ループモーションフラグ
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
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();

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
		iFiringCount--;

		//誘導カウントが発射カウントより大きいか確認
		if (iFiringCount <= ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL)
		{
			// 誘導カウントが発射カウントより大きい場合
			if (this->bWarningEffectFlg == true)	// 警告エフェクトフラグが有効の場合
			{
				this->bWarningEffectFlg = false;

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
		// エフェクトが再生中かどうか確認
		if (IsEffekseer3DEffectPlaying(this->pEffectWarning->iGetEffectHandle()))
		{
			if (this->bShotFlg == true)
			{
				// エフェクトが再生終了している場合
			// ビームを発射する
			Player_Range_Beam_Shot();

			// 発射カウントを初期化
			this->iFiringCount = ENEMY_BEAM_INTERVAL;

				this->bWarningEffectFlg = true;
			}
			this->bShotFlg = false;
		}
	}


}

// ビームの発射
void Enemy_Beam::Player_Range_Beam_Shot()
{
	// プレイヤーの座標を取得
	VECTOR playerPos = pPlayer->vecGetPosition();

	// ビームを生成
	this->pBulletRangeBeam = new BulletEnemyRangeBeam;

	//効果音再生
	gpDataList_Sound->SE_PlaySound(SE_ENEMY_BEAM_CHARGE);

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

//チャージ
void Enemy_Beam::Charge()
{
	if (this->bChargeFlg == TRUE)
	{
		iChargeCount--;	// チャージカウントを減算

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

			this->bChargeFlg = false;

			this->bFiringFlg = true;

			this->bDirectionFlg = false;

			this->bBeamSEFlg = true;
		}
	}
	if (this->bFiringFlg == TRUE)
	{
		if (this->bBeamSEFlg == TRUE)
		{
			//効果音再生
			gpDataList_Sound->SE_PlaySound(SE_ENEMY_BEAM_SHOT);

			this->bBeamSEFlg = false;
		}

		// ビームの持続カウントを減算
		this->iBeamDurationCount--;
		// ビームの持続カウントが0以下か確認
		if (this->iBeamDurationCount <= 0)
		{
			// ビームの持続カウントが0以下の場合
			this->bFiringFlg = false;

			this->iBeamDurationCount = ENEMY_BEAM_DURATION_COUNT;
		}
	}
}

// エネミーモデルアニメーション
void Enemy_Beam::Enemy_Model_Animation()
{

	// 攻撃モーションフラグが有効か確認
	if (this->bBeamAttackMotionFlg)
	{
		// 攻撃モーションフラグが有効の場合
		this->fBeamAttackPlayTime += 0.5f;
		// 再生時間をセットする
		MV1SetAttachAnimTime(this->iModelHandle, this->iBeamAttackAttachIndex, this->fBeamAttackPlayTime);

		// 再生時間がアニメーションの総再生時間に達したか確認
		if (this->fBeamAttackPlayTime >= this->fBeamAttackTotalTime)
		{
			// アニメーションの再生時間が総再生時間に達した場合
			// アタッチした攻撃アニメーションをデタッチする
			MV1DetachAnim(this->iModelHandle, iBeamAttackAttachIndex);
			// 再生時間を初期化する
			this->fBeamAttackPlayTime = 0.0f;
			// エネミーモデルに攻撃のアニメーションをアタッチする
			this->iBeamAttackNowAttachIndex = MV1AttachAnim(this->iModelHandle, 1, -1, FALSE);
			// アタッチした攻撃アニメーションの総再生時間を取得する
			this->fBeamAttackNowTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iBeamAttackNowAttachIndex);

			this->bBeamAttackNowMotionFlg = true;
			// 攻撃モーションフラグを無効化
			this->bBeamAttackMotionFlg = false;
		}
	}

	if (this->bBeamAttackNowMotionFlg)
	{
		this->fBeamAttackNowPlayTime += 1.0f;
		MV1SetAttachAnimTime(this->iModelHandle, this->iBeamAttackNowAttachIndex, this->fBeamAttackNowPlayTime);

		if (this->fBeamAttackNowPlayTime >= this->fBeamAttackNowTotalTime)
		{
			if (this->iBeamDurationCount <= this->iChargeCount)
			{
				// アタッチしたアニメーションをデタッチする
				MV1DetachAnim(this->iModelHandle, iBeamAttackNowAttachIndex);
				this->fBeamAttackNowPlayTime = 0.0f;
				// エネミーモデルに攻撃のアニメーションをアタッチする
				this->iBeamAttackEndAttachIndex = MV1AttachAnim(this->iModelHandle, 4, -1, FALSE);
				// アタッチした攻撃アニメーションの総再生時間を取得する
				this->fBeamAttackEndTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iBeamAttackEndAttachIndex);

				this->bBeamAttackNowMotionFlg = false;
				this->bBeamAttackEndMotionFlg = true;

				
			}
		}
	}

	if (this->bBeamAttackEndMotionFlg)
	{
		this->fBeamAttackEndPlayTime += 0.5f;
		MV1SetAttachAnimTime(this->iModelHandle, this->iBeamAttackEndAttachIndex, this->fBeamAttackEndPlayTime);

		if (this->fBeamAttackEndPlayTime >= this->fBeamAttackEndTotalTime)
		{
			// アタッチしたアニメーションをデタッチする
			MV1DetachAnim(this->iModelHandle, iBeamAttackEndAttachIndex);
			this->fBeamAttackEndPlayTime = 0.0f;
			// エネミーモデルに攻撃のアニメーションをアタッチする
			this->iBeamAttackEndLoopAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, TRUE);
			// アタッチした攻撃アニメーションの総再生時間を取得する
			this->fBeamAttackEndLoopTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iBeamAttackEndLoopAttachIndex);

			this->bBeamAttackEndMotionFlg = false;
			this->bBeamAttackEndLoopMotionFlg = true;

			this->bDirectionFlg = true;
		}
	}

	if (this->bBeamAttackEndLoopMotionFlg)
	{
		this->fBeamAttackEndLoopPlayTime += 0.5f;
		MV1SetAttachAnimTime(this->iModelHandle, this->iBeamAttackEndLoopAttachIndex, this->fBeamAttackEndPlayTime);

		if (this->fBeamAttackEndPlayTime >= this->fBeamAttackEndLoopTotalTime)
		{
			this->fBeamAttackEndLoopPlayTime = 0.0f;
			this->bBeamAttackEndLoopMotionFlg = false;
			// アニメーションのループが終了したら、最初の攻撃モーションフラグを再度有効化
			this->bBeamAttackMotionFlg = true;
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
		MV1DetachAnim(this->iModelHandle, this->iBeamAttackAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iBeamAttackNowAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iBeamAttackEndAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iBeamAttackEndLoopAttachIndex);

		//ビームエフェクトを削除
		if (this->pBulletRangeBeam != nullptr)
		{
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
			gpDataList_Sound->SE_PlaySound(SE_ENEMY_DAMAGE);
		}
		return;
	}

	// コリジョンセット
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}

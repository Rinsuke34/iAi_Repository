/* 2025.01.28 石川智也 ファイル作成 */
#include "Enemy_Explosion.h"

// コンストラクタ
Enemy_Explosion::Enemy_Explosion() : Enemy_Basic()
{
	//初期化

	//X軸の距離
	this->iXdistance = ENEMY_X_DISTANCE;

	//Z軸の距離
	this->iZdistance = ENEMY_Z_DISTANCE;

	// 移動速度
	this->fSpeed = ENEMY_CHASE_SPEED;

	//起爆範囲内
	this->iDetonationRange = ENEMY_DETONATION_RANGE;

	//重力
	this->fGravity = ENEMY_GRAVITY_SREED;

	//爆発範囲内
	this->iBlastRange		= ENEMY_EXPLOSION_RANGE;

	// HPを設定
	this->iMaxHp = 1;
	this->iNowHp = 1;

	// オブジェクトの種類をTypeEnemyに設定
	this->iObjectType = OBJECT_TYPE_ENEMY;

	// 出現するブラッド量を設定
	this->iBloodAmount = 10;


	// ストップカウントを初期化
	this->iStopCount = 0;

	// エフェクトをnullptrに設定
	this->pEffect = nullptr;

	// 起爆予告エフェクト生成フラグ
	this->bEffectGenerated = false;

	// 落下フラグ
	this->bFallFlg = true;

	// ストップフラグ
	this->bStopFlg = true;

	//カウントフラグ
	this->bCountFlg = false;

	// 爆発フラグ
	this->bBlastFlg = false;

	//ヒットエフェクト生成フラグ
	this->bHitEffectGenerated = false;	

	//向き固定フラグ
	this->bDirectionFlg = true;

	//追跡フラグ
	this->bChaseFlg = true;

	//座標保存フラグ
	this->bSavePositionFlg = true;

	//リターンカウント
	this->iReturnCount = ENEMY_RETURN_TIME;

	/* データリスト取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "エフェクトリソース管理"を取得 */
		this->EffectList = dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"));

		/* "ステージ状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));;

	}

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Explosion/Enemy_Explosion");
	}

	


	//エネミーの初期座標を保存
	this->vecStartPosition = this->vecPosition;
}

// デストラクタ
Enemy_Explosion::~Enemy_Explosion()
{

}

// 初期化
void Enemy_Explosion::Initialization()
{
	/* コリジョンセット */
	//エネミーのカプセルコリジョンの半径
	this->stCollisionCapsule.fCapsuleRadius = 100;

	//エネミーのカプセルコリジョンの上の座標
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));

	//エネミーのカプセルコリジョンの下の座標
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();

	//発光するフレームの処理
	UpdataLightFrame();
}

// 敵の移動
void Enemy_Explosion::MoveEnemy()
{
	// エネミーの壁の当たり判定用のカプセルコリジョンを設定
	// カプセルの半径
	this->stHorizontalCollision.fCapsuleRadius = 50;

	// カプセルの上の座標
	this->stHorizontalCollision.vecCapsuleTop = VAdd(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z), VGet(0, 50, 0));

	// カプセルの下の座標
	this->stHorizontalCollision.vecCapsuleBottom = VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z);

	//エネミーの座標を保存フラグが有効か確認
	if (this->bSavePositionFlg == true)
	{
		//座標保存フラグが有効な場合
		//エネミーの初期座標を保存
		this->vecStartPosition = this->vecPosition;

		//座標保存フラグを無効にする
		this->bSavePositionFlg = false;
	}

	// プレイヤーの座標を取得
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	//エネミーが落下しているか確認
	if (this->bFallFlg == false)
	{
		//エネミーが落下している場合
		//落下速度を40に設定
		fSpeed = 40;

		//エネミーがプレイヤーに向かって移動する
		this->vecPosition = VAdd(this->vecPosition, VScale(VNorm(VSub(this->vecPosition, playerPos)), fSpeed));

		//落下速度を初期化
		fSpeed = 0;

		//カウントフラグを有効にする
		this->bCountFlg = true;
	}

	//カウントフラグが有効か確認
	if (this->bCountFlg = true)
	{
		//カウントフラグが有効な場合
		//ストップカウントを加算
		iStopCount++;
	}

	//ストップカウントが60を超えたか確認
	if (iStopCount > 60)
	{
		//ストップカウントが60を超えた場合
		//ストップフラグを有効にする
		this->bStopFlg = true;

		//ストップカウントを初期化
		iStopCount = 0;

		//移動速度を設定
		this->fSpeed = ENEMY_CHASE_SPEED;
	}

	//エネミーの向きを初期化する
	VECTOR VRot = VGet(0, 0, 0);

	// 重力処理
	this->vecMove.y -= ENEMY_GRAVITY_SREED;
	this->vecPosition.y += this->vecMove.y;

	//プレイヤーの方向を向くようにエネミーの向きを定義
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//エネミーの向き固定フラグが有効か確認
	if (this->bDirectionFlg == true)
	{
		//エネミーの向き固定フラグが有効な場合
		//エネミーの向きを設定
		this->vecRotation = VRot;
		//エネミーの向きを設定
		MV1SetRotationXYZ(iModelHandle, VRot);
	}

	//プレイヤーとエネミーのXZ軸の距離を取得
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerY = fabs(this->vecPosition.y - playerPos.y);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//チェイスフラグが有効か確認
	if (bChaseFlg == TRUE)
	{
		//チェイスフラグが有効な場合
		// プレイヤーとエネミーの距離の平方を計算
		float distanceToPlayerSquared = (this->vecPosition.x - playerPos.x) * (this->vecPosition.x - playerPos.x) +
			(this->vecPosition.y - playerPos.y) * (this->vecPosition.y - playerPos.y) +
			(this->vecPosition.z - playerPos.z) * (this->vecPosition.z - playerPos.z);

		// 索敵範囲の半径の平方
		float detectionRadiusSquared = ENEMY_Y_DISTANCE * ENEMY_Y_DISTANCE;

		// プレイヤーが索敵範囲内にいるか確認
		if (distanceToPlayerSquared < detectionRadiusSquared)
		{
			// プレイヤーが探知範囲内にいる場合
			// 探知範囲内にいるエネミーのみ処理を行う
			// エネミーが起爆されていないか確認
			if (bEffectGenerated == false)
			{
				//エネミーが起爆されていない場合
				//待機モーションをデタッチする
				MV1DetachAnim(this->iModelHandle, this->iWaitAttachIndex);

				//走りモーションをアタッチする
				this->iRunAttachIndex = MV1AttachAnim(this->iModelHandle, 7, -1, FALSE);

				//走りモーションの総再生時間を取得する
				this->fRunTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iRunAttachIndex);

				//再生速度を加算
				this->fRunPlayTime += 1.0f;

				//再生時間をセットする
				MV1SetAttachAnimTime(this->iModelHandle, this->iRunAttachIndex, this->fRunPlayTime);

				//再生時間がアニメーションの総再生時間に達したか確認
				if (this->fRunPlayTime >= this->fRunTotalTime)
				{
					//アニメーションの再生時間が総再生時間に達した場合
					//再生時間を初期化する
					this->fRunPlayTime = 0.0f;
				}


				// エネミーをプレイヤーに近づける
				VECTOR direction = VNorm(VSub(playerPos, this->vecPosition));

				// プレイヤーに向かう方向と速度を取得
				this->vecPosition = VAdd(this->vecPosition, VScale(direction, fSpeed));

				// プレイヤーがエネミーの起爆範囲内に入ったかどうかを確認
				if (VSize(VSub(playerPos, this->vecPosition)) < ENEMY_DETONATION_RANGE)
				{
					// プレイヤーがエネミーの起爆範囲内に入った場合
					//爆発フラグを有効にする
					this->bBlastFlg = true;

				}
			}
		}

		//起爆予告エフェクト生成完了フラグが有効か確認
		if (bEffectGenerated == false)
		{
			//起爆予告エフェクト生成完了フラグが有効な場合
			//爆発フラグが有効か確認
			if (this->bBlastFlg == true)
			{
				//爆発フラグが有効な場合
				//走りモーションをデタッチする
				MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);

				//爆発モーションをアタッチする
				this->iExplosionAttachIndex = MV1AttachAnim(this->iModelHandle, 5, -1, FALSE);

				// 起爆予告エフェクトを生成
				this->pEffectDetonation = new EffectManualDelete();

				// エフェクトの読み込み
				this->pEffectDetonation->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_suicide_light/FX_e_suicide_light")));

				// エフェクトの座標設定
				this->pEffectDetonation->SetPosition(this->vecPosition);

				// エフェクトの回転量設定
				this->pEffectDetonation->SetRotation(this->vecRotation);

				// エフェクトの初期化
				this->pEffectDetonation->Initialization();

				// エフェクトをリストに登録
				{
					// "オブジェクト管理"データリストを取得
					DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
					// エフェクトをリストに登録
					ObjectListHandle->SetEffect(pEffectDetonation);
				}

				//起爆SE再生
				gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_WARNING_EXPLOSION, this->vecPosition, SE_3D_SOUND_RADIUS);

				// 起爆予告エフェクト生成完了フラグを有効化する
				bEffectGenerated = true;
			}
		}
		else
		{
			// 起爆予告エフェクトが再生中かどうか確認
			if (IsEffekseer3DEffectPlaying(this->pEffectDetonation->iGetEffectHandle()))
			{
				// エフェクトが再生終了している場合
				/* データリスト取得 */
				DataList_PlayerStatus* PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

				/* 爆発エフェクト生成 */
				{
					/* 時間経過で削除されるエフェクトを追加 */
					EffectSelfDelete* AddEffect = new EffectSelfDelete();

					/* エフェクト読み込み */
					AddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_die/FX_e_die")));

					/* エフェクトの座標設定 */
					AddEffect->SetPosition(this->vecPosition);

					/* エフェクトの回転量設定 */
					AddEffect->SetRotation(this->vecRotation);

					/* エフェクトの削除されるまでの時間を設定 */
					AddEffect->SetDeleteCount(75);

					/* エフェクトの初期化 */
					AddEffect->Initialization();

					/* リストに登録 */
					{
						/* "オブジェクト管理"データリストを取得 */
						DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

						/* エフェクトをリストに登録 */
						ObjectListHandle->SetEffect(AddEffect);
					}
				}

				/* エネミーの削除フラグを有効にする */
				this->bDeleteFlg = true;

				//爆発SE再生
				gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_DAMAGE, this->vecPosition, SE_3D_SOUND_RADIUS);

				//プレイヤーが爆風範囲内にいるかどうかを確認
				if (VSize(VSub(playerPos, this->vecPosition)) < ENEMY_EXPLOSION_RANGE)
				{
					//プレイヤーが爆風範囲内にいる場合
				//プレイヤーを吹き飛ばす
					this->PlayerStatusList->SetPlayerNowFallSpeed(-30.0f);
					// 当たっている場合
					/* プレイヤーのHPを減少 */
					this->PlayerStatusList->SetPlayerNowHp(this->PlayerStatusList->iGetPlayerNowHp() - 1);

					/* 被ダメージカウントを加算する */
					this->PlayerStatusList->SetPlayerDamageCount(this->PlayerStatusList->iGetPlayerDamageCount() + 1);

					/* プレイヤーの無敵時間を設定 */
					this->PlayerStatusList->SetPlayerNowInvincibleTime(this->PlayerStatusList->iGetPlayerMaxInvincibleTime());


					/* "被ダメージ"のSEを再生 */
					gpDataList_Sound->SE_PlaySound(SE_PLAYER_DAMAGE);

					/* "被ダメージビリビリ"のSEを再生 */
					gpDataList_Sound->SE_PlaySound(SE_PLAYER_DAMAGE_ELEC);

					/* 被ダメージボイスを再生 */
					gpDataList_Sound->VOICE_PlaySound(VOICE_PLAYER_DAMAGE);

					/* 被ダメージのエフェクトを生成 */
					{
						/* ダメージ発生時エフェクト */
						{
							/* 被ダメージの瞬間に発生するエフェクトを追加 */
							EffectSelfDelete* pDamageEffect = new EffectSelfDelete();

							/* 座標を設定 */
							pDamageEffect->SetPosition(VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT / 2, 0)));

							/* エフェクトを取得 */
							pDamageEffect->SetEffectHandle(this->EffectList->iGetEffect("FX_damaged/FX_damaged"));

							/* 拡大率を設定 */
							pDamageEffect->SetScale(VGet(1.f, 1.f, 1.f));

							/* 削除カウントを設定 */
							// ※仮で1秒間
							pDamageEffect->SetDeleteCount(60);

							/* エフェクト初期化処理 */
							pDamageEffect->Initialization();

							/* オブジェクトリストに登録 */
							this->ObjectList->SetEffect(pDamageEffect);
						}

						/* 感電エフェクト */
						{
							/* 感電エフェクトを生成 */
							EffectSelfDelete_PlayerFollow* pShockEffect = new EffectSelfDelete_PlayerFollow(false);

							/* 感電エフェクトの読み込み */
							pShockEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_eshock/FX_eshock")));

							/* 感電エフェクトの初期化 */
							pShockEffect->Initialization();

							/* 感電エフェクトの時間を設定 */
							pShockEffect->SetDeleteCount(this->PlayerStatusList->iGetPlayerMaxInvincibleTime());

							/* 感電エフェクトをリストに登録 */
							this->ObjectList->SetEffect(pShockEffect);
						}

						/* 画面エフェクト(被ダメージ)作成 */
						this->StageStatusList->SetScreenEffect(new ScreenEffect_Damage());

					}
				}
			}
		}
	}

	//チェイスフラグが無効か確認
	if (this->bChaseFlg == false)
	{
		//チェイスフラグが無効な場合
		//リターンカウントを減算
		iReturnCount--;

		//リターンカウントが0以下か確認
		if (this->iReturnCount <= 0)
		{
			//リターンカウントが0以下の場合
			//エネミーの座標を初期座標に戻す
			// プレイヤーに向かう方向と速度を取得
			VECTOR direction = VNorm(VSub(this->vecStartPosition, this->vecPosition));

			// プレイヤーに向かう方向と速度を設定
			this->vecPosition = VAdd(this->vecPosition, VScale(direction, 5));

			//エネミーの向きを初期化する
			VECTOR VRot = VGet(0, 0, 0);

			//エネミーの向きを初期座標に向ける
			VRot.y = atan2f(this->vecPosition.x - this->vecStartPosition.x, this->vecPosition.z - this->vecStartPosition.z);

			//エネミーの向きを設定
			this->vecRotation = VRot;

			//すべてのアニメーションをデタッチする
			MV1DetachAnim(this->iModelHandle, this->iWaitAttachIndex);
			MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);
			MV1DetachAnim(this->iModelHandle, this->iExplosionAttachIndex);

			//走りモーションをアタッチする
			this->iRunAttachIndex = MV1AttachAnim(this->iModelHandle, 7, -1, FALSE);

			//走りモーションの総再生時間を取得する
			this->fRunTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iRunAttachIndex);

			//再生速度を加算
			this->fRunPlayTime += 1.0f;

			//再生時間をセットする
			MV1SetAttachAnimTime(this->iModelHandle, this->iRunAttachIndex, this->fRunPlayTime);

			//再生時間がアニメーションの総再生時間に達したか確認
			if (this->fRunPlayTime >= this->fRunTotalTime)
			{
				//アニメーションの再生時間が総再生時間に達した場合
				//再生時間を初期化する
				this->fRunPlayTime = 0.0f;
			}
		}
	}
	//エネミーの座標が初期座標に戻ったかどうかを確認
	if (VSize(VSub(this->vecStartPosition, this->vecPosition)) < 10)
	{
		//エネミーの座標が初期座標に戻った場合
		//チェイスフラグを有効にする
		this->bChaseFlg = true;

		//すべてのアニメーションをデタッチする
		MV1DetachAnim(this->iModelHandle, this->iWaitAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iExplosionAttachIndex);

		//待機モーションをアタッチする
		this->iWaitAttachIndex = MV1AttachAnim(this->iModelHandle, 6, -1, FALSE);

		//待機モーションの総再生時間を取得する
		this->iReturnCount = ENEMY_RETURN_TIME;
	}
}


// エネミーの重力処理
void Enemy_Explosion::Enemy_Gravity()
{
	// 移動後の座標を取得(垂直方向)
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x;
	vecNextPosition.y = this->vecPosition.y + this->vecMove.y;
	vecNextPosition.z = this->vecPosition.z;

	// エネミーの上部分の当たり判定から下方向へ向けた線分を作成
	this->stVerticalCollision.vecLineStart = this->vecPosition;
	this->stVerticalCollision.vecLineStart.y += PLAYER_HEIGHT;
	this->stVerticalCollision.vecLineEnd = stVerticalCollision.vecLineStart;
	this->stVerticalCollision.vecLineEnd.y -= 300;

	// 足場を取得
	auto& PlatformList = ObjectList->GetPlatformList();

	// 接触フラグ
	bool bHitFlg = false;

	// 足場と接触するか確認
	for (auto* platform : PlatformList)
	{
		// 足場との接触判定
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stVerticalCollision);

		// 接触しているか確認
		if (stHitPolyDim.HitFlag == 1)
		{
			// 接触している場合
			// 移動後の座標を接触座標に設定
			this->vecPosition.y = stHitPolyDim.HitPosition.y;

			// 重力をリセット
			this->vecMove.y = 0;

			// 落下フラグを有効にする
			this->bFallFlg = true;

			// ストップフラグを有効にする
			this->bStopFlg = true;

			// 接触フラグを有効にする
			bHitFlg = true;

			break;
		}

		//接触フラグが無効か確認
		if (!bHitFlg)
		{
			//接触フラグが無効の場合

			//重力を初期化
			this->fGravity = 0;

			//エネミーのｙ座標を移動しないよう設定
			this->vecMove.y = 0;

			//落下フラグを無効にする
			this->bFallFlg = false;

			//ストップフラグを無効にする
			this->bStopFlg = false;
		}
	}
}

// エネミーの水平処理
void Enemy_Explosion::Movement_Horizontal()
{
	/* 移動後の座標を取得(水平方向) */
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x + this->vecMove.x;
	vecNextPosition.y = this->vecPosition.y;
	vecNextPosition.z = this->vecPosition.z + this->vecMove.z;

	/* 1フレームでの移動量を分割して判定する回数 */
	/* ※移動量に応じて分割を設定する */
	int iMoveHitCheckCount = (int)VSize(VGet(this->vecMove.x, 0, this->vecMove.z));

	/* 分割した移動量 */
	VECTOR vecDevisionMove = VScale(this->vecMove, 1.0f / iMoveHitCheckCount);

	/* 分割して移動した先の座標 */
	VECTOR vecDevisionMovePosition = this->vecPosition;

	/* 道中でオブジェクトに接触しているか判定 */

	{

		/* 足場を取得 */
		auto& PlatformList = ObjectList->GetPlatformList();

		/* 足場と接触するか確認 */
		for (auto* platform : PlatformList)
		{
			/* 足場との接触判定 */
			for (int i = 0; i < PLAYER_MOVE_COLLISION_MAX; i++)
			{
				/* オブジェクトと接触しているか確認 */
				MV1_COLL_RESULT_POLY_DIM stHitPolyDim = platform->HitCheck_Capsule(this->stHorizontalCollision);

				/* 接触しているか確認 */
				if (stHitPolyDim.HitNum > 0)
				{
					// 接触している場合
					//チェイスフラグを無効にする
					this->bChaseFlg = false;

					break;
				}
			}
		}
	}

	/* プレイヤーの座標を移動させる */
	this->vecPosition = vecNextPosition;
}

// 更新
void Enemy_Explosion::Update()
{
	// バレットリストを取得
	auto& BulletList = ObjectList->GetBulletList();

	// プレイヤー攻撃と接触するか確認
	for (auto* bullet : BulletList)
	{
		/* オブジェクトタイプが"弾(プレイヤー)"あるいは"近接攻撃(プレイヤー)"であるか確認 */
		if ((bullet->iGetObjectType() == OBJECT_TYPE_BULLET_PLAYER) || (bullet->iGetObjectType() == OBJECT_TYPE_MELEE_PLAYER))
		{
			// 弾(プレイヤー)の場合
			// 弾との接触判定
			if (bullet->HitCheck(this->stCollisionCapsule) == true)
			{
				// 接触している場合
				// ダメージ処理
				this->iNowHp -= 1;
			}
		}
	}

	// HPが0以下であるか確認
	if (this->iNowHp <= 0)
	{
		// HPが0以下である場合
		/* 死亡フラグを有効化 */
		this->bDeadFlg = true;

		/* 爆発予告エフェクトを一度でも生成したかを確認 */
		if (this->pEffectDetonation != nullptr)
		{
			// 一度でも生成した場合
			//爆発予告エフェクトの削除フラグを有効化
			this->pEffectDetonation->SetDeleteFlg(true);

			//死亡モーション以外のモーションをデタッチ
			MV1DetachAnim(this->iModelHandle, this->iWaitAttachIndex);
			MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);
			MV1DetachAnim(this->iModelHandle, this->iExplosionAttachIndex);

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
			}
		}
	}

	/* HPが0以下であるか確認 */
	if (this->iNowHp <= 0)
	{
		// HPが0以下である場合
		//ヒットエフェクト生成フラグが無効か確認
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

				//被弾時の処理
				DefeatAttack();

				//ヒットエフェクト生成完了フラグを有効にする
				this->bHitEffectGenerated = TRUE;
			}
		}

		//向き固定フラグを無効にする
		this->bDirectionFlg = false;

		//死亡モーション以外のモーションをデタッチ
		MV1DetachAnim(this->iModelHandle, this->iWaitAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iExplosionAttachIndex);

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

	// エネミーを移動させる
	MoveEnemy();

	// エネミーの重力処理
	Enemy_Gravity();

	// エネミーの水平処理
	Movement_Horizontal();

	//エネミー水平当たり判定用のコリジョン描写
	CollisionDraw();

	// コリジョンセット
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}


//コリジョン描写
void Enemy_Explosion::CollisionDraw()
{
	//エネミーの水平垂直当たり判定用のコリジョン描写
	DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, GetColor(255, 0, 0));

	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);

	DrawCapsule3D(this->stHorizontalCollision.vecCapsuleTop, this->stHorizontalCollision.vecCapsuleBottom, this->stHorizontalCollision.fCapsuleRadius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);
}
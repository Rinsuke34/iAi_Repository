/* 2025.01.2８ 石川智也 ファイル作成 */
#include "Enemy_Escape.h"

// コンストラクタ
Enemy_Escape::Enemy_Escape() : Enemy_Basic()
{
	//初期化
	//X軸の距離
	this->iXescapedistance = ENEMY_X_ESCAPE_DISTANCE;

	//Z軸の距離
	this->iZescapedistance = ENEMY_Z_ESCAPE_DISTANCE;

	// 移動速度
	this->iEscapespeed = ENEMY_ESCAPE_SPEED;

	//重力
	this->fGravity = ENEMY_GRAVITY_SREED;

	//SEを再生開始したかのフラグ
	this->bPlayeSeFlg	= false;		// SEを再生開始したかのフラグ(ゲーム開始後に実行しないと他のシーン中に再生されるため)

	//エフェクトをnullptrに設定
	this->pEffect = nullptr;

	// HPを設定
	this->iMaxHp = 1;
	this->iNowHp = 1;

	// オブジェクトの種類をTypeEnemyに設定
	this->iObjectType = OBJECT_TYPE_ENEMY;

	// 出現するブラッド量を設定
	this->iBloodAmount = 20;

	//ヒットエフェクト生成フラグ
	this->bHitEffectGenerated = false;

	//逃走エフェクト生成フラグ
	this->bEscapeEffectGenerated = true;

	//向き固定フラグ
	this->bDirectionFlg = true;

	//待機カウント
	this->iWaitCount = 5;

	//壁に当たったかのフラグ
	this->bWallHitFlg = false;

	//待機カウント
	this->iReturnCount = 1;

	//再スタートカウント
	this->iRestartCount = 10;

	//壁の法線ベクトル
	this->wallNormal = VGet(0, 0, 0);

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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Escape/Enemy_Escape");


	}

}

// デストラクタ
Enemy_Escape::~Enemy_Escape()
{

}

// 初期化
void Enemy_Escape::Initialization()
{
	/* コリジョンセット */
	//エネミーのカプセル半径
	this->stCollisionCapsule.fCapsuleRadius = 100;

	//カプセルコリジョンの上の座標
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));

	//カプセルコリジョンの下の座標
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	//初期座標を保存
	this->vecInitialPosition = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();

	//発光するフレームの処理
	UpdataLightFrame();
}

// エネミーの移動処理
void Enemy_Escape::MoveEnemy()
{
	//エネミーの水平処理用のカプセルコリジョンの設定
	//カプセルの半径を設定
	this->stHorizontalCollision.fCapsuleRadius = 50;

	//カプセルの上の座標を設定
	this->stHorizontalCollision.vecCapsuleTop = VAdd(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z), VGet(0, 50, 0));

	//カプセルの下の座標を設定
	this->stHorizontalCollision.vecCapsuleBottom = VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z);

	// プレイヤーの座標を取得
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	//エネミーの向きを初期化する
	VECTOR VRot = VGet(0, 0, 0);

	// 重力処理
	this->vecMove.y -= ENEMY_GRAVITY_SREED;

	// エネミーの座標を更新
	this->vecPosition.y += this->vecMove.y;

	//プレイヤーとエネミーのXZ軸の距離を取得
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerY = fabs(this->vecPosition.y - playerPos.y);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//エネミーが撃破されていないか確認
	if (this->iNowHp > 0)
	{
		//エネミーが撃破されていない場合
		// プレイヤーとエネミーの距離の平方を計算
		float distanceToPlayerSquared = (this->vecPosition.x - playerPos.x) * (this->vecPosition.x - playerPos.x) +
			(this->vecPosition.y - playerPos.y) * (this->vecPosition.y - playerPos.y) + (this->vecPosition.z - playerPos.z) * (this->vecPosition.z - playerPos.z);

		// 索敵範囲の半径の平方
		float detectionRadiusSquared = ENEMY_X_ESCAPE_DISTANCE * ENEMY_X_ESCAPE_DISTANCE;

		// プレイヤーが索敵範囲内にいるか確認
		if (distanceToPlayerSquared < detectionRadiusSquared)
		{
			//プレイヤーが索敵範囲内にいる場合
			//待機カウントを減算
			this->iWaitCount--;

			//待機カウントが0以下か確認
			if (this->iWaitCount <= 0)
			{
				//待機カウントが0以下の場合
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
				if (this->bEscapeEffectGenerated == true)
				{
					// エフェクトを生成
					this->pEffect = new EffectSelfDelete();

					// エフェクトの読み込み
					this->pEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_glitter/FX_e_glitter")));

					// エフェクトの座標設定
					this->pEffect->SetPosition(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z));

					// エフェクトの回転量設定
					this->pEffect->SetRotation(this->vecRotation);

					//エフェクトの削除時間
					this->pEffect->SetDeleteCount(60);

					// エフェクトの初期化
					this->pEffect->Initialization();

					// エフェクトをリストに登録
					{
						// "オブジェクト管理"データリストを取得
						DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

						// エフェクトをリストに登録
						ObjectListHandle->SetEffect(pEffect);
					}

					// プレイヤーが探知範囲内にいる場合
					// プレイヤーから逃げる
					VECTOR directionAwayFromPlayer = VNorm(VSub(VGet(this->vecPosition.x, 0, this->vecPosition.z), VGet(playerPos.x, 0, playerPos.z)));

					// プレイヤーから逃げる方向と速度を設定
					this->vecPosition = VAdd(this->vecPosition, VScale(directionAwayFromPlayer, this->iEscapespeed));

					// エネミーの向きを初期化する
					VRot = VGet(0, 0, 0);

					// プレイヤーの方向を向くようにエネミーの向きを定義
					VRot.y = atan2f(playerPos.x - this->vecPosition.x, playerPos.z - this->vecPosition.z);

					//エネミーの向き固定フラグが有効か確認
					if (this->bDirectionFlg == true)
					{
						//エネミーの向き固定フラグが有効の場合
						// エネミーの向きを設定
						this->vecRotation = VRot;

						//エネミーの向きを取得
						MV1SetRotationXYZ(iModelHandle, VRot);
					}
				}
			}
		}
		else
		{
			// 探知範囲外にいる場合

			//待機カウントを初期化
			this->iWaitCount = 5;

			// 走るモーションをデタッチする
			MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);

			// 待機モーションをアタッチする
			this->iWaitAttachIndex = MV1AttachAnim(this->iModelHandle, 3, -1, FALSE);

			// 待機モーションの総再生時間を取得する	
			this->fWaitTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iWaitAttachIndex);

			//再生速度を加算
			this->fWaitPlayTime += 1.0f;

			//再生時間をセットする
			MV1SetAttachAnimTime(this->iModelHandle, this->iWaitAttachIndex, this->fWaitPlayTime);

			//再生時間がアニメーションの総再生時間に達したか確認
			if (this->fWaitPlayTime >= this->fWaitTotalTime)
			{
				//アニメーションの再生時間が総再生時間に達した場合
				//再生時間を初期化する
				this->fWaitPlayTime = 0.0f;
			}

			// プレイヤーの方向を向くようにエネミーの向きを定義
			VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

			if (VRot.y <= vecRotation.y)
			{
				this->vecRotation = VGet(vecRotation.x, vecRotation.y - 0.2, vecRotation.z);
			}
			if (VRot.y >= vecRotation.y)
			{
				this->vecRotation = VGet(vecRotation.x, vecRotation.y + 0.2, vecRotation.z);
			}
			if (VRot.x == vecRotation.x && VRot.y == vecRotation.y)
			{
				//エネミーの向きを設定
				this->vecRotation = VRot;
			}
		}
	}

	//エネミーが壁に当たったかのフラグが有効か確認
	if (this->bWallHitFlg == true)
	{
		//エネミーが壁に当たった場合
		//待機カウントを減算
		this->iReturnCount--;

		// 走るモーションをデタッチする
		MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);

		// 待機モーションをアタッチする
		this->iWaitAttachIndex = MV1AttachAnim(this->iModelHandle, 3, -1, FALSE);

		// 待機モーションの総再生時間を取得する
		this->fWaitTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iWaitAttachIndex);

		//再生速度を加算
		this->fWaitPlayTime += 1.0f;

		//再生時間をセットする
		MV1SetAttachAnimTime(this->iModelHandle, this->iWaitAttachIndex, this->fWaitPlayTime);

		//再生時間がアニメーションの総再生時間に達したか確認
		if (this->fWaitPlayTime >= this->fWaitTotalTime)
		{
			//アニメーションの再生時間が総再生時間に達した場合
			//再生時間を初期化する
			this->fWaitPlayTime = 0.0f;
		}

		//待機カウントが0以下か確認
		if (this->iReturnCount < 0)
		{
			//待機カウントが0以下の場合
			// プレイヤーの方向に９０度右に周り移動
			VECTOR directionToPlayer = VNorm(VSub(playerPos, this->vecPosition));
			VECTOR directionToPlayerRight = VCross(directionToPlayer, VGet(0, 1, 0));

			// 壁の法線ベクトルとプレイヤーの方向ベクトルの内積を計算
			float dotProduct = VDot(wallNormal, directionToPlayerRight);

			// 内積が正なら右に回転、負なら左に回転
			VECTOR VRot = VGet(0, 0, 0);
			if (dotProduct > 0)
			{
				vecPosition = VAdd(vecPosition, VScale(directionToPlayerRight, this->iEscapespeed));
				VRot.y = atan2f(directionToPlayerRight.x, -directionToPlayerRight.z);
			}
			else
			{
				vecPosition = VAdd(vecPosition, VScale(VScale(directionToPlayerRight, -1), this->iEscapespeed));
				VRot.y = atan2f(-directionToPlayerRight.x, directionToPlayerRight.z);
			}

			// エネミーの向きを設定
			this->vecRotation = VRot;
			MV1SetRotationXYZ(iModelHandle, VRot);

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

			//再起動カウントを減算
			this->iRestartCount--;

			//エネミーの向きを設定
			this->vecRotation = VRot;

			//エネミーの向きを設定
			MV1SetRotationXYZ(iModelHandle, VRot);
		}

		//再プレイカウントが0以下か確認
		if (this->iRestartCount < 0)
		{
			//再プレイカウントが0以下の場合
			//待機カウントを初期化
			this->iReturnCount = 1;

			//再プレイカウントを初期化
			this->iRestartCount = 10;

			//待機カウントを初期化
			this->iWaitCount = 5;

			//エネミーの壁に当たったフラグを無効にする
			this->bWallHitFlg = false;

			//逃走エフェクト生成フラグを有効にする
			this->bEscapeEffectGenerated = true;
		}
	}
}

//コリジョン描写
void Enemy_Escape::CollisionDraw()
{
	//エネミーの水平垂直の当たり判定用のコリジョンの描写
	DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, GetColor(255, 0, 0));

	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);

	DrawCapsule3D(this->stHorizontalCollision.vecCapsuleTop, this->stHorizontalCollision.vecCapsuleBottom, this->stHorizontalCollision.fCapsuleRadius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);
}

// エネミーモデルアニメーション
void Enemy_Escape::Enemy_Model_Animation()
{
	if (this->iNowHp > 0)
	{
	this->fRunPlayTime += 1.0f;
	// 再生時間をセットする
	MV1SetAttachAnimTime(this->iModelHandle, this->iRunAttachIndex, this->fRunPlayTime);

	//再生時間がアニメーションの総再生時間に達したか確認
	if (this->fRunPlayTime >= this->fRunTotalTime)
	{
		// アニメーションの再生時間が総再生時間に達した場合
		// 再生時間を初期化する
		this->fRunPlayTime = 0.0f;
	}
}
}

// 移動処理(水平方向)
void Enemy_Escape::Movement_Horizontal()
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
					//逃走エフェクト生成フラグを無効にする
					this->bEscapeEffectGenerated = false;

					//壁に当たったかのフラグを有効にする
					this->bWallHitFlg = true;

					//壁の法線ベクトルを取得
					wallNormal = stHitPolyDim.Dim[0].Normal;
				}
			}
		}
	}
	/* プレイヤーの座標を移動させる */
	this->vecPosition = vecNextPosition;
}

// 更新
void Enemy_Escape::Update()
{
	/* SEを再生開始したかの確認 */
	if (this->bPlayeSeFlg == false)
	{
		// 再生していない場合
		/* "逃走キラキラ音"のSEをループ再生 */
		gpDataList_Sound->SE_PlaySound_Loop_3D(SE_ENEMY_RUN, this->vecPosition, SE_3D_SOUND_RADIUS);

		/* 再生フラグを有効にする */
		this->bPlayeSeFlg = true;
	}

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

	/* エネミーの移動処理 */
	MoveEnemy();

	//重力処理
	Enemy_Gravity();

	//水平方向の移動処理
	Movement_Horizontal();

	/* HPが0以下であるか確認 */
	if (this->iNowHp <= 0)
	{
		// HPが0以下である場合
		/* "逃走キラキラ音"のSEを停止 */
		gpDataList_Sound->SE_PlaySound_Stop(SE_ENEMY_RUN);

		/* 死亡フラグを有効化 */
		this->bDeadFlg = true;

		//ヒットエフェクト生成完了フラグが無効か確認
		if (this->bHitEffectGenerated == FALSE)
		{
			/* Hitエフェクト追加 */
			{
				/* 時間経過で削除されるエフェクトを追加 */
				EffectSelfDelete* AddEffect = new EffectSelfDelete();

				/* エフェクト読み込み */
				AddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_hit/FX_hit")));

				/* エフェクトの座標設定 */
				AddEffect->SetPosition(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z));

				/* エフェクトの回転量設定 */
				AddEffect->SetRotation(this->vecRotation);

				/* エフェクトの削除されるまでの時間を設定 */
				AddEffect->SetDeleteCount(25);

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

				//被弾処理
				DefeatAttack();

				//ヒットエフェクト生成完了フラグを有効にする
				this->bHitEffectGenerated = TRUE;
			}
		}

		//向き固定フラグを無効にする
		this->bDirectionFlg = false;

		//死亡モーション以外のモーションをデタッチ
		MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);

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

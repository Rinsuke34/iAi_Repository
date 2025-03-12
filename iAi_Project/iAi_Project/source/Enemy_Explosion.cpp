/* 2025.01.28 石川智也 ファイル作成 */
#include "Enemy_Explosion.h"

// コンストラクタ
Enemy_Explosion::Enemy_Explosion() : Enemy_Basic()
{


	this->iXdistance = ENEMY_X_DISTANCE;		// X軸の距離
	this->iZdistance = ENEMY_Z_DISTANCE;		// Z軸の距離
	this->fSpeed = ENEMY_CHASE_SPEED;				// 移動速度
	this->iDetonationRange = ENEMY_DETONATION_RANGE;	//起爆範囲内
	this->fGravity = ENEMY_GRAVITY_SREED;				// 重力
	this->iBlastRange		= ENEMY_EXPLOSION_RANGE;	// 爆発範囲内

	// HPを設定
	this->iMaxHp = 1;
	this->iNowHp = 1;
	this->iObjectType = OBJECT_TYPE_ENEMY;	// オブジェクトの種類

	/* データリスト取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Explosion/Enemy_Explosion");
	}
	this->iStopCount = 0;
	this->pEffect = nullptr;
    this->bEffectGenerated = false;
	this->bFallFlg = true;
	this->bStopFlg = true;
	this->bCountFlg = false;
	this->bBlastFlg = false;
	this->bHitEffectGenerated = false;	// ヒットエフェクト生成フラグ
}

// デストラクタ
Enemy_Explosion::~Enemy_Explosion()
{

}

// 初期化
void Enemy_Explosion::Initialization()
{
	/* コリジョンセット */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();
}

void Enemy_Explosion::MoveEnemy()
{
	// プレイヤーの座標を取得
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	//エネミーが落下しているか確認
	if (this->bFallFlg == false)
	{
		//エネミーが落下している場合
		//エネミーが移動していた方向の逆方向に10f移動
		fSpeed = 40;
		this->vecPosition = VAdd(this->vecPosition, VScale(VNorm(VSub(this->vecPosition, playerPos)), fSpeed));
		fSpeed = 0;
		this->bCountFlg = true;
	}
	if (this->bCountFlg = true)
	{
		iStopCount++;
	}
	if (iStopCount > 180)
	{
		this->bStopFlg = true;
		iStopCount = 0;
		this->fSpeed = ENEMY_CHASE_SPEED;
	}
	//エネミーの向きを初期化する
	VECTOR VRot = VGet(0, 0, 0);

	// 重力処理
	this->vecMove.y -= fGravity;
	this->vecPosition.y += this->vecMove.y;

	//プレイヤーの方向を向くようにエネミーの向きを定義
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//エネミーの向きを設定
	this->vecRotation = VRot;

	//プレイヤーとエネミーのXZ軸の距離を取得
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//プレイヤーが探知範囲内にいるか確認
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE && this->bStopFlg == true)  // x軸とz軸の距離が1000未満の場合
	{
		// プレイヤーが探知範囲内にいる場合
        // 探知範囲内にいるエネミーのみ処理を行う
        if (!bEffectGenerated)
		{
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
				this->bBlastFlg = true;
				
			}
		}
	}
	if (!bEffectGenerated)
	{
		if (this->bBlastFlg == true)
		{
				// プレイヤーがエネミーの起爆範囲内に入った場合
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

                // エフェクト生成フラグを設定
                bEffectGenerated = true;
			}
		}
        else
		{
            // エフェクトが再生中かどうか確認
            if (IsEffekseer3DEffectPlaying(this->pEffectDetonation->iGetEffectHandle()))
			{
                // エフェクトが再生終了している場合
				/* 撃破時の処理を実行 */
				Defeat();

				//プレイヤーが爆風範囲内にいるかどうかを確認
				if (VSize(VSub(playerPos, this->vecPosition)) < ENEMY_EXPLOSION_RANGE)
				{
					//プレイヤーが爆風範囲内にいる場合
				//プレイヤーを吹き飛ばす
				this->PlayerStatusList->SetPlayerNowFallSpeed(-30.0f);
				}
			}
		}
	
}

void Enemy_Explosion::Enemy_Gravity()
{
	// 移動後の座標を取得(垂直方向)
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x;
	vecNextPosition.y = this->vecPosition.y + this->vecMove.y;
	vecNextPosition.z = this->vecPosition.z;

	// 主人公の上部分の当たり判定から下方向へ向けた線分を作成
	this->stVerticalCollision.vecLineStart = this->vecPosition;
	this->stVerticalCollision.vecLineStart.y += PLAYER_HEIGHT;
	this->stVerticalCollision.vecLineEnd = stVerticalCollision.vecLineStart;
	this->stVerticalCollision.vecLineEnd.y -= 9999;

	// 足場を取得
	auto& PlatformList = ObjectList->GetCollisionList();

	//// 足場と接触するか確認
	bool bHitFlg = false;
	for (auto* platform : PlatformList)
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stVerticalCollision);

		// 接触しているか確認
		if (stHitPolyDim.HitFlag == 1)
		{
			// 接触している場合
				this->vecPosition.y = stHitPolyDim.HitPosition.y;
				this->vecMove.y = 0; // 落下速度をリセット
			this->bFallFlg = true;
			this->bStopFlg = true;
			bHitFlg = true;//接触フラグを有効にする
					break;
				}
		//接触フラグが無効か確認
		if (!bHitFlg)
		{
			//接触フラグが無効の場合
			//接触フラグが無効の場合
			this->fGravity = 0;
			this->vecMove.y = 0;
			this->bFallFlg = false;
			this->bStopFlg = false;
			}
		}
}

// 更新
void Enemy_Explosion::Update()
{
    // バレットリストを取得
	auto& BulletList = ObjectList->GetBulletList();

    // プレイヤー攻撃と接触するか確認
	for (auto* bullet : BulletList)
	{
        // オブジェクトタイプが"弾(プレイヤー)"であるか確認
		if (bullet->iGetObjectType() == OBJECT_TYPE_BULLET_PLAYER)
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

	if (this->iNowHp <= 0)
	{
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
			gpDataList_Sound->SE_PlaySound(SE_ENEMY_DAMAGE);
		}
		return;
	}

	// エネミーを移動させる
	MoveEnemy();

	Enemy_Gravity();

	// コリジョンセット
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}
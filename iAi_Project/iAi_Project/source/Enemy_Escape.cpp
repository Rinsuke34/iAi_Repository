/* 2025.01.2８ 石川智也 ファイル作成 */
#include "Enemy_Escape.h"

// コンストラクタ
Enemy_Escape::Enemy_Escape() : Enemy_Basic()
{

	this->iXescapedistance = ENEMY_X_ESCAPE_DISTANCE;		// X軸の距離
	this->iZescapedistance = ENEMY_Z_ESCAPE_DISTANCE;		// Z軸の距離
	this->iEscapespeed = ENEMY_ESCAPE_SPEED;			// 移動速度
	this->fGravity = ENEMY_GRAVITY_SREED;				// 重力


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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Escape/Enemy_Escape");
		this->pEffect = nullptr;
	}
	this->bHitEffectGenerated = false;	// ヒットエフェクト生成フラグ
	this->bEscapeEffectGenerated = true;	// 逃走エフェクト生成フラグ
	this->bDirectionFlg = true;					// 向き固定フラグ
}

// デストラクタ
Enemy_Escape::~Enemy_Escape()
{

}

// 初期化
void Enemy_Escape::Initialization()
{
	/* コリジョンセット */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();
}

void Enemy_Escape::MoveEnemy()
{
	this->stHorizontalCollision.fCapsuleRadius = 50;
	this->stHorizontalCollision.vecCapsuleTop = VAdd(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z),VGet(0, 50, 0));
	this->stHorizontalCollision.vecCapsuleBottom = VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z);
	// プレイヤーの座標を取得
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	//エネミーの向きを初期化する
	VECTOR VRot = VGet(0, 0, 0);

	// 重力処理
	this->vecMove.y -= ENEMY_GRAVITY_SREED;
	this->vecPosition.y += this->vecMove.y;

	//プレイヤーとエネミーのXZ軸の距離を取得
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerY = fabs(this->vecPosition.y - playerPos.y);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//プレイヤーが探知範囲内にいるか確認
	if (distanceToPlayerX < ENEMY_X_ESCAPE_DISTANCE && distanceToPlayerY < ENEMY_Y_DISTANCE && distanceToPlayerZ < ENEMY_Z_ESCAPE_DISTANCE)// x軸とz軸の距離が600未満の場合
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

			if (this->bDirectionFlg == true)
			{
		// エネミーの向きを設定
		this->vecRotation = VRot;
				//エネミーの向きを取得
				MV1SetRotationXYZ(iModelHandle, VRot);
	}
}
}
	else
	{
		// 探知範囲外にいる場合
		// プレイヤーの方向を向くようにエネミーの向きを定義
		VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

		//エネミーの向きを設定
		this->vecRotation = VRot;
	}
}

//コリジョン描写
void Enemy_Escape::CollisionDraw()
{
	DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, GetColor(255, 0, 0));

	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);

	DrawCapsule3D(this->stHorizontalCollision.vecCapsuleTop, this->stHorizontalCollision.vecCapsuleBottom, this->stHorizontalCollision.fCapsuleRadius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);
}

// エネミーモデルアニメーション
void Enemy_Escape::Enemy_Model_Animation()
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
					this->bEscapeEffectGenerated = false;
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

	MoveEnemy();

	Enemy_Gravity();

	Movement_Horizontal();

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


				this->bHitEffectGenerated = TRUE;
			}
		}
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
			gpDataList_Sound->SE_PlaySound(SE_ENEMY_DAMAGE);
		}
		return;
	}

	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}

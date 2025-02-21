/* 2025.01.28 石川智也 ファイル作成 */
#include "Enemy_Explosion.h"

// コンストラクタ
ExplosionEnemy::ExplosionEnemy() : EnemyBasic()
{


	this->iXdistance = ENEMY_X_DISTANCE;		// X軸の距離
	this->iZdistance = ENEMY_Z_DISTANCE;		// Z軸の距離
	this->fSpeed = ENEMY_SPEED;				// 移動速度
	this->iDetonationRange = ENEMY_DETONATION_RANGE;	//起爆範囲内
	this->fGravity = ENEMY_GRAVITY_SREED;				// 重力

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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy");
	}

	this->pEffect = nullptr;
    this->bEffectGenerated = false;
}

// デストラクタ
ExplosionEnemy::~ExplosionEnemy()
{

}

// 初期化
void ExplosionEnemy::Initialization()
{
	/* コリジョンセット */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();
}

void ExplosionEnemy::MoveEnemy()
{
	// プレイヤーの座標を取得
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	//エネミーの向きを初期化する
	VECTOR VRot = VGet(0, 0, 0);

	// 重力処理
	this->vecMove.y -= ENEMY_GRAVITY_SREED;
	this->vecPosition.y += this->vecMove.y;

	//プレイヤーの方向を向くようにエネミーの向きを定義
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//エネミーの向きを設定
	this->vecRotation = VRot;

	//プレイヤーとエネミーのXZ軸の距離を取得
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//プレイヤーが探知範囲内にいるか確認
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE)  // x軸とz軸の距離が1000未満の場合
	{
		// プレイヤーが探知範囲内にいる場合
        // 探知範囲内にいるエネミーのみ処理を行う
        if (!bEffectGenerated)
		{
			// エネミーをプレイヤーに近づける
			VECTOR direction = VNorm(VSub(playerPos, this->vecPosition));

			// プレイヤーに向かう方向と速度を取得
			this->vecPosition = VAdd(this->vecPosition, VScale(direction, ENEMY_SPEED));

			// プレイヤーがエネミーの起爆範囲内に入ったかどうかを確認
			if (VSize(VSub(playerPos, this->vecPosition)) < ENEMY_DETONATION_RANGE)
			{
				// プレイヤーがエネミーの起爆範囲内に入った場合
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
				//エネミーの削除フラグを有効にする
				this->bDeleteFlg = true;

				//プレイヤーを吹き飛ばす
				this->PlayerStatusList->SetPlayerNowFallSpeed(-30.0f);
			}
		}
	}
}

void ExplosionEnemy::Enemy_Gravity()
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

	// 着地する座標
	// 初期値を移動後の座標に設定
	float fStandPosY = vecNextPosition.y;

	// 足場と接触するか確認
	for (auto* platform : PlatformList)
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stVerticalCollision);

		// 接触しているか確認
		if (stHitPolyDim.HitFlag == 1)
		{
			// 接触している場合

			// ヒットした座標が現在の着地座標より高い位置であるか確認
			if (stHitPolyDim.HitPosition.y >= fStandPosY)
			{
				// エネミーのy座標を減算
				this->vecPosition.y = stHitPolyDim.HitPosition.y;
				this->vecMove.y = 0; // 落下速度をリセット

				// ヒットした座標がプレイヤーが歩いて登れる位置より低い位置であるか確認
				if (fStandPosY < this->vecPosition.y + PLAYER_CLIMBED_HEIGHT)
				{
					// 着地座標がプレイヤーの現在位置より低い場合
					// 地面に着地したと判定する
					// 着地座標を着地した座標に更新
					fStandPosY = stHitPolyDim.HitPosition.y;
				}
				else
				{
					// 着地座標がプレイヤーの現在位置より高い場合
					// 着地座標をプレイヤーが天井にめり込まない高さに更新
					fStandPosY = stHitPolyDim.HitPosition.y - PLAYER_HEIGHT - PLAYER_CLIMBED_HEIGHT;

					// ループを抜ける
					break;
				}
			}
		}

	}
}

// 更新
void ExplosionEnemy::Update()
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

	if (this->iGetNowHP() <= 0)
	{
		// 削除フラグを有効にする
		this->bDeleteFlg = true;
		/* 爆発予告エフェクトを一度でも生成したかを確認 */
		if (this->pEffectDetonation != nullptr)
		{
			// 一度でも生成した場合
			//爆発予告エフェクトの削除フラグを有効化
			this->pEffectDetonation->SetDeleteFlg(true);
		}
	}

	// エネミーを移動させる
	MoveEnemy();

	Enemy_Gravity();

	// コリジョンセット
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}
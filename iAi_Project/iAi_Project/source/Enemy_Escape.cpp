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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy");
		this->pEffect = nullptr;
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
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();
}

void Enemy_Escape::MoveEnemy()
{
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
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//プレイヤーが探知範囲内にいるか確認
	if (distanceToPlayerX < ENEMY_X_ESCAPE_DISTANCE && distanceToPlayerZ < ENEMY_Z_ESCAPE_DISTANCE)// x軸とz軸の距離が600未満の場合
	{
		// 逃走エフェクトを生成
		this->pEffect = new EffectManualDelete();

		// エフェクトの読み込み
		this->pEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_glitter/FX_e_glitter")));

		// エフェクトの座標設定
		this->pEffect->SetPosition(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z));

		// エフェクトの回転量設定
		this->pEffect->SetRotation(this->vecRotation);

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

		// エネミーの向きを設定
		this->vecRotation = VRot;
	}
}

void Enemy_Escape::Enemy_Gravity()
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

//コリジョン描写
void Enemy_Escape::CollisionDraw()
{
	DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, GetColor(255, 0, 0));
}

// 更新
void Enemy_Escape::Update()
{
	/* バレットリストを取得 */
	auto& BulletList = ObjectList->GetBulletList();

	/* プレイヤー攻撃と接触するか確認 */
	for (auto* bullet : BulletList)
	{
		/* オブジェクトタイプが"弾(プレイヤー)"であるか確認 */
		if (bullet->iGetObjectType() == OBJECT_TYPE_BULLET_PLAYER)
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

	/* HPが0以下であるか確認 */
	if (this->iNowHp <= 0)
	{
		// HPが0以下である場合
		/* 撃破時の処理を実行 */
		Defeat();

		return;
	}

	MoveEnemy();

	Enemy_Gravity();

	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}

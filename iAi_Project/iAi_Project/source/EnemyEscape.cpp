/* 2025.01.2８ 石川智也 ファイル作成 */
#include "EnemyEscape.h"

// コンストラクタ
EscapeEnemy::EscapeEnemy() : EnemyBasic()
{

	this->iXescapedistance = ENEMY_X_ESCAPE_DISTANCE;		// X軸の距離
	this->iZescapedistance = ENEMY_Z_ESCAPE_DISTANCE;		// Z軸の距離
	this->fEscapespeed = ENEMY_ESCAPE_SPEED;			// 移動速度


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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Kari_0127");
	}
}

// デストラクタ
EscapeEnemy::~EscapeEnemy()
{

}

// 初期化
void EscapeEnemy::Initialization()
{
	/* コリジョンセット */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition,VGet(0,100,0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();
}

void EscapeEnemy::MoveEnemy()
{
	// プレイヤーの座標を取得
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	//エネミーの向きを初期化する
	VECTOR VRot = VGet(0, 0, 0);

	//プレイヤーの方向を向くようにエネミーの向きを定義
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//エネミーの向きを設定
	this->vecRotation = VRot;

	//プレイヤーとエネミーのXZ軸の距離を取得
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//プレイヤーが探知範囲内にいるか確認
	if (distanceToPlayerX < ENEMY_X_ESCAPE_DISTANCE && distanceToPlayerZ < ENEMY_Z_ESCAPE_DISTANCE)// x軸とz軸の距離が600未満の場合
	{
		// プレイヤーが探知範囲内にいる場合
		// プレイヤーから逃げる
		VECTOR directionAwayFromPlayer = VNorm(VSub(VGet(this->vecPosition.x, 0, this->vecPosition.z), VGet(playerPos.x, 0, playerPos.z)));

		// プレイヤーから逃げる方向と速度を設定
		this->vecPosition = VAdd(this->vecPosition, VScale(directionAwayFromPlayer, ENEMY_ESCAPE_SPEED));

		// エネミーの向きを初期化する
		VECTOR VRot = VGet(0, 0, 0);

		// プレイヤーの方向を向くようにエネミーの向きを定義
		VRot.y = atan2f(playerPos.x - this->vecPosition.x, playerPos.z - this->vecPosition.z);

		// エネミーの向きを設定
		this->vecRotation = VRot;
	}
}

// 更新
void EscapeEnemy::Update()
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



	if (this->iGetNowHP() <= 0)
	{
		// 削除フラグを有効にする
		this->SetDeleteFlg(true);
	}

	MoveEnemy();
	
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}

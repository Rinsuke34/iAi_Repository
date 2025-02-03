/* 2025.01.28 石川智也 ファイル作成 */
#include "Enemy_Explosion.h"

// コンストラクタ
ExplosionEnemy::ExplosionEnemy() : EnemyBasic()
{


	this->iXdistance = ENEMY_X_DISTANCE;		// X軸の距離
	this->iZdistance = ENEMY_Z_DISTANCE;		// Z軸の距離
	this->fSpeed = ENEMY_SPEED;				// 移動速度
	this->iDetonationRange = ENEMY_DETONATION_RANGE;	//起爆範囲内
	this->iLastTime = ENEMY_DETONATION_TIME;	//起爆タイマー

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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy_Kari_0127");
	}

	this->pEffect = nullptr;
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


	// 現在の時間を取得
	int nowTime = GetNowCount();

	//エネミーの向きを初期化する
	VECTOR VRot = VGet(0, 0, 0);

	//プレイヤーの方向を向くようにエネミーの向きを定義
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//エネミーの向きを設定
	this->vecRotation = VRot;

	//プレイヤーとエネミーのXZ軸の距離を取得
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//起爆カウントを初期化
	static bool iActioncount = false;

	//プレイヤーが探知範囲内にいるか確認
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE)  // x軸とz軸の距離が1000未満の場合
	{
		// プレイヤーが探知範囲内にいる場合
		// 起爆カウントが進んでいるか確認
		if (iActioncount == false)
		{
			// 起爆カウントが進んでいる場合
			// エネミーをプレイヤーに近づける
			VECTOR direction = VNorm(VSub(playerPos, this->vecPosition));

			// プレイヤーに向かう方向と速度を取得
			this->vecPosition = VAdd(this->vecPosition, VScale(direction, ENEMY_SPEED));

			// プレイヤーがエネミーの起爆範囲内に入ったかどうかを確認
			if (VSize(VSub(playerPos, this->vecPosition)) < ENEMY_DETONATION_RANGE)
			{
				// プレイヤーがエネミーの起爆範囲内に入った場合
				//起爆カウントを開始
				iActioncount = true;
			}
		}
		//プレイヤーが探知範囲内おり起爆カウントが進んでいる場合であるか確認
		else if (iActioncount == true)
		{
			//プレイヤーが探知範囲内おり起爆カウントが進んでいる場合
			//タイマーを取得
			static int startTime = nowTime;

			// タイマーが3秒以上経過しているかどうかを確認
			if (nowTime - startTime > ENEMY_DETONATION_TIME)
			{
				//タイマーが3秒以上経過している場合
				//エネミーの削除フラグを有効にする
				this->bDeleteFlg = true;

				//タイマーをリセットする
				startTime = nowTime;

			}
		}
	}
}

// 更新
void ExplosionEnemy::Update()
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
		this->bDeleteFlg = true;
	}

	// エネミーを移動させる
	MoveEnemy();

	// コリジョンセット
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}

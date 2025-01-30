/* 2025.01.29 石川智也 ファイル作成 */
#include "EnemyNormal.h"

// コンストラクタ
NormalEnemy::NormalEnemy() : EnemyBasic()
{

	/* オブジェクトのハンドル */
	this->pBulletRangeNormal = nullptr;	// 近接攻撃(弱)の弾
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

	this->eEffect = nullptr;
}

// デストラクタ
NormalEnemy::~NormalEnemy()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
}

// 初期化
void NormalEnemy::Initialization()
{
	/* コリジョンセット */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();
}

void NormalEnemy::MoveEnemy()
{
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	VECTOR VRot = VGet(0, 0, 0); // 回転量
	VRot.y = atan2f(this->vecPosition.x -playerPos.x, this->vecPosition.z - playerPos.z); // プレイヤーの方向を向く
	this->vecRotation = VRot; // 回転量を設定
	if(CheckHitKey(KEY_INPUT_P))
	{
		Player_Range_Normal();
	}
}

void NormalEnemy::Player_Range_Normal()
{
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();
	this-> pBulletRangeNormal = new BulletEnemyRangeNormal;
	/* 攻撃の生成方向の設定 */
	/* 攻撃座標を算出 */
	VECTOR vecAdd;
	// 方向
	vecAdd.x = 0.f;
	vecAdd.y = 0.f;
	vecAdd.z = 0.f;
	vecAdd = VNorm(vecAdd);
	vecAdd = VScale(vecAdd, 100);
	// 高さ
	vecAdd.y = 100 / 2.f;
	vecAdd.x = PLAYER_WIDE / 2.f;

	// 攻撃生成座標をエネミーが向いている方向に設定
	this->pBulletRangeNormal->SetPosition(VAdd(this->vecPosition, vecAdd));

	// 攻撃の向きを設定
	this->pBulletRangeNormal->SetRotation(VGet(0.0f, -(this->vecRotation.y), 0.0f));
	
	//初期化
	this->pBulletRangeNormal->Initialization();

	//バレットリストに追加
	ObjectList->SetBullet(this->pBulletRangeNormal);


	
}

// 更新
void NormalEnemy::Update()
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

	//Player_Range_Normal();
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}

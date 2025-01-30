/* 2025.01.2８ 石川智也 ファイル作成 */
#include "EnemyEscape.h"

// コンストラクタ
EscapeEnemy::EscapeEnemy() : EnemyBasic()
{
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
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();
	// 現在の時間を取得
	int nowTime = GetNowCount();
	// 経過時間を計算
	float deltaTime = (nowTime - _lastTime) / 1000.0f; // ミリ秒を秒に変換
	_lastTime = nowTime;

	VECTOR VRot = VGet(0, 0, 0); // 回転量
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z); // プレイヤーの方向を向く
	this->vecRotation = VRot; // 回転量を設定
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);
	if (distanceToPlayerX < 600.0f && distanceToPlayerZ < 600.0f) { // x軸とz軸の距離が100未満の場合
		VECTOR directionAwayFromPlayer = VNorm(VSub(VGet(this->vecPosition.x, 0, this->vecPosition.z), VGet(playerPos.x, 0, playerPos.z)));
		this->vecPosition = VAdd(this->vecPosition, VScale(directionAwayFromPlayer, 5.0f));
		VECTOR VRot = VGet(0, 0, 0); // 回転量
		VRot.y = atan2f(playerPos.x - this->vecPosition.x, playerPos.z - this->vecPosition.z); // プレイヤーの方向を向く
		this->vecRotation = VRot; // 回転量を設定
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
		/* エフェクト追加 */
		{
			/* 近接攻撃(弱)のエフェクトを生成 */
			this->eEffect = new EffectManualDelete();

			/* エフェクトの読み込み */
			this->eEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_die03")));

			/* エフェクトの座標設定 */
			this->eEffect->SetPosition(this->vecPosition);

			/* エフェクトの回転量設定 */
			this->eEffect->SetRotation(this->vecRotation);

			/* エフェクトの初期化 */
			this->eEffect->Initialization();

			/* エフェクトをリストに登録 */
			{
				/* "オブジェクト管理"データリストを取得 */
				DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
				/* エフェクトをリストに登録 */
				ObjectListHandle->SetEffect(this->eEffect);

			}
		}
	}
	MoveEnemy();
	
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}

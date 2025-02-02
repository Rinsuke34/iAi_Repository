/* 2025.01.28 石川智也 ファイル作成 */
#include "Enemy_Test.h"

// コンストラクタ
TestEnemy::TestEnemy() : EnemyBasic()
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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Kari_0127");
	}
	
	this->eEffect	= nullptr;
}

// デストラクタ
TestEnemy::~TestEnemy()
{

}

// 初期化
void TestEnemy::Initialization()
{
	/* コリジョンセット */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition,VGet(0,100,0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* コアフレーム番号取得 */
	LoadCoreFrameNo();
}

void TestEnemy::MoveEnemy()
{

	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();
	// 現在の時間を取得
	int nowTime = GetNowCount();
	static bool effectPlayed = false; // エフェクトが再生されたかどうかを追跡するフラグ
	// actioncount 変数に基づく動作
	VECTOR VRot = VGet(0, 0, 0); // 回転量
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z); // プレイヤーの方向を向く
	this->vecRotation = VRot; // 回転量を設定
	if (actioncount == 0 && !effectPlayed) {
		//	// キャラクターをプレイヤーに近づける
		VECTOR direction = VNorm(VSub(playerPos,this->vecPosition));
		this->vecPosition = VAdd(this->vecPosition, VScale(direction, 5.0f)); // 速度を調整
		// プレイヤーに近づいたらカウントを増やす
		if (VSize(VSub(playerPos, this->vecPosition)) < 50.0f) { // 距離の閾値を設定
			actioncount = 2;
		}
	}
	else if (actioncount == 2 && !effectPlayed) {
		// 一定時間後に発動
		static int startTime = nowTime;
		// 3秒後に発動
		if (nowTime - startTime > 3000) { // 3秒後に発動
			this->bDeleteFlg = true;
			effectPlayed = true; // エフェクトが再生されたことを記録
			startTime = nowTime; // タイマーをリセット

		}
	}
}

// 更新
void TestEnemy::Update()
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
	MoveEnemy();
	
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}

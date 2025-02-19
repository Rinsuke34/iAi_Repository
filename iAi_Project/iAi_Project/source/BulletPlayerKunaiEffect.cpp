/* 2025.02.14 菊池雅道 ファイル作成 */

#include "BulletPlayerKunaiEffect.h"

/* クナイ(エフェクト)クラスの定義 */

// コンストラクタ
BulletPlayerKunaiEffect::BulletPlayerKunaiEffect() : BulletBase()
{
	/* 初期化 */
	this->iObjectType					= OBJECT_TYPE_BULLET_PLAYER;		// オブジェクトの種類を"弾(プレイヤー)"に設定
	this->vecKunaiTargetPosition		= VGet(0,0,0);						// ターゲット座標
	this->vecKunaiMoveDirection			= VGet(0, 0, 0);					// クナイの移動する方向
	this->fKunaiTargetDistance			= 0.0f;								// クナイの発射地点からターゲットまでの距離
	this->fKunaiMoveDistance			= 0.0f;								// クナイの移動距離
	this->fKunaiAngleX					= 0.0f;								// クナイのX軸回転角度
	this->fKunaiAngleY					= 0.0f;								// クナイのY軸回転角度
	this->iKunaiDeleteCount				= KUNAI_ATTACK_COUNT;				// クナイの削除カウント(攻撃時間)
	this->bKunaiAttackFlg				= false;							// クナイの攻撃フラグ

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Bullet/Kunai_kari");
	}
}

// デストラクタ
BulletPlayerKunaiEffect::~BulletPlayerKunaiEffect()
{
	
}

// 初期化
void BulletPlayerKunaiEffect::Initialization()
{
	/* クナイの生成地点からターゲットまでのベクトルをクナイの移動ベクトルに設定 */
	this->vecKunaiMoveDirection = VSub(this->vecKunaiTargetPosition, this->vecPosition);

	/* クナイの移動距離を設定 */
	this->fKunaiTargetDistance = VSize(this->vecKunaiMoveDirection);

	/* クナイの移動ベクトルを正規化 */
	this->vecKunaiMoveDirection = VNorm(this->vecKunaiMoveDirection);

	/* X軸回転の計算（Y軸の高さの差 / X-Z平面上の距離） */
	/* 高さの差 */ 
	float fHeightDiff = this->vecKunaiTargetPosition.y - this->vecPosition.y;
	/* X - Z 平面上の距離のみを計算 */ 
	float fHorizontalDist = VSize(VGet(this->vecKunaiTargetPosition.x - this->vecPosition.x, 0, this->vecKunaiTargetPosition.z - this->vecPosition.z));  

	/* X軸の回転角度を求める（ラジアン単位） */
	fKunaiAngleX = atan2f(fHeightDiff, fHorizontalDist);

	/* Y軸回転の計算(X-Z 平面上の方向) */
	fKunaiAngleY = atan2f(this->vecKunaiTargetPosition.x - this->vecPosition.x, this->vecKunaiTargetPosition.z - this->vecPosition.z); 
	
}

// 描画
void BulletPlayerKunaiEffect::Draw()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転(元のモデル + プレイヤーの向きの分回転させる) */
	MV1SetRotationXYZ(this->iModelHandle, VGet(DEG2RAD(90.0f) + fKunaiAngleX, DEG2RAD(180.0f) + fKunaiAngleY, 0.0f));

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);
}

// 更新
void BulletPlayerKunaiEffect::Update()
{
	/* クナイの移動ベクトルをスケールして移動 */
	this->vecPosition =  VAdd(this->vecPosition, VScale(vecKunaiMoveDirection,KUNAI_SPEED));;

	/* クナイの移動距離を加算 */
	this->fKunaiMoveDistance += KUNAI_SPEED;

	/* クナイの移動距離がターゲットまでの距離を超えたら */ 
	if (this->fKunaiMoveDistance >= this->fKunaiTargetDistance)
	{
		/* 攻撃処理を行う */
		this->Attack();
	}
}

// 攻撃処理
void BulletPlayerKunaiEffect::Attack()
{
	// 攻撃時の設定を行う
	/* クナイの攻撃フラグを確認 */
	if (this->bKunaiAttackFlg == false)
	{
		/* クナイの攻撃フラグを設定 */
		this->bKunaiAttackFlg = true;

		/* クナイの座標をターゲット座標に固定 */
		this->vecPosition = this->vecKunaiTargetPosition;

		/* モデルを非表示に設定 */
		MV1SetVisible(this->iModelHandle, false);

		/* 当たり判定設定 */
		{
			this->stCollisionSqhere.vecSqhere = this->vecPosition;
			this->stCollisionSqhere.fSqhereRadius = KUNAI_ATTACK_RADIUS;
		}
	}

	// クナイの削除処理
	/* クナイの削除カウント(攻撃時間)が残っていた場合 */
	if (iKunaiDeleteCount > 0)
	{
		/* クナイの削除カウント(攻撃時間)を減算 */
		iKunaiDeleteCount--;
	}
	/* クナイの削除カウント(攻撃時間)が0になった場合 */
	else
	{
		/* クナイの削除フラグを設定 */
		this->bDeleteFlg = true;
	}

}

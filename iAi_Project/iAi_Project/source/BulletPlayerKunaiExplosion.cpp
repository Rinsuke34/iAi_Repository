/* 2025.03.13 菊池雅道 ファイル作成 */

#include "BulletPlayerKunaiExplosion.h"

/* クナイ(爆発)クラスの定義 */

// コンストラクタ
BulletPlayerKunaiExplosion::BulletPlayerKunaiExplosion() 
{
	
}

// デストラクタ
BulletPlayerKunaiExplosion::~BulletPlayerKunaiExplosion()
{

}

// 初期化
void BulletPlayerKunaiExplosion::Initialization()
{
	/* クナイの生成地点からターゲットまでのベクトルをクナイの移動ベクトルに設定 */
	this->vecKunaiMoveDirection = VSub(this->vecKunaiTargetPosition, this->vecPosition);

	/* クナイの射線上を確認する線分コリジョンを設定 */
	COLLISION_LINE stCollisionLine;

	/* 射線の開始点を設定 */
	stCollisionLine.vecLineStart = this->StageStatusList->vecGetCameraPosition();

	/* 射線の終了点を設定 */
	stCollisionLine.vecLineEnd = this->vecKunaiTargetPosition;

	/* クナイ発射地点からターゲットの最小ベクトルを保持する */
	VECTOR vecMinDirection = VSub(this->vecKunaiTargetPosition, this->StageStatusList->vecGetCameraPosition());

	/* クナイ発射地点からターゲットの最小距離を保持する */
	float fMinDistance = VSize(vecMinDirection);

	/* プラットフォームを取得 */
	auto& PlatformList = ObjectList->GetPlatformList();

	// 射線上にプラットフォームが存在するか確認する
	for (auto* platform : PlatformList)
	{
		/* プラットフォームと接触しているか確認 */
		MV1_COLL_RESULT_POLY stHitPoly = platform->HitCheck_Line(stCollisionLine);

		/* 接触している場合 */
		if (stHitPoly.HitFlag == true)
		{
			/* クナイ発射地点から接触地点のベクトルを設定 */
			VECTOR vecDirection = VSub(stHitPoly.HitPosition, this->StageStatusList->vecGetCameraPosition());

			/* クナイ発射地点から接触地点の距離を設定 */
			float fDistance = VSize(vecDirection);

			/* クナイの射線上の最小距離を確認 */
			if (fMinDistance >= fDistance)
			{
				/* 接触した座標をターゲット座標に設定 */
				vecKunaiTargetPosition = stHitPoly.HitPosition;

				/* クナイの移動ベクトルを再設定 */
				this->vecKunaiMoveDirection = VSub(this->vecKunaiTargetPosition, this->vecPosition);

				/* クナイの射線上の最小距離を更新 */
				fMinDistance = fDistance;
			}
		}
	}

	/* クナイの移動距離を設定 */
	this->fKunaiTargetDistance = VSize(this->vecKunaiMoveDirection);

	/* クナイの移動ベクトルを正規化 */
	this->vecKunaiMoveDirection = VNorm(this->vecKunaiMoveDirection);

	/* モデルのX軸回転の計算 */
	/* 高さ(Y軸)の差 */
	float fHeightDiff = this->vecKunaiTargetPosition.y - this->vecPosition.y;
	/* X - Z 平面上の距離を計算 */
	float fHorizontalDist = VSize(VGet(this->vecKunaiTargetPosition.x - this->vecPosition.x, 0, this->vecKunaiTargetPosition.z - this->vecPosition.z));

	/* X軸の回転角度を求める（ラジアン単位） */
	fKunaiAngleX = atan2f(fHeightDiff, fHorizontalDist);

	/* モデルのY軸回転の計算(X-Z 平面上の方向) */
	fKunaiAngleY = atan2f(this->vecKunaiTargetPosition.x - this->vecPosition.x, this->vecKunaiTargetPosition.z - this->vecPosition.z);
}

// 描画
void BulletPlayerKunaiExplosion::Draw()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転(元のモデルの向き + 標的の向きの分回転させる) */
	MV1SetRotationXYZ(this->iModelHandle, VGet(fKunaiAngleX, DEG2RAD(180.0f) + fKunaiAngleY, 0.0f));

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);
}

// 更新
void BulletPlayerKunaiExplosion::Update()
{
	/* クナイの移動ベクトルをスケールして移動 */
	this->vecPosition = VAdd(this->vecPosition, VScale(this->vecKunaiMoveDirection, EXPLOSION_KUNAI_SPEED));;

	/* クナイの移動距離を加算 */
	this->fKunaiMoveDistance += EXPLOSION_KUNAI_SPEED;

	/* クナイの移動距離がターゲットまでの距離を超えたら */
	if (this->fKunaiMoveDistance >= this->fKunaiTargetDistance)
	{
		/* 攻撃処理を行う */
		this->Explosion();

	}
}

// 攻撃処理
void BulletPlayerKunaiExplosion::Explosion()
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

		/* 爆発SE再生 */
		gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_DAMAGE, this->vecPosition, SE_3D_SOUND_RADIUS);

		/* 爆発エフェクト生成 */
		{
			/* 時間経過で削除されるエフェクトを追加 */
			EffectSelfDelete* AddEffect = new EffectSelfDelete();

			/* エフェクト読み込み */
			AddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_kunai_explosion/FX_e_missile_explosion")));

			/* エフェクトの座標設定 */
			AddEffect->SetPosition(this->vecPosition);

			/* エフェクトの回転量設定 */
			AddEffect->SetRotation(this->vecRotation);

			/* エフェクトの削除されるまでの時間を設定 */
			AddEffect->SetDeleteCount(iKunaiDeleteCount);

			/* エフェクトのスケール設定 */
			AddEffect->SetScale(VGet(29.0f, 29.0f, 29.0f));

			/* エフェクトの初期化 */
			AddEffect->Initialization();

			/* エフェクトをリストに登録 */
			this->ObjectList->SetEffect(AddEffect);

		}
	}

	if (this->bKunaiAttackFlg == true)
	{
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
}
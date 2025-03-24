/* 2024.12.18 駒沢風助 ファイル作成 */

#include "BulletBase.h"

/* すべての弾丸のベースとなるクラスの定義 */

// コンストラクタ
BulletBase::BulletBase() : ActorBase()
{
	/* 初期化 */
	this->stCollisionSqhere	= {};		// コリジョン(球体)
	this->vecDirection		= {};		// 向き
	this->fMoveSpeed		= 0;		// 移動速度
	this->iTargetObjectType	= 0;		// 接触する対象となるオブジェクトのタイプ
	this->bParryFlg			= false;	// パリィフラグ(反射できるか)
	this->iBulletType		= 0;		// 弾丸の種類(反射可能であるか)
}

// 当たり判定描写
void BulletBase::CollisionDraw()
{
	/* 当たり判定を描写 */
	int Color = GetColor(255, 0, 0);
	DrawSphere3D(stCollisionSqhere.vecSqhere, stCollisionSqhere.fSqhereRadius, 16, Color, Color, FALSE);
}

/* 接触判定(簡易) */
// 球体 - カプセル
bool BulletBase::HitCheck(COLLISION_CAPSULE	stCapsule)
{
	// 引数
	// stCapsule	: 判定するカプセルコリジョン
	// 戻り値
	// bool : 接触している(true) / 接触していない(false)

	/* カプセルと接触しているか確認 */
	if(HitCheck_Sphere_Capsule(
		/* このオブジェクトのコリジョン */
		this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.fSqhereRadius,
		/* 判定するオブジェクトのコリジョン */
		stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius))
	{
		// 接触している場合
		return true;
	}
	// 接触していない場合
	return false;
}

// 球体 - 球体
bool BulletBase::HitCheck(COLLISION_SQHERE	stSqhere)
{
	// 引数
	// stCapsule	: 判定する球体コリジョン
	// 戻り値
	// bool			: 接触している(true) / 接触していない(false)

	/* 球体と接触しているか確認 */
	if (HitCheck_Sphere_Sphere(
		/* 判定するオブジェクトのコリジョン */
		stSqhere.vecSqhere, stSqhere.fSqhereRadius,
		/* このオブジェクトのコリジョン */
		this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.fSqhereRadius))
	{
		// 接触している場合
		return true;
	}
	// 接触していない場合
	return false;
}

// 球体 - モデル
bool BulletBase::HitCheck(int iModelHandle, int iFrameIndex)
{
	// 引数
	// iModelHandle	: 判定するモデルのハンドル
	// iFrameIndex	: 判定するモデルのフレーム番号
	// 戻り値
	// bool			: 接触している(true) / 接触していない(false)

	// ポリゴンとの接触情報
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* 対象のモデルと接触しているか確認 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* 判定するオブジェクトのコリジョン */
		iModelHandle, iFrameIndex,
		/* 弾のコリジョン */
		this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.fSqhereRadius);

	/* 接触数を取得 */
	if (stHitPolyDim.HitNum > 0)
	{
		// 接触している場合
		return true;
	}
	// 接触していない場合
	return false;
}
/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "CharacterBase.h"

/* すべてのキャラクターのベースとなるクラスの定義 */

// コンストラクタ
CharacterBase::CharacterBase() : ActorBase()
{
	/* 初期化 */
	this->stCollisionCapsule	= {};	// コリジョン(カプセル)
	this->vecDirection			= {};	// 向き
	this->iInvincibilityTime	= {};	// 無敵時間
}

/* 接触判定(簡易) */
// カプセル - カプセル
bool CharacterBase::HitCheck(COLLISION_CAPSULE	stCapsule)
{
	// 引数
	// stCapsule	: 判定するカプセルコリジョン
	// 戻り値
	// bool : 接触している(true) / 接触していない(false)

	/* カプセル同士が接触しているか確認 */
	if (HitCheck_Capsule_Capsule
		/* 判定するオブジェクトのコリジョン */
		(stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius,
		/* このオブジェクトのコリジョン */
		this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius))
	{
		// 接触している場合
		return true;
	}
	// 接触していない場合
	return false;
}

// カプセル - 球体
bool CharacterBase::HitCheck(COLLISION_SQHERE	stSqhere)
{
	// 引数
	// stCapsule	: 判定する球体コリジョン
	// 戻り値
	// bool			: 接触している(true) / 接触していない(false)

	/* カプセルと球体が接触しているか確認 */
	if(HitCheck_Sphere_Capsule(
		/* 判定するオブジェクトのコリジョン */
		stSqhere.vecSqhere, stSqhere.fSqhereRadius,
		/* このオブジェクトのコリジョン */
		this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius))
	{
		// 接触している場合
		return true;
	}
	// 接触していない場合
	return false;
}

// カプセル - モデル
bool CharacterBase::HitCheck(int iModelHandle, int iFrameIndex)
{
	// 引数
	// iModelHandle	: 判定するモデルのハンドル
	// iFrameIndex	: 判定するモデルのフレーム番号
	// 戻り値
	// bool			: 接触している(true) / 接触していない(false)

	// ポリゴンとの接触情報
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* プレイヤーと対象のモデルが接触しているかの情報取得 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* 判定するオブジェクトのコリジョン */
		iModelHandle, iFrameIndex,
		/* このオブジェクトのコリジョン */
		this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius);

	/* 接触数を取得 */
	if (stHitPolyDim.HitNum > 0)
	{
		// 接触している場合
		return true;
	}
	// 接触していない場合
	return false;
}

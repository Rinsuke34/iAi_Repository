/* 2024.12.15 駒沢風助 ファイル作成 */

#include "CollisionBase.h"

/* すべてのプラットフォームのベースとなるクラスの定義 */

// コンストラクタ
CollisionBase::CollisionBase() : PlatformBase()
{
	/* 初期化 */
	this->iCollisionFrameNo = -1;	// コリジョンフレーム番号
}

// 初期化
void CollisionBase::Initialization()
{
	PlatformBase::Initialization();

	/* コリジョンフレーム設定 */
	UpdateCollisionFrame();
}

// 当たり判定描写
void CollisionBase::CollisionDraw()
{
	/* コリジョンの設定されたフレームを描写するよう設定 */
	MV1SetFrameVisible(this->iModelHandle, this->iCollisionFrameNo, TRUE);

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);
}

/* 接触判定(簡易) */
// モデル - カプセル
bool CollisionBase::HitCheck(COLLISION_CAPSULE	stCapsule)
{
	// 引数
	// stCapsule	: 判定するカプセルコリジョン
	// 戻り値
	// bool : 接触している(true) / 接触していない(false)

	/* コリジョンフレームが存在しないか確認 */
	if (this->iCollisionFrameNo < 0)
	{
		// 存在しない場合
		/* 非接触として判定する */
		return false;
	}

	// ポリゴンとの接触情報
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* プラットフォームのモデルと対象のカプセルコリジョンが接触しているかの情報取得 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* このオブジェクトのコリジョン */
		this->iModelHandle, this->iCollisionFrameNo,
		/* 判定するオブジェクトのコリジョン */
		stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius);

	/* 接触数を取得 */
	if (stHitPolyDim.HitNum > 0)
	{
		// 接触している場合
		return true;
	}
	//接触していない場合
	return false;
}

// モデル - 球体
bool CollisionBase::HitCheck(COLLISION_SQHERE	stSqhere)
{
	// 引数
	// stCapsule	: 判定する球体コリジョン
	// 戻り値
	// bool			: 接触している(true) / 接触していない(false)

	/* コリジョンフレームが存在しないか確認 */
	if (this->iCollisionFrameNo < 0)
	{
		// 存在しない場合
		/* 非接触として判定する */
		return false;
	}

	// ポリゴンとの接触情報
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* プラットフォームのモデルと対象の球体コリジョンが接触しているかの情報取得 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* このオブジェクトのコリジョン */
		this->iModelHandle, this->iCollisionFrameNo,
		/* 判定するオブジェクトのコリジョン */
		stSqhere.vecSqhere, stSqhere.vecSqhere, stSqhere.fSqhereRadius);

	/* 接触数を取得 */
	if (stHitPolyDim.HitNum > 0)
	{
		// 接触している場合
		return true;
	}
	// 接触していない場合
	return false;
}

// モデル - 線分
bool CollisionBase::HitCheck(COLLISION_LINE		stLine)
{
	// 引数
	// stLine	: 判定する線分コリジョン
	// 戻り値
	// bool		: 接触している(true) / 接触していない(false)

	/* コリジョンフレームが存在しないか確認 */
	if (this->iCollisionFrameNo < 0)
	{
		// 存在しない場合
		/* 非接触として判定する */
		return false;
	}

	// ポリゴンとの接触情報
	MV1_COLL_RESULT_POLY stHitPolyDim;

	/* プラットフォームのモデルと対象の線分コリジョンが接触しているかの情報取得 */
	stHitPolyDim = MV1CollCheck_Line(
		/* このオブジェクトのコリジョン */
		this->iModelHandle, this->iCollisionFrameNo,
		/* 判定するオブジェクトのコリジョン */
		stLine.vecLineStart, stLine.vecLineEnd);

	/* 接触したか確認 */
	if (stHitPolyDim.HitFlag == 1)
	{
		// 接触している場合
		return true;
	}

	// 接触していない場合
	return false;
}

/* 接触判定(詳細) */
// モデル - 線分
MV1_COLL_RESULT_POLY CollisionBase::HitCheck_Line(COLLISION_LINE	stLine)
{
	// 引数
	// stLine				: 判定する線分コリジョン
	// 戻り値
	// MV1_COLL_RESULT_POLY	: 接触情報

	// ポリゴンとの接触情報
	MV1_COLL_RESULT_POLY stHitPolyDim;

	/* コリジョンフレームが存在しないか確認 */
	if (this->iCollisionFrameNo < 0)
	{
		// 存在しない場合
		/* 非接触として判定する */
		stHitPolyDim.HitFlag = FALSE;
		return stHitPolyDim;
	}

	/* プラットフォームのモデルと対象の線分コリジョンが接触しているかの情報取得 */
	stHitPolyDim = MV1CollCheck_Line(
		/* このオブジェクトのコリジョン */
		this->iModelHandle, this->iCollisionFrameNo,
		/* 判定するオブジェクトのコリジョン */
		stLine.vecLineStart, stLine.vecLineEnd);

	return stHitPolyDim;
}

// コリジョンの設定されたフレームの設定
void CollisionBase::UpdateCollisionFrame()
{
	/* コリジョンフレーム番号取得 */
	this->iCollisionFrameNo = MV1SearchFrame(this->iModelHandle, "Collision");

	/* コリジョンフレームの取得が成功したか確認 */
	if (this->iCollisionFrameNo >= 0)
	{
		// 成功した(設定されていた)場合
		/* コリジョンの設定されたフレームのコリジョン情報構築 */
		MV1SetupCollInfo(this->iModelHandle, this->iCollisionFrameNo, 1, 1, 1);

		/* コリジョンの設定されたフレームを描写しないように設定 */
		MV1SetFrameVisible(this->iModelHandle, this->iCollisionFrameNo, FALSE);
	}
}
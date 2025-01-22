/* 2024.12.15 駒沢風助 ファイル作成 */

#include "PlatformBase.h"

/* すべてのプラットフォームのベースとなるクラスの定義 */

// コンストラクタ
PlatformBase::PlatformBase() : ObjectBase()
{
	/* 初期化 */
	this->iModelHandle		= -1;	// モデルハンドル
	this->iCollisionFrameNo	= -2;	// コリジョンの設定されたモデルのフレーム番号	
	this->iLightFrameNo		= -2;	// 発光部分の設定されたモデルのフレーム番号
}

// デストラクタ
PlatformBase::~PlatformBase()
{
	/* モデルハンドル削除 */
	MV1DeleteModel(this->iModelHandle);
}

// 初期化
void PlatformBase::Initialization()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転 */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotate);

	/* モデル拡大 */
	MV1SetScale(this->iModelHandle, this->vecScale);

	/* コリジョンフレーム番号取得 */
	this->SetCollisionFrameNo(MV1SearchFrame(this->iModelHandle, "Collision"));

	/* 発光フレーム番号取得 */
	this->SetLightFrameNo(MV1SearchFrame(this->iModelHandle, "Light"));

	/* コリジョン情報構築 */
	MV1SetupCollInfo(this->iModelHandle, this->iGetCollisionFrameNo(), 4, 4, 4);

	/* コリジョンフレームを非表示に設定 */
	MV1SetFrameVisible(this->iModelHandle, this->iGetCollisionFrameNo(), FALSE);
}

/* 接触判定(簡易) */
// モデル - カプセル
bool PlatformBase::HitCheck(COLLISION_CAPSULE	stCapsule)
{
	// 引数
	// stCapsule	: 判定するカプセルコリジョン
	// 戻り値
	// bool : 接触している(true) / 接触していない(false)

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
	// 接触していない場合
	return false;
}

// モデル - 球体
bool PlatformBase::HitCheck(COLLISION_SQHERE	stSqhere)
{
	// 引数
	// stCapsule	: 判定する球体コリジョン
	// 戻り値
	// bool			: 接触している(true) / 接触していない(false)

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
bool PlatformBase::HitCheck(COLLISION_LINE		stLine)
{
	// 引数
	// stLine	: 判定する線分コリジョン
	// 戻り値
	// bool		: 接触している(true) / 接触していない(false)

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
MV1_COLL_RESULT_POLY PlatformBase::HitCheck_Line(COLLISION_LINE	stLine)
{
	// 引数
	// stLine				: 判定する線分コリジョン
	// 戻り値
	// MV1_COLL_RESULT_POLY	: 接触情報

	// ポリゴンとの接触情報
	MV1_COLL_RESULT_POLY stHitPolyDim;

	/* プラットフォームのモデルと対象の線分コリジョンが接触しているかの情報取得 */
	stHitPolyDim = MV1CollCheck_Line(
		/* このオブジェクトのコリジョン */
		this->iModelHandle, this->iCollisionFrameNo,
		/* 判定するオブジェクトのコリジョン */
		stLine.vecLineStart, stLine.vecLineEnd);

	return stHitPolyDim;
}

// 描写
void PlatformBase::Draw()
{
	/* 現在のモデルの透明度取得 */
	float OpacityRate = MV1GetOpacityRate(this->iModelHandle);

	/* 透明度確認 */
	if (OpacityRate > 0.f)
	{
		// 完全に透明でない場合
		/* モデル描写 */
		MV1DrawModel(this->iModelHandle);
	}
}

// 発光描写
void PlatformBase::BloomDraw()
{
	/* フレーム数を取得 */
	int iBackUpFrames = MV1GetFrameNum(this->iModelHandle);

	/* 元の色を保存 */
	std::vector<COLOR_F> vecOriginalDifColor(iBackUpFrames);
	std::vector<COLOR_F> vecOriginalSpcColor(iBackUpFrames);
	std::vector<COLOR_F> vecOriginalEmiColor(iBackUpFrames);
	std::vector<COLOR_F> vecOriginalAmbColor(iBackUpFrames);

	for (int i = 0; i < iBackUpFrames; i++)
	{
		vecOriginalDifColor[i] = MV1GetFrameDifColorScale(this->iModelHandle, i);
		vecOriginalSpcColor[i] = MV1GetFrameSpcColorScale(this->iModelHandle, i);
		vecOriginalEmiColor[i] = MV1GetFrameEmiColorScale(this->iModelHandle, i);
		vecOriginalAmbColor[i] = MV1GetFrameAmbColorScale(this->iModelHandle, i);
	}

	/* ターゲット以外の色を黒に設定 */
	for (int i = 0; i < iBackUpFrames; i++)
	{
		if (i != this->iLightFrameNo)
		{
			MV1SetFrameDifColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
			MV1SetFrameSpcColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
			MV1SetFrameEmiColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
			MV1SetFrameAmbColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
		}
	}

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);

	/* 元の色に戻す */
	for (int i = 0; i < iBackUpFrames; i++)
	{
		MV1SetFrameDifColorScale(this->iModelHandle, i, vecOriginalDifColor[i]);
		MV1SetFrameSpcColorScale(this->iModelHandle, i, vecOriginalSpcColor[i]);
		MV1SetFrameEmiColorScale(this->iModelHandle, i, vecOriginalEmiColor[i]);
		MV1SetFrameAmbColorScale(this->iModelHandle, i, vecOriginalAmbColor[i]);
	}
}

/* 2024.12.15 駒沢風助 ファイル作成 */

#include "PlatformBase.h"

/* すべてのプラットフォームのベースとなるクラスの定義 */

// コンストラクタ
PlatformBase::PlatformBase() : ObjectBase()
{
	/* 初期化 */
	this->iModelHandle		= 0;					// モデルハンドル
	this->vecRotation		= VGet(0.f, 0.f, 0.f);	// 回転量
	this->iCollisionFrameNo = -1;					// コリジョンフレーム番号
	this->vecPlatformMove	= VGet(0.f, 0.f, 0.f);	// プラットフォームの移動量
	this->bRidePlayerFlg	= false;				// プレイヤーが乗っているかのフラグ
}

// デストラクタ
PlatformBase::~PlatformBase()
{
	/* コリジョン情報後始末 */
	MV1TerminateCollInfo(this->iModelHandle, this->iCollisionFrameNo);

	/* モデルハンドル削除 */
	MV1DeleteModel(this->iModelHandle);
}

// 初期化
void PlatformBase::Initialization()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転 */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotation);

	/* モデル拡大 */
	MV1SetScale(this->iModelHandle, this->vecScale);

	/* コリジョンフレーム設定 */
	UpdateCollisionFrame();

	/* 発光フレーム番号取得 */
	UpdataLightFrame();
}

// 描写
void PlatformBase::Draw()
{
	/* コリジョンフレームを描写しない状態に設定 */
	DrawFrameCollisionSet(false);

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
		/* フレームの色を取得 */
		vecOriginalDifColor[i] = MV1GetFrameDifColorScale(this->iModelHandle, i);
		vecOriginalSpcColor[i] = MV1GetFrameSpcColorScale(this->iModelHandle, i);
		vecOriginalEmiColor[i] = MV1GetFrameEmiColorScale(this->iModelHandle, i);
		vecOriginalAmbColor[i] = MV1GetFrameAmbColorScale(this->iModelHandle, i);
	}

	/* ターゲット以外の色を黒に設定 */
	for (int i = 0; i < iBackUpFrames; i++)
	{
		/* 発光フレームではないか確認 */
		if (std::find(aiLightFrameNo.begin(), aiLightFrameNo.end(), i) != aiLightFrameNo.end() == false)
		{
			// 発光フレームではない場合
			/* フレームの色を黒色に設定 */
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
		/* フレームの色を元の色に設定 */
		MV1SetFrameDifColorScale(this->iModelHandle, i, vecOriginalDifColor[i]);
		MV1SetFrameSpcColorScale(this->iModelHandle, i, vecOriginalSpcColor[i]);
		MV1SetFrameEmiColorScale(this->iModelHandle, i, vecOriginalEmiColor[i]);
		MV1SetFrameAmbColorScale(this->iModelHandle, i, vecOriginalAmbColor[i]);
	}
}

// 当たり判定描写
void PlatformBase::CollisionDraw()
{
	/* コリジョンフレームを描写する状態に設定 */
	DrawFrameCollisionSet(true);

	/* コリジョンの設定されたフレームを描写するよう設定 */
	MV1SetFrameVisible(this->iModelHandle, this->iCollisionFrameNo, TRUE);

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);
}

/* 接触判定(簡易) */
// モデル - カプセル
bool PlatformBase::HitCheck(COLLISION_CAPSULE	stCapsule)
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

	/* オブジェクトの大まかなコリジョンと接触していないか確認 */
	// 軽量化のため、ポリゴンとの接触確認の前に大まかな円と接触しているかを確認する
	if (HitCheck_Sphere_Capsule(
		/* このオブジェクトのコリジョン(大まかな円) */
		this->vecCenterPosition, this->fRoughRadius,
		/* 判定するオブジェクトのコリジョン */
		stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius) == FALSE)
	{
		// 接触していない場合
		return false;
	}

	/* ポリゴンとの接触情報 */
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
bool PlatformBase::HitCheck(COLLISION_SQHERE	stSqhere)
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

	/* オブジェクトの大まかなコリジョンと接触していないか確認 */
	// 軽量化のため、ポリゴンとの接触確認の前に大まかな円と接触しているかを確認する
	if (HitCheck_Sphere_Sphere(
		/* このオブジェクトのコリジョン(大まかな円) */
		this->vecCenterPosition, this->fRoughRadius,
		/* 判定するオブジェクトのコリジョン */
		stSqhere.vecSqhere, stSqhere.fSqhereRadius) == FALSE)
	{
		// 接触していない場合
		return false;
	}

	/* ポリゴンとの接触情報 */
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

	/* コリジョンフレームが存在しないか確認 */
	if (this->iCollisionFrameNo < 0)
	{
		// 存在しない場合
		/* 非接触として判定する */
		return false;
	}

	/* オブジェクトの大まかなコリジョンと接触していないか確認 */
	// 軽量化のため、ポリゴンとの接触確認の前に大まかな円と接触しているかを確認する
	if (HitCheck_Line_Sphere(
		/* 判定するオブジェクトのコリジョン */
		stLine.vecLineStart, stLine.vecLineEnd,
		/* このオブジェクトのコリジョン(大まかな円) */
		this->vecCenterPosition, this->fRoughRadius) == FALSE)
	{
		// 接触していない場合
		return false;
	}

	/* ポリゴンとの接触情報 */
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

	/* ポリゴンとの接触情報 */
	MV1_COLL_RESULT_POLY stHitPolyDim;

	/* オブジェクトの大まかなコリジョンと接触していないか確認 */
	// 軽量化のため、ポリゴンとの接触確認の前に大まかな円と接触しているかを確認する
	if (HitCheck_Line_Sphere(
		/* 判定するオブジェクトのコリジョン */
		stLine.vecLineStart, stLine.vecLineEnd,
		/* このオブジェクトのコリジョン(大まかな円) */
		this->vecCenterPosition, this->fRoughRadius) == FALSE)
	{
		// 接触していない場合
		/* 非接触として判定する */
		stHitPolyDim.HitFlag = FALSE;
		return stHitPolyDim;
	}

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

// モデル - カプセル
MV1_COLL_RESULT_POLY_DIM PlatformBase::HitCheck_Capsule(COLLISION_CAPSULE	stCapsule)
{
	// 引数
	// stCapsule				: 判定するカプセルコリジョン
	// 戻り値
	// MV1_COLL_RESULT_POLY_DIM	: 接触情報

	/* ポリゴンとの接触情報 */
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* オブジェクトの大まかなコリジョンと接触していないか確認 */
	// 軽量化のため、ポリゴンとの接触確認の前に大まかな円と接触しているかを確認する
	if (HitCheck_Sphere_Capsule(
		/* このオブジェクトのコリジョン(大まかな円) */
		this->vecCenterPosition, this->fRoughRadius,
		/* 判定するオブジェクトのコリジョン */
		stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius) == FALSE)
	{
		// 接触していない場合
		/* 非接触として判定する */
		stHitPolyDim.HitNum = FALSE;
		return stHitPolyDim;
	}

	/* コリジョンフレームが存在しないか確認 */
	if (this->iCollisionFrameNo < 0)
	{
		// 存在しない場合
		/* 非接触として判定する */
		stHitPolyDim.HitNum = FALSE;
		return stHitPolyDim;
	}

	/* プラットフォームのモデルと対象のカプセルコリジョンが接触しているかの情報取得 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* このオブジェクトのコリジョン */
		this->iModelHandle, this->iCollisionFrameNo,
		/* 判定するオブジェクトのコリジョン */
		stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius);

	return stHitPolyDim;
}

// コリジョンの設定されたフレームの設定
void PlatformBase::UpdateCollisionFrame()
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

		/* コリジョンフレームに含まれるメッシュ番号を取得 */
		int iMeshNo = MV1GetFrameMesh(this->iModelHandle, this->iCollisionFrameNo, 0);

		/* フレームのワールド変換行列を取得 */
		MATRIX frameMatrix = MV1GetFrameLocalWorldMatrix(this->iModelHandle, this->iCollisionFrameNo);

		/*取得したメッシュの最大座標と最小座標を取得 */
		VECTOR vecMinPos = MV1GetMeshMinPosition(this->iModelHandle, iMeshNo);
		VECTOR vecMaxPos = MV1GetMeshMaxPosition(this->iModelHandle, iMeshNo);

		/* メッシュの最大座標と最小座標をワールド座標に変換 */
		vecMinPos = VTransform(vecMinPos, frameMatrix);
		vecMaxPos = VTransform(vecMaxPos, frameMatrix);

		/* メッシュの中心座標(コリジョンフレームの中心座標)を取得 */
		this->vecCenterPosition	= VScale(VAdd(vecMinPos, vecMaxPos), 0.5f);

		/* 中心座標からコリジョンを包み込む大まかな半径を取得 */
		this->fRoughRadius		= VSize(VSub(vecMaxPos, vecMinPos)) * 0.5f;
	}
}

// 発光の設定されたフレームを取得
void PlatformBase::UpdataLightFrame()
{
	/* モデルハンドルからフレーム数を取得 */
	int iFrameNum = MV1GetFrameNum(this->iModelHandle);

	/* 発光するフレーム番号を取得する */
	for (int i = 0; i < iFrameNum; i++)
	{
		/* フレーム名取得 */
		const char* cFrameName = MV1GetFrameName(this->iModelHandle, i);

		/* 最初の5文字が"Light"であるか確認 */
		if (strncmp(cFrameName, "Light", 5) == 0)
		{
			/* 発光フレーム番号を取得 */
			this->aiLightFrameNo.push_back(i);

			/* 発光フレームの親フレーム番号を取得 */
			int parentFrame = MV1GetFrameParent(this->iModelHandle, i);

			/* 発光フレームの親フレームが存在するならば */
			while (parentFrame >= 0)
			{
				// 親フレームが存在する場合
				/* 親フレーム番号を追加 */
				this->aiLightFrameNo.push_back(parentFrame);

				/* 親フレーム番号の親フレームを取得 */
				parentFrame = MV1GetFrameParent(this->iModelHandle, parentFrame);
			}
		}
	}

	/* 発光フレーム番号を昇順にソート */
	std::sort(this->aiLightFrameNo.begin(), this->aiLightFrameNo.end());

	/* 重複している番号を削除 */
	this->aiLightFrameNo.erase(std::unique(this->aiLightFrameNo.begin(), this->aiLightFrameNo.end()), this->aiLightFrameNo.end());
}

// コリジョンフレームを描写する状態にする
void PlatformBase::DrawFrameCollisionSet(bool bCollisionDraw)
{
	// 引数
	// bCollisionDraw	: コリジョンフレームを描写する(true) / 描写しない(false)
	// ※コリジョンフレームを描写しない場合、コリジョン以外のフレームの描写を有効にします

	/* フレーム数を取得 */
	int iFrameNo = MV1GetFrameNum(this->iModelHandle);

	/* すべてのフレームを非表示に設定 */
	for (int i = 0; i < iFrameNo; i++)
	{
		/* コリジョンフレーム番号であるか */
		if (i == this->iCollisionFrameNo)
		{
			// コリジョンフレーム番号である場合
			/* コリジョンフレームを描写する設定であるか確認 */
			if (bCollisionDraw == true)
			{
				// 描写する設定である場合
				/* フレームを表示に設定 */
				MV1SetFrameVisible(this->iModelHandle, i, TRUE);
			}
			else
			{
				// 描写しない設定である場合
				/* フレームを非表示に設定 */
				MV1SetFrameVisible(this->iModelHandle, i, FALSE);
			}
		}
		else
		{
			// コリジョンフレーム番号でない場合
			/* コリジョンフレームを描写する設定であるか確認 */
			if (bCollisionDraw == true)
			{
				// 描写する設定である場合
				/* フレームを非表示に設定 */
				MV1SetFrameVisible(this->iModelHandle, i, FALSE);
			}
			else
			{
				// 描写しない設定である場合
				/* フレームを表示に設定 */
				MV1SetFrameVisible(this->iModelHandle, i, TRUE);
			}
		}
	}


}

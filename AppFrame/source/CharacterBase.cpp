/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "CharacterBase.h"

/* すべてのキャラクターのベースとなるクラスの定義 */

// コンストラクタ
CharacterBase::CharacterBase() : ActorBase()
{
	/* 初期化 */
	this->stCollisionCapsule	= {};		// コリジョン(カプセル)
	this->iInvincibilityTime	= {};		// 無敵時間
}

// 初期化
void CharacterBase::Initialization()
{
	/* 発光するフレームを取得 */
	UpdataLightFrame();
}

// 発光描写
void CharacterBase::BloomDraw()
{
	/* 元の色を保存 */
	int iBackUpFrames = MV1GetFrameNum(this->iModelHandle);
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

	// 発光停止フラグが無効である場合
	/* ライトフレームNoに設定された番号以外を黒色でに設定 */
	for (int i = 0; i < iBackUpFrames; i++)
	{
		/* 発光フレームであるか確認 */
		if (std::find(aiLightFrameNo.begin(), aiLightFrameNo.end(), i) != aiLightFrameNo.end())
		{
			// 発光フレームである場合
			/* 発光停止フラグが有効であるか確認 */
			if (this->bBloomStopFlg == true)
			{
				// 発光停止フラグが有効である場合
				/* 対象フレームを黒色で描写 */
				MV1SetFrameDifColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
				MV1SetFrameSpcColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
				MV1SetFrameEmiColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
				MV1SetFrameAmbColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
			}

			/* 特殊発光色使用フラグを確認 */
			if (this->bSpBloomCollorFlg == true)
			{
				// 特殊発光色使用フラグが有効である場合
				/* 対象フレームを特殊発光色で描写 */
				MV1SetFrameDifColorScale(this->iModelHandle, i, stSpBloomColor);
				MV1SetFrameSpcColorScale(this->iModelHandle, i, stSpBloomColor);
				MV1SetFrameEmiColorScale(this->iModelHandle, i, stSpBloomColor);
				MV1SetFrameAmbColorScale(this->iModelHandle, i, stSpBloomColor);
			}
		}
		else
		{
			// 発光フレームでない場合
			/* 対象フレームを黒色で描写 */
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

// 当たり判定描写
void CharacterBase::CollisionDraw()
{
	/* 当たり判定を描写 */
	int iColor	= GetColor(255, 0, 0);
	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius, 16, iColor, iColor, FALSE);
}

// 描写
void CharacterBase::Draw()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転 */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotation);

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);
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

	/* ポリゴンとの接触情報 */
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

// 発光の設定されたフレームを取得
void CharacterBase::UpdataLightFrame()
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

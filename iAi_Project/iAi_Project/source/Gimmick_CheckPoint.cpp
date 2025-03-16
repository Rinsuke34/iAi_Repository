/* 2025.03.16 駒沢風助 ファイル作成 */

#include "Gimmick_CheckPoint.h"

/* 中間ポイントクラスの定義 */
// コンストラクタ
Gimmick_CheckPoint::Gimmick_CheckPoint() : PlatformBase()
{
	/* データリストを取得 */
	{
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Gimmick/CheckPoint/CheckPoint");
	}

	/* 初期化 */
	this->bActiveFlg		= false;
	this->bStartPositionFlg = false;
}

// 初期化
void Gimmick_CheckPoint::Initialization()
{
	PlatformBase::Initialization();

	/* コリジョンをセット */
	this->stCollisionSqhere.vecSqhere		= this->vecPosition;
	this->stCollisionSqhere.fSqhereRadius	= 200.0f;

	/* スタート地点であるか確認 */
	if (this->bStartPositionFlg == true)
	{
		// スタート地点である場合
		/* アクティブ状態に設定する */
		this->bActiveFlg = true;
	}
	else
	{
		// スタート地点でない場合
		/* 非アクティブ状態に設定する */
		this->bActiveFlg = false;
	}
}

// 更新
void Gimmick_CheckPoint::Update()
{
	/* アクティブ状態でないか確認 */
	if (this->bActiveFlg == false)
	{
		// アクティブ状態でない場合
		/* プレイヤーを取得 */
		CharacterBase* pPlayer = this->ObjectList->GetCharacterPlayer();

		/* プレイヤーとの接触判定 */
		if (pPlayer->HitCheck(this->stCollisionSqhere) == true)
		{
			// 接触している場合
			/* アクティブ状態に設定する */
			this->bActiveFlg = true;
		}
	}
}

// リセット処理
void Gimmick_CheckPoint::Reset()
{
	/* このオブジェクトの初期化処理を実行する */
	Initialization();
}

// 発光描写
void Gimmick_CheckPoint::BloomDraw()
{
	/* アクティブ状態であるか確認 */
	if (this->bActiveFlg == true)
	{
		// アクティブ状態である場合
		/* 発光描写 */
		// ※青色で描写
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
				else
				{
					// 発光フレームである場合
					/* フレームの色を青色に設定 */
					MV1SetFrameDifColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 1.f, 1.f));
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
	}
	else
	{
		// アクティブ状態でない場合
		/* 発光描写 */
		// ※デフォルトの色(赤)で描写
		PlatformBase::BloomDraw();
	}
}

// 当たり判定描写
void Gimmick_CheckPoint::CollisionDraw()
{
	/* 当たり判定を描写 */
	int iColor = GetColor(255, 0, 0);
	DrawSphere3D(this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.fSqhereRadius, 16, iColor, iColor, FALSE);
}

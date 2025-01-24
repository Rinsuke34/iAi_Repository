/* 2025.01.22 駒沢風助 ファイル作成 */

#include "BackGroundBase.h"

/* すべてのプラットフォームのベースとなるクラスの定義 */

// コンストラクタ
BackGroundBase::BackGroundBase() : PlatformBase()
{

}

// 初期化
void BackGroundBase::Initialization()
{
	PlatformBase::Initialization();

	/* 発光フレーム番号取得 */
	UpdataLightFrame();
}

// 描写
void BackGroundBase::Draw()
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
void BackGroundBase::BloomDraw()
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

// 発光の設定されたフレームを取得
void BackGroundBase::UpdataLightFrame()
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

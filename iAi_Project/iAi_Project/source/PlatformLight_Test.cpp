/* 2024.01.13 駒沢風助 ファイル作成 */

#include "PlatformLight_Test.h"

/* 発光するプラットフォームクラス(テスト)の定義 */

// コンストラクタ
PlatformLight_Test::PlatformLight_Test() : PlatformBase()
{

}

// デストラクタ
PlatformLight_Test::~PlatformLight_Test()
{

}

// 初期化
void PlatformLight_Test::Initialization()
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
	this->SetLightHandle(MV1SearchFrame(this->iModelHandle, "Light"));

	/* コリジョン情報構築 */
	MV1SetupCollInfo(this->iModelHandle, this->iGetCollisionFrameNo(), 4, 4, 4);

	/* コリジョンフレームを非表示に設定 */
	MV1SetFrameVisible(this->iModelHandle, this->iGetCollisionFrameNo(), FALSE);
}

// 描写
void PlatformLight_Test::Draw()
{
	/* 現在のモデルの透明度取得 */
	float OpacityRate = MV1GetOpacityRate(this->iModelHandle);

	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_UP] == TRUE)
	{		
		/* 透明度を上げる */
		OpacityRate += 0.01f;
		MV1SetOpacityRate(this->iModelHandle, OpacityRate);
	}
	else if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_DOWN] == TRUE)
	{
		/* 透明度を下げる */
		OpacityRate -= 0.01f;
		MV1SetOpacityRate(this->iModelHandle, OpacityRate);
	}

	/* 透明度確認 */
	if (OpacityRate > 0.f)
	{
		// 完全に透明でない場合
		/* モデル描写 */
		MV1DrawModel(this->iModelHandle);
	}
}

// 発光描写
void PlatformLight_Test::BloomDraw()
{
	/* 元の色を保存 */
	int iBackUpFrames = MV1GetFrameNum(this->iModelHandle);
	std::vector<COLOR_F> vecOriginalColor(iBackUpFrames);

	for (int i = 0; i < iBackUpFrames; i++)
	{
		vecOriginalColor[i] = MV1GetFrameDifColorScale(this->iModelHandle, i);
	}

	/* ターゲット以外の色を黒に設定 */
	for (int i = 0; i < iBackUpFrames; i++)
	{
		if (i != this->iLightFrameNo)
		{
			MV1SetFrameDifColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 0.f));
		}
	}

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);

	/* 元の色に戻す */
	for (int i = 0; i < iBackUpFrames; i++)
	{
		MV1SetFrameDifColorScale(this->iModelHandle, i, vecOriginalColor[i]);
	}
}

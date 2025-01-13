/* 2024.01.07 駒沢風助 ファイル作成 */

#include "PlatformBasic.h"

/* 基本プラットフォームクラスの宣言 */

// コンストラクタ
PlatformBasic::PlatformBasic() : PlatformBase()
{

}

// デストラクタ
PlatformBasic::~PlatformBasic()
{

}

// 初期化
void PlatformBasic::Initialization()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転 */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotate);

	/* モデル拡大 */
	MV1SetScale(this->iModelHandle, this->vecScale);

	/* コリジョンフレーム番号取得 */
	//this->SetCollisionFrameNo(MV1SearchFrame(this->iModelHandle, "Collision"));
	this->SetCollisionFrameNo(-1);

	/* 発光フレーム番号取得 */
	this->SetLightHandle(MV1SearchFrame(this->iModelHandle, "Light"));

	/* コリジョン情報構築 */
	MV1SetupCollInfo(this->iModelHandle, this->iGetCollisionFrameNo(), 4, 4, 4);

	/* コリジョンフレームを非表示に設定 */
	MV1SetFrameVisible(this->iModelHandle, this->iGetCollisionFrameNo(), FALSE);
}

// 描写
void PlatformBasic::Draw()
{
	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);
}

// 発光描写
void PlatformBasic::BloomDraw()
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

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

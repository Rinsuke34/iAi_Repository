/* 2025.03.03 駒沢風助 ファイル作成 */

#include "FallFog.h"

/* 霧(落下位置)クラスの定義 */
// コンストラクタ
FallFog::FallFog() : PlatformBase()
{
	/* 画像リソース取得 */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 霧 */
		this->piGrHandle_Fog = ImageList->piGetImage("Fog/Fog");
	}
}

// 初期化
void FallFog::Initialization()
{
	/* 座標の位置をランダムで下げる */
	this->vecPosition.y = this->vecPosition.y - GetRand(500) - 100;
}

// 描写
void FallFog::Draw()
{
	/* 霧の画像をビルボードとして描写する */
	DrawBillboard3D(this->vecPosition, 0.5f, 0.5f, 6500.0f, 0.f, *this->piGrHandle_Fog, TRUE);
}

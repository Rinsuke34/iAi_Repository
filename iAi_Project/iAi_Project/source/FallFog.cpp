/* 2025.03.03 駒沢風助 ファイル作成 */

#include "FallFog.h"

/* 霧(落下位置)クラスの定義 */
// コンストラクタ
FallFog::FallFog() : PlatformBasic()
{
	/* 画像リソース取得 */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 霧 */
		this->piGrHandle_Fog = ImageList->piGetImage("Fog/Fog");
	}
}

// 描写
void FallFog::Draw()
{
	/* 霧の画像をビルボードとして描写する */
	DrawBillboard3D(this->vecPosition, 0.5f, 0.5f, 650.0f, 0.f, *this->piGrHandle_Fog, TRUE);
}

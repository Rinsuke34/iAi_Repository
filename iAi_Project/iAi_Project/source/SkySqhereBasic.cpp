/* 2025.02.06 駒沢風助 ファイル作成 */

#include "SkySqhereBasic.h"

/* 基本スカイスフィアクラスの定義 */
// コンストラクタ
SkySqhereBasic::SkySqhereBasic() : SkySqhereBase()
{
	/* データリスト取得 */
	{
		/* "ステージ状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}
}

// デストラクタ
SkySqhereBasic::~SkySqhereBasic()
{

}

// 更新
void SkySqhereBasic::Update()
{
	/* カメラの注視点に移動させる */
	this->vecPosition = this->StageStatusList->vecGetCameraTarget();
}

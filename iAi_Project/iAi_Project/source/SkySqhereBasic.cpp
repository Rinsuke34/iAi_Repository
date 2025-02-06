/* 2025.02.06 駒沢風助 ファイル作成 */

#include "SkySqhereBasic.h"

/* 基本スカイスフィアクラスの定義 */
// コンストラクタ
SkySqhereBasic::SkySqhereBasic() : SkySqhereBase()
{
	/* データリスト取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}
}

// デストラクタ
SkySqhereBasic::~SkySqhereBasic()
{

}

// 更新
void SkySqhereBasic::Update()
{
	/* プレイヤーの座標に移動させる */
	// ※おいて枯れないようにするため毎フレーム実行
	this->vecPosition = this->ObjectList->GetCharacterPlayer()->vecGetPosition();
}

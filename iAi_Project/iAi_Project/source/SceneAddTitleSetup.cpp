/* 2025.03.05 ファイル作成 駒沢風助 */

#include "SceneAddTitleSetup.h"

/* シーン"タイトル"追加セットアップの定義 */
// コンストラクタ
SceneAddTitleSetup::SceneAddTitleSetup() : SceneBase("AddSceneTitleSetup", 10, true)
{

}

// 計算
void SceneAddTitleSetup::Process()
{
	/* データリスト"ステージ状態管理"を取得 */
	std::shared_ptr<DataList_StageStatus> StageStatusList = std::dynamic_pointer_cast<DataList_StageStatus>(gpDataListServer->GetDataList("DataList_StageStatus"));

	/* "ステージ状態管理"を初期化する */
	StageStatusList->Initialization();

	/* 現行シーン削除フラグを有効化 */
	gpSceneServer->SetDeleteCurrentSceneFlg(true);

	/* シーン"タイトル"を追加 */
	gpSceneServer->AddSceneReservation(std::make_shared<SceneTitle>());
}

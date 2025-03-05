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
	/* 現行シーン削除フラグを有効化 */
	gpSceneServer->SetDeleteCurrentSceneFlg(true);

	/* シーン"タイトル"を追加 */
	gpSceneServer->AddSceneReservation(new SceneTitle());
}

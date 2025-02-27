/* 2025.02.27 ファイル作成 駒沢風助 */

#include "SceneAddStageSetup.h"

/* シーン「ステージ追加セットアップ」の定義 */
// コンストラクタ
SceneAddStageSetup::SceneAddStageSetup() : SceneBase("AddStageSetup", 10, true)
{

}

// 計算
void SceneAddStageSetup::Process()
{
	/* 現行シーン削除フラグを有効化 */
	gpSceneServer->SetDeleteCurrentSceneFlg(true);

	/* シーン"ゲーム"を追加 */
	gpSceneServer->AddSceneReservation(new SceneGame());
}

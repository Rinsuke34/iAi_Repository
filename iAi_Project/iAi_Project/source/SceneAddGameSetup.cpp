/* 2025.02.27 ファイル作成 駒沢風助 */

#include "SceneAddGameSetup.h"

/* シーン"ゲーム"追加セットアップの定義 */
// コンストラクタ
SceneAddSceneGameSetup::SceneAddSceneGameSetup() : SceneBase("AddSceneGameSetup", 10, true)
{

}

// 計算
void SceneAddSceneGameSetup::Process()
{
	/* 現行シーン削除フラグを有効化 */
	gpSceneServer->SetDeleteCurrentSceneFlg(true);

	/* シーン"ゲーム"を追加 */
	gpSceneServer->AddSceneReservation(new SceneGame());
}

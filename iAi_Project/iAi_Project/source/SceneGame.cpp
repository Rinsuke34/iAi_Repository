/* 2024.12.XX YYYY ZZZZ */

#include "SceneGame.h"

/* シーン「ゲーム」の定義 */

// コンストラクタ
SceneGame::SceneGame() : SceneBase("Game", 0, false)
{
	/* 非同期読み込みを有効化する */
	SetUseASyncLoadFlag(true);

	/* テスト用処理 開始 */

	/* "オブジェクト管理"を作成 */

	/* データリストサーバーに"オブジェクト管理"を追加 */
	gpDataListServer->AddDataList(new DataList_Object()); 

	/* 今追加した"オブジェクト管理"を取得 */
	ObjectList	=	dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

	/* "オブジェクト管理"に要素追加 */
	ObjectList->SetCharacterPlayer(new CharacterPlayer());

	/* テスト用処理 終了 */

	/* 非同期読み込みを無効化する */
	SetUseASyncLoadFlag(false);
}

// デストラクタ
SceneGame::~SceneGame()
{
	/* オブジェクトサーバーの"オブジェクト管理"削除 */
	gpDataListServer->DeleteDataList("DataList_Object");
}

// 計算
void SceneGame::Process()
{
	/* すべてのオブジェクトの更新 */
	ObjectList->UpdateAll();
}

// 描画
void SceneGame::Draw()
{
	/* 3D基本設定 */
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	/* すべてのオブジェクトの描写 */
	ObjectList->DrawAll();

	/* カメラ設定(仮) */
	VECTOR stVecCameraPosition	= VGet(0, 100, -300);
	VECTOR stVecCameraTarget	= VGet(0, 100, 0);
	VECTOR stVecCameraUp		= VGet(0, 1, 0);

	SetCameraPositionAndTargetAndUpVec(stVecCameraPosition, stVecCameraTarget, stVecCameraUp);
}

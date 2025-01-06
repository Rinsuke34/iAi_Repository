/* 2024.12.XX YYYY ZZZZ */

#include "SceneGame.h"

/* シーン「ゲーム」の定義 */

// コンストラクタ
SceneGame::SceneGame() : SceneBase("Game", 0, false)
{
	/* 非同期読み込みを有効化する */
	SetUseASyncLoadFlag(true);

	/* テスト用処理 開始 */

	/* データリスト作成 */
	{
		/* データリストサーバーに"オブジェクト管理"を追加 */
		gpDataListServer->AddDataList(new DataList_Object());

		/* データリストサーバーに"プレイヤー状態"を追加 */
		gpDataListServer->AddDataList(new DataList_PlayerStatus());
	}
	
	/* データリスト取得 */
	{
		/* "オブジェクト管理"を取得 */
		ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}
	
	/* 要素追加 */
	{
		/* "オブジェクト管理"にプレイヤーを追加 */
		ObjectList->SetCharacterPlayer(new CharacterPlayer());
	}

	/* テスト用処理 終了 */

	/* シーン"カメラ"を作成 */
	gpSceneServer->AddSceneReservation(new SceneGame_Camera(), false);

	/* 非同期読み込みを無効化する */
	SetUseASyncLoadFlag(false);
}

// デストラクタ
SceneGame::~SceneGame()
{
	/* データリスト削除 */
	gpDataListServer->DeleteDataList("DataList_Object");		// オブジェクト管理
	gpDataListServer->DeleteDataList("DataList_PlayerStatus");	// プレイヤー状態
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
	/* すべてのオブジェクトの描写 */
	ObjectList->DrawAll();
}

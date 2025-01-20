/* 2024.12.XX YYYY ZZZZ */

#include "SceneTitle.h"
#include "SceneHome.h"

/* シーン「タイトル」の定義 */

// コンストラクタ
SceneTitle::SceneTitle() : SceneBase("Title", 0, false)
{

}

// デストラクタ
SceneTitle::~SceneTitle()
{

}

// 初期化
void SceneTitle::Initialization()
{
	/* SceneBaseの初期化を実施(リソース競合対策) */
	SceneBase::Initialization();
}

// 計算
void SceneTitle::Process()
{
	/* いずれかのボタンが入力されたらホームを追加 */
	// 仮作成
	/* 決定が入力されたら */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		/* ロードシーン追加フラグを有効化 */
		gpSceneServer->SetAddLoadSceneFlg(true);

		/* 現行シーン削除フラグを有効化 */
		gpSceneServer->SetDeleteCurrentSceneFlg(true);

		/* シーン"ホーム"を追加 */
		gpSceneServer->AddSceneReservation(new SceneHome());
		return;
	}
}

// 描画
void SceneTitle::Draw()
{
	
}

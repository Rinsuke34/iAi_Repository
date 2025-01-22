/* 2024.12.XX YYYY ZZZZ */

#include "SceneTitle.h"
#include "SceneHome.h"

#include "SceneInputConfig.h"

/* シーン「タイトル」の定義 */

// コンストラクタ
SceneTitle::SceneTitle() : SceneBase("Title", 0, false)
{
	/* 非同期読み込みを有効化する */
	SetUseASyncLoadFlag(true);

	/* 非同期読み込みを無効化する */
	SetUseASyncLoadFlag(false);
}

// デストラクタ
SceneTitle::~SceneTitle()
{

}

// 計算
void SceneTitle::Process()
{
	/* いずれかのボタンが入力されたらホームを追加 */
	// 仮作成
	/* 決定が入力されたら */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		gpSceneServer->AddSceneReservation(new SceneHome(), true);
		//gpSceneServer->AddSceneReservation(new SceneInputConfig(), true);
		return;
	}
}

// 描画
void SceneTitle::Draw()
{
	
}

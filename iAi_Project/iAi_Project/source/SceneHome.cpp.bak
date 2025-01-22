/* 2024.12.XX YYYY ZZZZ */

#include "SceneHome.h"
#include "SceneGame.h"


/* シーン「ホーム」の定義 */

// コンストラクタ
SceneHome::SceneHome() : SceneBase("Home", 0, false)
{
	/* 非同期読み込みを有効化する */
	SetUseASyncLoadFlag(true);

	/* 非同期読み込みを無効化する */
	SetUseASyncLoadFlag(false);
}

// デストラクタ
SceneHome::~SceneHome()
{

}

// 計算
void SceneHome::Process()
{
	/* いずれかのボタンが入力されたらシーンを削除 */
	/* 決定が入力されたら */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		gpSceneServer->AddSceneReservation(new SceneGame(), true);
		return;
	}
}

// 描画
void SceneHome::Draw()
{

}

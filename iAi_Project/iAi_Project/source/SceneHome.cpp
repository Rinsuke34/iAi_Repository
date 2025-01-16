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
		SceneGame* AddScene	= new SceneGame();
		gbTutorialFlg		= true;	// チュートリアルフラグ有効化
		gpSceneServer->AddSceneReservation(AddScene, true);
		return;
	}
	/* キャンセルが入力されたら */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
	{
		SceneGame* AddScene = new SceneGame();
		gpSceneServer->AddSceneReservation(AddScene, true);
		return;
	}
}

// 描画
void SceneHome::Draw()
{
	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "決定			：ステージ0_1(チュートリアル)へ");
	DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "キャンセル	：ステージ1_1へ");
}

/* 2024.12.XX YYYY ZZZZ */

#include "SceneHome.h"
#include "SceneGame.h"


/* シーン"ホーム画面"の定義 */

// コンストラクタ
SceneHome::SceneHome() : SceneBase("Home", 0, true)
{
	/* BGMを設定 */
	gpDataList_Sound->BGM_SetHandle(BGM_HOME);
}

// デストラクタ
SceneHome::~SceneHome()
{

}

// 初期化
void SceneHome::Initialization()
{
	
}

// 計算
void SceneHome::Process()
{
	/* いずれかのボタンが入力されたらシーンを削除 */
	/* 決定が入力されたら */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		/* チュートリアルフラグを有効化 */
		gbTutorialFlg = true;

		/* ロード画面追加フラグを有効化 */
		gpSceneServer->SetAddLoadSceneFlg(true);

		/* 現行シーン削除フラグを有効化 */
		gpSceneServer->SetDeleteCurrentSceneFlg(true);

		/* シーン"ゲーム"を追加 */
		gpSceneServer->AddSceneReservation(new SceneGame());
		return;
	}
	/* キャンセルが入力されたら */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
	{
		/* チュートリアルフラグを無効化 */
		gbTutorialFlg = false;

		/* ロード画面追加フラグを有効化 */
		gpSceneServer->SetAddLoadSceneFlg(true);

		/* 現行シーン削除フラグを有効化 */
		gpSceneServer->SetDeleteCurrentSceneFlg(true);

		/* シーン"ゲーム"を追加 */
		gpSceneServer->AddSceneReservation(new SceneGame());
		return;
	}
}

// 描画
void SceneHome::Draw()
{
	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "決定			：ステージ0_1(チュートリアル)へ");
	DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "キャンセル	：ステージ1_1へ");
}

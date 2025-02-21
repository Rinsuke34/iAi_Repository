/* 2024.12.XX YYYY ZZZZ */

#include "SceneTitle.h"
#include "SceneHome.h"

/* シーン「タイトル」の定義 */

// コンストラクタ
SceneTitle::SceneTitle() : SceneBase("Title", 0, false)
{

	iTitleLogoHandle = LoadGraph("resource/ImageData/Test/TitleLogo.mp4");

	iTitleBackGroundHandle = LoadGraph("resource/ImageData/Test/skysphere1.png");


	/* 初期化 */
	Initialization();
}

// デストラクタ
SceneTitle::~SceneTitle()
{

}

// 初期化
void SceneTitle::Initialization()
{
	/* BGMを設定 */
	gpDataList_Sound->BGM_SetHandle(BGM_TITLE);
}

// 計算
void SceneTitle::Process()
{
	/* いずれかのボタンが入力されたらホームを追加 */
	// 仮作成
	/* "決定"が入力されたか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		// "決定"が入力されたならば
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
	
	// タイトル背景を描画
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, iTitleBackGroundHandle, FALSE);
	/* タイトルロゴを描画 */
	PlayMovieToGraph(iTitleLogoHandle);
	// ムービー映像を画面いっぱいに描画します
	DrawExtendGraph(100, 100, 1000, 600, iTitleLogoHandle, FALSE);


	//再生が終了しているか確認
	if (GetMovieStateToGraph(iTitleLogoHandle) == FALSE)
	{
		//再生が終了している場合
		//ムービーを削除
		//DeleteGraph(iTitleLogoHandle);

		iTitleLogoHandle = LoadGraph("resource/ImageData/Test/TitleLogo.mp4");
		/* タイトルロゴを描画 */
		PlayMovieToGraph(iTitleLogoHandle);
		// ムービー映像を画面いっぱいに描画します
		DrawExtendGraph(100, 100, 1000, 600, iTitleLogoHandle, FALSE);
	}

}

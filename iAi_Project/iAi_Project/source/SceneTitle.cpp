/* 2024.12.XX YYYY ZZZZ */

#include "SceneTitle.h"
#include "SceneHome.h"

/* シーン「タイトル」の定義 */

// コンストラクタ
SceneTitle::SceneTitle() : SceneBase("Title", 10, false)
{
	iTitleLogoHandle = LoadGraph("resource/ImageData/Test/TitleLogo.mp4");

	//iTitleBackGroundHandle = LoadGraph("resource/ImageData/Test/skysphere1.png");

	/* データリスト取得 */
	{
		/* "ステージ状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

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

	/* 最初のステージ番号を"タイトル/ホーム"に設定 */
	this->StageStatusList->SetNowStageNo(STAGE_NO_TITLE);

	/* カメラモードを"タイトル"に設定 */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_TITLE);

	/* UI追加フラグを無効化 */
	this->StageStatusList->SetAddUiFlg(false);

	/* "タイトル"のステージを読み込む */
	/* シーン"タイトル"を作成 */
	SceneBase* pAddScene = new SceneStage();

	/* シーン"ステージ"をシーンサーバーに追加 */
	gpSceneServer->AddSceneReservation(pAddScene);

	/* ステージの読み込みを開始 */
	dynamic_cast<SceneStage*>(pAddScene)->LoadMapData();

	/* 初期化処理 */
	pAddScene->Initialization();
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
	/* 描画ブレンドモードを加算にする */
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	
	// タイトル背景を描画
	//DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, iTitleBackGroundHandle, FALSE);
	/* タイトルロゴを描画 */
	PlayMovieToGraph(iTitleLogoHandle);
	// ムービー映像を画面いっぱいに描画します
//	DrawExtendGraph(100, 100, 1000, 600, iTitleLogoHandle, TRUE);
	DrawGraph(100, -100, iTitleLogoHandle, TRUE);


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
		DrawExtendGraph(100, 100, 1000, 600, iTitleLogoHandle, TRUE);
	}

	/* 描画ブレンドモードをブレンド無しに戻す */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	/* 描画モードを二アレストに戻す */
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

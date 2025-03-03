/* 2024.12.XX YYYY ZZZZ */

#include "SceneTitle.h"


/* シーン「タイトル」の定義 */

// コンストラクタ
SceneTitle::SceneTitle() : SceneBase("Title", 10, false)
{
	/* データリスト取得 */
	{
		/* "ステージ状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "入力管理"を取得 */
		this->InputList = dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	}

	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* タイトルロゴ */
		this->piGrHandle_TitleLogo = ImageList->piGetImage_Movie("Test/TitleLogo");
	}

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
	this->pSceneStage = new SceneStage();

	/* シーン"ステージ"をシーンサーバーに追加 */
	gpSceneServer->AddSceneReservation(this->pSceneStage);

	/* ステージの読み込みを開始 */
	dynamic_cast<SceneStage*>(this->pSceneStage)->LoadMapData();

	/* 初期化処理 */
	this->pSceneStage->Initialization();

	this->UICount = 0;

	pSceneStage->iGetNowCameraFixedPositionNo();
	pSceneStage->SetNowCameraFixedPositionNo(0);
}

// デストラクタ
SceneTitle::~SceneTitle()
{
	
}

// 初期化
void SceneTitle::Initialization()
{
	
}

// 計算
void SceneTitle::Process()
{
	
	
	/* キーボードから移動方向を取得 */
	/* 前進 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_UP))
	{
		UICount++;
		if (UICount >= CAMERA_FIXED_POSITION_MAX)
		{
			UICount = 1;
		}
	pSceneStage->iGetNowCameraFixedPositionNo();
		pSceneStage->SetNowCameraFixedPositionNo(UICount);
	}

	/* 後退 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DOWN))
	{
		UICount--;
		if (UICount < 0)
		{
			UICount = CAMERA_FIXED_POSITION_E;

		}
		pSceneStage->iGetNowCameraFixedPositionNo();
		pSceneStage->SetNowCameraFixedPositionNo(UICount);
	}
	

	/* いずれかのボタンが入力されたらシーンを削除 */
	/* 決定が入力されたら */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		/* ロード画面追加フラグを有効化 */
		gpSceneServer->SetAddLoadSceneFlg(true);

		/* 現行シーン削除フラグを有効化 */
		gpSceneServer->SetDeleteCurrentSceneFlg(true);

		/* シーン"ゲーム"を追加 */
		gpSceneServer->AddSceneReservation(new SceneAddStageSetup());
		return;
	}
}

// 描画
void SceneTitle::Draw()
{
	/* 描画ブレンドモードを加算にする */
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	/* タイトルロゴを再生 */
	PlayMovieToGraph(*this->piGrHandle_TitleLogo);

	/* ムービーを描写 */
	DrawGraph(100, -100, *this->piGrHandle_TitleLogo, TRUE);

	/* 再生が終了しているか確認 */
	if (GetMovieStateToGraph(*this->piGrHandle_TitleLogo) == FALSE)
	{
		// 再生が終了している場合
		/* ムービーの再生時間を初期化する */
		SeekMovieToGraph(*this->piGrHandle_TitleLogo, 0);
	}

	/* 描画ブレンドモードをブレンド無しに戻す */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	/* 描画モードを二アレストに戻す */
	SetDrawMode(DX_DRAWMODE_NEAREST);

	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "決定			：ステージ1_1へ");
}

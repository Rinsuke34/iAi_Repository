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

	this->bGameStartFlg = false;

	//UIカウントを初期化
	this->UICount = 0;

	//カメラ固定位置を設定
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
	//カメラの位置がポジションAまたはBか確認
	if (UICount == CAMERA_FIXED_POSITION_A || UICount == CAMERA_FIXED_POSITION_B)
	{
		//カメラの位置がポジションAまたはBの場合
		//決定ボタンが押された場合
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
		{
			//決定ボタンが押された場合
			//UIカウントをポジションEに設定
			UICount = CAMERA_FIXED_POSITION_E;
			//カメラ固定位置を取得
			pSceneStage->iGetNowCameraFixedPositionNo();
			//カメラ固定位置をUIカウントの値に設定
			pSceneStage->SetNowCameraFixedPositionNo(UICount);
			//ゲームスタートフラグを無効
			this->bGameStartFlg = FALSE;
		}
		
	}
	//カメラの位置がポジションEか確認
	if (UICount == CAMERA_FIXED_POSITION_E)
	{
		//カメラの位置がポジションEの場合
		//決定ボタンが押されたか確認
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID)&&this->bGameStartFlg == TRUE)
		{
			//決定ボタンが押された場合
			/* ロード画面追加フラグを有効化 */
			gpSceneServer->SetAddLoadSceneFlg(true);
	
			/* 現行シーン削除フラグを有効化 */
			gpSceneServer->SetDeleteCurrentSceneFlg(true);
	
			/* シーン"ゲーム"を追加 */
			gpSceneServer->AddSceneReservation(new SceneAddSceneGameSetup());
			return;
		}
		//ゲームスタートフラグを有効化
		this->bGameStartFlg = TRUE;
	}
	//カメラの位置が初期位置か確認
	if (UICount == 0)
	{
		//カメラの位置が初期位置の場合
		//決定ボタンが押されたか確認
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
		{
			//決定ボタンが押された場合
			//UIカウントを増やす
			UICount++;
			//カメラ固定位置を取得
			pSceneStage->iGetNowCameraFixedPositionNo();
			//カメラ固定位置をUIカウントの値に設定
			pSceneStage->SetNowCameraFixedPositionNo(UICount);
		}
	}
	//カメラの位置が初期位置以外か確認
	if ((5 > UICount) || (UICount > 0))
	{
		//カメラの位置が初期位置以外の場合
		//上ボタンが押されたか確認
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_UP))
	{
			//上ボタンが押された場合
			//UIカウントを増やす
		UICount++;
			//UIカウントがポジションE以上か確認
			if (UICount >= CAMERA_FIXED_POSITION_E)
		{
				//UIカウントがポジションE以上の場合
				//UIカウントをポジションAに設定
			UICount = 1;
		}
			//カメラ固定位置を取得
		pSceneStage->iGetNowCameraFixedPositionNo();
			//カメラ固定位置をUIカウントの値に設定
		pSceneStage->SetNowCameraFixedPositionNo(UICount);
	}
		//下ボタンが押されたか確認
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DOWN))
	{
			//下ボタンが押された場合
			//UIカウントを減らす
		UICount--;
			//UIカウントがポジションA未満か確認
			if (UICount < 1)
		{
				//UIカウントがポジションA未満の場合
				//UIカウントをポジションDに設定
				UICount = CAMERA_FIXED_POSITION_D;

		}
			//カメラ固定位置を取得
		pSceneStage->iGetNowCameraFixedPositionNo();
			//カメラ固定位置をUIカウントの値に設定
		pSceneStage->SetNowCameraFixedPositionNo(UICount);
			//	pScreen->SetUICount(UICount);
	}
		//キャンセルボタンが押されたか確認
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
	{
			//キャンセルボタンが押された場合
			//UIカウントを初期化
			UICount = 0;
			//カメラ固定位置を取得
			pSceneStage->iGetNowCameraFixedPositionNo();
			//カメラ固定位置をUIカウントの値に設定
			pSceneStage->SetNowCameraFixedPositionNo(UICount);
		}
	}
	if (UICount == 5)
	{
		//キャンセルボタンが押されたか確認
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
		{
			//キャンセルボタンが押された場合
			//UIカウントを初期化
			UICount = 1;
			//カメラ固定位置を取得
			pSceneStage->iGetNowCameraFixedPositionNo();
			//カメラ固定位置をUIカウントの値に設定
			pSceneStage->SetNowCameraFixedPositionNo(UICount);
		}
	}
}

// 描画
void SceneTitle::Draw()
{
	if (UICount == 0)
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
}

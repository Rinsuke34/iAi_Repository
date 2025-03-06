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

		/* ニューゲーム */
		this->iImageNewgameHandle = *ImageList->piGetImage("Test/UINewgame");
		this->iImageNewgameChoiceHandle = *ImageList->piGetImage("Test/UINewgame_Choice");

		/* コンティニュー */
		this->iImageContinueHandle = *ImageList->piGetImage("Test/UIContinue");
		this->iImageContinueChoiceHandle = *ImageList->piGetImage("Test/UIContinue_Choice");

		/* データ */
		this->iImageDateHandle = *ImageList->piGetImage("Test/UIData");
		this->iImageDateChoiceHandle = *ImageList->piGetImage("Test/UIData_Choice");

		/* コンフィグ */
		this->iImageConfigHandle = *ImageList->piGetImage("Test/UIConfig");
		this->iImageConfigChoiceHandle = *ImageList->piGetImage("Test/UIConfig_Choice");

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
	this->iUICount = CAMERA_FIXED_POSITION_START;

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
	//UIカウントによって処理を分岐
    switch (iUICount)
	{
		// カメラの位置がポジションAまたはBか確認
        case CAMERA_FIXED_POSITION_A:
        case CAMERA_FIXED_POSITION_B:

		//カメラの位置がポジションAまたはBの場合
		// 決定ボタンが押されたか確認
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
		{
			//決定ボタンが押された場合
			//UiカウントをポジションEに変更
            iUICount = CAMERA_FIXED_POSITION_E;

			//カメラ固定位置を取得
			pSceneStage->iGetNowCameraFixedPositionNo();

			//カメラ固定位置をUIカウントに設定
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);

			//ゲームスタートフラグを無効化
			this->bGameStartFlg = FALSE;
		}
		
		// 上ボタンが押されたか確認
        if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_UP))
        {
            // 上ボタンが押された場合
            //UIカウントを減少
            iUICount--;

			//UIカウントがポジションAより小さいか確認
            if (iUICount < CAMERA_FIXED_POSITION_A)
            {
				//UIカウントがポジションAより小さい場合
				//UIカウントをポジションDに設定
                iUICount = CAMERA_FIXED_POSITION_D;
	}

			//カメラ固定位置を取得
            pSceneStage->iGetNowCameraFixedPositionNo();

			//カメラ固定位置をUIカウントに設定
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
        }

		// 下ボタンが押されたか確認
        if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DOWN))
        {
            // 下ボタンが押された場合
			//UIカウントを増加
            iUICount++;

			//UIカウントがポジションEより大きいか確認
            if (iUICount >= CAMERA_FIXED_POSITION_E)
            {
				//UIカウントがポジションEより大きい場合
				//UIカウントをポジションAに設定
                iUICount = CAMERA_FIXED_POSITION_A;
            }

			//カメラ固定位置を取得
            pSceneStage->iGetNowCameraFixedPositionNo();

			//カメラ固定位置をUIカウントに設定
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
        }

		// キャンセルボタンが押されたか確認
        if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
	{
            // キャンセルボタンが押された場合
			//UIカウントをポジションスタートに設定
            iUICount = CAMERA_FIXED_POSITION_START;

			//カメラ固定位置を取得
            pSceneStage->iGetNowCameraFixedPositionNo();

			//カメラ固定位置をUIカウントに設定
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
        }
        break;

		// カメラの位置がポジションEか確認
    case CAMERA_FIXED_POSITION_E:

		//カメラの位置がポジションEの場合
		//決定ボタンが押されたか確認
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID)&&this->bGameStartFlg == TRUE)
		{
			//決定ボタンが押された場合
            // シーンの追加を設定
			gpSceneServer->SetAddLoadSceneFlg(true);
	
			// シーンの削除を設定
			gpSceneServer->SetDeleteCurrentSceneFlg(true);
	
			// シーン"ゲームセットアップ"を追加
			gpSceneServer->AddSceneReservation(new SceneAddSceneGameSetup());
			return;
		}
		//ゲームスタートフラグを有効化
		this->bGameStartFlg = TRUE;

        // キャンセルボタンが押されたか確認
        if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
		{
			// キャンセルボタンが押された場合
			//UIカウントをポジションAに設定
            iUICount = CAMERA_FIXED_POSITION_A;

			//カメラ固定位置を取得
			pSceneStage->iGetNowCameraFixedPositionNo();

			//カメラ固定位置をUIカウントに設定
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
	}
        break;

		// カメラの位置がポジションスタートか確認
    case CAMERA_FIXED_POSITION_START:

		// カメラの位置がポジションスタートの場合
			// 何かボタンが押されたか確認
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_ANY))
	{
			// 何かボタンが押された場合
			//UIカウントをポジションAに設定
            iUICount++;

			//カメラ固定位置を取得
            pSceneStage->iGetNowCameraFixedPositionNo();

			//カメラ固定位置をUIカウントに設定
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
        }
        break;

		// カメラの位置がポジションCまたはDか確認
    case CAMERA_FIXED_POSITION_D:
    case CAMERA_FIXED_POSITION_C:

		// カメラの位置がポジションCまたはDの場合
		//上ボタンが押されたか確認
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_UP))
	{
			//上ボタンが押された場合
			//UIカウントを減少
            iUICount--;

			//UIカウントがポジションAより小さいか確認
            if (iUICount < CAMERA_FIXED_POSITION_A)
		{
				//UIカウントがポジションAより小さい場合
				//UIカウントをポジションDに設定
                iUICount = CAMERA_FIXED_POSITION_D;
		}
			//カメラ固定位置を取得
		pSceneStage->iGetNowCameraFixedPositionNo();

			//カメラ固定位置をUIカウントに設定
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
	}
		//下ボタンが押されたか確認
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DOWN))
	{
			//下ボタンが押された場合
			//UIカウントを増加
            iUICount++;

			//UIカウントがポジションEより大きいか確認
            if (iUICount >= CAMERA_FIXED_POSITION_E)
	{
				//UIカウントがポジションEより大きい場合
				//UIカウントをポジションAに設定
                iUICount = CAMERA_FIXED_POSITION_A;
            }
           
			//カメラ固定位置を取得
			pSceneStage->iGetNowCameraFixedPositionNo();

			//カメラ固定位置をUIカウントに設定
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
	}

		//キャンセルボタンが押されたか確認
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
		{
			//キャンセルボタンが押された場合
			//UIカウントをポジションスタートに設定
            iUICount = CAMERA_FIXED_POSITION_START;

			//カメラ固定位置を取得
			pSceneStage->iGetNowCameraFixedPositionNo();

			//カメラ固定位置をUIカウントに設定
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
		}
        break;
	}
}

// 描画
void SceneTitle::Draw()
{
	if (iUICount == CAMERA_FIXED_POSITION_START)
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

	switch (iUICount)
	{
	case CAMERA_FIXED_POSITION_A:
		/* ニューゲーム */
		DrawGraph(100, 589, this->iImageNewgameChoiceHandle, TRUE);
		DrawGraph(100, 690, this->iImageContinueHandle, TRUE);
		DrawGraph(100, 795, this->iImageDateHandle, TRUE);
		DrawGraph(100, 900, this->iImageConfigHandle, TRUE);
		break;
	case CAMERA_FIXED_POSITION_B:
		DrawGraph(100, 589, this->iImageNewgameHandle, TRUE);
		DrawGraph(100, 690, this->iImageContinueChoiceHandle, TRUE);
		DrawGraph(100, 795, this->iImageDateHandle, TRUE);
		DrawGraph(100, 900, this->iImageConfigHandle, TRUE);
		break;
	case CAMERA_FIXED_POSITION_C:
		DrawGraph(100, 589, this->iImageNewgameHandle, TRUE);
		DrawGraph(100, 690, this->iImageContinueHandle, TRUE);
		DrawGraph(100, 795, this->iImageDateChoiceHandle, TRUE);
		DrawGraph(100, 900, this->iImageConfigHandle, TRUE);
		break;
	case CAMERA_FIXED_POSITION_D:
		DrawGraph(100, 589, this->iImageNewgameHandle, TRUE);
		DrawGraph(100, 690, this->iImageContinueHandle, TRUE);
		DrawGraph(100, 795, this->iImageDateHandle, TRUE);
		DrawGraph(100, 900, this->iImageConfigChoiceHandle, TRUE);
		break;
	}
}

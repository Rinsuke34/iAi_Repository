/* 2024.12.20 ファイル追加						石川智也 */
/* 2025.01.09 提出用臨時コーディング修正		駒沢風助 */
/* 2025.03.25 セーブデータ初期化失敗バグ修正	駒沢風助 */ 

#include "SceneTitle.h"

bool g_bActiveFlg = false; // 初期値を設定

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
		this->piGrHandle_TitleLogo = ImageList->piGetImage_Movie("Home/TitleLogo");

		/* ニューゲーム */
		this->iImageNewgameHandle = *ImageList->piGetImage("Home/UINewgame");
		this->iImageNewgameChoiceHandle = *ImageList->piGetImage("Home/UINewgame_Choice");

		/* コンティニュー */
		this->iImageContinueHandle = *ImageList->piGetImage("Home/UIContinue");
		this->iImageContinueChoiceHandle = *ImageList->piGetImage("Home/UIContinue_Choice");

		/* データ */
		this->iImageDateHandle = *ImageList->piGetImage("Home/UIConfig");
		this->iImageDateChoiceHandle = *ImageList->piGetImage("Home/UIConfig_Choice");

		/* コンフィグ */
		this->iImageConfigHandle = *ImageList->piGetImage("Home/UIGameend"); 
		this->iImageConfigChoiceHandle = *ImageList->piGetImage("Home/UIGameend_Choice"); 

		/* 最終確認背景 */
		this->iImageFinalCheckHandle = *ImageList->piGetImage("Home/UI_Window_GameStart");

		/* yes */
		this->iImageYesHandle = *ImageList->piGetImage("Home/UI_Moji_Yes_NotSelected");
		this->iImageYesChoiceHandle = *ImageList->piGetImage("Home/UI_Moji_Yes_Selected");

		/* no */
		this->iImageNoHandle = *ImageList->piGetImage("Home/UI_Moji_No_NotSelected");
		this->iImageNoChoiceHandle = *ImageList->piGetImage("Home/UI_Moji_No_Selected");

		/* aボタンスタート */
		this->iImageAButtonStartHandle = *ImageList->piGetImage("Home/UI_Title_PressA");

	}

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

	//スタートフラグを無効化
	this->bGameStartFlg = false;

	//ホームフラグを無効化
	this->bHomeFlg = false;

	//シーン遷移フラグを無効化
	this->bTransition = false;

	//タイマーを初期化
	this->iTimer = 0;

	//最終確認画面を隠すフラグを無効化
	this->bHideFinalCheck = false;

	//アルファカウントを初期化
	this->iAlphaCount = 0;

	//アルファフラグを無効化
	this->bAlphaFlg = false;

	//コンフィグフラグを無効化
	this->bConfigFlg = false;

	//設定フラグを無効化
	this->bSettingFlg = false;


	//UIカウントを初期化
	this->iUICount = CAMERA_FIXED_POSITION_START;

	//カメラ固定位置を設定
	pSceneStage->SetNowCameraFixedPositionNo(0);

	// BGM再生フラグ
	this->bPlayTitleBgmFlg = true;
}

// デストラクタ
SceneTitle::~SceneTitle()
{
	
}

// 初期化
void SceneTitle::Initialization()
{
	
}

// 処理
void SceneTitle::Process()
{
	/* BGM再生フラグが有効ならBGMを再生開始 */
	if (this->bPlayTitleBgmFlg == true)
	{
		/* BGMを設定 */
		gpDataList_Sound->BGM_SetHandle(BGM_TITLE);

		/* ボイス"タイトルコール"再生 */
		gpDataList_Sound->VOICE_PlaySound(VOICE_TITLE_CALL);

		/* BGM再生フラグを無効化 */
		this->bPlayTitleBgmFlg = false;
	}

	// シーン遷移フラグが有効な場合、タイマーをカウント
	if (this->bTransition == true)
	{

		g_bActiveFlg = true;
		this->iTimer++;
		if (this->iTimer > 90) // 3秒後にシーンを変更
		{
			// シーンの追加を設定
			gpSceneServer->SetAddLoadSceneFlg(true);

			// シーンの削除を設定
			gpSceneServer->SetDeleteCurrentSceneFlg(true);

			// シーン"ゲームセットアップ"を追加
			gpSceneServer->AddSceneReservation(new SceneAddSceneGameSetup());

			g_bActiveFlg = false;
		}
		return;
	}
	// 決定ボタンが押されたか確認
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		/* "決定"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);


		switch (iUICount)
		{
		case CAMERA_FIXED_POSITION_START:
			//UIカウント(カメラ)をはじめからホーム画面に設定
			iUICount++;

			//カメラ固定位置をはじめからホーム画面に設定
			pSceneStage->SetNowCameraFixedPositionNo(iUICount);
			this->bHomeFlg = TRUE;

			/* BGMを設定 */
			gpDataList_Sound->BGM_SetHandle(BGM_HOME);
			break;

			//はじめからホーム画面
		case CAMERA_FIXED_POSITION_A:
			//Uiカウント(カメラ)を確認画面に変更
			iUICount = CAMERA_FIXED_POSITION_E;

			//カメラ固定位置をUIカウント(カメラ)に設定
			pSceneStage->SetNowCameraFixedPositionNo(iUICount);

			//ゲームスタートフラグを無効化
			this->bGameStartFlg = FALSE;

			//ホームフラグを無効化
			this->bHomeFlg = FALSE;
			break;

			//つづきからホーム画面
		case CAMERA_FIXED_POSITION_B:
			//Uiカウント(カメラ)を確認画面に変更
			iUICount = CAMERA_FIXED_POSITION_E;

			//カメラ固定位置をUIカウント(カメラ)に設定
			pSceneStage->SetNowCameraFixedPositionNo(iUICount);

			// シーンの追加を設定
			gpSceneServer->SetAddLoadSceneFlg(true);

			// シーンの削除を設定
			gpSceneServer->SetDeleteCurrentSceneFlg(true);

			// シーン"ゲームセットアップ"を追加
			gpSceneServer->AddSceneReservation(new SceneAddSceneGameSetup());

			break;

			//確認画面
		case CAMERA_FIXED_POSITION_E:
			if (this->bGameStartFlg == TRUE)
			{
				// シーン遷移フラグを有効化
				bTransition = true;

				// タイマーをリセット
				iTimer = 0;

				// 最終確認画面を隠すフラグを有効化
				bHideFinalCheck = true;

				/* 2025.03.25 セーブデータ初期化失敗バグ修正	駒沢風助 開始 */
				/* 中断セーブデータのパスを取得 */
				std::string SaveDataFileName = "resource/SaveData/SuspensionSaveData.json";

				/* 中断セーブデータを削除する */
				PUBLIC_FUNCTION::FileDeletesAndStand(SaveDataFileName);
				/* 2025.03.25 セーブデータ初期化失敗バグ修正	駒沢風助 終了 */
			}
			else
			{
				// 「no」を選択した場合、はじめからホーム画面に戻る
				iUICount = CAMERA_FIXED_POSITION_A;

				//カメラ固定位置をはじめからホーム画面に設定
				pSceneStage->SetNowCameraFixedPositionNo(iUICount);
			}
			break;

			//データホーム画面
		case CAMERA_FIXED_POSITION_C:

			/* 現在のカメラポジションが設定画面であるか確認 */
			if (this->iUICount == CAMERA_FIXED_POSITION_C)
			{
				/* シーン"オプション"を追加 */
				gpSceneServer->AddSceneReservation(new SceneOption());
			}

			break;

			//設定ホーム画面
		case CAMERA_FIXED_POSITION_D:

			//エンドフラグを有効化
			gbEndFlg = true;

			break;
		}
	}

	// キャンセルボタンが押されたか確認
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
	{
		/* "キャンセル"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_CANCEL);

		switch (iUICount)
		{
			//はじめからホーム画面
		case CAMERA_FIXED_POSITION_A:

			//つづきからホーム画面
		case CAMERA_FIXED_POSITION_B:

			//データホーム画面
		case CAMERA_FIXED_POSITION_C:

			//ホームフラグが有効か確認
			if (this->bHomeFlg == FALSE)
			{
				//UIカウント(カメラ)をはじめからホーム画面に設定
				iUICount = CAMERA_FIXED_POSITION_C;
			}

			//ホームフラグが有効か確認
			if (this->bHomeFlg == TRUE)
			{
				//ホームフラグが有効な場合
				//UIカウント(カメラ)をはじめからホーム画面に設定
				iUICount = CAMERA_FIXED_POSITION_START;
			}

			//ホームフラグを有効化
			this->bHomeFlg = TRUE;

			/* BGMを設定 */
			gpDataList_Sound->BGM_SetHandle(BGM_TITLE);

			break;


			//設定ホーム画面
		case CAMERA_FIXED_POSITION_D:

			//UIカウント(カメラ)をタイトルに設定
			iUICount = CAMERA_FIXED_POSITION_START;

			break;

			//確認画面
		case CAMERA_FIXED_POSITION_E:

			//UIカウントをはじめからホーム画面に設定
			iUICount = CAMERA_FIXED_POSITION_A;

			//ゲームスタートフラグを無効化
			this->bGameStartFlg = FALSE;
			break;
		}

		//カメラ固定位置をカメラに設定
		pSceneStage->SetNowCameraFixedPositionNo(iUICount);
	}

	//上ボタンが押されたか確認
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
	{
		/* "カーソル移動"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		switch (iUICount)
		{
			//タイトル画面
		case CAMERA_FIXED_POSITION_START:
			iUICount = 0;
			break;

			//はじめからホーム画面
		case CAMERA_FIXED_POSITION_A:

			//つづきからホーム画面
		case CAMERA_FIXED_POSITION_B:

			//データホーム画面
		case CAMERA_FIXED_POSITION_C:

			//設定ホーム画面
		case CAMERA_FIXED_POSITION_D:

			//UIカウントを減少
			iUICount--;

			//UIの選択肢が上にあるか確認
			if (iUICount < CAMERA_FIXED_POSITION_A)
			{
				//上にない場合
				//UIカウント(カメラ)を設定ホーム画面に設定
				iUICount = CAMERA_FIXED_POSITION_D;
			}
			break;
		}

		//カメラ固定位置をUIカウントに設定
		pSceneStage->SetNowCameraFixedPositionNo(iUICount);
	}

	//下ボタンが押されたか確認
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
	{
		/* "カーソル移動"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		switch (iUICount)
		{
			//タイトル画面
		case CAMERA_FIXED_POSITION_START:
			iUICount = 0;
			break;

			//はじめからホーム画面
		case CAMERA_FIXED_POSITION_A:

			//つづきからホーム画面
		case CAMERA_FIXED_POSITION_B:

			//データホーム画面
		case CAMERA_FIXED_POSITION_C:

			//設定ホーム画面
		case CAMERA_FIXED_POSITION_D:

			//UIカウントを増加
			iUICount++;

			//選択肢が下にあるか確認
			if (iUICount >= CAMERA_FIXED_POSITION_E)
			{
				//下にない場合
				//UIカウント(カメラ)をはじめからホーム画面に設定
				iUICount = CAMERA_FIXED_POSITION_A;
			}
			break;
		}

		//カメラ固定位置をUIカウントに設定
		pSceneStage->SetNowCameraFixedPositionNo(iUICount);
	}

	// 左ボタンが押されたか確認
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT))
	{
		// 左ボタンが押された場合
		// /* "カーソル移動"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		//カメラの位置が最終確認画面か確認
		if (iUICount == CAMERA_FIXED_POSITION_E)
		{
			//最終確認画面の場合
			// 「はい」を選択
			this->bGameStartFlg = TRUE;
		}
	}

	// 右ボタンが押されたか確認
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT))
	{
		// 右ボタンが押された場合
		/* "カーソル移動"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		//カメラの位置が最終確認画面か確認
		if (iUICount == CAMERA_FIXED_POSITION_E)
		{
			// 「いいえ」を選択
			this->bGameStartFlg = FALSE;
		}
	}
	//ボタンスタートの明度を変更
	if (iUICount == CAMERA_FIXED_POSITION_START)
	{
		//アルファフラグが無効か確認
		if (this->bAlphaFlg == false)
		{
			//アルファフラグが無効の場合
			//アルファカウントが0以上か確認
			if (this->iAlphaCount > 0)
			{
				//アルファカウントが0以上の場合
				//アルファカウントを減少
				this->iAlphaCount -= 5;
			}
			else
			{
				//アルファフラグを有効化
				this->bAlphaFlg = true;
			}
		}
		else
		{
			//アルファカウントが255以下か確認
			if (this->iAlphaCount < 255)
			{
				//アルファカウントが255以下の場合
				//アルファカウントを増加
				this->iAlphaCount += 5;
			}
			else
			{
				//アルファフラグを無効化
				this->bAlphaFlg = false;
			}
		}
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
	}

	switch (iUICount)
	{
	case CAMERA_FIXED_POSITION_START:
		/* タイトル画面 */
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, iAlphaCount);
		DrawGraph(680, 800, this->iImageAButtonStartHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		break;
		case CAMERA_FIXED_POSITION_A:
			/* ニューゲーム */
			DrawGraph(100, 589, this->iImageNewgameChoiceHandle, TRUE);
			DrawGraph(100, 690, this->iImageContinueHandle, TRUE);
			DrawGraph(100, 795, this->iImageDateHandle, TRUE);
			DrawGraph(100, 900, this->iImageConfigHandle, TRUE);
			break;

		case CAMERA_FIXED_POSITION_B:
			/* コンティニュー */
			DrawGraph(100, 589, this->iImageNewgameHandle, TRUE);
			DrawGraph(100, 690, this->iImageContinueChoiceHandle, TRUE);
			DrawGraph(100, 795, this->iImageDateHandle, TRUE);
			DrawGraph(100, 900, this->iImageConfigHandle, TRUE);
			break;

		case CAMERA_FIXED_POSITION_C:
			/* コンフィグ */
			DrawGraph(100, 589, this->iImageNewgameHandle, TRUE);
			DrawGraph(100, 690, this->iImageContinueHandle, TRUE);
			DrawGraph(100, 795, this->iImageDateChoiceHandle, TRUE);
			DrawGraph(100, 900, this->iImageConfigHandle, TRUE);
			break;

		case CAMERA_FIXED_POSITION_D:
			/* エンド */
			DrawGraph(100, 589, this->iImageNewgameHandle, TRUE);
			DrawGraph(100, 690, this->iImageContinueHandle, TRUE);
			DrawGraph(100, 795, this->iImageDateHandle, TRUE);
			DrawGraph(100, 900, this->iImageConfigChoiceHandle, TRUE);
			break;

		case CAMERA_FIXED_POSITION_E:
			/* 画面全体を暗くする */
			if (this->bHideFinalCheck == false)
			{
				/* 画面全体を暗くする */
				{
					/* 描写ブレンドモードを"アルファブレンド"に設定 */
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, PAUSE_BLACK_ALPHA);

					/* 画面全体を黒色で描写 */
					DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);

					/* 描写ブレンドモードを"ノーブレンド"に設定 */
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}

			//最終確認背景
			DrawGraph(570, 270, this->iImageFinalCheckHandle, TRUE);

			//yes
			if (this->bGameStartFlg)
			{
				DrawGraph(690, 560, this->iImageYesChoiceHandle, TRUE);
				DrawGraph(1020, 560, this->iImageNoHandle, TRUE);
			}
			else
			{
				DrawGraph(690, 560, this->iImageYesHandle, TRUE);
				DrawGraph(1020, 560, this->iImageNoChoiceHandle, TRUE);
			}
		}
		break;
	}
}
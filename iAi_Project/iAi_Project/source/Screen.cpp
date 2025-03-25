/* 2025.02.28 石川智也 ファイル作成 */
#include "Screen.h"

// コンストラクタ
Screen::Screen() : PlatformBase()
{
	/* データリスト */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}
	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));
		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Object/SignBoard/SignBoard");
	}

	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* スクリーンに映る映像 */
		this->iTextureTitleHandle = *ImageList->piGetImage_Movie("Home/TitleLogo");			//タイトル
		this->iTextureNewgameHandle = *ImageList->piGetImage_Movie("Home/Newgame");			//ニューゲーム
		this->iTextureContinueHandle = *ImageList->piGetImage_Movie("Home/Continue");		//コンティニュー
		this->iTextureDateHandle = *ImageList->piGetImage_Movie("Home/Config");				//コンフィグ
		this->iTextureConfigHandle = *ImageList->piGetImage("Home/GameEnd");				//データ
		this->iTextureStageHandle = *ImageList->piGetImage_Movie("Home/TitleLogo");			//ステージ
	}

	/* UIカウントを初期化 */
	this->iUICount = CAMERA_FIXED_POSITION_START;

	//動画再生フラグを初期化
	this->bStartFlg = false;

	//ホームフラグを初期化
	this->bHomeFlg = false;

	//ゲームスタートフラグを初期化
	this->bGameStartFlg = false;

	/* スクリーンを発光フレームとして登録 */
	{
		/* モデルハンドルからフレーム数を取得 */
		int iFrameNum = MV1GetFrameNum(this->iModelHandle);

		/* 発光するフレーム番号を取得する */
		for (int i = 0; i < iFrameNum; i++)
		{
			/* フレーム名取得 */
			const char* cFrameName = MV1GetFrameName(this->iModelHandle, i);

			/* 最初の6文字が"Screen"であるか確認 */
			if (strncmp(cFrameName, "Screen", 5) == 0)
			{
				/* 発光フレーム番号を取得 */
				this->aiLightFrameNo.push_back(i);

				/* 発光フレームの親フレーム番号を取得 */
				int parentFrame = MV1GetFrameParent(this->iModelHandle, i);

				/* 発光フレームの親フレームが存在するならば */
				while (parentFrame >= 0)
				{
					// 親フレームが存在する場合
					/* 親フレーム番号を追加 */
					this->aiLightFrameNo.push_back(parentFrame);

					/* 親フレーム番号の親フレームを取得 */
					parentFrame = MV1GetFrameParent(this->iModelHandle, parentFrame);
				}

				/* ループを抜ける */
				break;
			}
		}
	}
}

// デストラクタ
Screen::~Screen()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
}

//処理
void Screen::Process()
{
	if (g_bActiveFlg == false)
	{
	//現在のシーンがタイトルシーンか確認
	if (gpSceneServer->GetScene("Title"))
	{
		// 決定ボタンが押されたか確認
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
		{
			switch (iUICount)
			{
				//タイトル画面
			case CAMERA_FIXED_POSITION_START:
				// Homeフラグを有効化
				this->bHomeFlg = TRUE;

				// UIカウントをはじめからに変更
				iUICount = CAMERA_FIXED_POSITION_A;
				break;

				//はじめからホーム画面
			case CAMERA_FIXED_POSITION_A:
				//つづきからホーム画面
			case CAMERA_FIXED_POSITION_B:
				// Homeフラグを無効化
				this->bGameStartFlg = FALSE;
				//ホームフラグを無効化
				this->bHomeFlg = FALSE;

				this->bStartFlg = TRUE;
				break;

				//データホーム画面
			case CAMERA_FIXED_POSITION_C:
				//設定ホーム画面
			case CAMERA_FIXED_POSITION_D:
				// Homeフラグを無効化

			if (this->bHomeFlg == FALSE)
			{
				this->bHomeFlg = TRUE;
			}
					this->bHomeFlg = FALSE;

					this->bStartFlg = TRUE;
					break;
				}
		}

		// キャンセルボタンが押されたか確認
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
		{
			switch (iUICount)
			{
				//はじめからホーム画面
			case CAMERA_FIXED_POSITION_A:
				//つづきからホーム画面
			case CAMERA_FIXED_POSITION_B:
				//ホームフラグが有効か確認
				if (this->bHomeFlg == FALSE)
				{
					//ホームフラグが有効な場合
					//UIカウント(カメラ)をはじめからに設定
					iUICount = CAMERA_FIXED_POSITION_A;
				}
				if (this->bHomeFlg == TRUE)
				{
					//ホームフラグが有効な場合
					//UIカウント(カメラ)をタイトルに設定
					iUICount = CAMERA_FIXED_POSITION_START;
				}

				//ホームフラグを有効化
				this->bHomeFlg = TRUE;

				this->bStartFlg = TRUE;
				break;
				//データホーム画面
			case CAMERA_FIXED_POSITION_C:

				if (this->bHomeFlg == FALSE)
				{
				if (iUICount == CAMERA_FIXED_POSITION_C)
				{
					//現在のカメラポジションが設定画面であるか確認
					this->iUICount = CAMERA_FIXED_POSITION_C;
					this->bHomeFlg = TRUE;
				}
				}
				else
				{
					//UIカウント(カメラ)をタイトルに設定
					iUICount = CAMERA_FIXED_POSITION_START;
				}

				this->bStartFlg = TRUE;
				break;
				//設定ホーム画面
			case CAMERA_FIXED_POSITION_D:
				
				if (this->bHomeFlg == FALSE)
				{
				if (iUICount == CAMERA_FIXED_POSITION_D)
				{
					iUICount = CAMERA_FIXED_POSITION_D;
					this->bHomeFlg = TRUE;
				}
				}
				else
				{
					//UIカウント(カメラ)をタイトルに設定
					iUICount = CAMERA_FIXED_POSITION_START;
				}

				this->bStartFlg = TRUE;
				break;

			
			}
		}

		// 上ボタンが押されたか確認
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
		{
			switch (iUICount)
			{
				//タイトル画面
			case CAMERA_FIXED_POSITION_START:
				iUICount = 0;

				this->bStartFlg = TRUE;
				break;
				//はじめからホーム画面
			case CAMERA_FIXED_POSITION_A:
				if(this->bHomeFlg == FALSE)
				{
					//はじめから画面
					iUICount = CAMERA_FIXED_POSITION_A;
				}
				else
				{
					// UIカウントを減少
					iUICount--;

					// UIカウントがはじめからより小さいか確認
					if (iUICount < CAMERA_FIXED_POSITION_A)
					{
						//カメラ固定位置を設定ホーム画面に設定
						iUICount = CAMERA_FIXED_POSITION_D;
					}
				}
				this->bStartFlg = TRUE;
				break;
				//つづきからホーム画面
			case CAMERA_FIXED_POSITION_B:
				if(this->bHomeFlg == FALSE)
				{
					//つづきから画面
					iUICount = CAMERA_FIXED_POSITION_B;
				}
				else
				{
					// UIカウントを減少
					iUICount--;
					// UIカウントがはじめからより小さいか確認
					if (iUICount < CAMERA_FIXED_POSITION_A)
					{
						//カメラ固定位置を設定ホーム画面に設定
						iUICount = CAMERA_FIXED_POSITION_D;
					}
				}

				this->bStartFlg = TRUE;
				break;
				//データホーム画面
			case CAMERA_FIXED_POSITION_C:
				//設定ホーム画面
			case CAMERA_FIXED_POSITION_D:
				// UIカウントを減少
				iUICount--;

				// UIカウントがはじめからより小さいか確認
				if (iUICount < CAMERA_FIXED_POSITION_A)
				{
					//カメラ固定位置を設定ホーム画面に設定
					iUICount = CAMERA_FIXED_POSITION_D;
				}
				this->bStartFlg = TRUE;
				break;
			}
		}

		// 下ボタンが押されたか確認
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
		{
			switch (iUICount)
			{
				//タイトル画面
			case CAMERA_FIXED_POSITION_START:
				iUICount = 0;

				this->bStartFlg = TRUE;
				break;
				//はじめからホーム画面
			case CAMERA_FIXED_POSITION_A:
				if(this->bHomeFlg == FALSE)
				{
					//はじめから画面
					iUICount = CAMERA_FIXED_POSITION_A;
				}
				else
				{
					// UIカウントを増加
					iUICount++;
					// UIカウントが確認画面より大きいか確認
					if (iUICount >= CAMERA_FIXED_POSITION_E)
					{
						//カメラ固定位置をはじめからに設定
						iUICount = CAMERA_FIXED_POSITION_A;
					}
				}
				this->bStartFlg = TRUE;
				break;
				//つづきからホーム画面
			case CAMERA_FIXED_POSITION_B:
				if(this->bHomeFlg == FALSE)
				{
					//つづきから画面
					iUICount = CAMERA_FIXED_POSITION_B;
				}
				else
				{
					// UIカウントを増加
					iUICount++;
					// UIカウントが確認画面より大きいか確認
					if (iUICount >= CAMERA_FIXED_POSITION_E)
					{
						//カメラ固定位置をはじめからに設定
						iUICount = CAMERA_FIXED_POSITION_A;
					}
				}
				this->bStartFlg = TRUE;
				break;
				//データホーム画面
			case CAMERA_FIXED_POSITION_C:
				//設定ホーム画面
			case CAMERA_FIXED_POSITION_D:
				// UIカウントを増加
				iUICount++;

				// UIカウントが確認画面より大きいか確認
				if (iUICount >= CAMERA_FIXED_POSITION_E)
				{
					// カメラ固定位置をはじめからに設定
					iUICount = CAMERA_FIXED_POSITION_A;
				}
				this->bStartFlg = TRUE;
				break;
			}
		}

		// 左ボタンが押されたか確認
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT))
		{
			// 左ボタンが押された場合			
			//カメラの位置が最終確認画面か確認
			if (iUICount == CAMERA_FIXED_POSITION_E)
			{
				//最終確認画面の場合
				// 「はい」を選択
				this->bGameStartFlg = TRUE;
			}
			this->bStartFlg = TRUE;
		}

		// 右ボタンが押されたか確認
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT))
		{
			if (iUICount == CAMERA_FIXED_POSITION_E)
			{
				// 「いいえ」を選択
				this->bGameStartFlg = FALSE;
			}
			this->bStartFlg = TRUE;
		}

      
	}
	else if (gpSceneServer->GetScene("Stage"))
	{
		////スタートフラグを有効化か確認
		//if (this->bStartFlg == TRUE)
		//{
		//	//スタートフラグが有効な場合
		//	//タイトル映像の再生位置を0に設定
		//	SeekMovieToGraph(this->iTextureTitleHandle, 0);
		//}

		//モデルのテクスチャをタイトルテクスチャに設定
		MV1SetTextureGraphHandle(iModelHandle, 1, this->iTextureTitleHandle, true);

		//タイトル映像の再生
		PlayMovieToGraph(this->iTextureTitleHandle);

		//タイトル映像の描写
		DrawGraph(100, -100, this->iTextureTitleHandle, TRUE);

		//タイトル映像の再生が終了しているか確認
		if (GetMovieStateToGraph(this->iTextureTitleHandle) == FALSE)
        {
			//タイトル映像の再生が終了している場合
			//タイトル映像の再生位置を0に設定
			SeekMovieToGraph(this->iTextureTitleHandle, 0);
		}

		//スタートフラグを無効化
		//this->bStartFlg = false;
		}
	}
}

// 描画
void Screen::Draw()
{
	//UIカウントによって処理を分岐
	switch (iUICount)
    {
		// カメラ固定位置がタイトルか確認
        case CAMERA_FIXED_POSITION_START:

			//スタートフラグを有効化か確認
            if (this->bStartFlg == TRUE)
			{
				//スタートフラグが有効な場合
				//タイトル映像の再生位置を0に設定
                SeekMovieToGraph(this->iTextureTitleHandle, 0);
				PauseMovieToGraph(this->iTextureConfigHandle, 0);
				PauseMovieToGraph(this->iTextureContinueHandle, 0);
				PauseMovieToGraph(this->iTextureDateHandle, 0);
				PauseMovieToGraph(this->iTextureNewgameHandle, 0);
            }

			//モデルのテクスチャをタイトルテクスチャに設定
            MV1SetTextureGraphHandle(iModelHandle, 1, this->iTextureTitleHandle, true);

			/* 描画ブレンドモードを減算にする */
			SetDrawBlendMode(DX_BLENDMODE_SUB, 0);

			//タイトル映像の再生
            PlayMovieToGraph(this->iTextureTitleHandle);

			//タイトル映像の描写
            DrawGraph(100, -100, this->iTextureTitleHandle, TRUE);

			//タイトル映像の再生が終了しているか確認
            if (GetMovieStateToGraph(this->iTextureTitleHandle) == FALSE)
            {
				//タイトル映像の再生が終了している場合
				//タイトル映像の再生位置を0に設定
                SeekMovieToGraph(this->iTextureTitleHandle, 0);
            }
			/* 描画ブレンドモードをブレンド無しに戻す */
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			//スタートフラグを無効化
            this->bStartFlg = false;
            break;

			// はじめからか確認
        case CAMERA_FIXED_POSITION_A:
			//スタートフラグが有効か確認
            if (this->bStartFlg == TRUE)
            {
				//スタートフラグが有効な場合
				PauseMovieToGraph(this->iTextureTitleHandle, 0);
				PauseMovieToGraph(this->iTextureConfigHandle, 0);
				PauseMovieToGraph(this->iTextureContinueHandle, 0);
				PauseMovieToGraph(this->iTextureDateHandle, 0);
                SeekMovieToGraph(this->iTextureNewgameHandle, 0);
            }

			//モデルのテクスチャをニューゲームテクスチャに設定
			MV1SetTextureGraphHandle(iModelHandle, 1, this->iTextureNewgameHandle, false);

			/* 描画ブレンドモードを減算にする */
			SetDrawBlendMode(DX_BLENDMODE_SUB, 0);

			//ニューゲーム映像の再生
            PlayMovieToGraph(this->iTextureNewgameHandle);

			//ニューゲーム映像の再生が終了しているか確認
            if (GetMovieStateToGraph(this->iTextureNewgameHandle) == FALSE)
            {
				//ニューゲーム映像の再生が終了している場合
				//ニューゲーム映像の再生位置を0に設定
                SeekMovieToGraph(this->iTextureNewgameHandle, 0);
            }
			/* 描画ブレンドモードをブレンド無しに戻す */
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			/* 描画ブレンドモードをブレンド無しに戻す */
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			//スタートフラグを無効化
            this->bStartFlg = false;
            break;

			// つづきからか確認
        case CAMERA_FIXED_POSITION_B:
			//スタートフラグが有効か確認
            if (this->bStartFlg == TRUE)
			{
				//スタートフラグが有効な場合
				PauseMovieToGraph(this->iTextureTitleHandle, 0);
				PauseMovieToGraph(this->iTextureConfigHandle, 0);
                SeekMovieToGraph(this->iTextureContinueHandle, 0);
				PauseMovieToGraph(this->iTextureDateHandle, 0);
				PauseMovieToGraph(this->iTextureNewgameHandle, 0);
			}

			//モデルのテクスチャをコンティニューテクスチャに設定
            MV1SetTextureGraphHandle(iModelHandle, 1, this->iTextureContinueHandle, true);



			//スタートフラグを無効化
            this->bStartFlg = false;
            break;

			// データか確認
        case CAMERA_FIXED_POSITION_C:
			//スタートフラグが有効か確認
            if (this->bStartFlg == TRUE)
			{
				//スタートフラグが有効な場合
				PauseMovieToGraph(this->iTextureTitleHandle, 0);
				PauseMovieToGraph(this->iTextureConfigHandle, 0);
				PauseMovieToGraph(this->iTextureContinueHandle, 0);
                SeekMovieToGraph(this->iTextureDateHandle, 0);
				PauseMovieToGraph(this->iTextureNewgameHandle, 0);
			}

			//モデルのテクスチャをデータテクスチャに設定
            MV1SetTextureGraphHandle(iModelHandle, 1, this->iTextureDateHandle, true);

			/* 描画ブレンドモードを減算にする */
			SetDrawBlendMode(DX_BLENDMODE_SUB, 0);

			//データ映像の再生
            PlayMovieToGraph(this->iTextureDateHandle);

			//データ映像の再生が終了しているか確認
            if (GetMovieStateToGraph(this->iTextureDateHandle) == FALSE)
            {
				//データ映像の再生が終了している場合
				//データ映像の再生位置を0に設定
                SeekMovieToGraph(this->iTextureDateHandle, 0);
			}
			/* 描画ブレンドモードをブレンド無しに戻す */
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			//スタートフラグを無効化
            this->bStartFlg = false;
            break;

			// 設定か確認
        case CAMERA_FIXED_POSITION_D:

			//スタートフラグが有効か確認
            if (this->bStartFlg == TRUE)
			{
				//スタートフラグが有効な場合
				PauseMovieToGraph(this->iTextureTitleHandle, 0);
                SeekMovieToGraph(this->iTextureConfigHandle, 0);
				PauseMovieToGraph(this->iTextureContinueHandle, 0);
				PauseMovieToGraph(this->iTextureDateHandle, 0);
				PauseMovieToGraph(this->iTextureNewgameHandle, 0);
            }

			//モデルのテクスチャをコンフィグテクスチャに設定
            MV1SetTextureGraphHandle(iModelHandle, 1, this->iTextureConfigHandle, true);

			/* 描画ブレンドモードを減算にする */
			SetDrawBlendMode(DX_BLENDMODE_SUB, 0);

			//コンフィグ映像の再生
			PauseMovieToGraph(this->iTextureConfigHandle);

			//コンフィグ映像の再生が終了しているか確認
            if (GetMovieStateToGraph(this->iTextureConfigHandle) == FALSE)
            {
				//コンフィグ映像の再生が終了している場合
				//コンフィグ映像の再生位置を0に設定
                SeekMovieToGraph(this->iTextureConfigHandle, 0);
			}
			/* 描画ブレンドモードをブレンド無しに戻す */
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			//スタートフラグを無効化
            this->bStartFlg = false;
            break;
	}
	// モデルの描画
	MV1DrawModel(iModelHandle);

	/* 描画ブレンドモードを減算にする */
	SetDrawBlendMode(DX_BLENDMODE_SUB, 0);

	//コンティニュー映像の再生
	PlayMovieToGraph(this->iTextureContinueHandle);

	//コンティニュー映像の再生が終了しているか確認
	if (GetMovieStateToGraph(this->iTextureContinueHandle) == FALSE)
    {
		//コンティニュー映像の再生が終了している場合
		//コンティニュー映像の再生位置を0に設定
		SeekMovieToGraph(this->iTextureContinueHandle, 0);
	}
	/* 描画ブレンドモードをブレンド無しに戻す */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}


// 更新
void Screen::Update()
{
	//処理
	Process();

	//描画
	Draw();

}

/* 2025.02.28 石川智也 ファイル作成 */
#include "LargeScreen.h"

// コンストラクタ
LargeScreen::LargeScreen() : PlatformBasic()
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
		this->iModelHandle = ModelListHandle->iGetModel("Object/LargeScreen/LargeScreen");
	}

	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* スクリーンに映る映像 */
		this->iTextureTitleHandle = *ImageList->piGetImage_Movie("Test/TitleLogo");			//タイトル
		this->iTextureNewgameHandle = *ImageList->piGetImage_Movie("Test/Newgame");			//ニューゲーム
		this->iTextureContinueHandle = *ImageList->piGetImage_Movie("Test/Continue");		//コンティニュー
		this->iTextureDateHandle = *ImageList->piGetImage_Movie("Test/Date");				//データ
		this->iTextureConfigHandle = *ImageList->piGetImage_Movie("Test/Config");			//コンフィグ
		this->iTextureStageHandle = *ImageList->piGetImage_Movie("Test/TitleLogo");			//ステージ
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
			if (strncmp(cFrameName, "Large", 5) == 0)
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
LargeScreen::~LargeScreen()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
}

//処理
void LargeScreen::Process()
{
	// 現在のシーンがタイトルシーンか確認
	if (gpSceneServer->GetScene("Title"))
	{
		// タイトルシーンの場合
		//UIカウントによって処理を分岐
		switch (iUICount)
		{
			// カメラ固定位置が初期位置か確認
		case CAMERA_FIXED_POSITION_START:

			// 初期位置の場合
			// 何かボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_ANY))
			{
				// 何かボタンが押された場合
				// Homeフラグを有効化
				this->bHomeFlg = TRUE;

				//UIカウントをポジションAに変更
				iUICount = CAMERA_FIXED_POSITION_A;
			}

			//スタートフラグを有効化か確認
			if (this->bStartFlg == TRUE)
			{
				//スタートフラグが有効な場合
				//タイトル映像の再生位置を0に設定
				SeekMovieToGraph(this->iTextureTitleHandle, 0);
			}

			//モデルのテクスチャをタイトルテクスチャに設定
			MV1SetTextureGraphHandle(iModelHandle, 0, this->iTextureTitleHandle, true);

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
			this->bStartFlg = false;
			break;

			// ポジションAか確認
		case CAMERA_FIXED_POSITION_A:

			// ポジションAの場合
			// 決定ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
			{
				// 決定ボタンが押された場合
				// Homeフラグを無効化
				this->bGameStartFlg = FALSE;

				//Homeフラグを有効化
				this->bHomeFlg = FALSE;

			}
			// 上ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_UP))
			{
				// 上ボタンが押された場合
				// スタートフラグを有効化
				this->bStartFlg = TRUE;

				// bGameStartFlgフラグを有効化
				this->bGameStartFlg = TRUE;

				//Homeフラグを有効か確認
				if (this->bHomeFlg == TRUE)
				{
					//Homeフラグが有効な場合
					//UIカウントをポジションDに変更
					iUICount = CAMERA_FIXED_POSITION_D;
				}

				//Homeフラグが無効か確認
				if (this->bHomeFlg == FALSE)
				{
					//Homeフラグが無効な場合
					//UIカウントをポジションスタートに変更
					iUICount = CAMERA_FIXED_POSITION_A;
				}

			}

			// 下ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DOWN))
			{
				// 下ボタンが押された場合
				// スタートフラグを有効化
				this->bStartFlg = TRUE;

				// bGameStartFlgフラグを有効化
				this->bGameStartFlg = TRUE;

				//Homeフラグを有効か確認
				if (this->bHomeFlg == TRUE)
				{
					//Homeフラグが有効な場合
					//UIカウントをポジションDに変更
					iUICount = CAMERA_FIXED_POSITION_B;
				}

				//Homeフラグが無効か確認
				if (this->bHomeFlg == FALSE)
				{
					//Homeフラグが無効な場合
					//UIカウントをポジションスタートに変更
					iUICount = CAMERA_FIXED_POSITION_A;
				}
			}

			// キャンセルボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
			{
				// キャンセルボタンが押された場合
				//スタートフラグを有効化
				this->bStartFlg = TRUE;


				//bGameStartFlgフラグが無効か確認
				if (this->bGameStartFlg == FALSE)
				{
					//bGameStartFlgフラグが有効な場合
					//bGameStartFlgフラグを無効化
					this->bGameStartFlg = TRUE;
				}

				//Homeフラグが有効か確認
				if (this->bHomeFlg == TRUE)
				{
					//Homeフラグが有効な場合
					//UIカウントをポジションスタートに変更
					iUICount = CAMERA_FIXED_POSITION_START;

					//bGameStartFlgフラグを無効化
					this->bGameStartFlg = FALSE;
				}

				//bGameStartFlgフラグが有効か確認
				if (this->bGameStartFlg == TRUE)
				{
					//bGameStartFlgフラグが有効な場合
					//UIカウントをポジションAに変更
					iUICount = CAMERA_FIXED_POSITION_A;

					//bGameStartFlgフラグを有効化
					this->bHomeFlg = TRUE;
				}
			}

			//スタートフラグが有効か確認
			if (this->bStartFlg == TRUE)
			{
				//スタートフラグが有効な場合
				//ニューゲーム映像の再生位置を0に設定
				SeekMovieToGraph(this->iTextureNewgameHandle, 0);
			}

			//モデルのテクスチャをニューゲームテクスチャに設定
			MV1SetTextureGraphHandle(iModelHandle, 0, this->iTextureNewgameHandle, true);

			//ニューゲーム映像の再生
			PlayMovieToGraph(this->iTextureNewgameHandle);

			//ニューゲーム映像の描写
			DrawGraph(100, -100, this->iTextureNewgameHandle, TRUE);

			//ニューゲーム映像の再生が終了しているか確認
			if (GetMovieStateToGraph(this->iTextureNewgameHandle) == FALSE)
			{
				//ニューゲーム映像の再生が終了している場合
				//ニューゲーム映像の再生位置を0に設定
				SeekMovieToGraph(this->iTextureNewgameHandle, 0);
			}

			//スタートフラグを無効化
			this->bStartFlg = false;
			break;

			// ポジションBか確認
		case CAMERA_FIXED_POSITION_B:

			// ポジションBの場合
			// 決定ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
			{
				// 決定ボタンが押された場合
				// Homeフラグを無効化
				this->bGameStartFlg = FALSE;

				//Homeフラグを有効化
				this->bHomeFlg = FALSE;

			}
			// 上ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_UP))
			{
				// 上ボタンが押された場合
				// スタートフラグを有効化
				this->bStartFlg = TRUE;

				// bGameStartFlgフラグを有効化
				this->bGameStartFlg = TRUE;

				//Homeフラグを有効か確認
				if (this->bHomeFlg == TRUE)
				{
					//Homeフラグが有効な場合
					//UIカウントをポジションDに変更
					iUICount = CAMERA_FIXED_POSITION_A;
				}

				//Homeフラグが無効か確認
				if (this->bHomeFlg == FALSE)
				{
					//Homeフラグが無効な場合
					//UIカウントをポジションスタートに変更
					iUICount = CAMERA_FIXED_POSITION_B;
				}

			}

			// 下ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DOWN))
			{
				// 下ボタンが押された場合
				// スタートフラグを有効化
				this->bStartFlg = TRUE;

				// bGameStartFlgフラグを有効化
				this->bGameStartFlg = TRUE;

				//Homeフラグを有効か確認
				if (this->bHomeFlg == TRUE)
				{
					//Homeフラグが有効な場合
					//UIカウントをポジションDに変更
					iUICount = CAMERA_FIXED_POSITION_C;
				}

				//Homeフラグが無効か確認
				if (this->bHomeFlg == FALSE)
				{
					//Homeフラグが無効な場合
					//UIカウントをポジションスタートに変更
					iUICount = CAMERA_FIXED_POSITION_B;
				}
			}

			// キャンセルボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
			{
				// キャンセルボタンが押された場合
				//スタートフラグを有効化
				this->bStartFlg = TRUE;


				//bGameStartFlgフラグが無効か確認
				if (this->bGameStartFlg == FALSE)
				{
					//bGameStartFlgフラグが有効な場合
					//bGameStartFlgフラグを無効化
					this->bGameStartFlg = TRUE;
				}

				//Homeフラグが有効か確認
				if (this->bHomeFlg == TRUE)
				{
					//Homeフラグが有効な場合
					//UIカウントをポジションスタートに変更
					iUICount = CAMERA_FIXED_POSITION_START;

					//bGameStartFlgフラグを無効化
					this->bGameStartFlg = FALSE;
				}

				//bGameStartFlgフラグが有効か確認
				if (this->bGameStartFlg == TRUE)
				{
					//bGameStartFlgフラグが有効な場合
					//UIカウントをポジションAに変更
					iUICount = CAMERA_FIXED_POSITION_A;

					//bGameStartFlgフラグを有効化
					this->bHomeFlg = TRUE;
				}
			}

			//スタートフラグが有効か確認
			if (this->bStartFlg == TRUE)
			{
				//スタートフラグが有効な場合
				//コンティニュー映像の再生位置を0に設定
				SeekMovieToGraph(this->iTextureContinueHandle, 0);
			}

			//モデルのテクスチャをコンティニューテクスチャに設定
			MV1SetTextureGraphHandle(iModelHandle, 0, this->iTextureContinueHandle, true);

			//コンティニュー映像の再生
			PlayMovieToGraph(this->iTextureContinueHandle);

			//コンティニュー映像の描写
			DrawGraph(100, -100, this->iTextureContinueHandle, TRUE);

			//コンティニュー映像の再生が終了しているか確認
			if (GetMovieStateToGraph(this->iTextureContinueHandle) == FALSE)
			{
				//コンティニュー映像の再生が終了している場合
				//コンティニュー映像の再生位置を0に設定
				SeekMovieToGraph(this->iTextureContinueHandle, 0);
			}

			//スタートフラグを無効化
			this->bStartFlg = false;
			break;

			// ポジションCか確認
		case CAMERA_FIXED_POSITION_C:

			// ポジションCの場合
			// 決定ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
			{
				// 決定ボタンが押された場合
				// Homeフラグを無効化
				this->bHomeFlg = FALSE;
			}

			// 上ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_UP))
			{
				// 上ボタンが押された場合
				// スタートフラグを有効化
				this->bStartFlg = TRUE;

				// Homeフラグを有効化
				this->bHomeFlg = TRUE;

				//UIカウントをポジションBに変更
				iUICount = CAMERA_FIXED_POSITION_B;
			}

			// 下ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DOWN))
			{
				// 下ボタンが押された場合
				// スタートフラグを有効化
				this->bStartFlg = TRUE;

				// Homeフラグを有効化
				this->bHomeFlg = TRUE;

				//UIカウントをポジションDに変更
				iUICount = CAMERA_FIXED_POSITION_D;
			}

			// キャンセルボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
			{
				// キャンセルボタンが押された場合
				//スタートフラグを有効化
				this->bStartFlg = TRUE;

				//Homeフラグを有効化
				this->bHomeFlg = TRUE;

				//UIカウントをポジションスタートに変更
				iUICount = CAMERA_FIXED_POSITION_START;
			}

			//スタートフラグが有効か確認
			if (this->bStartFlg == TRUE)
			{
				//スタートフラグが有効な場合
				//データ映像の再生位置を0に設定
				SeekMovieToGraph(this->iTextureDateHandle, 0);
			}

			//モデルのテクスチャをデータテクスチャに設定
			MV1SetTextureGraphHandle(iModelHandle, 0, this->iTextureDateHandle, true);

			//データ映像の再生
			PlayMovieToGraph(this->iTextureDateHandle);

			//データ映像の描写
			DrawGraph(100, -100, this->iTextureDateHandle, TRUE);

			//データ映像の再生が終了しているか確認
			if (GetMovieStateToGraph(this->iTextureDateHandle) == FALSE)
			{
				//データ映像の再生が終了している場合
				//データ映像の再生位置を0に設定
				SeekMovieToGraph(this->iTextureDateHandle, 0);
			}

			//スタートフラグを無効化
			this->bStartFlg = false;
			break;

			// ポジションDか確認
		case CAMERA_FIXED_POSITION_D:

			// ポジションDの場合
			// 決定ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
			{
				// 決定ボタンが押された場合
				// Homeフラグを無効化
				this->bHomeFlg = FALSE;
			}

			// 上ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_UP))
			{
				// 上ボタンが押された場合
				// スタートフラグを有効化
				this->bStartFlg = TRUE;

				// Homeフラグを有効化
				this->bHomeFlg = TRUE;

				//UIカウントをポジションCに変更
				iUICount = CAMERA_FIXED_POSITION_C;
			}

			// 下ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DOWN))
			{
				// 下ボタンが押された場合
				// スタートフラグを有効化
				this->bStartFlg = TRUE;

				// Homeフラグを有効化
				this->bHomeFlg = TRUE;

				//UIカウントをポジションAに変更
				iUICount = CAMERA_FIXED_POSITION_A;
			}

			// キャンセルボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
			{
				// キャンセルボタンが押された場合
				//スタートフラグを有効化
				this->bStartFlg = TRUE;

				//Homeフラグを有効化
				this->bHomeFlg = TRUE;

				//UIカウントをポジションスタートに変更
				iUICount = CAMERA_FIXED_POSITION_START;
			}

			//スタートフラグが有効か確認
			if (this->bStartFlg == TRUE)
			{
				//スタートフラグが有効な場合
				//コンフィグ映像の再生位置を0に設定
				SeekMovieToGraph(this->iTextureConfigHandle, 0);
			}

			//モデルのテクスチャをコンフィグテクスチャに設定
			MV1SetTextureGraphHandle(iModelHandle, 0, this->iTextureConfigHandle, true);

			//コンフィグ映像の再生
			PlayMovieToGraph(this->iTextureConfigHandle);

			//コンフィグ映像の描写
			DrawGraph(100, -100, this->iTextureConfigHandle, TRUE);

			//コンフィグ映像の再生が終了しているか確認
			if (GetMovieStateToGraph(this->iTextureConfigHandle) == FALSE)
			{
				//コンフィグ映像の再生が終了している場合
				//コンフィグ映像の再生位置を0に設定
				SeekMovieToGraph(this->iTextureConfigHandle, 0);
			}

			//スタートフラグを無効化
			this->bStartFlg = false;
			break;
		}
	}
	else if (gpSceneServer->GetScene("Stage"))
	{
		// 現在のシーンがステージシーン以外の場合
		MV1SetTextureGraphHandle(iModelHandle, 0, this->iTextureStageHandle, true);
		PlayMovieToGraph(this->iTextureStageHandle);
		DrawGraph(100, -100, this->iTextureStageHandle, TRUE);

		if (GetMovieStateToGraph(this->iTextureStageHandle) == FALSE)
		{
			SeekMovieToGraph(this->iTextureStageHandle, 1);
		}
	}
}



// 更新
void LargeScreen::Update()
{
	//処理
	Process();
}

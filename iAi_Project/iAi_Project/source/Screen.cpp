/* 2025.02.28 石川智也 ファイル作成 */
#include "Screen.h"

// コンストラクタ
Screen::Screen() : PlatformBasic()
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
		this->textureTitleHandle = *ImageList->piGetImage_Movie("Test/TitleLogo");			//タイトル
		this->textureNewgameHandle = *ImageList->piGetImage_Movie("Test/Newgame");			//ニューゲーム
		this->textureContinueHandle = *ImageList->piGetImage_Movie("Test/Continue");		//コンティニュー
		this->textureDateHandle = *ImageList->piGetImage_Movie("Test/Date");				//データ
		this->textureConfigHandle = *ImageList->piGetImage_Movie("Test/Config");			//コンフィグ
		this->textureStageHandle = *ImageList->piGetImage_Movie("Test/TitleLogo");			//ステージ
	}

	/* UIカウントを初期化 */
	this->UICount = 0;

	//動画再生フラグを初期化
	this->StartFlg = false;
	this->bHomeFlg = false;

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
	//現在のシーンがタイトルシーンか確認
	if (gpSceneServer->GetScene("Title"))
	{
		//タイトルシーンの場合
		//カメラ固定位置が初期位置か確認
		if (UICount > 0)
		{
			//決定ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
			{
				//決定ボタンが押された場合
				this->bHomeFlg = FALSE;
			}
		}
		if (UICount == 0)
		{
			//初期位置の場合
			//決定ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
			{
				//決定ボタンが押された場合
				this->bHomeFlg = TRUE;
				//UIカウントを増やす
				UICount = 1;
			}
		}
		//初期位置以外か確認
		if ((5 > UICount) || (UICount > 0))
		{
			//初期位置以外の場合
			//上ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_UP))
			{
				//上ボタンが押された場合
				//動画再生フラグを有効化
				this->StartFlg = TRUE;
				this->bHomeFlg = TRUE;
				//UIカウントを増やす
				UICount++;
				//UIカウントがポジションE以上か確認
				if (UICount >= CAMERA_FIXED_POSITION_E)
				{
					//UIカウントがポジションE以上の場合
					//UIカウントをポジションAに設定
					UICount = 1;
				}
			}

			//下ボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DOWN))
			{
				//下ボタンが押された場合
				//動画再生フラグを有効化
				this->StartFlg = TRUE;
				this->bHomeFlg = TRUE;
				//UIカウントを減らす
				UICount--;
				//UIカウントがポジションA未満か確認
				if (UICount < 1)
				{
					//UIカウントがポジションA未満の場合
					//UIカウントをポジションDに設定
					UICount = CAMERA_FIXED_POSITION_D;

				}
			}
			//キャンセルボタンが押されたか確認
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
{
				//キャンセルボタンが押された場合
				if (this->bHomeFlg ==TRUE)
				{
					//UIカウントを初期化
					UICount = 0;
					this->StartFlg = TRUE;
				}
				if(this->bHomeFlg == FALSE)
				{
					//UIカウントをポジションAに設定
					UICount = 1;

				}

				this->bHomeFlg = TRUE;
			}
		}
		//カメラ固定位置が初期位置か確認
		if (UICount == 0)
		{
			//初期位置の場合
			//動画再生フラグが有効か確認
			if (this->StartFlg == TRUE)
			{
				//動画再生フラグが有効の場合
				//ムービーの再生時間を初期化する
				SeekMovieToGraph(this->textureTitleHandle, 0);
			}
			//モデルのテクスチャをTitleHandleに設定
			MV1SetTextureGraphHandle(iModelHandle, 1, this->textureTitleHandle, true);
	/* タイトルロゴを再生 */
	PlayMovieToGraph(this->textureTitleHandle);

	/* ムービーを描写 */
	DrawGraph(100, -100, this->textureTitleHandle, TRUE);

	/* 再生が終了しているか確認 */
	if (GetMovieStateToGraph(this->textureTitleHandle) == FALSE)
	{
		// 再生が終了している場合
		/* ムービーの再生時間を初期化する */
		SeekMovieToGraph(this->textureTitleHandle, 0);
	}
			//動画再生フラグを無効化
			this->StartFlg = false;
		}
		//カメラ固定位置がポジションAか確認
		if (UICount == 1)
		{
			//ポジションAの場合
			//動画再生フラグが有効か確認
			if (this->StartFlg == TRUE)
			{
				//動画再生フラグが有効の場合
				//ムービーの再生時間を初期化する
				SeekMovieToGraph(this->textureNewgameHandle, 0);
			}
			//モデルのテクスチャをNewgameHandleに設定
			MV1SetTextureGraphHandle(iModelHandle, 1, this->textureNewgameHandle, true);
			/* タイトルロゴを再生 */
			PlayMovieToGraph(this->textureNewgameHandle);
			/* ムービーを描写 */
			DrawGraph(100, -100, this->textureNewgameHandle, TRUE);
			/* 再生が終了しているか確認 */
			if (GetMovieStateToGraph(this->textureNewgameHandle) == FALSE)
			{
				// 再生が終了している場合
				/* ムービーの再生時間を初期化する */
				SeekMovieToGraph(this->textureNewgameHandle, 0);
			}
			//動画再生フラグを無効化
			this->StartFlg = false;
		}
		//カメラ固定位置がポジションBか確認
		if (UICount == 2)
		{
			//ポジションBの場合
			//動画再生フラグが有効か確認
			if (this->StartFlg == TRUE)
			{
				//動画再生フラグが有効の場合
				//ムービーの再生時間を初期化する
				SeekMovieToGraph(this->textureContinueHandle, 0);
			}
			//モデルのテクスチャをContinueHandleに設定
			MV1SetTextureGraphHandle(iModelHandle, 1, this->textureContinueHandle, true);
			/* タイトルロゴを再生 */
			PlayMovieToGraph(this->textureContinueHandle);
			/* ムービーを描写 */
			DrawGraph(100, -100, this->textureContinueHandle, TRUE);
			/* 再生が終了しているか確認 */
			if (GetMovieStateToGraph(this->textureContinueHandle) == FALSE)
			{
				// 再生が終了している場合
				/* ムービーの再生時間を初期化する */
				SeekMovieToGraph(this->textureContinueHandle, 0);
			}
			//動画再生フラグを無効化
			this->StartFlg = false;
		}
		//カメラ固定位置がポジションCか確認
		if (UICount == 3)
		{
			//ポジションCの場合
			//動画再生フラグが有効か確認
			if (this->StartFlg == TRUE)
			{
				//動画再生フラグが有効の場合
				//ムービーの再生時間を初期化する
				SeekMovieToGraph(this->textureDateHandle, 0);
			}
			//モデルのテクスチャをDateHandleに設定
			MV1SetTextureGraphHandle(iModelHandle, 1, this->textureDateHandle, true);
			/* タイトルロゴを再生 */
			PlayMovieToGraph(this->textureDateHandle);
			/* ムービーを描写 */
			DrawGraph(100, -100, this->textureDateHandle, TRUE);
			/* 再生が終了しているか確認 */
			if (GetMovieStateToGraph(this->textureDateHandle) == FALSE)
			{
				// 再生が終了している場合
				/* ムービーの再生時間を初期化する */
				SeekMovieToGraph(this->textureDateHandle, 0);
			}
			//動画再生フラグを無効化
			this->StartFlg = false;
		}
		//カメラ固定位置がポジションDか確認
		if (UICount == 4)
		{
			//ポジションDの場合
			//動画再生フラグが有効か確認
			if (this->StartFlg == TRUE)
			{
				//動画再生フラグが有効の場合
				//ムービーの再生時間を初期化する
				SeekMovieToGraph(this->textureConfigHandle, 0);
			}
			//モデルのテクスチャをConfigHandleに設定
			MV1SetTextureGraphHandle(iModelHandle, 1, this->textureConfigHandle, true);
			/* タイトルロゴを再生 */
			PlayMovieToGraph(this->textureConfigHandle);
			/* ムービーを描写 */
			DrawGraph(100, -100, this->textureConfigHandle, TRUE);
			/* 再生が終了しているか確認 */
			if (GetMovieStateToGraph(this->textureConfigHandle) == FALSE)
			{
				// 再生が終了している場合
				/* ムービーの再生時間を初期化する */
				SeekMovieToGraph(this->textureConfigHandle, 0);
			}
			//動画再生フラグを無効化
			this->StartFlg = false;
		}
	}
	//現在のシーンがステージシーン以外か確認
	else if (gpSceneServer->GetScene("Stage"))
	{
		//ステージシーン以外の場合
		//モデルのテクスチャをStageHandleに設定
		MV1SetTextureGraphHandle(iModelHandle, 1, this->textureStageHandle, true);
		/* タイトルロゴを再生 */
		PlayMovieToGraph(this->textureStageHandle);
		/* ムービーを描写 */
		DrawGraph(100, -100, this->textureStageHandle, TRUE);
		/* 再生が終了しているか確認 */
		if (GetMovieStateToGraph(this->textureStageHandle) == FALSE)
		{
			// 再生が終了している場合
			/* ムービーの再生時間を初期化する */
			SeekMovieToGraph(this->textureStageHandle, 1);
		}
	}
}


// 更新
void Screen::Update()
{
	//処理
	Process();
}

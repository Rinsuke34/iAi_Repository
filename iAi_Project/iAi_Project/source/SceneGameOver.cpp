/* 2025.02.20 ファイル作成 駒沢風助 */

#include "SceneGameOver.h"

/* シーン"ゲームオーバー"クラスの定義 */

// コンストラクタ
SceneGameOver::SceneGameOver() : SceneBase("GameOver", 200, true)
{
	/* データリスト取得 */
	{
		/* "ゲーム状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList				= dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 画像取得 */
		this->piGrHandle_GameOver				= ImageList->piGetImage_Movie("GameOver/UI_GameOver");

		/* ウィンドウ(リトライ) */
		this->piGrHandle_Window_GameOver		= ImageList->piGetImage("GameOver/UI_Window_GameOver");

		/* ウィンドウ(リトライ警告) */
		this->piGrHandle_Window_GameOverCheck	= ImageList->piGetImage("GameOver/UI_Window_GameOver_Check");

		/* スキップ確認ウィンドウ_ボタン */
		this->apiGrHandle_SkipWindow_Yes[0]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_Yes_Selected");
		this->apiGrHandle_SkipWindow_Yes[1]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_Yes_NotSelected");
		this->apiGrHandle_SkipWindow_No[0]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_No_Selected");
		this->apiGrHandle_SkipWindow_No[1]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_No_NotSelected");
	}

	/* 初期化 */
	this->iBlendAlpha	= 0;		// 描写する画像のアルファ値(0～255)
	this->iDrawPhase	= 0;		// 描写フェイズ(0:ゲームオーバー, 1:リトライ確認, 2:リトライ最終確認)
	this->bSelectYes	= false;	// YESを選択中であるか(スキップ画面)
}

// 計算
void SceneGameOver::Process()
{
	/* アルファブレンド値を加算 */
	this->iBlendAlpha += FADE_ALPHA_CHANGE_SPEED;

	/* アルファブレンド値が最大値(255)を超えているか確認 */
	if (this->iBlendAlpha > ALPHA_MAX)
	{
		// 最大値を超えている場合
		/* 最大値を超えないように補正を行う */
		this->iBlendAlpha = ALPHA_MAX;

		/* "決定"が入力されたか確認 */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
		{
			// "決定"が入力されたならば
			/* "決定"のSEを再生 */
			gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

			/* 描写フェイズに応じた処理 */
			switch (this->iDrawPhase)
			{
				/* ゲームオーバー */
				case 0:
					/* 描写フェイズを"リトライ確認"に設定 */
					this->iDrawPhase = 1;
					break;

				/* リトライ確認 */
				case 1:
					/* YESを選択中であるか確認 */
					if (this->bSelectYes == true)
					{
						// YESを選択中である場合
						/* ゲーム状態を"リセット"に設定 */
						this->StageStatusList->SetGameStatus(GAMESTATUS_RESET);

						/* このシーンの削除フラグを有効にする */
						this->bDeleteFlg = true;
					}
					else
					{
						// YESを選択中でない場合
						/* 描写フェイズを"リトライ最終確認"に設定 */
						this->iDrawPhase = 2;

						/* NOを選択中の状態にする */
						this->bSelectYes = false;
					}
					break;

				/* リトライ最終確認 */
				case 2:
					/* YESを選択中であるか確認 */
					if (this->bSelectYes == true)
					{
						// YESを選択中である場合
						/* ロードシーン追加フラグを有効化 */
						gpSceneServer->SetAddLoadSceneFlg(true);

						/* 現行シーン削除フラグを有効化 */
						gpSceneServer->SetDeleteCurrentSceneFlg(true);

						/* シーン"タイトル"を追加 */
						gpSceneServer->AddSceneReservation(new SceneAddTitleSetup());
					}
					else
					{
						// YESを選択中でない場合
						/* 描写フェイズを"リトライ確認"に設定 */
						this->iDrawPhase = 1;
					}
					break;
			}
		}

		/* "左"が入力されたか確認 */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT))
		{
			// 入力された場合
			/* "カーソル移動"のSEを再生 */
			gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

			/* YESを選択中の状態にする */
			this->bSelectYes = true;
		}

		/* "右"が入力されたか確認 */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT))
		{
			// 入力された場合
			/* "カーソル移動"のSEを再生 */
			gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

			/* NOを選択中の状態にする */
			this->bSelectYes = false;
		}
	}
}

// 描画
void SceneGameOver::Draw()
{
	/* 描写ブレンドモードを"アルファブレンド"に設定 */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->iBlendAlpha);

	/* 画面全体を黒色で描写 */
	DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);

	/* 描写ブレンドモードを"ノーブレンド"に設定 */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	/* アルファブレンド値が最大値(255)を超えているか確認 */
	if (this->iBlendAlpha >= ALPHA_MAX)
	{
		// 最大値を超えている場合
		/* 描写フェイズに応じた処理 */
		switch (this->iDrawPhase)
		{
			/* ゲームオーバー */
			case 0:
				/* ゲームオーバー画面を再生 */
				PlayMovieToGraph(*this->piGrHandle_GameOver);

				/* "ゲームオーバー"を描写 */
				DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->piGrHandle_GameOver, TRUE);

				/* 再生が終了しているか確認 */
				if (GetMovieStateToGraph(*this->piGrHandle_GameOver) == FALSE)
				{
					// 再生が終了している場合
					/* ムービーの再生時間を初期化する */
					SeekMovieToGraph(*this->piGrHandle_GameOver, 0);
				}
				break;

			/* リトライ確認 */
			case 1:
				/* "リトライ確認"を描写 */
				DrawGraph(570, 270, *this->piGrHandle_Window_GameOver, TRUE);
				break;

			/* リトライ最終確認 */
			case 2:
				/* "リトライ最終確認"を描写 */
				DrawGraph(570, 270, *this->piGrHandle_Window_GameOverCheck, TRUE);
				break;
		}
	}

	/* 描写フェイズが"ゲームオーバー"以外であるか確認 */
	if (this->iDrawPhase != 0)
	{
		// "ゲームオーバー"以外である場合
		/* YESが選択中であるか確認 */
		if (this->bSelectYes == true)
		{
			// YESが選択中の場合
			/* YESを選択中として描写 */
			DrawGraph(690, 560, *this->apiGrHandle_SkipWindow_Yes[0], TRUE);

			/* NOを非選択中として描写 */
			DrawGraph(1020, 560, *this->apiGrHandle_SkipWindow_No[1], TRUE);
		}
		else
		{
			// YESが選択中でない場合
			/* YESを非選択中として描写 */
			DrawGraph(690, 560, *this->apiGrHandle_SkipWindow_Yes[1], TRUE);

			/* NOを選択中として描写 */
			DrawGraph(1020, 560, *this->apiGrHandle_SkipWindow_No[0], TRUE);
		}
	}
}

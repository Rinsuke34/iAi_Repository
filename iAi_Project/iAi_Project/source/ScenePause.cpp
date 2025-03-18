/* 2025.03.05 ファイル作成 駒沢風助 */

#include "ScenePause.h"

/* 一時停止クラスの定義 */
// コンストラクタ
ScenePause::ScenePause() : SceneBase("Pause", 450, true)
{
	/* データリスト取得 */
	{
		/* "ステージ状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 矢印 */
		this->piGrHandle_Arrow = ImageList->piGetImage("Test/Sign");
	}

	/* 初期化 */
	this->iSelectItem	= PAUSE_MANU_CONTINUE;
}

// 計算
void ScenePause::Process()
{
	/* "決定"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		// 入力されている場合
		/* 選択中の項目によって処理を分岐 */
		switch (this->iSelectItem)
		{
			/* 続ける */
			case PAUSE_MANU_CONTINUE:
				/* このシーンの削除フラグを有効にする */
				this->bDeleteFlg = true;
				break;

			/* 最初から */
			case PAUSE_MANU_RESTART:
				/* ゲーム状態を"リセット"に変更する */
				this->StageStatusList->SetGameStatus(GAMESTATUS_RESET);

				/* このシーンの削除フラグを有効にする */
				this->bDeleteFlg = true;
				break;

			/* オプション */
			case PAUSE_MANU_OPTION:
				/* シーン"オプション"を追加 */
				gpSceneServer->AddSceneReservation(new SceneOption());
				break;

			/* タイトルへ */
			case PAUSE_MANU_TITLE:
				/* ロード画面追加フラグを有効化 */
				gpSceneServer->SetAddLoadSceneFlg(true);

				/* 現行シーン削除フラグを有効化 */
				gpSceneServer->SetDeleteCurrentSceneFlg(true);

				/* シーン"タイトル"を追加 */
				gpSceneServer->AddSceneReservation(new SceneAddTitleSetup());
				break;
		}

		return;
	}

	/* "キャンセル"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
	{
		// 入力されている場合
		/* このシーンの削除フラグを有効にする */
		this->bDeleteFlg = true;

		return;
	}

	/* "上"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
	{
		// 入力されている場合
		/* 選択項目を上に進める */
		this->iSelectItem -= 1;
	}

	/* "下"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
	{
		// 入力されている場合
		/* 選択項目を下に進める */
		this->iSelectItem += 1;
	}

	/* 選択中の項目の番号を範囲内に収める*/
	if (this->iSelectItem < 0)
	{
		this->iSelectItem = 0;
	}
	else if (this->iSelectItem >= PAUSE_MANU_MAX)
	{
		this->iSelectItem = PAUSE_MANU_MAX - 1;
	}
}

// 描画
void ScenePause::Draw()
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

	/* 選択肢描写 */
	{
		/* 続ける */
		DrawFormatStringToHandle(SCREEN_SIZE_WIDE / 2 - 100, SCREEN_SIZE_HEIGHT / 2 - 100, GetColor(255, 255, 255), giFontHandle_Small, "続ける");

		/* 最初から */
		DrawFormatStringToHandle(SCREEN_SIZE_WIDE / 2 - 100, SCREEN_SIZE_HEIGHT / 2 - 50, GetColor(255, 255, 255), giFontHandle_Small, "最初から");

		/* オプション */
		DrawFormatStringToHandle(SCREEN_SIZE_WIDE / 2 - 100, SCREEN_SIZE_HEIGHT / 2, GetColor(255, 255, 255), giFontHandle_Small, "オプション");

		/* タイトルへ */
		DrawFormatStringToHandle(SCREEN_SIZE_WIDE / 2 - 100, SCREEN_SIZE_HEIGHT / 2 + 50, GetColor(255, 255, 255), giFontHandle_Small, "タイトルへ");
	}

	/* 矢印描写 */
	{
		/* 矢印の描写 */
		DrawGraph(SCREEN_SIZE_WIDE / 2 - 150, SCREEN_SIZE_HEIGHT / 2 - 100 + this->iSelectItem * 50, *this->piGrHandle_Arrow, TRUE);
	}
}

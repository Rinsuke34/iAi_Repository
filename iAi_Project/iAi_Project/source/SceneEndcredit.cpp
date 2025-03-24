/* 2025.03.24 ファイル追加 駒沢風助 */

#include "SceneEndcredit.h"

/* シーン"エンドクレジット"の定義 */
// コンストラクタ
SceneEndcredit::SceneEndcredit() : SceneBase("Endcredit", 500, true)
{
	/* データリスト取得 */
	{
		/* "オプション設定管理"を取得 */
		this->OptionList = dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));
	}

	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 決定アイコン(0:コントローラー/1:キーボード) */
		this->piGrHandle_Icon_Button_Select[0] = ImageList->piGetImage("Input_Icon/XBOX/xbox_button_a");
		this->piGrHandle_Icon_Button_Select[1] = ImageList->piGetImage("Input_Icon/Keyboard/keyboard_z");

		/* ホールドアイコン */
		this->piGrHandle_Icon_Hold = ImageList->piGetImage("Conversation/HoldTimer");

		/* エンドクレジット */
		this->piGrhandle_EndCredit = ImageList->piGetImage("Endcredit/Endcredit");
	}

	/* 初期化 */
	this->iElapsedTime		= 0;	// 経過時間
	this->iScrollEndTime	= 0;	// スクロール終了時間
	this->iHoldTimer		= 0;	// 長押し時間

	/* 終了時間を算出 */
	{
		/* エンドクレジット画像の高さを取得 */
		int iSizeX, iSizeY;
		GetGraphSize(*this->piGrhandle_EndCredit, &iSizeX, &iSizeY);

		/* スクロール終了時間を算出 */
		this->iScrollEndTime = iSizeY - SCREEN_SIZE_HEIGHT;
	}
}

// デストラクタ
SceneEndcredit::~SceneEndcredit()
{
	/* シーン"タイトル画面"を追加 */
	gpSceneServer->AddSceneReservation(new SceneAddTitleSetup());
}

// 計算
void SceneEndcredit::Process()
{
	/* "決定"がホールド入力されているか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_HOLD, UI_DECID))
	{
		// 入力されている場合
		/* 長押し時間を加算 */
		this->iHoldTimer += 1;

		/* 長押し時間が一定時間を超えたか確認 */
		if (this->iHoldTimer >= 60)
		{
			// 一定時間を超えた場合
			/* シーンの削除フラグを有効にする */
			this->bDeleteFlg = true;
		}
	}
	else
	{
		// 入力されていない場合
		/* 長押し時間をリセット */
		this->iHoldTimer = 0;
	}

	/* スクロール終了時間を超えているか確認 */
	if (this->iElapsedTime >= this->iScrollEndTime)
	{
		// 超えている場合
		/* 経過時間をスクロール終了時間に設定 */
		this->iElapsedTime = this->iScrollEndTime;
	}
	else
	{
		// 超えていない場合
		/* 経過時間を加算する */
		this->iElapsedTime += 1;
	}
}

// 描画
void SceneEndcredit::Draw()
{
	/* エンドクレジット描写 */
	DrawGraph(0, -this->iElapsedTime, *this->piGrhandle_EndCredit, FALSE);

	/* キーボード描写であるか確認 */
	int iDrawTypeNo = 0;
	if (OptionList->bGetOperation_Keyboard() == true)
	{
		// キーボード描写である場合
		/* 描写タイプ番号をキーボード描写に設定 */
		iDrawTypeNo = 1;
	}
	else
	{
		// キーボード描写でない場合
		/* 描写タイプ番号をコントローラー描写に設定 */
		iDrawTypeNo = 0;
	}

	/* Aボタン描写 */
	DrawGraph(1820, 980, *this->piGrHandle_Icon_Button_Select[iDrawTypeNo], TRUE);
	double dComboTimerPercent = (static_cast<double>(this->iHoldTimer / 60.f) * 100.0);
	DrawCircleGauge(1820 + 32, 980 + 32, dComboTimerPercent, *this->piGrHandle_Icon_Hold);
}

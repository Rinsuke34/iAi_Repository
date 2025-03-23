/* 2025.03.22 ファイル作成 駒沢風助 */

#include "SceneUi_Time.h"

/* UI(時間)クラスの定義 */
// コンストラクタ
SceneUi_Time::SceneUi_Time() : SceneBase("UI_Time", 106, false)
{
	/* データリスト取得 */
	{
		/* "ゲーム状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* テキストフレーム */
		this->piGrHandle_Text_Frame = ImageList->piGetImage("UI_Player_Blood/UI_Blood_Timer_Frame");
	}
}

// 計算
void SceneUi_Time::Process()
{
	/* ゲーム状態が"ゲーム実行"以外であるならシーンを削除 */
	if (this->StageStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
		return;
	}
	/* ステージ開始からの経過時間を取得 */
	// ※停止時間も含める
	int iElapsedTime = GetNowCount() - this->StageStatusList->iGetStartTime() - this->StageStatusList->iGetStopTotalTime();

	/* 現在の経過時間の分の値を取得 */
	this->iTimeMinute = iElapsedTime / 1000 / 60;

	/* 現在の経過時間の秒の値を取得 */
	this->iTimeSecond = iElapsedTime / 1000 % 60;

	/* 現在の経過時間の少数秒の値を取得 */
	this->iTimeFractionalSecond = iElapsedTime % 1000 / 10;
}

// 描画
void SceneUi_Time::Draw()
{
	/* テキストフレームを描写 */
	DrawGraph(60, 35, *this->piGrHandle_Text_Frame, true);

	/* 現在の経過時間を描写 */
	DrawFormatStringToHandle(60, 35, GetColor(0, 0, 0), giFontHandle_Medium, "%02d'%02d''%02d", this->iTimeMinute, this->iTimeSecond, this->iTimeFractionalSecond);
}

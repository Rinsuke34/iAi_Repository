/* 2025.02.11 ファイル作成 駒沢風助 */

#include "SceneUi_Blood.h"

/* UI(ブラッド(ゲーム内通貨))クラスの定義 */
// コンストラクタ
SceneUi_Blood::SceneUi_Blood() : SceneBase("UI_Blood", 104, false)
{
	/* データリスト取得 */
	{
		/* "ゲーム内リソース管理"を取得 */
		this->GameResourceList	= dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));

		/* "ステージ状態管理"を取得 */
		this->StageStatusList	= dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* ブラッドアイコン */
		this->piGrHandle_Blood_Icon		= ImageList->piGetImage("UI_Player_Blood/Blood");

		/* テキストフレーム */
		this->piGrHandle_Text_Frame		= ImageList->piGetImage("UI_Player_Blood/UI_Blood_Timer_Frame");
	}
}

// 計算
void SceneUi_Blood::Process()
{
	/* ゲーム状態が"ゲーム実行"以外であるならシーンを削除 */
	if (this->StageStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
		return;
	}
}

// 描画
void SceneUi_Blood::Draw()
{
	/* テキストフレームを描写 */
	DrawGraph(1470, 35, *this->piGrHandle_Text_Frame, true);

	/* ブラッドアイコンを描写 */
	DrawGraph(1470, 35, *this->piGrHandle_Blood_Icon, true);

	/* 現在のブラッドを描写 */
	DrawFormatStringToHandle(1470 + 64, 35, GetColor(255, 255, 255), giFontHandle_Medium, "%d", this->GameResourceList->iGetHaveBlood());
}

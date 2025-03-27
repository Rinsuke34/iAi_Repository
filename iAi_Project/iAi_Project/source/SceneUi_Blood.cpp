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

		/* "プレイヤー状態管理"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}

	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* ブラッドアイコン */
		this->piGrHandle_Blood_Icon					= ImageList->piGetImage("UI_Player_Blood/Blood");

		/* テキストフレーム */
		this->piGrHandle_Text_Frame					= ImageList->piGetImage("UI_Player_Blood/UI_Blood_Timer_Frame");

		/* テキストフレーム(倍率用) */
		this->piGrHandle_Text_Frame_Magnification	= ImageList->piGetImage("UI_Player_Blood/UI_Bairitu_Frame");
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
	DrawGraph(1470, 35, *this->piGrHandle_Text_Frame, TRUE);

	/* ブラッドアイコンを描写 */
	DrawGraph(1470, 35, *this->piGrHandle_Blood_Icon, TRUE);

	/* 現在のブラッドを描写 */
	DrawFormatStringToHandle(1470 + 64, 35, GetColor(255, 255, 255), giFontHandle_Medium, "%d", this->GameResourceList->iGetHaveBlood());

	/* プレイヤーのコンボによる取得倍率を描写 */
	int iComboRank		= PlayerStatusList->iGetPlayerComboRunk();

	/* コンボランクが"無し"以外であるか確認 */
	if (iComboRank != COMBO_RANK_NONE)
	{
		// "無し"以外である場合
		/* コンボによる取得倍率を取得 */
		float fBloodMagnification = 1.f + static_cast<float>(COMBO_RANK_MAX - iComboRank) / COMBO_RANK_MAX;

		/* テキストフレーム(倍率用)を描写 */
		DrawExtendGraph(1470, 99, 1470 + 165, 99 + 64, *this->piGrHandle_Text_Frame_Magnification, TRUE);

		/* コンボによる取得倍率を描写 */
		DrawFormatStringToHandle(1470, 99, GetColor(255, 255, 255), giFontHandle_Medium, "×%.1f", fBloodMagnification);
	}
}


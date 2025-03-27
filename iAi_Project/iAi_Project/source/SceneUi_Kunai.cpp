/* 2025.01.28 ファイル作成 駒沢風助 */

#include "SceneUi_Kunai.h"

/* UI(クナイ)クラスの定義 */

// コンストラクタ
SceneUi_Kunai::SceneUi_Kunai() : SceneBase("UI_Kunai", 102, false)
{
	/* データリスト取得 */
	{
		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "ゲーム状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* クナイフレーム */
		this->piGrHandle_Kunai_Frame = ImageList->piGetImage("UI_Player_Kunai/UI_Player_Kunai");
	}
}

// 計算
void SceneUi_Kunai::Process()
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
void SceneUi_Kunai::Draw()
{
	/* クナイフレーム描写 */
	DrawGraph(60, 765, *this->piGrHandle_Kunai_Frame, true);

	/* 文字枠の補正座標 */
	st2DPosition astStringCorrectionPos[8];
	astStringCorrectionPos[0] = { -2,	-2 };
	astStringCorrectionPos[1] = { 0,	-2 };
	astStringCorrectionPos[2] = { +2,	-2 };
	astStringCorrectionPos[3] = { -2,	0 };
	astStringCorrectionPos[4] = { +2,	0 };
	astStringCorrectionPos[5] = { -2,	+2 };
	astStringCorrectionPos[6] = { 0,	+2 };
	astStringCorrectionPos[7] = { +2,	+2 };

	/* 文字描写(枠) */
	for (int i = 0; i < 8; i++)
	{
		/* 現在のクナイの所持本数を描写 */
		DrawFormatStringToHandle(95 + astStringCorrectionPos[i].ix, 785 + astStringCorrectionPos[i].iy, GetColor(255, 255, 255), giFontHandle_Large, "%d", this->PlayerStatusList->iGetNowHaveKunai());
	}

	/* 文字描写(中心) */
	DrawFormatStringToHandle(95, 785, GetColor(0, 0, 0), giFontHandle_Large, "%d", this->PlayerStatusList->iGetNowHaveKunai());
}

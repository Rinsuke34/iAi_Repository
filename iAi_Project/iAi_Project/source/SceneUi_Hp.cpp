/* 2025.01.28 ファイル作成 駒沢風助 */

#include "SceneUi_Hp.h"

/* UI(HP)クラスの定義 */

// コンストラクタ
SceneUi_Hp::SceneUi_Hp() : SceneBase("UI_Hp", 101, false)
{
	/* データリスト取得 */
	{
		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "ステージ状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList	= dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* HPフレーム */
		this->piGrHandle_Hp_Frame	= ImageList->piGetImage("UI_Player_HP/UI_Player_HP_frame");

		/* HPゲージ */
		this->piGrHandle_Hp_Gauge	= ImageList->piGetImage("UI_Player_HP/UI_Player_HP_gauge");
	}
}

// 計算
void SceneUi_Hp::Process()
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
void SceneUi_Hp::Draw()
{
	/* HPフレーム描画(仮) */
	DrawGraph(60, 880, *this->piGrHandle_Hp_Frame, TRUE);

	/* HPゲージ描写 */
	for (int i = 0; i < this->PlayerStatusList->iGetPlayerNowHp(); i++)
	{
		DrawGraph(245 + (25 * i), 880 + 40, *this->piGrHandle_Hp_Gauge, TRUE);
	}
}

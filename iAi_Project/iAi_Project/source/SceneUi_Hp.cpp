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

		/* "ゲーム状態管理"を取得 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
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

// デストラクタ
SceneUi_Hp::~SceneUi_Hp()
{

}

// 計算
void SceneUi_Hp::Process()
{
	/* ゲーム状態が"ゲーム実行"以外であるならシーンを削除 */
	if (this->GameStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
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
	DrawGraph(100, 740, *this->piGrHandle_Hp_Frame, TRUE);

	/* HPゲージ描写 */
	for (int i = 0; i < this->PlayerStatusList->iGetPlayerNowHp(); i++)
	{
		DrawGraph(100 + 185 + (25 * i), 740 + 40, *this->piGrHandle_Hp_Gauge, TRUE);
	}

	/* 現在HP */
	DrawFormatString(500, 700 + 16 * 0, GetColor(255, 255, 255), "現在HP : %d", this->PlayerStatusList->iGetPlayerNowHp());

	/* 最大HP */
	DrawFormatString(500, 700 + 16 * 1, GetColor(255, 255, 255), "最大HP : %d", this->PlayerStatusList->iGetPlayerMaxHp());

	/* 無敵時間 */
	DrawFormatString(500, 700 + 16 * 2, GetColor(255, 255, 255), "無敵時間 : %d", this->PlayerStatusList->iGetPlayerNowInvincibleTime());
}

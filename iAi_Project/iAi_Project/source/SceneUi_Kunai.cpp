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
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
	}

	/* 画像読み込み */
	{
		/* クナイアイコン */
		this->iCgHandle_Kunai_Icon = LoadGraph("resource/ImageData/UI_Player_Kunai/UI_Player_Kunai.png");

		/* クナイ所持数(仮) */
		this->iCgHandle_Kunai_No[0] = LoadGraph("resource/ImageData/UI_Player_Kunai/UI_Player_Kunai_three.png");
	}
}

// デストラクタ
SceneUi_Kunai::~SceneUi_Kunai()
{
	/* 画像削除 */
	{
		/* クナイアイコン */
		DeleteGraph(this->iCgHandle_Kunai_Icon);

		/* クナイ所持数(仮) */
		DeleteGraph(this->iCgHandle_Kunai_No[0]);
	}
}

// 計算
void SceneUi_Kunai::Process()
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
void SceneUi_Kunai::Draw()
{
	/* クナイアイコン描画(仮) */
	DrawGraph(100, 620, this->iCgHandle_Kunai_Icon, TRUE);
}

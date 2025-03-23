/* 2025.02.11 ファイル作成 駒沢風助 */

#include "SceneUi_Edit.h"

/* UI(エディット)クラスの定義 */
// コンストラクタ
SceneUi_Edit::SceneUi_Edit() : SceneBase("UI_Edit", 105, false)
{
	/* データリスト取得 */
	{
		/* "ゲーム状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "ゲーム内リソース管理"を取得 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}
}

// 計算
void SceneUi_Edit::Process()
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
void SceneUi_Edit::Draw()
{
	/* エディット内容を描写 */
	for (int i = 0; i < EDIT_MAX; i++)
	{
		/* エディットフレーム描写 */
		DrawExtendGraph(150 + 75 * i, 777, 150 + 75 * i + 128, 777 + 128, *this->GameResourceList->piGetGrHandle_EditFrame(this->GameResourceList->stGetNowEditData(i).iEditRank), TRUE);

		/* エディット効果描写 */
		DrawExtendGraph(150 + 75 * i, 777, 150 + 75 * i + 128, 777 + 128, *this->GameResourceList->piGetGrHandle_EditEffect(this->GameResourceList->stGetNowEditData(i).iEditEffect), TRUE);
	}
}

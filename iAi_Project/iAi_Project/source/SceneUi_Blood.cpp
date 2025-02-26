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
}

// デストラクタ
SceneUi_Blood::~SceneUi_Blood()
{

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
	/* 現在のブラッドを描写(仮) */
	DrawFormatString(1600, 800 + 16 * 0, GetColor(255, 255, 255), "現在のBLOOD : %d", this->GameResourceList->iGetHaveBlood());
}

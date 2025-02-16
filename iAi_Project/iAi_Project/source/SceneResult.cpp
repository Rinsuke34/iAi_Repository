/* 2025.02.16 ファイル作成 駒沢風助 */

#include "SceneResult.h"

/* シーン"リザルト"クラスの定義 */

// コンストラクタ
SceneResult::SceneResult() : SceneBase("Edit", 80, true)
{
	/* データリスト取得 */
	{
		/* "ゲーム状態管理"を取得 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));

		/* "ゲーム内リソース管理"を取得 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}
}

// デストラクタ
SceneResult::~SceneResult()
{

}

// 初期化
void SceneResult::Initialization()
{

}

// 計算
void SceneResult::Process()
{
	/* ゲーム状態を確認 */
	int iGameStatus = this->GameStatusList->iGetGameStatus();

	/* ゲーム状態に応じて処理を変更 */
	switch (iGameStatus)
	{
		/* "リザルト"状態 */
		case GAMESTATUS_RESULT:
			/* 決定が入力されたら */
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
			{
				/* ゲーム状態を"エディット"に変更する */
				this->GameStatusList->SetGameStatus(GAMESTATUS_EDIT);
			}
			break;

		/* 該当無し */
		default:
			/* シーンの削除フラグを有効にする */
			this->bDeleteFlg = true;
			break;
	}
}

// 描画
void SceneResult::Draw()
{
	DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "決定			：エディット画面へ");
}

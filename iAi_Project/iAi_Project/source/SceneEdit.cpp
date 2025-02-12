/* 2025.01.19 ファイル作成 駒沢風助 */

#include "SceneEdit.h"

/* シーン"エディット"クラスの定義 */

// コンストラクタ
SceneEdit::SceneEdit() : SceneBase("Edit", 100, true)
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
SceneEdit::~SceneEdit()
{

}

// 初期化
void SceneEdit::Initialization()
{

}

// 計算
void SceneEdit::Process()
{
	/* ゲーム状態を確認 */
	int iGameStatus = this->GameStatusList->iGetGameStatus();

	/* ゲーム状態に応じて処理を変更 */
	switch (iGameStatus)
	{
		/* "エディット"状態 */
		case GAMESTATUS_EDIT:
			/* 決定が入力されたら */
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
			{
				/* ゲーム状態を"次のステージへ遷移"に変更する */
				this->GameStatusList->SetGameStatus(GAMESTATUS_NEXTSTAGE);
			}
			break;

		/* "次のステージへ遷移"状態 */
		case GAMESTATUS_NEXTSTAGE:
			/* シーンの削除フラグを有効にする */
			this->bDeleteFlg = true;
			break;
	}
}

// 描画
void SceneEdit::Draw()
{
	DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "決定			：次のステージへ");
}
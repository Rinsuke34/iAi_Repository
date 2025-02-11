/* 2025.02.11 ファイル作成 駒沢風助 */

#include "SceneUi_Edit.h"

/* UI(エディット)クラスの定義 */
// コンストラクタ
SceneUi_Edit::SceneUi_Edit() : SceneBase("UI_Edit", 105, false)
{
	/* データリスト取得 */
	{
		/* "ゲーム内リソース管理"を取得 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}

	/* エディット情報初期化 */
	{
		/* エディット情報を初期化 */
		for (int i = 0; i < EDIT_MAX; i++)
		{
			/* 初期状態ではすべて"効果なし"に設定 */
			this->NowEditData[i].iEditEffect = EDIT_EFFECT_NONE;
		}

		/* テスト */
		this->NowEditData[0].iEditEffect = EDIT_EFFECT_NORMAL_MOVE_SPEED_UP;
	}
}

// デストラクタ
SceneUi_Edit::~SceneUi_Edit()
{

}

// 計算
void SceneUi_Edit::Process()
{

}

// 描画
void SceneUi_Edit::Draw()
{
	/* 現在のエディット内容を描写(テスト) */
	{
		/* エディット内容を描写 */
		for (int i = 0; i < EDIT_MAX; i++)
		{
			std::string strEditType = "なし";

			/* 効果名を取得 */
			for (int j = 0; j < EDIT_EFFECT_MAX; j++)
			{
				if (this->NowEditData[i].iEditEffect == EDIT_LIST[j].iEditEffect)
				{
					strEditType = EDIT_LIST[j].strEditName;
					break;
				}
			}

			/* エディット内容を描写 */
			DrawFormatStringToHandle(0, 1000 + 24 * i, GetColor(255, 255, 255), giFontHandle, strEditType.c_str());
		}
	}
}

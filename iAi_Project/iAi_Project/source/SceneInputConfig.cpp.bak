/* 2024.12.21 駒沢風助 ファイル作成 */

#include "SceneInputConfig.h"

/* シーン「入力設定」の定義 */

// コンストラクタ
SceneInputConfig::SceneInputConfig() : SceneBase("Option - InputConfig", 1, false)
{
	/* 非同期読み込みを有効化する */
	SetUseASyncLoadFlag(true);

	/* 非同期読み込みを無効化する */
	SetUseASyncLoadFlag(false);
}

// デストラクタ
SceneInputConfig::~SceneInputConfig()
{

}

// 計算
void SceneInputConfig::Process()
{
	/* 決定が入力されたら */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		// このシーンの削除フラグを有効にする
		this->bDeleteFlg = true;
		return;
	}

	///* いずれかのボタンが入力されたらシーンを削除 */
	//// 仮作成
	//if (gstInputData_Interaction.igRel != 0)
	//{
	//	// このシーンの削除フラグを有効にする
	//	this->bDeleteFlg = true;
	//	return;
	//}
}

// 描画
void SceneInputConfig::Draw()
{

}

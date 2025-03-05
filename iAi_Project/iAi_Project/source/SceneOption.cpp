/* 2025.03.05 ファイル追加 駒沢風助 */

#include "SceneOption.h"

/* シーン「オプション」の定義 */

// コンストラクタ
SceneOption::SceneOption() : SceneBase("Option", 500, true)
{

}

// デストラクタ
SceneOption::~SceneOption()
{

}

// 計算
void SceneOption::Process()
{
	/* いずれかのボタンが入力されたらシーンを削除 */
	// 仮作成
	/* 決定が入力されたら */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		// このシーンの削除フラグを有効にする
		this->bDeleteFlg = true;
		return;
	}
}

// 描画
void SceneOption::Draw()
{
	
}

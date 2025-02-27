/* 2024.12.XX YYYY ZZZZ */

#include "SceneOption.h"

/* シーン「オプション」の定義 */

// コンストラクタ
SceneOption::SceneOption() : SceneBase("Option", 0, false)
{

}

// デストラクタ
SceneOption::~SceneOption()
{

}

// 初期化
void SceneOption::Initialization()
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

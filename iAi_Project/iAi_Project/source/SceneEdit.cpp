/* 2025.01.19 ファイル作成 駒沢風助 */

#include "SceneEdit.h"

/* シーン"エディット"クラスの定義 */

// コンストラクタ
SceneEdit::SceneEdit() : SceneBase("Edit", 100, true)
{

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
	/* 決定が入力されたら */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		// このシーンの削除フラグを有効にする
		this->bDeleteFlg = true;
		return;
	}
}

// 描画
void SceneEdit::Draw()
{
	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "決定			：次のステージへ");
}
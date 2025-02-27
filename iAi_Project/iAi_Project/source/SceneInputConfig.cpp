/* 2024.12.21 駒沢風助 ファイル作成 */

#include "SceneInputConfig.h"

/* シーン「入力設定」の定義 */

// コンストラクタ
SceneInputConfig::SceneInputConfig() : SceneBase("Option - InputConfig", 1, false)
{

}

// デストラクタ
SceneInputConfig::~SceneInputConfig()
{

}

// 初期化
void SceneInputConfig::Initialization()
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
}

// 描画
void SceneInputConfig::Draw()
{

}


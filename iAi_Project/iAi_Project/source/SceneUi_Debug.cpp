/* 2025.01.31 ファイル作成 駒沢風助 */

#include "SceneUi_Debug.h"

/* UI(デバッグメニュー)クラスの定義 */

// コンストラクタ
SceneUi_Debug::SceneUi_Debug() : SceneBase("UI_Debug", 200, true)
{
	/* 初期化 */
	this->iSelectNo	= 0;

	/* グローバル変数をデバッグ項目に登録 */
	pDebugManu.push_back(&gbDrawSceneListFlg);			// シーンリストの描写
	pDebugManu.push_back(&gbDrawDatalistFlg);			// データリストの描写
	pDebugManu.push_back(&gbDrawShadowMapFlg);			// シャドウマップの描写
	pDebugManu.push_back(&gbDrawLightMapFlg);			// ライトマップの描写
	pDebugManu.push_back(&gbDrawLightMapDownScaleFlg);	// ライトマップ(縮小)の描写
	pDebugManu.push_back(&gbDrawLightMapGaussFlg);		// ライトマップ(ぼかし)のハンドル
	pDebugManu.push_back(&gbDrawCollisionFlg);			// 全オブジェクトのコリジョン描写
	pDebugManu.push_back(&gbDrawDeleteBackGroundFlg);	// バックグランドオブジェクトの非表示
}

// 計算
void SceneUi_Debug::Process()
{
	/* プレイヤーの入力取得 */
	// ※プレイヤーの入力に応じて選択中の項目番号を変更する
	// 上入力
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
	{
		this->iSelectNo -= 1;
		if (this->iSelectNo < 0)
		{
			this->iSelectNo = 0;
		}
	}

	// 下入力
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
	{
		this->iSelectNo += 1;
		if (this->iSelectNo > pDebugManu.size())
		{
			this->iSelectNo = (int)pDebugManu.size();
		}
	}

	// 決定
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		*pDebugManu[this->iSelectNo] = bToggleFlg(*pDebugManu[this->iSelectNo]);
	}

	// 戻る
	{
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
		{
			this->bDeleteFlg = true;
		}
	}
}

// 描画
void SceneUi_Debug::Draw()
{
	DrawBox(780, 300, 1200, 300 + 16 * 9, GetColor(0, 0, 0), TRUE);
	DrawFormatString(800, 300 + 16 * 0, GetColor(255, 255, 255), "シーンリストの描写");
	DrawFormatString(800, 300 + 16 * 1, GetColor(255, 255, 255), "データリストの描写");
	DrawFormatString(800, 300 + 16 * 2, GetColor(255, 255, 255), "シャドウマップの描写");
	DrawFormatString(800, 300 + 16 * 3, GetColor(255, 255, 255), "ライトマップの描写");
	DrawFormatString(800, 300 + 16 * 4, GetColor(255, 255, 255), "ライトマップ(縮小)の描写");
	DrawFormatString(800, 300 + 16 * 5, GetColor(255, 255, 255), "ライトマップ(ぼかし)のハンドル");
	DrawFormatString(800, 300 + 16 * 6, GetColor(255, 255, 255), "全オブジェクトのコリジョン描写");
	DrawFormatString(800, 300 + 16 * 7, GetColor(255, 255, 255), "バックグランドオブジェクトの非表示");
	DrawFormatString(800, 300 + 16 * 8, GetColor(255, 255, 255), "マウス使用フラグ");

	DrawFormatString(780, 300 + 16 * this->iSelectNo, GetColor(255, 255, 255), "→");
}

// trueとfalseの切り替え
bool SceneUi_Debug::bToggleFlg(bool bFlg)
{
	// 引数
	// bFlg	: 切り替えるフラグ

	return !bFlg;
}

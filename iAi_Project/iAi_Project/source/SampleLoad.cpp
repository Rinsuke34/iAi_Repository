#include "SampleLoad.h"

// コンストラクタ
SceneLoad::SceneLoad() : SceneBase("Loading", 9999, true)
{

}

// デストラクタ
SceneLoad::~SceneLoad()
{

}

// 計算
void SceneLoad::Process()
{
	/* 非同期読み込みが完了しているか確認 */
	if (GetASyncLoadNum() > 0)
	{
		/* 非同期読み込みが実行中の場合 */
	}
	else
	{
		/* 非同期読み込みが完了している場合 */
		// このシーンの削除フラグを有効にする
		this->bDeleteFlg = true;
	}
}

// 描画
void SceneLoad::Draw()
{
	DrawFormatString(10, 50, GetColor(237, 26, 61), "シーン : シーンロード中");
}

/* 2024.12.XX YYYY ZZZZ */

#include "SceneLoad.h"

/* シーン「ロード」の定義 */

// コンストラクタ
SceneLoad::SceneLoad() : SceneBase("Load", 0, false)
{
	/* 非同期読み込みを有効化する */
	SetUseASyncLoadFlag(true);

	/* 非同期読み込みを無効化する */
	SetUseASyncLoadFlag(false);
}

// デストラクタ
SceneLoad::~SceneLoad()
{

}

// 計算
void SceneLoad::Process()
{
	/* 非同期読み込みが完了しているか確認 */
	if (GetASyncLoadNum() <= 0)
	{
		/* 非同期読み込みが完了している場合 */
		// このシーンの削除フラグを有効にする
		this->bDeleteFlg = true;
		return;
	}
}

// 描画
void SceneLoad::Draw()
{

}

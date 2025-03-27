/* 2024.12.20 ファイル追加 駒沢風助 */

#include "SceneLoad.h"

/* シーン「ロード」の定義 */

// コンストラクタ
SceneLoad::SceneLoad() : SceneBase("Load", 9999, true)
{
	/* ロード中フラグを有効にする */
	gbNowLoadingFlg = true;
}

// 初期化
void SceneLoad::Initialization()
{

}

// 計算
void SceneLoad::Process()
{
	/* 非同期読み込みが完了しているか確認 */
	if (GetASyncLoadNum() <= 0)
	{
		// 非同期読み込みが完了している場合
		/* シーン削除フラグを有効にする */
		this->bDeleteFlg = true;

		/* ロード中フラグを無効にする */
		gbNowLoadingFlg = false;
		return;
	}

	return;
}

// 描画
void SceneLoad::Draw()
{

}

/* 2024.12.XX YYYY ZZZZ */

#include "SceneLoad.h"

/* シーン「ロード」の定義 */

// コンストラクタ
SceneLoad::SceneLoad() : SceneBase("Load", 9999, false)
{

}

// デストラクタ
SceneLoad::~SceneLoad()
{

}

// 初期化
void SceneLoad::Initialization()
{

}

// 計算
void SceneLoad::Process()
{
	/* 別スレッドでのローディング処理が実行中であるか確認 */
	size_t sLoadingSize			= gstLoadingThread.size();	// ロード数
	size_t sLoadCompleteSize	= 0;						// ロード完了数

	for (auto& Load : gstLoadingThread)
	{
		/* ロードが完了しているか */
		if (Load.joinable() == true)
		{
			// 完了している場合
			/* ロード完了数を増加 */
			sLoadCompleteSize++;
		}
	}

	/* ロード完了数がロード数と同じであるか確認 */
	if (sLoadingSize == sLoadCompleteSize)
	{
		// 完了している場合
		/* すべてのスレッドを削除 */
		for (auto& Load : gstLoadingThread)
		{
			/* スレッドを削除 */
			Load.join();
		}

		/* ロードデータをクリア */
		gstLoadingThread.clear();

		/* シーン削除フラグを有効にする */
		this->bDeleteFlg = true;
	}

	return;
}

// 描画
void SceneLoad::Draw()
{
	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "なうろーでぃんぐ");
}

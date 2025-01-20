/* 2024.12.XX YYYY ZZZZ */

#include "SceneLoad.h"

/* シーン「ロード」の定義 */

// コンストラクタ
SceneLoad::SceneLoad() : SceneBase("Load", 9999, true)
{
	/* テスト用 */
	this->iTestCount = 0;
}

// デストラクタ
SceneLoad::~SceneLoad()
{

}

// 初期化
void SceneLoad::Initialization()
{
	/* SceneBaseの初期化を実施(リソース競合対策) */
	SceneBase::Initialization();
}

// 計算
void SceneLoad::Process()
{
	/* ロードスレッドが建っているか確認 */
	if (gstLoadingFutures.empty())
	{
		// スレッドが建っていないならば
		/* シーン削除フラグを有効にする */
		this->bDeleteFlg = true;

		/* ローディングフラグを無効にする */
		gbNowLoadingFlg = false;
		return;
	}

	/* ローディングが完了しているか確認 */
	for (auto load = gstLoadingFutures.begin(); load != gstLoadingFutures.end(); )
	{
		/* 100ms待機する */
		auto status = load->wait_for(std::chrono::milliseconds(100));

		/* 対象のスレッドが完了しているか確認 */
		if (status == std::future_status::ready)
		{
			// スレッドが完了している場合
			/* ベクターから削除 */
			load = gstLoadingFutures.erase(load);
		}
		else
		{
			// スレッドが完了していない場合
			/* 次のスレッドを確認 */
			++load;
		}
	}

	/* テストカウント */
	this->iTestCount++;

	/* ローディングフラグを有効にする */
	gbNowLoadingFlg = true;

	return;
}

// 描画
void SceneLoad::Draw()
{
	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "なうろーでぃんぐ");
	DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "カウント : %d", this->iTestCount);
}

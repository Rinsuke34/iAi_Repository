/* 2025.02.20 ファイル作成 駒沢風助 */

#include "SceneGameOver.h"

/* シーン"ゲームオーバー"クラスの定義 */

// コンストラクタ
SceneGameOver::SceneGameOver() : SceneBase("GameOver", 200, true)
{
	/* データリスト取得 */
	{
		/* "ゲーム状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList	= dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 画像取得 */
		this->piGrHandle_GameOver	= ImageList->piGetImage_Movie("GameOver/UI_GameOver");
	}

	/* 初期化 */
	this->iBlendAlpha	= 0;	// 描写する画像のアルファ値(0～255)
}

// デストラクタ
SceneGameOver::~SceneGameOver()
{

}

// 計算
void SceneGameOver::Process()
{
	/* アルファブレンド値を加算 */
	this->iBlendAlpha += FADE_ALPHA_CHANGE_SPEED;

	/* アルファブレンド値が最大値(255)を超えているか確認 */
	if (this->iBlendAlpha > ALPHA_MAX)
	{
		// 最大値を超えている場合
		/* 最大値を超えないように補正を行う */
		this->iBlendAlpha = ALPHA_MAX;

		/* "決定"が入力されたか確認 */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
		{
			// "決定"が入力されたならば
			/* ロードシーン追加フラグを有効化 */
			gpSceneServer->SetAddLoadSceneFlg(true);

			/* 現行シーン削除フラグを有効化 */
			gpSceneServer->SetDeleteCurrentSceneFlg(true);

			/* シーン"ホーム"を追加 */
			gpSceneServer->AddSceneReservation(new SceneTitle());
			return;
		}
	}
}

// 描画
void SceneGameOver::Draw()
{
	/* 描写ブレンドモードを"アルファブレンド"に設定 */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->iBlendAlpha);

	/* 画面全体を黒色で描写 */
	DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);

	/* 描写ブレンドモードを"ノーブレンド"に設定 */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	/* アルファブレンド値が最大値(255)を超えているか確認 */
	if (this->iBlendAlpha >= ALPHA_MAX)
	{
		// 最大値を超えている場合
		/* ゲームオーバー画面を再生 */
		PlayMovieToGraph(*this->piGrHandle_GameOver);

		/* "ゲームオーバー"を描写 */
		DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->piGrHandle_GameOver, TRUE);

		/* 再生が終了しているか確認 */
		if (GetMovieStateToGraph(*this->piGrHandle_GameOver) == FALSE)
		{
			// 再生が終了している場合
			/* ムービーの再生時間を初期化する */
			SeekMovieToGraph(*this->piGrHandle_GameOver, 0);
		}

	}
}

// メイン処理
void SceneGameOver::Process_Main()
{

}

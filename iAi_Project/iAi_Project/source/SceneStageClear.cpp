/* 2025.03.02 ファイル作成 駒沢風助 */

#include "SceneStageClear.h"

/* シーン"ゲームクリア"クラスの定義 */
// コンストラクタ
SceneGameClear::SceneGameClear() : SceneBase("GameClear", 200, true)
{
	/* データリスト取得 */
	{
		/* "ゲーム状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}
	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 画像取得 */
		this->piGrHandle_GameClear = ImageList->piGetImage_Movie("GameClear/UI_GameClear");
	}
}

// デストラクタ
SceneGameClear::~SceneGameClear()
{

}

// 計算
void SceneGameClear::Process()
{
	/* ゲーム状態を確認 */
	int iGameStatus = this->StageStatusList->iGetGameStatus();

	/* ゲーム状態に応じて処理を変更 */
	switch (iGameStatus)
	{
		/* "ステージクリア"状態 */
		case GAMESTATUS_STAGE_CLEAR:
			/* メインの処理を実施 */
			Process_Main();
			break;

		/* 該当無し */
		default:
			/* シーンの削除フラグを有効にする */
			this->bDeleteFlg = true;
			break;
	}
}

// 描画
void SceneGameClear::Draw()
{
	/* 描画ブレンドモードを加算にする */
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	/* ステージクリア画面を再生 */
	PlayMovieToGraph(*this->piGrHandle_GameClear);

	/* "ゲームオーバー"を描写 */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->piGrHandle_GameClear, TRUE);

	/* 再生が終了しているか確認 */
	if (GetMovieStateToGraph(*this->piGrHandle_GameClear) == FALSE)
	{
		// 再生が終了している場合
		/* ムービーの再生時間を初期化する */
		SeekMovieToGraph(*this->piGrHandle_GameClear, 0);
	}

	/* 描画ブレンドモードをブレンド無しに戻す */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	/* 描画モードを二アレストに戻す */
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

// メイン処理
void SceneGameClear::Process_Main()
{
	/* "決定"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// 入力されている場合
		/* ゲーム状態を"リザルト"に変更する */
		this->StageStatusList->SetGameStatus(GAMESTATUS_RESULT);
	}
};

/* 2025.02.20 ファイル作成 駒沢風助 */

#include "SceneGameOver.h"

/* シーン"ゲームオーバー"クラスの定義 */

// コンストラクタ
SceneGameOver::SceneGameOver() : SceneBase("GameOver", 200, true)
{
	/* データリスト取得 */
	{
		/* "ゲーム状態管理"を取得 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
	}

	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList	= dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 画像取得 */
		this->piGrHandle_GameOver	= ImageList->piGetImage("GameOver/gameover_kari");
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
	this->iBlendAlpha += 3;

	/* アルファブレンド値が最大値(255)を超えているか確認 */
	if (this->iBlendAlpha > 255)
	{
		// 最大値を超えている場合
		/* 最大値を超えないように補正を行う */
		this->iBlendAlpha = 255;

		/* "決定"が入力されたか確認 */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
		{
			// "決定"が入力されたならば
			/* ロードシーン追加フラグを有効化 */
			gpSceneServer->SetAddLoadSceneFlg(true);

			/* 現行シーン削除フラグを有効化 */
			gpSceneServer->SetDeleteCurrentSceneFlg(true);

			/* シーン"ホーム"を追加 */
			gpSceneServer->AddSceneReservation(new SceneHome());
			return;
		}
	}
}

// 描画
void SceneGameOver::Draw()
{
	/* 描写ブレンドモードを"アルファブレンド"に設定 */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->iBlendAlpha);

	/* "ゲームオーバー"を描写 */
	DrawGraph(0, 0, *this->piGrHandle_GameOver, TRUE);

	/* 描写ブレンドモードを"ノーブレンド"に設定 */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

// メイン処理
void SceneGameOver::Process_Main()
{

}

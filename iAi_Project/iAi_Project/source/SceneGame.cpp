/* 2024.12.XX YYYY ZZZZ */

#include "SceneGame.h"

/* シーン「ゲーム」の定義 */

// コンストラクタ
SceneGame::SceneGame() : SceneBase("Game", 0, false)
{
	/* 初期化 */
	this->iNowStageNo	= 0;	// 現在のステージ番号
	this->iEndStageNo	= 0;	// 最終ステージ番号

	/* ローディング情報の作成 */
	//gstLoadingFutures.push_back(std::async(std::launch::async, &SceneGame::Initialization, this));
	Initialization();
}

// デストラクタ
SceneGame::~SceneGame()
{
	/* データリスト削除 */
	gpDataListServer->DeleteDataList("DataList_PlayerStatus");	// プレイヤー状態
	gpDataListServer->DeleteDataList("DataList_Model");			// 3Dモデル管理

	/* Effkseerの使用を終了する */
	Effkseer_End();
}

// 初期化
void SceneGame::Initialization()
{
	/* SceneBaseの初期化を実施(リソース競合対策) */
	SceneBase::Initialization();

	/* Effekseer初期化処理 */
	if (Effekseer_Init(EFFECT_MAX_PARTICLE) == -1)
	{
		// エラーが起きたら直ちに終了
		DxLib_End();
		gbEndFlg = true;
		return;
	}

	/* データリスト作成 */
	{
		/* データリストサーバーに"プレイヤー状態"を追加 */
		gpDataListServer->AddDataList(new DataList_PlayerStatus());

		/* データリストサーバーに"3Dモデル管理"を追加 */
		gpDataListServer->AddDataList(new DataList_Model());
	}

	/* 初期化 */
	// ※チュートリアルフラグに応じて初期ステージを変更

	/* チュートリアルフラグが有効であるか確認 */
	if (gbTutorialFlg == true)
	{
		// チュートリアルフラグが有効
		/* 最初のステージ番号を"チュートリアル開始"に設定 */
		this->iNowStageNo = STAGE_NO_TUTORIAL_START;

		/* 最終ステージ番号を"チュートリアル終了"に設定 */
		this->iEndStageNo = STAGE_NO_TUTORIAL_END;
	}
	else
	{
		// チュートリアルフラグが無効
		/* 最初のステージ番号を"実践開始"に設定 */
		this->iNowStageNo = STAGE_NO_PRACTICE_START;

		/* 最終ステージ番号を"実践終了"に設定 */
		this->iEndStageNo = STAGE_NO_PRACTICE_END;
	}

	/* "最初のステージ番号"のステージを読み込む */
	///* ロードシーン追加フラグを有効化 */
	//gpSceneServer->SetAddLoadSceneFlg(true);

	/* シーン"ステージ"を作成 */
	SceneBase* pAddScene = new SceneStage();

	/* シーン"ステージ"をシーンサーバーに追加 */
	gpSceneServer->AddSceneReservation(pAddScene);

	/* ステージの読み込みを開始 */
	dynamic_cast<SceneStage*>(pAddScene)->LoadMapData(this->iNowStageNo);
}

// 計算
void SceneGame::Process()
{

}

// 描画
void SceneGame::Draw()
{

}


/* 2024.12.XX YYYY ZZZZ */

#include "SceneGame.h"

/* シーン「ゲーム」の定義 */

// コンストラクタ
SceneGame::SceneGame() : SceneBase("Game", 0, false)
{
	/* データリスト作成 */
	{
		/* データリストサーバーに"3Dモデル管理"を追加 */
		gpDataListServer->AddDataList(new DataList_Model());

		/* データリストサーバーに"ゲーム状態管理"を追加 */
		gpDataListServer->AddDataList(new DataList_GameStatus());

		/* データリストサーバーに"エフェクトリソース管理"を追加 */
		gpDataListServer->AddDataList(new DataList_Effect());

		/* データリストサーバーに"ゲームリソース管理"を追加 */
		gpDataListServer->AddDataList(new DataList_GameResource());

		/* データリストサーバーに"画像リソース管理"を追加 */
		gpDataListServer->AddDataList(new DataList_Image());
	}

	/* データリスト取得 */
	{
		/* "ゲーム状態管理"を取得 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
	}

	/* ローディング情報の作成 */
	//gstLoadingFutures.push_back(std::async(std::launch::async, &SceneGame::Initialization, this));
	Initialization();
}

// デストラクタ
SceneGame::~SceneGame()
{
	/* データリスト削除 */
	{
		/* 3Dモデル管理 */
		gpDataListServer->DeleteDataList("DataList_Model");

		/* ゲーム状態管理 */
		gpDataListServer->DeleteDataList("DataList_GameStatus");

		/* エフェクトリソース管理 */
		gpDataListServer->DeleteDataList("DataList_Effect");

		/* ゲームリソース管理 */
		gpDataListServer->DeleteDataList("DataList_GameResource");

		/* 画像リソース管理 */
		gpDataListServer->DeleteDataList("DataList_Image");
	}

	/* Effkseerの使用を終了する */
	Effkseer_End();
}

// 初期化
void SceneGame::Initialization()
{
	/* BGMを設定 */
	gpDataList_Sound->BGM_SetHandle(BGM_STAGE);

	/* Effekseer初期化処理 */
	if (Effekseer_Init(EFFECT_MAX_PARTICLE) == -1)
	{
		// エラーが起きたら直ちに終了
		DxLib_End();
		gbEndFlg = true;
		return;
	}

	/* 初期化 */
	// ※チュートリアルフラグに応じて初期ステージを変更

	/* チュートリアルフラグが有効であるか確認 */
	if (gbTutorialFlg == true)
	{
		// チュートリアルフラグが有効
		/* 最初のステージ番号を"チュートリアル開始"に設定 */
		this->GameStatusList->SetNowStageNo(STAGE_NO_TUTORIAL_START);

		/* 最終ステージ番号を"チュートリアル終了"に設定 */
		this->GameStatusList->SetEndStageNo(STAGE_NO_TUTORIAL_END);
	}
	else
	{
		// チュートリアルフラグが無効
		/* 最初のステージ番号を"実践開始"に設定 */
		this->GameStatusList->SetNowStageNo(STAGE_NO_PRACTICE_START);

		/* 最終ステージ番号を"実践終了"に設定 */
		this->GameStatusList->SetEndStageNo(STAGE_NO_PRACTICE_END);
	}

	/* "最初のステージ番号"のステージを読み込む */
	/* シーン"ステージ"を作成 */
	SceneBase* pAddScene = new SceneStage();

	/* シーン"ステージ"をシーンサーバーに追加 */
	gpSceneServer->AddSceneReservation(pAddScene);

	/* ステージの読み込みを開始 */
	dynamic_cast<SceneStage*>(pAddScene)->LoadMapData();
}

// 計算
void SceneGame::Process()
{
	/* 現在のステージ番号を取得 */
	int iNowStageNo = this->GameStatusList->iGetNowStageNo();

	/* ステージ番号を+1する */
	iNowStageNo++;

	/* ステージ番号が最終ステージ番号を超えていないか確認 */
	if (iNowStageNo <= this->GameStatusList->iGetEndStageNo())
	{
		// 超えていない(次のステージがある)場合
		/* ステージ番号を設定 */
		this->GameStatusList->SetNowStageNo(iNowStageNo);

		/* ロードシーン追加フラグを有効化 */
		gpSceneServer->SetAddLoadSceneFlg(true);

		/* シーン"ステージ"を作成 */
		SceneBase* pAddScene = new SceneStage();

		/* シーン"ステージ"をシーンサーバーに追加 */
		gpSceneServer->AddSceneReservation(pAddScene);

		/* ステージの読み込みを開始 */
		dynamic_cast<SceneStage*>(pAddScene)->LoadMapData();
	}
	else
	{
		// 超えている(次のステージがない)場合
		/* シーン削除フラグを有効にする */
		this->bDeleteFlg = true;

		/* ロード画面追加フラグを有効化 */
		gpSceneServer->SetAddLoadSceneFlg(true);

		/* 現行シーン削除フラグを有効化 */
		gpSceneServer->SetDeleteCurrentSceneFlg(true);

		/* シーン"ホーム画面"を追加 */
		gpSceneServer->AddSceneReservation(new SceneHome());
	}
}

// 描画
void SceneGame::Draw()
{
	/* 現在のステージ番号を取得 */
	int iNowStageNo = this->GameStatusList->iGetNowStageNo();

	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "現在のステージ番号 ： %d", iNowStageNo);
}


/* 2024.12.XX YYYY ZZZZ */

#include "SceneGame.h"

/* シーン「ゲーム」の定義 */

// コンストラクタ
SceneGame::SceneGame() : SceneBase("Game", 0, false)
{
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

	/* ステージを作成 */
	StageBase* AddStage = new StageBase();

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
	AddStage->
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

// 計算
void SceneGame::Process()
{

}

// 描画
void SceneGame::Draw()
{
	
}


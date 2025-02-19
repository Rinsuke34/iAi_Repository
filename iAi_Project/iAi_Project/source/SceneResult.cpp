/* 2025.02.16 ファイル作成 駒沢風助 */

#include "SceneResult.h"

/* シーン"リザルト"クラスの定義 */

// コンストラクタ
SceneResult::SceneResult() : SceneBase("Edit", 80, true)
{
	/* データリスト取得 */
	{
		/* "ゲーム状態管理"を取得 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));

		/* "ゲーム内リソース管理"を取得 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}

	/* 初期化処理 */
	Initialization();
}

// デストラクタ
SceneResult::~SceneResult()
{

}

// 初期化
void SceneResult::Initialization()
{
	/* 各評価を取得(仮) */
	{
		/* 最大コンボ */
		this->iClearEvaluation_Combo	= RESULT_EVALUAtiON_S;	// 評価(最大コンボ)

		/* クリアタイム */
		this->iClearEvaluation_Time		= RESULT_EVALUAtiON_S;	// 評価(クリアタイム)

		/* 被ダメージ */
		this->iClearEvaluation_Damage	= RESULT_EVALUAtiON_S;	// 評価(被ダメージ)
	}

	/* 総合評価を実施 */
	{
		/* 各評価を合算 */
		int iEvaluationTotal = 0;
		iEvaluationTotal += this->iClearEvaluation_Combo;
		iEvaluationTotal += this->iClearEvaluation_Time;
		iEvaluationTotal += this->iClearEvaluation_Damage;

		/* 総合値に応じて設定 */
		// ※ 総合評価は下記の通り
		//	合算値,	 評価
		//	12		: S
		//	11 ～ 9	: A
		//	8  ～ 4 : B
		//	3  ～ 2 : C
		//  1  ～ 0 : D

		if (iEvaluationTotal >= 12)
		{
			// S
			this->iClearEvaluation_Total = RESULT_EVALUAtiON_S;
		}
		else if (iEvaluationTotal >= 9)
		{
			// A
			this->iClearEvaluation_Total = RESULT_EVALUAtiON_A;
		}
		else if (iEvaluationTotal >= 4)
		{
			// B
			this->iClearEvaluation_Total = RESULT_EVALUAtiON_B;
		}
		else if (iEvaluationTotal >= 2)
		{
			// C
			this->iClearEvaluation_Total = RESULT_EVALUAtiON_C;
		}
		else
		{
			// D
			this->iClearEvaluation_Total = RESULT_EVALUAtiON_D;
		}
	}
	
}

// 計算
void SceneResult::Process()
{
	/* ゲーム状態を確認 */
	int iGameStatus = this->GameStatusList->iGetGameStatus();

	/* ゲーム状態に応じて処理を変更 */
	switch (iGameStatus)
	{
		/* "リザルト"状態 */
		case GAMESTATUS_RESULT:
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
void SceneResult::Draw()
{
	DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "決定			：エディット画面へ");
}

// メイン処理
void SceneResult::Process_Main()
{
	/* 決定入力時の処理 */
	Process_Decid();
}

// 決定入力時の処理
void SceneResult::Process_Decid()
{
	/* "決定"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// 入力されている場合
		/* ゲーム状態を"エディット"に変更する */
		this->GameStatusList->SetGameStatus(GAMESTATUS_EDIT);

		/* 各評価の総合値をゲーム内リソースサーバーに登録 */
		this->GameResourceList->SetClearEvaluation(this->iClearEvaluation_Total);
	}
}


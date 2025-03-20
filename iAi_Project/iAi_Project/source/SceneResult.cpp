/* 2025.02.16 ファイル作成 駒沢風助 */

#include "SceneResult.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* シーン"リザルト"クラスの定義 */

// コンストラクタ
SceneResult::SceneResult() : SceneBase("Edit", 80, true)
{
	/* データリスト取得 */
	{
		/* "ゲーム状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "ゲーム内リソース管理"を取得 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));

		/* "プレイヤー状態管理"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}

	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* リザルト画面背景 */
		this->piGrHandle_ResultBackGround	= ImageList->piGetImage("Result/UI_ResultBackGround_mini");

		/* リザルト画面の文字(リザルト) */
		this->piGrHandle_String_Result		= ImageList->piGetImage("Result/UI_Moji_Result");

		/* リザルト画面の文字(ランク) */
		this->piGrHandle_String_Rank		= ImageList->piGetImage("Result/UI_Moji_Rank");

		/* リザルトフレーム */
		this->piGrHandle_ResultFrame		= ImageList->piGetImage("Result/UI_Result_Frame");

		/* アルファベット(コンボ用の物を流用) */
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_S]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_S");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_A]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_A");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_B]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_B");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_C]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_C");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_D]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_D");
	}

	/* 初期化 */
	this->iAddTextNo	= -1;

	/* 各評価基準を取得 */
	ResultCalculation_JsonLoad();

	/* 各評価点を算出 */
	ClearEvaluation();
}

// 計算
void SceneResult::Process()
{
	/* ゲーム状態を確認 */
	int iGameStatus = this->StageStatusList->iGetGameStatus();

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
	/* リザルト用のフレームを描写 */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->piGrHandle_ResultFrame, FALSE);

	/* 画面の背景描写 */
	DrawExtendGraph(0 + RESULT_BACKGROUND_POSITION_REDUCTION, 0 + RESULT_BACKGROUND_POSITION_REDUCTION, SCREEN_SIZE_WIDE - RESULT_BACKGROUND_POSITION_REDUCTION, SCREEN_SIZE_HEIGHT - RESULT_BACKGROUND_POSITION_REDUCTION, *this->piGrHandle_ResultBackGround, TRUE);

	/* 文字描写(画像部分) */
	DrawGraph(RESULT_STRING_RESULT_POSITION_X, RESULT_STRING_RESULT_POSITION_Y, *this->piGrHandle_String_Result, TRUE);
	DrawGraph(RESULT_STRING_RANK_POSITION_X, RESULT_STRING_RANK_POSITION_Y, *this->piGrHandle_String_Rank, TRUE);
	
	/* 白線 */
	DrawBox(RESULT_STRING_RESULT_LINE_LU, RESULT_STRING_RESULT_LINE_LD, RESULT_STRING_RESULT_LINE_RU, RESULT_STRING_RESULT_LINE_RD, GetColor(255, 255, 255), TRUE);
	DrawBox(RESULT_STRING_RANK_LINE_LU, RESULT_STRING_RANK_LINE_LD, RESULT_STRING_RANK_LINE_RU, RESULT_STRING_RANK_LINE_RD, GetColor(255, 255, 255), TRUE);

	/* 文字(マキナスフォント使用部分) */
	DrawFormatStringToHandle(80, 240, GetColor(0, 0, 0), giFontHandle_Large,	"CLEAR TIME");
	DrawFormatStringToHandle(80 + 600, 240, GetColor(0, 0, 0), giFontHandle_Large,	"%d s", (StageStatusList->iGetClearTime() - StageStatusList->iGetStartTime()) / 1000);

	DrawFormatStringToHandle(80, 400, GetColor(0, 0, 0), giFontHandle_Large,	"MAX COMBO");
	DrawFormatStringToHandle(80 + 600, 400, GetColor(0, 0, 0), giFontHandle_Large, "%d COMBO", PlayerStatusList->iGetPlayerComboMaxCount());

	DrawFormatStringToHandle(80, 560, GetColor(0, 0, 0), giFontHandle_Large,	"TAKE DAMAGE");
	DrawFormatStringToHandle(80 + 600, 560, GetColor(0, 0, 0), giFontHandle_Large, "%d DAMAGE", PlayerStatusList->iGetPlayerDamageCount());

	DrawFormatStringToHandle(80, 720, GetColor(0, 0, 0), giFontHandle_Large,	"GET BLOOD");

	/* 評価描写 */
	{
		/* 評価(クリアタイム) */
		DrawGraph(1500, 200, *this->apiGrHandle_Alphabet[this->iClearEvaluation_Time], TRUE);
		/* 評価(最大コンボ) */
		DrawGraph(1500, 360, *this->apiGrHandle_Alphabet[this->iClearEvaluation_Combo], TRUE);
		/* 評価(被ダメージ) */
		DrawGraph(1500, 540, *this->apiGrHandle_Alphabet[this->iClearEvaluation_Damage], TRUE);
		/* 評価(総合) */
		DrawGraph(1600, 720, *this->apiGrHandle_Alphabet[this->iClearEvaluation_Total], TRUE);
	}
}

// メイン処理
void SceneResult::Process_Main()
{
	/* "決定"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// 入力されている場合
		/* ゲーム状態を"エディット"に変更する */
		this->StageStatusList->SetGameStatus(GAMESTATUS_EDIT);

		/* 各評価の総合値をゲーム内リソースサーバーに登録 */
		this->GameResourceList->SetClearEvaluation(this->iClearEvaluation_Total);

		/* テキスト番号が無効(-1)以外であるか確認 */
		if (this->iAddTextNo != -1)
		{
			// テキスト番号が有効な場合
			/* シーン"会話パート"を追加 */
			SceneConversation* pAddScene = new SceneConversation();
			gpSceneServer->AddSceneReservation(pAddScene);

			/* シーン"会話パート"にテキスト番号を設定 */
			pAddScene->SetTextFileNo(this->iAddTextNo);

			/* 初期化処理を実施 */
			pAddScene->Initialization();
		}
	}
}

// 評価基準取得
void SceneResult::ResultCalculation_JsonLoad()
{
	/* Jsonファイルの読み込み */
	// jsonファイルから各評価の基準点を取得

	/* パスとファイル名の設定 */
	std::string FilePath		= "resource/SetupData/";	// 保存場所
	std::string jsonFileName	= "StageDataBase.json";		// ファイル名

	/* ファイル展開 */
	std::ifstream inputFile(FilePath + jsonFileName);

	/* ファイルの展開が成功したか確認 */
	if (inputFile.is_open())
	{
		// ファイルが存在する場合
		/* 現在のステージ名を取得 */
		std::string StageName = STAGE_NAME[StageStatusList->iGetNowStageNo()];

		/* 現在のステージの各評価の基準値を取得する */
		nlohmann::json	json;
		inputFile >> json;

		/* 評価基準(コンボ数)取得 */
		{
			/* jsonファイルから読み込み */
			std::string GetName = "Combo";
			nlohmann::json Data = json.at(StageName).at(GetName);
			
			/* 読み込んだ値を配列に代入 */
			for (int i = 0; i < RESULT_EVALUATION_MAX; i++)
			{
				this->Calculation_Combo[i] = Data.at(i);
			}			
		}
		
		/* 評価基準(クリアタイム)取得 */
		{
			/* jsonファイルから読み込み */
			std::string GetName = "Time";
			nlohmann::json Data = json.at(StageName).at(GetName);

			/* 読み込んだ値を配列に代入 */
			for (int i = 0; i < RESULT_EVALUATION_MAX; i++)
			{
				this->Calculation_Time[i] = Data.at(i);
			}
		}

		/* 評価基準(被ダメージ数)取得 */
		{
			/* jsonファイルから読み込み */
			std::string GetName = "Damage";
			nlohmann::json Data = json.at(StageName).at(GetName);
			/* 読み込んだ値を配列に代入 */
			for (int i = 0; i < RESULT_EVALUATION_MAX; i++)
			{
				this->Calculation_Damage[i] = Data.at(i);
			}
		}

		/* 会話パート番号を取得 */
		{
			/* jsonファイルから読み込み */
			std::string GetName = "Conversation";
			nlohmann::json Data = json.at(StageName).at(GetName);

			/* 読み込んだ値を変数に保存 */
			this->iAddTextNo = Data;
		}

		/* ファイルを閉じる */
		inputFile.close();
	}
}

// 評価算出
void SceneResult::ClearEvaluation()
{
	/* 最大コンボ数の評価算出 */
	{
		/* 最大コンボ数を取得 */
		int iMaxCombo = PlayerStatusList->iGetPlayerComboMaxCount();

		/* 初期状態では評価を最低に設定しておく */
		this->iClearEvaluation_Combo = RESULT_EVALUATION_D;

		/* 評価算出 */
		for (int i = 0; i < RESULT_EVALUATION_MAX; i++)
		{
			/* 評価基準を超えているか確認 */
			if (iMaxCombo >= this->Calculation_Combo[i])
			{
				// 該当の評価基準を超えている場合
				this->iClearEvaluation_Combo = i;
				break;
			}
		}
	}

	/* クリアタイムの評価算出 */
	{
		/* クリアタイムを取得 */
		// ※評価時は小数点以下切り捨て
		int iClearTime = (StageStatusList->iGetClearTime() - StageStatusList->iGetStartTime()) / 1000;

		/* 初期状態では評価を最低に設定しておく */
		this->iClearEvaluation_Time = RESULT_EVALUATION_D;

		/* 評価算出 */
		for (int i = 0; i < RESULT_EVALUATION_MAX; i++)
		{
			/* 評価基準以下の値であるか確認 */
			if (iClearTime <= this->Calculation_Time[i])
			{
				// 該当の評価基準を超えている場合
				this->iClearEvaluation_Time = i;
				break;
			}
		}
	}

	/* 被ダメージ数の評価算出 */
	{
		/* 被ダメージ数を取得 */
		int iDamage = PlayerStatusList->iGetPlayerDamageCount();

		/* 初期状態では評価を最低に設定しておく */
		this->iClearEvaluation_Damage = RESULT_EVALUATION_D;

		/* 評価算出 */
		for (int i = 0; i < RESULT_EVALUATION_MAX; i++)
		{
			/* 評価基準を超えているか確認 */
			if (iDamage <= this->Calculation_Damage[i])
			{
				// 該当の評価基準を超えている場合
				this->iClearEvaluation_Damage = i;
				break;
			}
		}
	}

	/* 総合評価の算出 */
	{
		/* 各評価を合算 */
		int iEvaluationTotal = 0;
		iEvaluationTotal += this->iClearEvaluation_Combo;
		iEvaluationTotal += this->iClearEvaluation_Time;
		iEvaluationTotal += this->iClearEvaluation_Damage;

		/* 総合値に応じて設定 */
		// ※ 総合評価は下記の通り
		//	合算値,	 評価
		//	～  0 : S
		//	～  3 : A
		//	～  6 : B
		//	～  9 : C
		//  10 ～ : D

		if (iEvaluationTotal <= 0)
		{
			// S
			this->iClearEvaluation_Total = RESULT_EVALUATION_S;
		}
		else if (iEvaluationTotal <= 3)
		{
			// A
			this->iClearEvaluation_Total = RESULT_EVALUATION_A;
		}
		else if (iEvaluationTotal >= 6)
		{
			// B
			this->iClearEvaluation_Total = RESULT_EVALUATION_B;
		}
		else if (iEvaluationTotal >= 9)
		{
			// C
			this->iClearEvaluation_Total = RESULT_EVALUATION_C;
		}
		else
		{
			// D
			this->iClearEvaluation_Total = RESULT_EVALUATION_D;
		}
	}
}

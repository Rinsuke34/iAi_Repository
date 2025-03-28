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
		this->piGrHandle_ResultBackGround	= ImageList->piGetImage("Result/UI_Result");

		/* 各評価のアルファベット */
		this->apiGrHandle_Alphabet_Section[RESULT_EVALUATION_S] = ImageList->piGetImage("Result/UI_Player_Grade_S_150");
		this->apiGrHandle_Alphabet_Section[RESULT_EVALUATION_A] = ImageList->piGetImage("Result/UI_Player_Grade_A_150");
		this->apiGrHandle_Alphabet_Section[RESULT_EVALUATION_B] = ImageList->piGetImage("Result/UI_Player_Grade_B_150");
		this->apiGrHandle_Alphabet_Section[RESULT_EVALUATION_C] = ImageList->piGetImage("Result/UI_Player_Grade_C_150");
		this->apiGrHandle_Alphabet_Section[RESULT_EVALUATION_D] = ImageList->piGetImage("Result/UI_Player_Grade_D_150");

		/* 総合評価アルファベット(コンボ用の物を流用) */
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_S]	= ImageList->piGetImage("Result/UI_Player_RankGrade_S_256");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_A]	= ImageList->piGetImage("Result/UI_Player_RankGrade_A_256");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_B]	= ImageList->piGetImage("Result/UI_Player_RankGrade_B_256");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_C]	= ImageList->piGetImage("Result/UI_Player_RankGrade_C_256");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_D]	= ImageList->piGetImage("Result/UI_Player_RankGrade_D_256");
	}

	/* 初期化 */
	this->iAddTextNo					= -1;
	this->iDrawFaze						= RESULT_DRAW_FAZE_CLEAR_TIME;
	this->iDrawTimeMinute				= 0;
	this->iDrawTimeSecond				= 0;
	this->iDrawTimeFractionalSecond		= 0;
	this->iDrawMaxCombo					= 0;
	this->iDrawTakeDamage				= 0;
	this->iDrawTotalGetBlood			= 0;
	this->iDrawDelayTime				= RESULT_DRAW_FAZE_DELAY_TIME;
	this->bPlaySoundCount				= false;

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
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->piGrHandle_ResultBackGround, FALSE);

	/* 文字(マキナスフォント使用部分) */
	int iColorWhite = GetColor(255, 255, 255);
	int iColorBlack = GetColor(50, 50, 50);

	/* 文字の描写座標 */
	st2DPosition astStringPos[8];
	for (int i = 0; i < 4; ++i)
	{
		astStringPos[i * 2] = { 80, 240 + i * 160 };
		astStringPos[i * 2 + 1] = { 80 + 600, 240 + i * 160 };
	}

	/* 文字枠の補正座標 */
	st2DPosition astStringCorrectionPos[8];
	astStringCorrectionPos[0] = { -2,	-2	};
	astStringCorrectionPos[1] = { 0,	-2	};
	astStringCorrectionPos[2] = { +2,	-2	};
	astStringCorrectionPos[3] = { -2,	0	};
	astStringCorrectionPos[4] = { +2,	0	};
	astStringCorrectionPos[5] = { -2,	+2	};
	astStringCorrectionPos[6] = { 0,	+2	};
	astStringCorrectionPos[7] = { +2,	+2	};

	/* 文字描写(枠) */
	for (int i = 0; i < 8; i++)
	{
		DrawFormatStringToHandle(astStringPos[0].ix + astStringCorrectionPos[i].ix, astStringPos[0].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "CLEAR TIME");
		DrawFormatStringToHandle(astStringPos[1].ix + astStringCorrectionPos[i].ix, astStringPos[1].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "%02d'%02d''%02d", this->iDrawTimeMinute, this->iDrawTimeSecond, iDrawTimeFractionalSecond);

		DrawFormatStringToHandle(astStringPos[2].ix + astStringCorrectionPos[i].ix, astStringPos[2].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "MAX COMBO");
		DrawFormatStringToHandle(astStringPos[3].ix + astStringCorrectionPos[i].ix, astStringPos[3].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "%d COMBO", this->iDrawMaxCombo);

		DrawFormatStringToHandle(astStringPos[4].ix + astStringCorrectionPos[i].ix, astStringPos[4].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "TAKE DAMAGE");
		DrawFormatStringToHandle(astStringPos[5].ix + astStringCorrectionPos[i].ix, astStringPos[5].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "%d DAMAGE", this->iDrawTakeDamage);

		DrawFormatStringToHandle(astStringPos[6].ix + astStringCorrectionPos[i].ix, astStringPos[6].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "GET BLOOD");
		DrawFormatStringToHandle(astStringPos[7].ix + astStringCorrectionPos[i].ix, astStringPos[7].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "%d BLOOD", this->iDrawTotalGetBlood);
	}

	/* 文字描写(中心) */
	DrawFormatStringToHandle(astStringPos[0].ix, astStringPos[0].iy, iColorBlack, giFontHandle_Large,	"CLEAR TIME");
	DrawFormatStringToHandle(astStringPos[1].ix, astStringPos[1].iy, iColorBlack, giFontHandle_Large,	"%02d'%02d''%02d", this->iDrawTimeMinute, this->iDrawTimeSecond, iDrawTimeFractionalSecond);

	DrawFormatStringToHandle(astStringPos[2].ix, astStringPos[2].iy, iColorBlack, giFontHandle_Large,	"MAX COMBO");
	DrawFormatStringToHandle(astStringPos[3].ix, astStringPos[3].iy, iColorBlack, giFontHandle_Large, "%d COMBO", this->iDrawMaxCombo);

	DrawFormatStringToHandle(astStringPos[4].ix, astStringPos[4].iy, iColorBlack, giFontHandle_Large, "TAKE DAMAGE");
	DrawFormatStringToHandle(astStringPos[5].ix, astStringPos[5].iy, iColorBlack, giFontHandle_Large, "%d DAMAGE", this->iDrawTakeDamage);

	DrawFormatStringToHandle(astStringPos[6].ix, astStringPos[6].iy, iColorBlack, giFontHandle_Large,	"GET BLOOD");
	DrawFormatStringToHandle(astStringPos[7].ix, astStringPos[7].iy, iColorBlack, giFontHandle_Large, "%d BLOOD", this->iDrawTotalGetBlood);

	/* 評価描写 */
	{
		/* 描写フェーズが"クリアタイム評価描写"以降であるか */
		if (this->iDrawFaze >= RESULT_DRAW_FAZE_CREAR_TIME_EVALUATION)
		{
			/* 評価(クリアタイム) */
			DrawGraph(1500, 200, *this->apiGrHandle_Alphabet_Section[this->iClearEvaluation_Time], TRUE);
		}

		/* 描写フェーズが"コンボ評価描写"以降であるか */
		if (this->iDrawFaze >= RESULT_DRAW_FAZE_COMBO_EVALUATION)
		{
			/* 評価(最大コンボ) */
			DrawGraph(1500, 360, *this->apiGrHandle_Alphabet_Section[this->iClearEvaluation_Combo], TRUE);
		}

		/* 描写フェーズが"ダメージ評価描写"以降であるか */
		if (this->iDrawFaze >= RESULT_DRAW_FAZE_DAMAGE_EVALUATION)
		{
			/* 評価(被ダメージ) */
			DrawGraph(1500, 540, *this->apiGrHandle_Alphabet_Section[this->iClearEvaluation_Damage], TRUE);
		}

		/* 描写フェーズが"総合評価描写"以降であるか */
		if (this->iDrawFaze >= RESULT_DRAW_FAZE_TOTAL_EVALUATION)
		{
			/* 評価(総合) */
			DrawGraph(1550, 685, *this->apiGrHandle_Alphabet[this->iClearEvaluation_Total], TRUE);
		}
	}
}

// メイン処理
void SceneResult::Process_Main()
{
	/* 現時点で"リザルト"SEを再生中であるかを保持 */
	bool bPlaySound = this->bPlaySoundCount;

	/* 現在の描写遅延時間割合を取得 */
	float fDrawDelayTimePercent = (static_cast<float>(RESULT_DRAW_FAZE_DELAY_TIME) - static_cast<float>(this->iDrawDelayTime)) / static_cast<float>(RESULT_DRAW_FAZE_DELAY_TIME);

	/* フェーズに応じて描写用の数値を設定 */
	switch (this->iDrawFaze)
	{
		/* クリアタイム描写 */
		case RESULT_DRAW_FAZE_CLEAR_TIME:
			{
				/* 総合クリアタイムを取得 */
				int iClearTime = StageStatusList->iGetClearTime() - StageStatusList->iGetStartTime() - StageStatusList->iGetStopTotalTime();

				/* クリアタイムの分の値を取得 */
				int iTimeMinute = iClearTime / 1000 / 60;

				/* クリアタイムの秒の値を取得 */
				int iTimeSecond = iClearTime / 1000 % 60;

				/* クリアタイムの少数秒の値を取得 */
				int iTimeFractionalSecond = iClearTime % 1000 / 10;

				/* 取得した値の(描写遅延時間最大値/描写遅延時間)の値を描写値として設定 */
				this->iDrawTimeMinute			= iTimeMinute * fDrawDelayTimePercent;
				this->iDrawTimeSecond			= iTimeSecond * fDrawDelayTimePercent;
				this->iDrawTimeFractionalSecond	= iTimeFractionalSecond * fDrawDelayTimePercent;

				/* "リザルト"のSEを再生中に設定 */
				this->bPlaySoundCount = true;
			}
			break;

		/* クリアタイム評価描写 */
		case RESULT_DRAW_FAZE_CREAR_TIME_EVALUATION:
			/* "リザルト"のSEを非再生中に設定 */
			this->bPlaySoundCount = false;

			/* 描写開始直後であるか */
			if (this->iDrawDelayTime == RESULT_DRAW_FAZE_DELAY_TIME)
			{
				// 開始直後である場合
				/* "リザルト小評価"のSEを再生 */
				gpDataList_Sound->SE_PlaySound(SE_SYSTEM_RESULT_RANK_SMALL);
			}
			break;

		/* コンボ描写 */
		case RESULT_DRAW_FAZE_COMBO:
			/* コンボ数の(描写遅延時間最大値/描写遅延時間)の値を描写値として設定 */
			this->iDrawMaxCombo = static_cast<int>(PlayerStatusList->iGetPlayerComboMaxCount() * fDrawDelayTimePercent);

			/* "リザルト"のSEを再生中に設定 */
			this->bPlaySoundCount = true;
			break;

		/* コンボ評価描写 */
		case RESULT_DRAW_FAZE_COMBO_EVALUATION:
			/* "リザルト"のSEを非再生中に設定 */
			this->bPlaySoundCount = false;

			/* 描写開始直後であるか */
			if (this->iDrawDelayTime == RESULT_DRAW_FAZE_DELAY_TIME)
			{
				// 開始直後である場合
				/* "リザルト小評価"のSEを再生 */
				gpDataList_Sound->SE_PlaySound(SE_SYSTEM_RESULT_RANK_SMALL);
			}
			break;

		/* ダメージ描写 */
		case RESULT_DRAW_FAZE_DAMAGE:
			/* ダメージ数の(描写遅延時間最大値/描写遅延時間)の値を描写値として設定 */
			this->iDrawTakeDamage = static_cast<int>(PlayerStatusList->iGetPlayerDamageCount() * fDrawDelayTimePercent);

			/* "リザルト"のSEを再生中に設定 */
			this->bPlaySoundCount = true;
			break;

		/* ダメージ評価描写 */
		case RESULT_DRAW_FAZE_DAMAGE_EVALUATION:
			/* "リザルト"のSEを非再生中に設定 */
			this->bPlaySoundCount = false;

			/* 描写開始直後であるか */
			if (this->iDrawDelayTime == RESULT_DRAW_FAZE_DELAY_TIME)
			{
				// 開始直後である場合
				/* "リザルト小評価"のSEを再生 */
				gpDataList_Sound->SE_PlaySound(SE_SYSTEM_RESULT_RANK_SMALL);
			}
			break;

		/* 取得ブラッド描写 */
		case RESULT_DRAW_FAZE_GETBLOOD:
			/* 獲得ブラッド数の(描写遅延時間/描写遅延時間最大値)の値を描写値として設定 */
			this->iDrawTotalGetBlood = static_cast<int>((this->GameResourceList->iGetHaveBlood() - this->GameResourceList->iGetStartBlood()) * fDrawDelayTimePercent);

			/* "リザルト"のSEを再生中に設定 */
			this->bPlaySoundCount = true;
			break;

		/* 総合評価描写 */
		case RESULT_DRAW_FAZE_TOTAL_EVALUATION:
			/* "リザルト"のSEを非再生中に設定 */
			this->bPlaySoundCount = false;

			/* 描写開始直後であるか */
			if (this->iDrawDelayTime == RESULT_DRAW_FAZE_DELAY_TIME)
			{
				// 開始直後である場合
				/* 総合評価に応じたボイスを再生する */
				switch (this->iClearEvaluation_Total)
				{
					/* S評価 */
					case RESULT_EVALUATION_S:
						/* "最高"ボイスを再生する */
						gpDataList_Sound->VOICE_PlaySound(VOICE_DOCTOR_PRAISE_S);
						break;

					/* A評価 */
					case RESULT_EVALUATION_A:
						/* "結果A"ボイスを再生する */
						gpDataList_Sound->VOICE_PlaySound(VOICE_DOCTOR_RESULT_A);
						break;

					/* BC評価 */
					case RESULT_EVALUATION_B:
					case RESULT_EVALUATION_C:
						/* "結果BC"ボイスを再生する */
						gpDataList_Sound->VOICE_PlaySound(VOICE_DOCTOR_RESULT_BC);
						break;

					/* D評価 */
					case RESULT_EVALUATION_D:
						/* "結果D"ボイスを再生する */
						gpDataList_Sound->VOICE_PlaySound(VOICE_DOCTOR_RESULT_D);
						break;
				}
			}
			break;

		/* 描写終了 */
		case RESULT_DRAW_END:
			/* "リザルト"のSEを非再生中に設定 */
			this->bPlaySoundCount = false;
			break;
	}

	/* 描写遅延時間を減少 */
	this->iDrawDelayTime -= 1;

	/* "リザルト"のSEを再生開始するか確認 */
	if ((bPlaySound == false) && (this->bPlaySoundCount == true))
	{
		// 再生開始する場合
		/* "リザルト"のSEを再生 */
		gpDataList_Sound->SE_PlaySound_Loop(SE_SYSTEM_RESULT_COUNT);
	}
	else if ((bPlaySound == true) && (this->bPlaySoundCount == false))
	{
		// 再生停止する場合
		/* "リザルト"のSEを停止 */
		gpDataList_Sound->SE_PlaySound_Stop(SE_SYSTEM_RESULT_COUNT);
	}

	/* 描写遅延時間が0以下であるか確認 */
	if (this->iDrawDelayTime <= 0)
	{
		// 0以下である場合
		/* 描写遅延時間をリセット */
		this->iDrawDelayTime = RESULT_DRAW_FAZE_DELAY_TIME;

		/* 描写フェーズを進める */
		this->iDrawFaze += 1;
	}

	/* "決定"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// 入力されている場合
		/* "決定"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

		/* 総合評価描写が終了しているか確認 */
		if (this->iDrawFaze > RESULT_DRAW_END)
		{
			// 終了している場合
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
		else
		{
			// 終了していない場合
			/* 描写フェーズを"描写終了"まで進める */
			this->iDrawFaze = RESULT_DRAW_END;
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
		else if (iEvaluationTotal <= 6)
		{
			// B
			this->iClearEvaluation_Total = RESULT_EVALUATION_B;
		}
		else if (iEvaluationTotal <= 9)
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

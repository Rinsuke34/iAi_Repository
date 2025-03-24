/* 2025.01.28 ファイル作成 駒沢風助 */

#include "SceneUi_Combo.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* UI(コンボ)クラスの定義 */

// コンストラクタ
SceneUi_Combo::SceneUi_Combo() : SceneBase("UI_Combo", 103, false)
{
	/* データリスト取得 */
	{
		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "ゲーム状態管理"を取得 */
		this->StageStatusList	= dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* コンボフレーム */
		this->piGrHandle_Combo_Frame	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/UI_Player_ComboGrade_frame_fix");

		/* コンボタイマー */
		this->piGrHandle_Combo_Timer	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/UI_Player_ComboTimer");

		/* コンボアルファベット */
		this->piGrHandle_Combo_Alphabet[COMBO_RANK_S]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_S");
		this->piGrHandle_Combo_Alphabet[COMBO_RANK_A]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_A");
		this->piGrHandle_Combo_Alphabet[COMBO_RANK_B]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_B");
		this->piGrHandle_Combo_Alphabet[COMBO_RANK_C]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_C");
		this->piGrHandle_Combo_Alphabet[COMBO_RANK_D]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_D");
	}

	/* 初期化 */
	this->iPlayerComboRank = COMBO_RANK_NONE;

	/* ランク基準取得 */
	RankBorder_JsonLoad();
}

// ランク基準取得
void SceneUi_Combo::RankBorder_JsonLoad()
{
	/* Jsonファイルの読み込み */
	// jsonファイルから各評価の基準点を取得

	/* パスとファイル名の設定 */
	std::string FilePath = "resource/SetupData/";	// 保存場所
	std::string jsonFileName = "StageDataBase.json";		// ファイル名

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
			for (int i = 0; i < COMBO_RANK_MAX; i++)
			{
				this->iComboBorder[i] = Data.at(i);
			}
		}

		/* ファイルを閉じる */
		inputFile.close();
	}
}

// 計算
void SceneUi_Combo::Process()
{
	/* 現在のコンボ数を取得 */
	int iNowCombo = this->PlayerStatusList->iGetPlayerComboNowCount();

	/* ゲーム状態が"ゲーム実行"以外であるならシーンを削除 */
	if (this->StageStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
		return;
	}

	/* コンボ継続時間が終了しているか確認 */
	if (this->PlayerStatusList->iGetPlayerComboDuration() > 0)
	{
		// 終了していない場合
		/* コンボ継続時間を減算 */
		this->PlayerStatusList->SetPlayerComboDuration(this->PlayerStatusList->iGetPlayerComboDuration() - 1);

		/* 現在のコンボ数が最大コンボ数より多いか確認 */
		if (iNowCombo > this->PlayerStatusList->iGetPlayerComboMaxCount())
		{
			// 多い場合
			/* 最大コンボ数を更新 */
			this->PlayerStatusList->SetPlayerComboMaxCount(iNowCombo);
		}
	}
	else
	{
		// 終了している場合
		/* コンボ数をリセット */
		this->PlayerStatusList->SetPlayerComboNowCount(0);

		/* ランクを"無し"に設定 */
		this->iPlayerComboRank = COMBO_RANK_NONE;
	}

	/* コンボ数が1以上であるか確認 */
	if (iNowCombo > 0)
	{
		// 1以上である場合
		/* 現在のコンボ数からランクを設定する */
		if (iNowCombo >= this->iComboBorder[COMBO_RANK_S])
		{
			// Sランク
			/* ランクを"Sランク"に設定 */
			this->iPlayerComboRank = COMBO_RANK_S;
		}
		else if (iNowCombo >= this->iComboBorder[COMBO_RANK_A])
		{
			// Aランク
			/* ランクを"Aランク"に設定 */
			this->iPlayerComboRank = COMBO_RANK_A;
		}
		else if (iNowCombo >= this->iComboBorder[COMBO_RANK_B])
		{
			// Bランク
			/* ランクを"Bランク"に設定 */
			this->iPlayerComboRank = COMBO_RANK_B;
		}
		else if (iNowCombo >= this->iComboBorder[COMBO_RANK_C])
		{
			// Cランク
			/* ランクを"Cランク"に設定 */
			this->iPlayerComboRank = COMBO_RANK_C;
		}
		else
		{
			// Dランク
			/* ランクを"Dランク"に設定 */
			this->iPlayerComboRank = COMBO_RANK_D;
		}
	}

	/* 現在のコンボランクを設定 */
	this->PlayerStatusList->SetPlayerComboRunk(this->iPlayerComboRank);
}

// 描画
void SceneUi_Combo::Draw()
{
	/* 現在のコンボランクが"無し"以外であるか確認 */
	if (this->iPlayerComboRank != COMBO_RANK_NONE)
	{
		// ランクが"無し"以外である場合
		/* コンボフレーム描画(仮) */
		DrawGraph(100, 360, *this->piGrHandle_Combo_Frame, TRUE);

		/* コンボタイマー描写 */
		double dComboTimerPercent = (static_cast<double>(this->PlayerStatusList->iGetPlayerComboDuration()) / (INIT_ATTRIBUTES_COMBO_DURATION + this->PlayerStatusList->iGetAddComboTime())) * 100.0;
		DrawCircleGauge(189, 448, dComboTimerPercent, *this->piGrHandle_Combo_Timer);

		/* ランクを描写 */
		/* 描写予定のアルファベットのサイズを取得 */
		int iSizeX, iSizeY;
		GetGraphSize(*this->piGrHandle_Combo_Alphabet[this->iPlayerComboRank], &iSizeX, &iSizeY);

		/* アルファベット描写 */
		DrawGraph(189 - (iSizeX / 2), 448 - (iSizeY / 2), *this->piGrHandle_Combo_Alphabet[this->iPlayerComboRank], TRUE);
	}
}

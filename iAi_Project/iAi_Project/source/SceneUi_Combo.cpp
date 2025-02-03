/* 2025.01.28 ファイル作成 駒沢風助 */

#include "SceneUi_Combo.h"

/* UI(コンボ)クラスの定義 */

// コンストラクタ
SceneUi_Combo::SceneUi_Combo() : SceneBase("UI_Combo", 103, false)
{
	/* データリスト取得 */
	{
		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "ゲーム状態管理"を取得 */
		this->GameStatusList	= dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));

		/* "スコア関連管理"を取得 */
		this->ScoreList			= dynamic_cast<DataList_Score*>(gpDataListServer->GetDataList("DataList_Score"));
	}

	/* 画像読み込み */
	{
		/* コンボフレーム */
		this->iCgHandle_Combo_Frame			= LoadGraph("resource/ImageData/UI_Player_ComboGrade-Timer/UI_Player_ComboGrade_frame_fix.png");

		/* コンボタイマー */
		this->iCgHandle_Combo_Timer			= LoadGraph("resource/ImageData/UI_Player_ComboGrade-Timer/UI_Player_ComboTimer.png");

		/* コンボアルファベット */
		this->iCgHandle_Combo_Alphabet[0]	= LoadGraph("resource/ImageData/UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_D.png");
		this->iCgHandle_Combo_Alphabet[1]	= LoadGraph("resource/ImageData/UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_C.png");
		this->iCgHandle_Combo_Alphabet[2]	= LoadGraph("resource/ImageData/UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_B.png");
		this->iCgHandle_Combo_Alphabet[3]	= LoadGraph("resource/ImageData/UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_A.png");
		this->iCgHandle_Combo_Alphabet[4]	= LoadGraph("resource/ImageData/UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_S.png");
	}
}

// デストラクタ
SceneUi_Combo::~SceneUi_Combo()
{
	/* 画像削除 */
	{
		/* コンボフレーム */
		DeleteGraph(this->iCgHandle_Combo_Frame);

		/* コンボタイマー */
		DeleteGraph(this->iCgHandle_Combo_Timer);

		/* コンボアルファベット */
		DeleteGraph(this->iCgHandle_Combo_Alphabet[0]);
		DeleteGraph(this->iCgHandle_Combo_Alphabet[1]);
		DeleteGraph(this->iCgHandle_Combo_Alphabet[2]);
		DeleteGraph(this->iCgHandle_Combo_Alphabet[3]);
		DeleteGraph(this->iCgHandle_Combo_Alphabet[4]);
	}
}

// 計算
void SceneUi_Combo::Process()
{
	/* ゲーム状態が"ゲーム実行"以外であるならシーンを削除 */
	if (this->GameStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
		return;
	}

	/* コンボ継続時間が終了しているか確認 */
	if (this->ScoreList->iGetPlayerComboDuration() > 0)
	{
		// 終了していない場合
		/* コンボ継続時間を減算 */
		this->ScoreList->SetPlayerComboDuration(this->ScoreList->iGetPlayerComboDuration() - 1);

		/* 現在のコンボ数が最大コンボ数より多いか確認 */
		if (this->ScoreList->iGetPlayerComboNowCount() > this->ScoreList->iGetPlayerComboMaxCount())
		{
			// 多い場合
			/* 最大コンボ数を更新 */
			this->ScoreList->SetPlayerComboMaxCount(this->ScoreList->iGetPlayerComboNowCount());
		}
	}
	else
	{
		// 終了している場合
		/* コンボ数をリセット */
		this->ScoreList->SetPlayerComboNowCount(0);
	}
}

// 描画
void SceneUi_Combo::Draw()
{
	/* コンボフレーム描画(仮) */
	DrawGraph(100, 360, this->iCgHandle_Combo_Frame, TRUE);

	/* コンボタイマー描写(仮) */
	double dComboTimerPercent = (static_cast<double>(this->ScoreList->iGetPlayerComboDuration()) / PLAYER_COMBO_DURATION) * 100.0;
	DrawCircleGauge(101 + (176 / 2), 360 + (176 / 2), dComboTimerPercent, this->iCgHandle_Combo_Timer);

	/* 現在のコンボ数描写(仮) */
	DrawFormatString(400, 360 + 16 * 0, GetColor(255, 255, 255), "現在のコンボ数 : %d", this->ScoreList->iGetPlayerComboNowCount());

	/* 最大コンボ数描写(仮) */
	DrawFormatString(400, 360 + 16 * 1, GetColor(255, 255, 255), "最大コンボ数 :  %d", this->ScoreList->iGetPlayerComboMaxCount());

	/* コンボの残り継続時間描写(仮) */
	DrawFormatString(400, 360 + 16 * 2, GetColor(255, 255, 255), "コンボ継続時間 : %d", this->ScoreList->iGetPlayerComboDuration());
}

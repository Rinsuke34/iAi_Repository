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
}

// デストラクタ
SceneUi_Combo::~SceneUi_Combo()
{

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
		if (iNowCombo >= COMBO_RANK_BORDER_S)
		{
			// Sランク
			/* ランクを"Sランク"に設定 */
			this->iPlayerComboRank = COMBO_RANK_S;
		}
		else if (iNowCombo >= COMBO_RANK_BORDER_A)
		{
			// Aランク
			/* ランクを"Aランク"に設定 */
			this->iPlayerComboRank = COMBO_RANK_A;
		}
		else if (iNowCombo >= COMBO_RANK_BORDER_B)
		{
			// Bランク
			/* ランクを"Bランク"に設定 */
			this->iPlayerComboRank = COMBO_RANK_B;
		}
		else if (iNowCombo >= COMBO_RANK_BORDER_C)
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

		/* コンボタイマー描写(仮) */
		double dComboTimerPercent = (static_cast<double>(this->PlayerStatusList->iGetPlayerComboDuration()) / INIT_ATTRIBUTES_COMBO_DURATION) * 100.0;
		DrawCircleGauge(101 + (176 / 2), 360 + (176 / 2), dComboTimerPercent, *this->piGrHandle_Combo_Timer);

		/* ランクを描写 */
		DrawGraph(100 + (176 / 2) - (118 / 2), 360 + (176 / 2) - (156 / 2), *this->piGrHandle_Combo_Alphabet[this->iPlayerComboRank], TRUE);
	}

	/* 現在のコンボ数描写(仮) */
	DrawFormatString(400, 360 + 16 * 0, GetColor(255, 255, 255), "現在のコンボ数 : %d", this->PlayerStatusList->iGetPlayerComboNowCount());

	/* 最大コンボ数描写(仮) */
	DrawFormatString(400, 360 + 16 * 1, GetColor(255, 255, 255), "最大コンボ数 :  %d", this->PlayerStatusList->iGetPlayerComboMaxCount());

	/* コンボの残り継続時間描写(仮) */
	DrawFormatString(400, 360 + 16 * 2, GetColor(255, 255, 255), "コンボ継続時間 : %d", this->PlayerStatusList->iGetPlayerComboDuration());
}

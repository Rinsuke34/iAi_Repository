/* 2025.01.28 ファイル作成 駒沢風助 */

#include "SceneUi_Combo.h"

/* UI(コンボ)クラスの定義 */

// コンストラクタ
SceneUi_Combo::SceneUi_Combo() : SceneBase("UI_Combo", 103, false)
{
	/* データリスト取得 */
	{
		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "ゲーム状態管理"を取得 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
	}

	/* 画像読み込み */
	{
		/* コンボフレーム */
		this->iCgHandle_Combo_Frame			= LoadGraph("resource/ImageData/UI_Player_ComboGrade-Timer/UI_Player_ComboGrade_frame.png");

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
}

// 描画
void SceneUi_Combo::Draw()
{
	/* コンボフレーム描画(仮) */
	DrawGraph(100, 360, this->iCgHandle_Combo_Frame, TRUE);

	/* コンボタイマー描写(仮) */
	DrawGraph(100, 360, this->iCgHandle_Combo_Timer, TRUE);
}

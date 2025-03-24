/* 2025.03.24 ファイル作成 駒沢風助 */

#include "SceneUi_OperationInstructions.h"

/* UI(操作説明)クラスの定義 */
// コンストラクタ
SceneUi_OperationInstructions::SceneUi_OperationInstructions() : SceneBase("UI_OperationInstructions", 107, false)
{
	/* データリスト取得 */
	{
		/* "オプション設定管理"を取得 */
		this->OptionList		= dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));

		/* "プレイヤー状態管理"を取得 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "ステージ状態管理"を取得 */
		this->StatusStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 操作説明画像ベース(0:コントローラー、1:キーボード) */
		this->piGrHandle_Base[0]	= ImageList->piGetImage("UI_Operation/UI_Guide_CS");
		this->piGrHandle_Base[1]	= ImageList->piGetImage("UI_Operation/UI_Guide_KM");

		/* 通常時操作説明画像(0:コントローラー、1:キーボード) */
		this->piGrHandle_Attack[0]	= ImageList->piGetImage("UI_Operation/UI_Guide_CS_AttackOnly");
		this->piGrHandle_Attack[1]	= ImageList->piGetImage("UI_Operation/UI_Guide_KM_AttackOnly");

		/* クナイ構え時操作説明画像(0:コントローラー、1:キーボード) */
		this->piGrHandle_Kunai[0]	= ImageList->piGetImage("UI_Operation/UI_Guide_CS_KunaiOnly");
		this->piGrHandle_Kunai[1]	= ImageList->piGetImage("UI_Operation/UI_Guide_KM_KunaiOnly");
	}

	/* 初期化 */
	this->iDrawTypeNo = 0;				// 描画タイプ番号(0:コントローラー、1:キーボード)
}

// 計算
void SceneUi_OperationInstructions::Process()
{
	/* ゲーム状態が"ゲーム実行"以外であるならシーンを削除 */
	if (this->StatusStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
		return;
	}
}

// 描画
void SceneUi_OperationInstructions::Draw()
{
	/* キーボード描写であるか確認 */
	if (OptionList->bGetOperation_Keyboard() == true)
	{
		// キーボード描写である場合
		/* 描写タイプ番号をキーボード描写に設定 */
		this->iDrawTypeNo = 1;
	}
	else
	{
		// キーボード描写でない場合
		/* 描写タイプ番号をコントローラー描写に設定 */
		this->iDrawTypeNo = 0;
	}

	/* 操作説明画像ベース描写 */
	DrawGraph(1330, 870, *this->piGrHandle_Base[this->iDrawTypeNo], TRUE);

	/* プレイヤーの攻撃状態が遠距離攻撃構え中"であるか確認 */
	if (this->PlayerStatusList->iGetPlayerAttackState() == PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE)
	{
		// 遠距離攻撃構え中である場合
		/* クナイ構え時操作説明画像描写 */
		DrawGraph(1330, 870, *this->piGrHandle_Kunai[this->iDrawTypeNo], TRUE);
	}
	else
	{
		// 遠距離攻撃構え中でない場合
		/* 通常時操作説明画像描写 */
		DrawGraph(1330, 870, *this->piGrHandle_Attack[this->iDrawTypeNo], TRUE);
	}
}

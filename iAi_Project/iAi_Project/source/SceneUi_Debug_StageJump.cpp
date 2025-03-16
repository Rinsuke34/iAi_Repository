/* 2025.03.11 ファイル作成 駒沢風助 */

#include "SceneUi_Debug_StageJump.h"

/* UI(デバッグメニュー/ステージジャンプ)クラスの定義 */
// コンストラクタ
SceneUi_Debug_StageJump::SceneUi_Debug_StageJump() : SceneBase("UI_Debug_StageJump", 201, true)
{
	/* データリスト取得 */
	{
		/* "ステージ状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* 初期化 */
	this->iJumpStageNo = 0;
}

// 計算
void SceneUi_Debug_StageJump::Process()
{
	/* 上が押されているか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
	{
		// 押されている場合
		/* ステージ番号を+1する */
		this->iJumpStageNo += 1;
	}

	/* 下が押されているか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
	{
		// 押されている場合
		/* ステージ番号を-1する */
		this->iJumpStageNo -= 1;
	}

	/* 決定が押されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// 押されている場合
		/* ステージ状態を"ステージジャンプ"に設定 */
		this->StageStatusList->SetGameStatus(GAMESTATUS_STAGE_JUMP);

		/* ジャンプ後ステージ番号を設定 */
		this->StageStatusList->SetJumpStageNo(this->iJumpStageNo);

		/* シーンを削除する */
		this->bDeleteFlg = true;
	}

	/* キャンセルが押されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
	{
		// 押されている場合
		/* シーンを削除する */
		this->bDeleteFlg = true;
	}

	/* ステージ番号を範囲内に変更 */
	if (this->iJumpStageNo < 0)
	{
		// 0未満の場合
		/* ステージ番号を初期化する */
		this->iJumpStageNo = 0;
	}
	else if (this->iJumpStageNo >= STAGE_MAX)
	{
		// ステージ数以上の場合
		/* ステージ番号を最後のステージに設定 */
		this->iJumpStageNo = STAGE_MAX - 1;
	}
}

// 描画
void SceneUi_Debug_StageJump::Draw()
{
	DrawBox(850, 350, 1400, 350 + 16 * 1, GetColor(0, 0, 0), TRUE);
	DrawFormatString(850, 350, GetColor(255, 255, 255), "ジャンプ後ステージ番号 :");
	DrawFormatString(1200, 350, GetColor(255, 255, 255), STAGE_NAME[this->iJumpStageNo].c_str());
}

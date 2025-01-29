/* 2025.01.27 駒沢風助 ファイル作成 */

#include "EnemyBasic.h"

/* 基本エネミークラスの定義 */

// コンストラクタ
EnemyBasic::EnemyBasic() : EnemyBase()
{
	/* 初期化 */
	this->iPlayerLockOnType	= PLAYER_LOCKON_NONE;	// ロックオンされていない状態にする
	this->iCoreFrameNo		= -1;					// コアフレーム番号を初期化
}

// デストラクタ
EnemyBasic::~EnemyBasic()
{
	/* プレイヤーのコンボ数加算＆継続時間リセット */
	{
		/* データリスト取得 */
		DataList_Score* ScoreList = dynamic_cast<DataList_Score*>(gpDataListServer->GetDataList("DataList_Score"));

		/* プレイヤーのコンボ数加算 */
		ScoreList->SetPlayerComboNowCount(ScoreList->iGetPlayerComboNowCount() + 1);

		/* プレイヤーのコンボ継続時間リセット */
		ScoreList->SetPlayerComboDuration(PLAYER_COMBO_DURATION);
	}
}

// コアフレーム番号取得
void EnemyBasic::LoadCoreFrameNo()
{
	/* コアフレーム番号を取得 */
	this->iCoreFrameNo = MV1SearchFrame(this->iModelHandle, "Core");
}

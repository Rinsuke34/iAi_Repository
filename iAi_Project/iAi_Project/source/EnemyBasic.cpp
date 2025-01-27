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

// コアフレーム番号取得
void EnemyBasic::LoadCoreFrameNo()
{
	/* コアフレーム番号を取得 */
	this->iCoreFrameNo = MV1SearchFrame(this->iModelHandle, "Core");
}

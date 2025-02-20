/* 2025.02.19 菊池雅道 ファイル作成 */

#include "EffectManualDelete_PlayerFollow_Frame.h"

/* 手動で削除タイミングを設定するエフェクトクラスの定義 */
// ※プレイヤーのフレームに自動追従
// コンストラクタ
EffectManualDelete_PlayerFollow_Frame::EffectManualDelete_PlayerFollow_Frame(int iFrameHandle) : EffectManualDelete()
{
	/* フレームハンドル番号を設定 */
	this->iFrameHandle = iFrameHandle;	

	/* プレイヤー取得 */
	this->pCharacterPlayer = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();

	/* プレイヤーモデルのハンドルを取得 */
	this->iModelHandle = this->pCharacterPlayer->iGetModelHandle();
}

// 更新
void EffectManualDelete_PlayerFollow_Frame::Update()
{
	/* 座標更新(設定したフレーム座標に) */
	this->vecPosition = MV1GetFramePosition(this->iModelHandle, this->iFrameHandle);

	/* エフェクト座標更新 */
	Effect_PosUpdate();

	/* エフェクト回転量更新 */
	Effect_RotationUpdate();
}

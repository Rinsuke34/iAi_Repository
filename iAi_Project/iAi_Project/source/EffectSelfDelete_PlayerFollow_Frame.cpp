/* 2025.02.20 菊池雅道 ファイル作成 */

#include "EffectSelfDelete_PlayerFollow_Frame.h"

/* 時間経過で削除されるエフェクトクラスの定義 */
// コンストラクタ
EffectSelfDelete_PlayerFollow_Frame::EffectSelfDelete_PlayerFollow_Frame(int iFrameHandle) : EffectSelfDelete()
{
	/* フレームハンドル番号を設定 */
	this->iFrameHandle = iFrameHandle;

	/* プレイヤー取得 */
	this->pCharacterPlayer = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();

	/* プレイヤーモデルのハンドルを取得 */
	this->iModelHandle = this->pCharacterPlayer->iGetModelHandle();
}

// 更新
void EffectSelfDelete_PlayerFollow_Frame::Update()
{
	/* 削除カウントを確認 */
	if (this->iDeleteCount > 0)
	{
		/* カウントを減算 */
		this->iDeleteCount--;
	}
	else
	{
		/* 削除フラグを有効化 */
		this->bDeleteFlg = true;
	}

	/* 座標更新(設定したフレーム座標に) */
	this->vecPosition = MV1GetFramePosition(this->iModelHandle, this->iFrameHandle);

	/* エフェクト座標更新 */
	Effect_PosUpdate();

	/* エフェクト回転量更新 */
	Effect_RotationUpdate();
}

/* 2025.02.04 菊池雅道	ファイル作成 */

#include "CharacterPlayer.h"

// 描写
void CharacterPlayer::Draw()
{
	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);

	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転 */
	MV1SetRotationXYZ(this->iModelHandle, VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

	/* モーションの再生時間を設定 */
	MV1SetAttachAnimTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move(), this->PlayerStatusList->fGetMotionTimer_Move());
	MV1SetAttachAnimTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack(), this->PlayerStatusList->fGetMotionTimer_Attack());

	/* モーションのブレンド率を設定 */
	MV1SetAttachAnimBlendRate(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move(), 0.3f);
	MV1SetAttachAnimBlendRate(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack(), 0.7f);

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);


	/* テスト用 */
	DrawFormatString(200, 500 + 16 * 0, GetColor(255, 255, 255), "移動系");
	DrawFormatString(200, 500 + 16 * 1, GetColor(255, 255, 255), "現在モーション番号 : %f", this->PlayerStatusList->iGetPlayerMotion_Move());
	DrawFormatString(200, 500 + 16 * 2, GetColor(255, 255, 255), "変更前モーション番号 : %f", this->PlayerStatusList->iGetPlayerMotion_Move_Old());
	DrawFormatString(200, 500 + 16 * 3, GetColor(255, 255, 255), "再生時間 : %f", this->PlayerStatusList->fGetMotionTimer_Move());
	DrawFormatString(200, 500 + 16 * 4, GetColor(255, 255, 255), "最終再生時間 : %f", this->PlayerStatusList->fGetMotionTimer_Move_End());
	DrawFormatString(200, 500 + 16 * 5, GetColor(255, 255, 255), "攻撃系");
	DrawFormatString(200, 500 + 16 * 6, GetColor(255, 255, 255), "現在モーション番号 : %f", this->PlayerStatusList->iGetPlayerMotion_Attack());
	DrawFormatString(200, 500 + 16 * 7, GetColor(255, 255, 255), "変更前モーション番号 : %f", this->PlayerStatusList->iGetPlayerMotion_Attack_Old());
	DrawFormatString(200, 500 + 16 * 8, GetColor(255, 255, 255), "再生時間 : %f", this->PlayerStatusList->fGetMotionTimer_Attack());
	DrawFormatString(200, 500 + 16 * 9, GetColor(255, 255, 255), "最終再生時間 : %f", this->PlayerStatusList->fGetMotionTimer_Attack_End());
}

// 当たり判定描写
void CharacterPlayer::CollisionDraw()
{
	CharacterBase::CollisionDraw();

	/* プレイヤー座標 */
	int iColor = GetColor(255, 0, 0);
	DrawLine3D(VAdd(this->vecPosition, VGet(+50, 0, 0)), VAdd(this->vecPosition, VGet(-50, 0, 0)), iColor);
	DrawLine3D(VAdd(this->vecPosition, VGet(0, 0, +50)), VAdd(this->vecPosition, VGet(0, 0, -50)), iColor);

	/* 垂直方向のコリジョン */
	iColor = GetColor(0, 255, 0);
	DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, iColor);

	/* 並行方向のコリジョン */
	iColor = GetColor(0, 0, 255);
	DrawCapsule3D(this->stHorizontalCollision[0].vecCapsuleTop, this->stHorizontalCollision[0].vecCapsuleBottom, this->stHorizontalCollision[0].fCapsuleRadius, 16, iColor, iColor, FALSE);
	DrawCapsule3D(this->stHorizontalCollision[1].vecCapsuleTop, this->stHorizontalCollision[1].vecCapsuleBottom, this->stHorizontalCollision[1].fCapsuleRadius, 16, iColor, iColor, FALSE);

	/* 強攻撃を使用する場合 */
	if (this->PlayerStatusList->bGetMeleeSearchCollisionUseFlg() == true)
	{
		/* 強攻撃ロックオン範囲 */
		iColor = GetColor(255, 0, 255);
		COLLISION_CAPSULE stMeleeCollision = this->PlayerStatusList->stGetMeleeSearchCollision();
		DrawCapsule3D(stMeleeCollision.vecCapsuleTop, stMeleeCollision.vecCapsuleBottom, stMeleeCollision.fCapsuleRadius, 16, iColor, iColor, FALSE);

		/* 強攻撃移動後座標 */
		iColor = GetColor(255, 255, 0);
		DrawCapsule3D(this->stMeleeStrongMoveCollsion.vecCapsuleTop, this->stMeleeStrongMoveCollsion.vecCapsuleBottom, this->stMeleeStrongMoveCollsion.fCapsuleRadius, 16, iColor, iColor, FALSE);
	}

	/* カメラ注視点 */
	iColor = GetColor(0, 255, 255);
	DrawLine3D(VAdd(this->PlayerStatusList->vecGetCameraTarget(), VGet(+50, 0, 0)), VAdd(this->PlayerStatusList->vecGetCameraTarget(), VGet(-50, 0, 0)), iColor);
	DrawLine3D(VAdd(this->PlayerStatusList->vecGetCameraTarget(), VGet(0, 0, +50)), VAdd(this->PlayerStatusList->vecGetCameraTarget(), VGet(0, 0, -50)), iColor);
}
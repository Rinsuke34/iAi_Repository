/* 2025.02.04 菊池雅道	ファイル作成 */

#include "CharacterPlayer.h"

// 描写
void CharacterPlayer::Draw()
{
	/* 攻撃モーション使用フラグ */
	bool	bUseAttackMotionFlg = false;

	/* 攻撃モーションを使用するか(攻撃モーションが"無し"以外であるか)確認 */
	if (this->PlayerStatusList->iGetPlayerMotion_Attack() != MOTION_ID_ATTACK_NONE)
	{
		// 攻撃モーションを使用する場合
		/* 攻撃モーション使用フラグを有効にする */
		bUseAttackMotionFlg = true;
	}

	/* モーションの再生時間設定 */
	{
		/* 移動系モーションの再生時間設定 */
		MV1SetAttachAnimTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move(), this->PlayerStatusList->fGetMotionTimer_Move());

		/* 攻撃系モーションの再生時間設定 */
		/* 攻撃モーション使用フラグが有効であるか確認 */
		if (bUseAttackMotionFlg == true)
		{
			// 有効である場合
			/* 攻撃系モーションの再生時間設定 */
			MV1SetAttachAnimTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack(), this->PlayerStatusList->fGetMotionTimer_Attack());
		}
	}

	/* モーションのブレンド率を設定 */
	{
		/* 全身のモーションブレンド率 */
		float	fWholeMoveBlendrate		= 1.f;		// 移動モーション
		float	fWholeAttackBlendrate	= 0.f;		// 攻撃モーション

		/* 上半身のモーションブレンド率 */
		float	fUpperMoveBlendRate		= 1.f;		// 移動モーション
		float	fUpperAttackBlendRate	= 0.f;		// 攻撃モーション

		/* 攻撃モーション使用フラグが有効であるか確認 */
		if (bUseAttackMotionFlg == true)
		{
			// 有効である場合
			/* 攻撃モーションが"強攻撃(終了)"であるか確認 */
			if (this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
			{
				// "強攻撃(終了)"である場合
				/* 全身のモーションブレンド率を設定 */
				// ※攻撃モーションを100パーセントに設定
				fWholeMoveBlendrate		= 0.f;
				fWholeAttackBlendrate	= 1.f;
			}
			
			/* 上半身のモーションブレンド率を設定 */
			// ※攻撃モーションを100パーセントに設定
			fUpperMoveBlendRate		= 0.f;
			fUpperAttackBlendRate	= 1.f;
		}

		/* 全身のブレンド率を設定 */
		MV1SetAttachAnimBlendRate(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move(),	fWholeMoveBlendrate);	// 移動モーション
		MV1SetAttachAnimBlendRate(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack(),	fWholeAttackBlendrate);	// 攻撃モーション

		/* 上半身のブレンド率を設定 */
		MV1SetAttachAnimBlendRateToFrame(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move(),	63, fUpperMoveBlendRate,	TRUE);
		MV1SetAttachAnimBlendRateToFrame(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack(),	63, fUpperAttackBlendRate,	TRUE);
	}

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);

	/* テスト用 */
	//float Draw;
	//DrawFormatString(600, 200 + 16 * 0, GetColor(255, 255, 255), "移動系");
	//Draw = this->PlayerStatusList->iGetPlayerMotion_Move();
	//DrawFormatString(600, 200 + 16 * 1, GetColor(255, 255, 255), "現在モーション番号 : %f", Draw);
	//Draw = this->PlayerStatusList->iGetPlayerMotion_Move_Old();
	//DrawFormatString(600, 200 + 16 * 2, GetColor(255, 255, 255), "変更前モーション番号 : %f", Draw);
	//Draw = this->PlayerStatusList->fGetMotionTimer_Move();
	//DrawFormatString(600, 200 + 16 * 3, GetColor(255, 255, 255), "再生時間 : %f", Draw);
	//Draw = this->PlayerStatusList->fGetMotionTimer_Move_End();
	//DrawFormatString(600, 200 + 16 * 4, GetColor(255, 255, 255), "最終再生時間 : %f", Draw);
	//DrawFormatString(600, 200 + 16 * 6, GetColor(255, 255, 255), "攻撃系");
	//Draw = this->PlayerStatusList->iGetPlayerMotion_Attack();
	//DrawFormatString(600, 200 + 16 * 7, GetColor(255, 255, 255), "現在モーション番号 : %f", Draw);
	//Draw = this->PlayerStatusList->iGetPlayerMotion_Attack_Old();
	//DrawFormatString(600, 200 + 16 * 8, GetColor(255, 255, 255), "変更前モーション番号 : %f", Draw);
	//Draw = this->PlayerStatusList->fGetMotionTimer_Attack();
	//DrawFormatString(600, 200 + 16 * 9, GetColor(255, 255, 255), "再生時間 : %f", Draw);
	//Draw = this->PlayerStatusList->fGetMotionTimer_Attack_End();
	//DrawFormatString(600, 200 + 16 * 10, GetColor(255, 255, 255), "最終再生時間 : %f", Draw);

	/* 移動量描写 */
	DrawFormatString(600, 200 + 16 * 0, GetColor(255, 255, 255), "移動量 X:%f, Y:%f, Z:%f", vecMoveSize.x, vecMoveSize.y, vecMoveSize.z);
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
	DrawLine3D(VAdd(this->StageStatusList->vecGetCameraTarget(), VGet(+50, 0, 0)), VAdd(this->StageStatusList->vecGetCameraTarget(), VGet(-50, 0, 0)), iColor);
	DrawLine3D(VAdd(this->StageStatusList->vecGetCameraTarget(), VGet(0, 0, +50)), VAdd(this->StageStatusList->vecGetCameraTarget(), VGet(0, 0, -50)), iColor);
}
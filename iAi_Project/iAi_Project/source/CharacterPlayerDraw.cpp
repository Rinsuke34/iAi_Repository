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
		// 移動モーション
		float fBlendRate = this->PlayerStatusList->fGetNowMoveMotionBlendRate();
		MV1SetAttachAnimBlendRate(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move(),		fWholeMoveBlendrate * (1.f - fBlendRate));
		MV1SetAttachAnimBlendRate(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move_Old(),	fWholeMoveBlendrate * fBlendRate);
		// 攻撃モーション
		fBlendRate = this->PlayerStatusList->fGetNowAttackMotionBlendRate();
		MV1SetAttachAnimBlendRate(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack(), fWholeAttackBlendrate);

		/* 上半身のブレンド率を設定 */
		// 移動モーション
		fBlendRate = this->PlayerStatusList->fGetNowMoveMotionBlendRate();
		MV1SetAttachAnimBlendRateToFrame(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move(),		this->iUpperBodyFrameNo,	fUpperMoveBlendRate * (1.f - fBlendRate), TRUE);
		MV1SetAttachAnimBlendRateToFrame(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move_Old(),	this->iUpperBodyFrameNo,	fUpperMoveBlendRate * fBlendRate, TRUE);
		// 攻撃モーション
		fBlendRate = this->PlayerStatusList->fGetNowAttackMotionBlendRate();
		MV1SetAttachAnimBlendRateToFrame(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack(), this->iUpperBodyFrameNo, fUpperAttackBlendRate, TRUE);
	}

	/* シェイプを適用 */
	MV1SetShapeRate(this->iModelHandle, this->iShapeNo_Blink, this->fShapeRate);

	/* プレイヤー状態が"近接攻撃中(強)"以外であるか確認 */
	if (this->PlayerStatusList->iGetPlayerAttackState() != PLAYER_ATTACKSTATUS_MELEE_STRONG)
	{
		// 近接攻撃中(強)以外である場合
		/* モデル描写 */
		MV1DrawModel(this->iModelHandle);
	}
}

// 発光描写
void CharacterPlayer::BloomDraw()
{
	/* プレイヤー状態が"近接攻撃中(強)"以外であるか確認 */
	if (this->PlayerStatusList->iGetPlayerAttackState() != PLAYER_ATTACKSTATUS_MELEE_STRONG)
	{
		// 近接攻撃中(強)以外である場合
		/* モデル描写 */
		CharacterBase::BloomDraw();
	}
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
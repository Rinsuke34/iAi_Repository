/* 2025.02.04 菊池雅道	ファイル作成 */
/* 2025.01.22 菊池雅道	攻撃処理追加 */
/* 2025.01.24 菊池雅道	攻撃処理追加 */
/* 2025.01.27 菊池雅道	エフェクト処理追加 */
/* 2025.02.03 菊池雅道	近距離攻撃(強)後の処理追加 */
/* 2025.02.05 菊池雅道	ステータス関連修正 */
/* 2025.02.07 菊池雅道	エフェクト処理修正 */
/* 2025.02.12 菊池雅道	遠距離攻撃処理追加 */
/* 2025.02.14 菊池雅道	遠距離攻撃処理追加 */
/* 2025.02.19 菊池雅道	エフェクト処理修正 */
/* 2025.02.21 菊池雅道	遠距離攻撃修正 */
/* 2025.02.26 菊池雅道	クールタイム処理追加 */
/* 2025.02.26 菊池雅道	近距離攻撃(強)処理修正 */
/* 2025.03.03 菊池雅道	近距離攻撃(強)処理修正 */
/* 2025.03.04 菊池雅道	スローモーション処理追加 */
/* 2025.03.04 菊池雅道	近距離攻撃(強)処理修正 */
/* 2025.03.06 菊池雅道	スローモーション処理修正 */
/* 2025.03.06 菊池雅道	近距離攻撃(強)処理修正 */
/* 2025.03.06 菊池雅道	エフェクト処理追加 */
/* 2025.03.10 菊池雅道	エフェクト処理追加 */
/* 2025.03.12 菊池雅道	スローモーション処理修正 */
/* 2025.03.13 駒沢風助	クナイ弾数設定 */
/* 2025.03.13 菊池雅道	クナイ処理変更 */
/* 2025.03.17 駒沢風助	画面エフェクト追加 */
/* 2025.03.17 菊池雅道	エフェクト処理追加 */
/* 2025.03.17 菊池雅道	近距離攻撃(強)処理修正 */
/* 2025.03.18 菊池雅道	エディットによる処理追加 */
/* 2025.03.21 菊池雅道	スローモーション処理追加 */
/* 2025.03.26 菊池雅道	クールタイム・遠距離攻撃処理修正 */
/* 2025.07.19 菊池雅道	コードリファクタリング */
/* 2025.10.15 菊池雅道	近距離攻撃(強)処理修正 */
/* 2025.11.23 菊池雅道	コードリファクタリング */
/* 2025.12.13 菊池雅道	コードリファクタリング */

#include "CharacterPlayer.h"

/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */
/* 2025.03.03 菊池雅道	近距離攻撃(強)処理修正 開始 */
/* 2025.03.04 菊池雅道	スローモーション処理追加	開始 */
/* 2025.03.17 菊池雅道	エフェクト処理追加	開始 */
/* 2025.03.21 菊池雅道	スローモーション処理追加 開始 */
// 攻撃状態遷移管理
void CharacterPlayer::Player_Attack_Transition()
{
	/* 攻撃状態の遷移は下記とする */
	//           --> 構え(近接)   ---> 弱攻撃(近接) --
	//           |                 |                 |
	// 自由状態 -|                 --> 強攻撃(近接) ---> 自由状態
	//           |                                   |
	//           --> 構え(遠距離) ---> 攻撃(遠距離) --

	/* プレイヤーの攻撃状態を取得 */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

	/* プレイヤーの攻撃状態に応じて処理を変更 */
	switch (iPlayerAttackState)
	{
		/* 自由状態 */
		case PLAYER_ATTACKSTATUS_FREE:
			/* 自由状態の処理 */
			Player_Attack_Free();
			break;
			
		/* 近接攻撃構え中 */
		case PLAYER_ATTACKSTATUS_MELEE_POSTURE:
			/* 近接攻撃(構え) */
			Player_Melee_Posture();
			break;

		/* 近接攻撃中(弱) */
		case PLAYER_ATTACKSTATUS_MELEE_WEEK:
			/* 近接攻撃(弱) */
			Player_Melee_Weak();
			break;

		/* 近接攻撃中(強) */
		case PLAYER_ATTACKSTATUS_MELEE_STRONG:
			/* 近距離攻撃(強) */
			Player_Charge_Attack();
			break;

		/* 遠距離攻撃構え中 */
		case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:
			/* 遠距離攻撃(構え) */
			Player_Projectile_Posture();
			break;

		/* 遠距離攻撃中 */
		case PLAYER_ATTACKSTATUS_PROJECTILE:
			/* 遠距離攻撃 */
			Player_Projectile();
			break;

		/* 死亡状態(操作不可) */
		case PLAYER_ATTACKSTATUS_DEAD:
			/* 処理を行わない */
			break;

	}
}
/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */
/* 2025.03.03 菊池雅道	近距離攻撃(強)処理修正 終了 */
/* 2025.03.04 菊池雅道	スローモーション処理追加	終了 */
/* 2025.03.17 菊池雅道	エフェクト処理追加	終了 */
/* 2025.03.21 菊池雅道	スローモーション処理追加 終了 */

// 自由状態
void CharacterPlayer::Player_Attack_Free()
{
	//近接攻撃(強)の処理
	/* 攻撃入力がされているか確認 */
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK))
	{
		// 攻撃入力がされている場合
		/* プレイヤー状態を"近接攻撃構え中"に設定 */
		this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_MELEE_POSTURE);
		return;
	}

	// 近距離攻撃(強)で敵を倒した後の処理
	/* プレイヤーが近接攻撃(強)で敵を倒した後かのフラグを確認 */
	if (this->PlayerStatusList->bGetPlayerMeleeStrongEnemyAttackFlg() == true)
	{
		// 近接攻撃(強)で敵を倒した後の場合
		/* プレイヤーが近距離攻撃(強)を連続で行えるかのフラグを確認 */
		if (this->PlayerStatusList->bGetPlayerMeleeStrongContinuousFlg() == true)
		{
			//近距離攻撃(強)を連続で行える場合
			//連続攻撃可能のエフェクトとSEを出す
			Player_Continuous_Charge_Attack_Enabled_Process();
		}
		else
		{
			//近距離攻撃(強)を連続で行えない場合
			/* スローモーションフラグが有効であるか確認 */
			/* スローモーション終了 */
			this->Player_SlowMotion_Stop();
		}
	}
	else
	{
		// 近距離攻撃(強)で敵を倒した後でない場合		
		/* スローモーション終了 */
		this->Player_SlowMotion_Stop();
	}

	/* スローモーションが有効であるか確認 */
	if (this->StageStatusList->bGetGameSlowFlg() == true)
	{
		// 有効である場合
		/* スローモーションカウントの更新 */
		Player_UpdateSlowMotionCount();
	}

	// 遠距離攻撃の処理
	/* エイム(構え)入力がされているか確認 */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_AIM))
	{
		/* エイム(構え)キャンセルフラグが解除されている場合 */
		if (this->PlayerStatusList->bGetPlayerAimCancelledFlg() == false)
		{
			// エイム(構え)入力がされている場合
			/* プレイヤー状態を"遠距離攻撃構え中"に設定 */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE);
		}
	}
	// エイム(構え)がキャンセルされた後、ボタン押しっぱなしで再発動させないための処理
	/* エイム(構え)キャンセルフラグが設定されている場合 */
	else if (this->PlayerStatusList->bGetPlayerAimCancelledFlg() == true)
	{
		/* エイム(構え)ボタンを離したら */
		if (this->InputList->bGetGameInputAction(INPUT_REL, GAME_AIM) != true)
		{
			/* エイム(構え)キャンセルフラグを解除 */
			this->PlayerStatusList->SetPlayerAimCancelledFlg(false);
		}
	}
}

/* 2025.01.24 菊池雅道	攻撃処理追加		開始 */
/* 2025.01.26 駒沢風助	コード修正		開始*/
/* 2025.01.27 菊池雅道	エフェクト処理追加 開始 */
/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */
/* 2025.02.07 菊池雅道	エフェクト処理修正 開始 */
/* 2025.02.19 菊池雅道	エフェクト処理修正 開始 */
/* 2025.02.26 菊池雅道	近距離攻撃(強)処理修正	開始 */
/* 2025.03.03 菊池雅道	近距離攻撃(強)処理修正 開始 */
/* 2025.03.18 菊池雅道	エディットによる処理追加 開始 */
/* 2025.03.21 菊池雅道	スローモーション処理追加 開始 */
/* 2025.10.15 菊池雅道	近距離攻撃(強)処理修正 開始 */
/* 2025.11.23 菊池雅道	コードリファクタリング		開始 */
// 近接攻撃(構え)
void CharacterPlayer::Player_Melee_Posture()
{
	/* 近接攻撃(強)の切り替えフレーム数を取得 */
	int iMeleeStrongChangeFrame = this->PlayerStatusList->iGetPlayerMeleeStrongChangeChargeFrame();

	/* プレイヤーの現在の攻撃チャージフレームを取得 */
	int iNowAttakChargeFlame = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame();

	/* 近接攻撃(強)チャージ最大フレーム数を取得 */
	int iMeleeChargeMaxFlame = this->PlayerStatusList->iGetPlayerMeleeStrongMaxChargeFrame();

	/* プレイヤーの空中での近接攻撃(強)の回数を取得 */
	int iNowMeleeStrongAirCount = this->PlayerStatusList->iGetPlayerMeleeStrongAirCount();

	/* プレイヤーが近接攻撃(強)で敵を倒した後のカウントを取得 */
	int iPlayerMeleeStrongAfterCount = this->PlayerStatusList->iGetPlayerMeleeStrongAfterCount();

	/* 近接攻撃(強)で連続できる最大フレーム数を取得 */
	int iMeleeStrongContinuosMaxFrame = this->PlayerStatusList->iGetPlayerMeleeStrongContinusMaxFrame();

	// 近接攻撃(強)で敵を倒した後、一定時間内であれば攻撃チャージフレーム数を最大にする 
	if (bHandleAfterStrongKill(iPlayerMeleeStrongAfterCount, iMeleeStrongContinuosMaxFrame, iMeleeChargeMaxFlame))
	{
		iNowAttakChargeFlame = PlayerStatusList->iGetPlayerNowAttakChargeFlame();
	}

	/* 攻撃入力がされているか確認 */
	if (InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK))
	{
		// 攻撃入力がされている場合
		// 空中での近接攻撃(強)の制限を超えていたら、処理を行わない
		if (bHandleAirStrongLimit(iNowMeleeStrongAirCount))
		{
			return;
		}

		// 近接攻撃(強)で敵を倒した後、一定時間内であれば近接攻撃(強)を行う
		if (bHandleAfterStrongKillAttackTransition(iPlayerMeleeStrongAfterCount, iMeleeStrongContinuosMaxFrame, iMeleeChargeMaxFlame))
		{
			return;
		}	

	/* プレイヤーが近接攻撃(強)で敵を倒した後かのフラグを確認 */
	if (this->PlayerStatusList->bGetPlayerMeleeStrongEnemyAttackFlg() == true)
	{
		// 近接攻撃(強)で敵を倒した後の場合		
			/* 処理を行わない */
			return;
		}

		/* 近接攻撃(強)への切り替わり処理（チャージ到達時） */
		HandleChargeToStrongAttack(iNowAttakChargeFlame, iMeleeStrongChangeFrame, iMeleeStrongContinuosMaxFrame);

		/* 近接攻撃(強)チャージ処理 */
		ProcessCharge(iNowAttakChargeFlame, iMeleeStrongContinuosMaxFrame);

		/* チャージ移動量の適用 */
		ApplyChargeMovement();

		// チャージ中のロックオン処理
		HandleRockOnDuringCharge(iNowAttakChargeFlame, iMeleeStrongChangeFrame);
	}
	/* 攻撃入力を離したか確認 */
	else if (this->InputList->bGetGameInputAction(INPUT_REL, GAME_ATTACK) == true)
		{
		// 近距離攻撃(強)で敵を攻撃した後の場合
		if (this->PlayerStatusList->bGetPlayerMeleeStrongEnemyAttackFlg() == true)
		{
			/* 処理を行わない */
			return;
		}

		/* 攻撃ボタンを離したときの処理 */ 
		HandleAttackRelease(iNowAttakChargeFlame, iMeleeStrongChangeFrame, iMeleeChargeMaxFlame);
	}

	//エフェクトの削除
	CleanupEffectsIfPostureEnded();
	
}
/* 2025.01.24 菊池雅道	攻撃処理追加			終了*/
/* 2025.01.26 駒沢風助	コード修正				終了*/
/* 2025.01.27 菊池雅道	エフェクト処理追加 終了 */
/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */
/* 2025.02.07 菊池雅道	エフェクト処理修正 終了 */
/* 2025.02.19 菊池雅道	エフェクト処理修正 終了 */
/* 2025.02.26 菊池雅道	近距離攻撃(強)処理修正	終了 */
/* 2025.03.18 菊池雅道	エディットによる処理追加 終了 */
/* 2025.03.21 菊池雅道	スローモーション処理追加 終了 */
/* 2025.10.15 菊池雅道	近距離攻撃(強)処理修正		終了 */
/* 2025.11.23 菊池雅道	コードリファクタリング 終了 */

/* 2025.11.23 菊池雅道	コードリファクタリング		開始 */
// 近接攻撃(強)で敵を倒した後の処理
bool CharacterPlayer::bHandleAfterStrongKill(int iAfterCount, int iAfterContinueMax, int iChargeMax)
{
	/* プレイヤーが近接攻撃(強)で敵を倒した後かのフラグを確認 */
	if (!PlayerStatusList->bGetPlayerMeleeStrongEnemyAttackFlg())
	{
		// 近接攻撃(強)で敵を倒した後でない場合
		/* 処理を行わない */
		return false;
	}

	/* 近接攻撃(強)で敵を倒した後のカウントが一定値以上か確認 */
	if (iAfterCount > iAfterContinueMax)
	{
		// 近接攻撃(強)で敵を倒した後のカウントが一定値以上の場合
		/* スローモーション終了 */
		Player_SlowMotion_Stop();
		
		/* 処理を行わない */
		return false;
	}

	/* 近接攻撃(強)の攻撃チャージフレーム数を最大に設定 */
	PlayerStatusList->SetPlayerNowAttakChargeFlame(iChargeMax);

	/* 近距離攻撃(強)による移動距離のスケールを求める */
	float fMoveScale = this->PlayerStatusList->fGetPlayerMeleeStrongMoveScale();

	/* チャージフレーム数に移動距離のスケールを乗算し移動量を算出する */
	float fMoveDistance = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() * fMoveScale;

	/* 移動方向算出 */
	VECTOR vecMoveDirection = VNorm(VSub(this->StageStatusList->vecGetCameraTarget(), this->StageStatusList->vecGetCameraPosition()));

	/* 近接攻撃(強)による移動量を設定 */
	this->PlayerStatusList->SetPlayerChargeAttakTargetMove(VScale(vecMoveDirection, fMoveDistance));
			
	/* 近接攻撃(強)のロックオン処理を行う */
	Player_Charge_Attack_RockOn();			

	/* 処理を行った */
	return true;
}
/* 2025.11.23 菊池雅道	コードリファクタリング		終了 */

/* 2025.11.23 菊池雅道	コードリファクタリング		開始 */
// 空中での近接攻撃(強)の制限処理
bool CharacterPlayer::bHandleAirStrongLimit(int iAirCount)
{
		/* 空中での近接攻撃(強)の回数が最大数が超えていないか確認 */
	if (iAirCount < PlayerStatusList->iGetPlayerMeleeStrongAirMaxCount())
	{
		// 超えていない場合
		/* 近接攻撃(強)の処理を行う */
		return false;
	}
	
			/* プレイヤーの現在の攻撃チャージフレームを0設定 */
	PlayerStatusList->SetPlayerNowAttakChargeFlame(0);

			/* 近接攻撃(強)の処理を行わない */
	return true;
}
/* 2025.11.23 菊池雅道	コードリファクタリング		終了 */

/* 2025.11.23 菊池雅道	コードリファクタリング		開始 */
// 近接攻撃(強)で敵を倒した後の近接攻撃(強)遷移処理
bool CharacterPlayer::bHandleAfterStrongKillAttackTransition(int iAfterCount, int iAfterContinueMax, int iChargeMax)
{
		/* プレイヤーが近接攻撃(強)で敵を倒した後かのフラグを確認 */
	if (!PlayerStatusList->bGetPlayerMeleeStrongEnemyAttackFlg())
		{
		// 近接攻撃(強)で敵を倒した後でない場合
		/* 処理を行わない */
		return false;
	}

	/* 近接攻撃(強)で敵を倒した後のカウントが一定値以上か確認 */
	if (iAfterCount > iAfterContinueMax)
			{
		// 近接攻撃(強)で敵を倒した後のカウントが一定値以上の場合
		/* 処理を行わない */
		return false;
	}

	/* プレイヤーの状態を"近接攻撃中(強)"に設定 */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_MELEE_STRONG);

	/* プレイヤーのため攻撃用のカウントを初期化 */
	this->PlayerStatusList->SetPlayerMeleeStrongChargeCount(0);

	/* 落下の加速度を初期化 */
	this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);

				/* SE終了 */
	if (this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() >= iChargeMax)
	{
		gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_CHARGE_HOLD);
	}
	else if (this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() < iChargeMax)
	{
		gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_CHARGE);
	}

				/* プレイヤーの現在の攻撃チャージフレームをリセット */
	PlayerStatusList->SetPlayerNowAttakChargeFlame(0);

	/* 近接攻撃(強)で敵を倒した後のカウントをリセット */
	PlayerStatusList->SetPlayerMeleeStrongAfterCount(0);

	/* 溜めエフェクトを削除 */
	DeleteChargeEffect();

	return true;
}
/* 2025.11.23 菊池雅道	コードリファクタリング		終了 */

/* 2025.11.23 菊池雅道	コードリファクタリング		開始 */
// 近接攻撃(強)への切り替わり処理（チャージ到達時）
void CharacterPlayer::HandleChargeToStrongAttack(int iNowCharge, int iChangeFrame, int iChargeMax)
{
	/* 攻撃チャージフレームが強攻撃に達していなければ、処理を行わない */
	if (iNowCharge != iChangeFrame)
	{
		return;
	}

	/* エディットによる攻撃チャージフレームの短縮値を取得 */
	int iEditChargeFlameShortening = this->PlayerStatusList->iGetAddAttackChargeFrameShortening();

	//エディットによりチャージフレームが短くなりすぎないようにする
	/* チャージフレームが一定の値を超えていないか確認 */
	if (iNowCharge - iEditChargeFlameShortening > iChargeMax - PLAYER_MELEE_STRONG_MIN_CHARGE_FRAME)
	{
		// 超えている場合
		/* プレイヤーの現在の攻撃チャージフレームを一定の値に設定 */
		this->PlayerStatusList->SetPlayerNowAttakChargeFlame(iChargeMax - PLAYER_MELEE_STRONG_MIN_CHARGE_FRAME);
	}
	else
	{
		// 超えていない場合
		/* エディットによる攻撃チャージフレームの短縮を適用 */
		this->PlayerStatusList->SetPlayerNowAttakChargeFlame(iNowCharge - iEditChargeFlameShortening);
	}

	/* プレイヤーの現在の攻撃チャージフレームを取得 */
	iNowCharge = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame();

	/* プレイヤーモーションを"居合(溜め)"に変更 */
	this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_CHARGE);

	/* 溜めのSEを再生 */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_CHARGE);

	/* 溜めのエフェクトを刀の位置に生成 */
	this->pChargeEffect = std::make_shared<EffectManualDelete_PlayerFollow_Frame>(this->iKatanaFrameNo);
	this->pChargeEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_charge/FX_charge")));
	this->pChargeEffect->SetRotation(this->vecRotation);
	this->pChargeEffect->Initialization();
	this->ObjectList->SetEffect(this->pChargeEffect);
}
/* 2025.11.23 菊池雅道	コードリファクタリング		終了 */

/* 2025.11.23 菊池雅道	コードリファクタリング		開始 */
// 攻撃チャージ処理
void CharacterPlayer::ProcessCharge(int iNowCharge, int iChargeMax)
{
	/* チャージフレームが最大値を超えていないか確認 */
	if (iNowCharge <= iChargeMax)
	{
		// 超えていない場合
		/* プレイヤーの現在の攻撃チャージフレームを加算 */
		PlayerStatusList->SetPlayerNowAttakChargeFlame(iNowCharge + 1);

		/* 加算によりチャージフレームが最大値に達したか確認 */
		if ((iNowCharge + 1) == iChargeMax)
		{
			// チャージ完了時の処理
			OnChargeComplete();
		}
	}
}
/* 2025.11.23 菊池雅道	コードリファクタリング		終了 */

/* 2025.11.23 菊池雅道	コードリファクタリング		開始 */
// チャージ移動量の適用
void CharacterPlayer::ApplyChargeMovement()
{
	/* 近距離攻撃(強)による移動距離のスケールを求める */
	float fMoveScale = this->PlayerStatusList->fGetPlayerMeleeStrongMoveScale();

	/* チャージフレーム数に移動距離のスケールを乗算し移動量を算出する */
	float fMoveDistance = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() * fMoveScale;

	/* 移動方向算出 */
	VECTOR vecMoveDirection = VNorm(VSub(this->StageStatusList->vecGetCameraTarget(), this->StageStatusList->vecGetCameraPosition()));

	/* 近接攻撃(強)による移動量を設定 */
	this->PlayerStatusList->SetPlayerChargeAttakTargetMove(VScale(vecMoveDirection, fMoveDistance));
}
/* 2025.11.23 菊池雅道	コードリファクタリング		終了 */

// チャージ中のロックオン処理
void CharacterPlayer::HandleRockOnDuringCharge(int iNowCharge, int iChangeFrame)
{
	/* 攻撃チャージフレームが強攻撃に派生しているか確認 */
	if (iNowCharge >= iChangeFrame)
				{
		/* 近接攻撃(強)のロックオン処理を行う */
		Player_Charge_Attack_RockOn();
	}
}
/* 2025.11.23 菊池雅道	コードリファクタリング		終了 */

/* 2025.11.23 菊池雅道	コードリファクタリング		開始 */
// チャージ完了時の処理
void CharacterPlayer::OnChargeComplete()
{
	/* 溜めのSEを再生終了 */
	gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_CHARGE);

	/* 溜め居合チャージ完了のSEを再生 */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_CHARGE_COMPLETE);

	/* 溜めエフェクトが存在するか確認 */
	if (this->pChargeEffect != nullptr)
	{
		// 溜めエフェクトが存在する場合
		/* 溜めエフェクトは削除 */
		this->pChargeEffect->SetDeleteFlg(true);
		this->pChargeEffect = nullptr;
	}

	/* 溜め完了エフェクトを生成 */
	std::shared_ptr<EffectSelfDelete_PlayerFollow_Frame> pAddEffect = std::make_shared<EffectSelfDelete_PlayerFollow_Frame>(iKatanaFrameNo);
	pAddEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_charge_finish/FX_charge_finish")));
	pAddEffect->Initialization();
	pAddEffect->SetDeleteCount(PLAYER_CHARGE_FINISH_EFFECT_FRAME);
	this->ObjectList->SetEffect(pAddEffect);

	/* 溜め完了後エフェクトを生成 */
	this->pChargeHoldEffect = std::make_shared<EffectManualDelete_PlayerFollow_Frame>(iKatanaFrameNo);
	this->pChargeHoldEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_charge_hold/FX_charge_hold")));
	this->pChargeHoldEffect->SetRotation(this->vecRotation);
	this->pChargeHoldEffect->Initialization();
	this->ObjectList->SetEffect(this->pChargeHoldEffect);

	gpDataList_Sound->SE_PlaySound_Loop(SE_PLAYER_CHARGE_HOLD);
}
/* 2025.11.23 菊池雅道	コードリファクタリング		終了 */

/* 2025.11.23 菊池雅道	コードリファクタリング		開始 */
// 溜めエフェクトの生成
void CharacterPlayer::CreateChargeEffect()
{
	/* 溜めのエフェクトを刀の位置に生成 */
	this->pChargeEffect = std::make_shared<EffectManualDelete_PlayerFollow_Frame>(this->iKatanaFrameNo);
	this->pChargeEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_charge/FX_charge")));
	this->pChargeEffect->SetRotation(this->vecRotation);
	this->pChargeEffect->Initialization();
	this->ObjectList->SetEffect(this->pChargeEffect);
}
/* 2025.11.23 菊池雅道	コードリファクタリング		終了 */

/* 2025.11.23 菊池雅道	コードリファクタリング		開始 */
// 溜め関連エフェクトの削除
void CharacterPlayer::DeleteChargeEffect()
{
	//エフェクトが存在している場合、削除する
	if (this->pChargeEffect != nullptr)
	{
		/* 溜めエフェクトを削除 */
		this->pChargeEffect->SetDeleteFlg(true);
		this->pChargeEffect = nullptr;
	}
	if (this->pChargeHoldEffect != nullptr)
	{
		/* 溜め完了後エフェクトを削除 */
		this->pChargeHoldEffect->SetDeleteFlg(true);
		this->pChargeHoldEffect = nullptr;
	}
}
/* 2025.11.23 菊池雅道	コードリファクタリング		終了 */

/* 2025.11.23 菊池雅道	コードリファクタリング		開始 */
// 攻撃ボタンを離したときの処理
void CharacterPlayer::HandleAttackRelease(int iNowAttakChargeFlame,int iMeleeStrongChangeFrame,int iMeleeChargeMaxFlame)
{
	
	/* チャージフレームに応じて攻撃種別を変更 */
	if (iNowAttakChargeFlame < iMeleeStrongChangeFrame)
	{
	// 攻撃チャージフレームが近接攻撃(強)の切り替えフレーム数未満の場合
		/* プレイヤーの状態を"近接攻撃中(弱)"に設定 */
		this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_MELEE_WEEK);
	}
	else
	{
		// 攻撃チャージフレームが近接攻撃(強)の切り替えフレーム数以上の場合		
		/* プレイヤーの状態を"近接攻撃中(強)"に設定 */
		this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_MELEE_STRONG);

		/* プレイヤーが近距離攻撃(強)状態になってからのチャージフレーム数を設定 */ 
		this->PlayerStatusList->SetPlayerMeleeStrongChargeCount(0);

		/* 落下の加速度を初期化 */
		this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);

		/* SE終了 */
		if (this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() >= iMeleeChargeMaxFlame)
		{
			gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_CHARGE_HOLD);
		}
		else if (this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() < iMeleeChargeMaxFlame)
		{
			gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_CHARGE);
		}
	}

	/* チャージフレーム初期化 */
	this->PlayerStatusList->SetPlayerNowAttakChargeFlame(0);
}
/* 2025.11.23 菊池雅道	コードリファクタリング		終了 */

/* 2025.11.23 菊池雅道	コードリファクタリング		開始 */
// 近接攻撃(構え)エフェクトの後処理
void CharacterPlayer::CleanupEffectsIfPostureEnded()
{
	/* プレイヤーの攻撃状態が近接攻撃(構え)の場合 */
	if (PlayerStatusList->iGetPlayerAttackState() == PLAYER_ATTACKSTATUS_MELEE_POSTURE)
	{
		/* 処理を行わない */
		return;
	}

	/* プレイヤーの現在の攻撃チャージフレームをリセット */
	PlayerStatusList->SetPlayerNowAttakChargeFlame(0);
	
	/* 溜めエフェクトの削除 */
	DeleteChargeEffect();
}
/* 2025.11.23 菊池雅道	コードリファクタリング		終了 */

// 近接攻撃(弱)
void CharacterPlayer::Player_Melee_Weak()
{
	/* 2025.01.22 菊池雅道	攻撃処理追加			開始 */
	/* 2025.01.26 駒沢風助	コード修正				開始 */
	/* 2025.02.05 菊池雅道	ステータス関連修正		開始 */
	/* 2025.02.26 菊池雅道	クールタイム処理追加	開始 */
	/* 2025.03.06 菊池雅道	エフェクト処理追加		開始 */
	/* 2025.03.26 菊池雅道	攻撃処理追加			開始 */

	// クールタイムが残っている場合攻撃しない
	/* 近接攻撃(弱)のクールタイムを確認 */
	if (this->iMeleeWeakNowCoolTime > 0)
	{
		// クールタイムが残っている場合
		/* プレイヤー攻撃状態を"自由状態"に設定 */
		this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

		/* 近距離攻撃(弱)処理を行わない */
		return;
	}

	// 近接攻撃(弱)でない場合
	/* プレイヤーのモーションを近接攻撃(弱)に設定 */
	this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_WEAK);

	/* 近接攻撃として扱う弾を作成 */
	// ※現在のプレイヤーの向きに弾を作成
	this->pBulletMeleeWeak = std::make_shared<BulletPlayerMeleeWeak>();

	/* 攻撃の向きを設定 */
	this->pBulletMeleeWeak->SetRotation(VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

	/* 初期化を行う */
	this->pBulletMeleeWeak->Initialization();

	/* バレットリストに追加 */
	ObjectList->SetBullet(this->pBulletMeleeWeak);

	/* 近接攻撃(弱)のSEを再生 */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_NIAI);

	/* 攻撃ボイスを再生 */
	gpDataList_Sound->VOICE_PlaySound(VOICE_PLAYER_ACTION);

	/* 抜刀エフェクトを生成 */
	std::shared_ptr<EffectSelfDelete_PlayerFollow_Frame> pSheathEffect = std::make_shared<EffectSelfDelete_PlayerFollow_Frame>(iKatanaFrameNo);
	pSheathEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_seath_unseath/FX_seath_unseath")));
	pSheathEffect->Initialization();
	pSheathEffect->SetDeleteCount(PLAYER_SHEATH_FRAME);
	this->ObjectList->SetEffect(pSheathEffect);
	
	/* 近接攻撃(弱)のクールタイム設定値を取得 */
	int iMeleeWeakCoolTime = this->PlayerStatusList->iGetPlayerMeleeWeakCoolTime();

	/* 近接攻撃(弱)のクールタイム設定 */
	this->iMeleeWeakNowCoolTime = iMeleeWeakCoolTime;

	/* 自由状態に戻す */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
}
/* 2025.01.22 菊池雅道　攻撃処理追加	終了 */
/* 2025.01.26 駒沢風助	コード修正		終了 */
/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */
/* 2025.02.26 菊池雅道	クールタイム処理追加 終了 */
/* 2025.03.06 菊池雅道	エフェクト処理追加		終了 */
/* 2025.03.26 菊池雅道	攻撃処理追加			終了 */

/* 2025.01.22 菊池雅道	攻撃処理追加		開始 */
/* 2025.01.26 駒沢風助	コード修正		開始 */
/* 2025.02.03 菊池雅道	近距離攻撃(強)後の処理追加	開始 */
/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */
/* 2025.02.26 菊池雅道	近距離攻撃(強)処理修正		開始 */
/* 2025.03.03 菊池雅道	近距離攻撃(強)処理修正		開始 */
/* 2025.03.04 菊池雅道	近距離攻撃(強)処理修正		開始 */
/* 2025.03.06 菊池雅道	近距離攻撃(強)処理修正		開始 */
/* 2025.03.17 駒沢風助	画面エフェクト追加			開始 */
/* 2025.03.17 菊池雅道	近距離攻撃(強)処理修正		開始 */
/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 近距離攻撃(強)
void CharacterPlayer::Player_Charge_Attack()
{
	/* 近距離攻撃(強)状態でのチャージフレーム数を取得 */
	const int chargeCount = PlayerStatusList->iGetPlayerMeleeStrongChargeCount();

	// チャージフレーム数に応じて処理を分岐
	if (chargeCount == 0)
	{
		// 0である場合(近接攻撃(強)開始直後)
		/* 近接攻撃(強)開始処理を行う */
		HandleChargeAttackStart();
	}
	else
	{
		// 1以上である場合(近接攻撃(強)移動中)
		/* 近接攻撃(強)移動処理を行う */
		HandleChargeAttackMove(chargeCount);
	}

	/* 近接攻撃(強)連続敵探索処理 */
	HandleContinuousChargeSearch();

	// フレームカウント更新
	PlayerStatusList->SetPlayerMeleeStrongChargeCount(chargeCount + 1);

}
/* 2025.01.22 菊池雅道	攻撃処理追加				終了 */
/* 2025.01.26 駒沢風助	コード修正					終了 */
/* 2025.02.03 菊池雅道	近距離攻撃(強)後の処理追加	終了 */
/* 2025.02.05 菊池雅道	ステータス関連修正			終了 */
/* 2025.02.26 菊池雅道	近距離攻撃(強)処理修正		終了 */
/* 2025.03.03 菊池雅道	近距離攻撃(強)処理修正		終了 */
/* 2025.03.04 菊池雅道	近距離攻撃(強)処理修正		終了 */
/* 2025.03.06 菊池雅道	近距離攻撃(強)処理修正		終了 */
/* 2025.03.17 駒沢風助	画面エフェクト追加			終了 */
/* 2025.03.17 菊池雅道	近距離攻撃(強)処理修正		終了 */
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 近距離攻撃(強)開始処理
void CharacterPlayer::HandleChargeAttackStart()
{
	/* プレイヤーのモーションを近距離攻撃(強)に設定 */
	this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_STRONG);

	/* 近距離攻撃(強)の音声処理 */
	PlayChargeAttackSounds();

	/* 近距離攻撃(強)の空中回数管理 */
	HandleAirStrongAttackCount();

	/* 近距離攻撃(強)の移動地点設定 */
	SetupChargeAttackTargetPosition();

	/* 画面エフェクトの生成 */
	CreateScreenEffectLine();
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 *

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 近距離攻撃(強)の音声再生処理
void CharacterPlayer::PlayChargeAttackSounds()
{
	/* "溜め居合攻撃"のSEを再生 */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_SPIAI);

	/* "溜め居合放電"のSEを再生 */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_SPIAI_ELEC);

	/* 近距離攻撃(強)ボイスを再生 */
	gpDataList_Sound->VOICE_PlaySound(VOICE_PLAYER_STRONG_MELEE);
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 近距離攻撃(強)の空中回数管理
void CharacterPlayer::HandleAirStrongAttackCount()
{
	/* プレイヤーが着地している場合 */
	if (this->PlayerStatusList->bGetPlayerLandingFlg() == true)
		{
		//処理を行わない
		return;
	}

	/* 現在の空中での近距離攻撃(強)回数を取得 */
	int iNowMelleeStrongAirCount = this->PlayerStatusList->iGetPlayerMeleeStrongAirCount();

	/* 空中での近距離攻撃(強)回数を加算 */
	this->PlayerStatusList->SetPlayerMeleeStrongAirCount(iNowMelleeStrongAirCount + 1);
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 近距離攻撃(強)の移動地点設定
void CharacterPlayer::SetupChargeAttackTargetPosition()
{
	/* ロックオン中のエネミーを取得 */
	std::shared_ptr<Enemy_Basic> pLockOnEnemy = this->PlayerStatusList->pGetPlayerLockOnEnemy();

	/* 近接攻撃(強)による移動量を取得 */
	VECTOR vecMoveDirection = this->PlayerStatusList->vecGetPlayerChargeAttakTargetMove();

	// ロックオン中のエネミーが存在するか確認
	if (pLockOnEnemy == nullptr)
	{
		// 存在しない場合(敵に攻撃しない場合)
		/* 近接攻撃(強)での撃破数をリセット */
		this->PlayerStatusList->SetMeleeStrongDestroyCount(0);
		return;
	}

	/* 空中での近接攻撃(強)の回数をリセット */
	this->PlayerStatusList->SetPlayerMeleeStrongAirCount(0);

	/* 敵を攻撃したフラグを設定 */
	this->PlayerStatusList->SetPlayerMeleeStrongEnemyAttackFlg(true);

	/* 近距離攻撃(強)に伴うプレイヤー落下防止処理 */
	AdjustMoveForPlatformLanding(vecMoveDirection);

	/* 移動量をプレイヤーの現在位置からロックオン中のエネミーの位置に修正 */
	vecMoveDirection = VSub(pLockOnEnemy->vecGetPosition(), this->vecPosition);

	/* 近接攻撃(強)後の接地フラグを確認 */
	if(this->PlayerStatusList->bGetPlayerLandingAfterMeleeStrongFlg() == true)
	{
		// 攻撃後プレイヤーが接地する場合
		/* エネミーの位置から追加で移動(突き抜ける感じを出すため) */
		vecMoveDirection = VAdd(vecMoveDirection, VScale(VNorm(vecMoveDirection), PLAYER_MELEE_STRONG_THROUGH_SCALE));
	}

	/* 近接攻撃(強)による移動量を設定 */
	this->PlayerStatusList->SetPlayerChargeAttakTargetMove(vecMoveDirection);
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 近距離攻撃(強)に伴うプレイヤー落下防止処理
void CharacterPlayer::AdjustMoveForPlatformLanding(VECTOR& vecMoveDirection)
{	
	//移動後の座標に足場があるか確認し、プレイヤーが落ちないようにする処理			
	/* プレイヤーの足場を判定する線分 */
	COLLISION_LINE stCollisionLine;

	/* 移動後のプレイヤーの頂点から下方向へ向けた線分を作成 */
	stCollisionLine.vecLineStart = VAdd(this->vecGetPosition(), vecMoveDirection);
	stCollisionLine.vecLineStart.y += PLAYER_HEIGHT;
	stCollisionLine.vecLineEnd = stCollisionLine.vecLineStart;
	stCollisionLine.vecLineEnd.y -= PLAYER_HEIGHT + PLAYER_CLIMBED_HEIGHT;

	/* 足場とプレイヤーが接触するか確認する処理 */
	for (auto& platform : this->ObjectList->GetPlatformList())
	{
		/* 足場と線分の接触判定を行う */
		if (platform->HitCheck_Line(stCollisionLine).HitFlag)
		{
			/* 攻撃後の接地フラグを設定する */
			this->PlayerStatusList->SetPlayerLandingAfterMeleeStrongFlg(true);
			return;
		}
	}

	/* 攻撃後の接地フラグを解除する */
	this->PlayerStatusList->SetPlayerLandingAfterMeleeStrongFlg(false);
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 近距離攻撃(強)移動処理
void CharacterPlayer::HandleChargeAttackMove(int iChargeCount)
{
		/* 近接攻撃(強)による移動量を取得 */
		VECTOR vecMoveDirection = this->PlayerStatusList->vecGetPlayerChargeAttakTargetMove();
			
		/* 近接攻撃(強)の移動速度を取得 */
		float fMoveSpeed = this->PlayerStatusList->fGetPlayerMeleeStrongMoveSpeed();

		//近接攻撃(強)中に壁に当たった場合、下に移動しないようにする
		/* 壁との接触フラグを確認 */
	if (this->PlayerStatusList->bGetPlayerWallTouchFlg() == true)
	{
		// 壁に接触している場合
		/* 下方向に移動しているか確認 */
		if (vecMoveDirection.y <= 0)
		{
			// 下方向に移動している場合
			/* 移動量のY成分を0に設定 */
			vecMoveDirection.y = 0;
		}
	}

	/* 移動量をfloat型で取得 */
	float fMove = VSize(vecMoveDirection);
	/* 移動量を移動速度で割ってこの処理を行う回数を算出する */
	int	iMoveCount = (int)(fMove / fMoveSpeed);

	/* 現在のカウントと移動回数を比較 */
	if (iChargeCount <= iMoveCount)
	{
		// 現在のカウントが移動回数以下である場合
		/* 移動量分プレイヤーを移動させる */
		this->vecMove = VAdd(this->vecMove, VScale(VNorm(vecMoveDirection), fMoveSpeed));
	}
	else
	{
		// 最後の移動の場合
		/* 最後の移動量を取得 */
		FinishChargeAttack(vecMoveDirection, fMove, fMoveSpeed, iMoveCount);
	}

	/* 近距離攻撃(強)の攻撃判定を生成 */
	CreateChargeAttackBullet();

	/* 近距離攻撃(強)のエフェクトを生成 */
	CreateChargeAttackEffect();

}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 近距離攻撃(強)終了処理
void CharacterPlayer::FinishChargeAttack(const VECTOR& vecMoveDirection, float fMove, float fMoveSpeed, int iMoveCount)
{
	// 最後の移動の場合
	/* 最後の移動量を取得 */
	float	iLastMove = fMove - (iMoveCount * fMoveSpeed);

	/* 最後の移動量分プレイヤーを移動させる */
	this->vecMove = VAdd(this->vecMove, VScale(VNorm(vecMoveDirection), iLastMove));

	// それら以外である場合(一連の行動が終了した場合)
	/* プレイヤーの状態を"自由状態"に遷移 */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

	/* プレイヤーのモーションを"近距離攻撃(強)(終了)"に変更 */
	this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_STRONG_END);

	/* ロックオン範囲コリジョン使用フラグを無効化 */
	this->PlayerStatusList->SetMeleeSearchCollisionUseFlg(false);
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 近距離攻撃(強)攻撃判定生成
void CharacterPlayer::CreateChargeAttackBullet()
{
	/* 近接攻撃として扱う弾を作成 */
	// ※通常の弾とは違いカプセル型で作成する
	std::shared_ptr<BulletPlayerMeleeStrong> pBulletMeleeStrong = std::make_shared<BulletPlayerMeleeStrong>();

	/* 弾に使用するカプセルを作成 */
	COLLISION_CAPSULE stBulletCollision;

	/* コリジョンの算出 */
	/* 当たり判定は大きめに取る(仮で半径をプレイヤーの全長に設定) */
	stBulletCollision.fCapsuleRadius = PLAYER_HEIGHT;

	/* 片方は現在のプレイヤーの中心に設定 */
	stBulletCollision.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT / 2.f, 0));

	/* もう片方は移動後(推定)のプレイヤーの中心に設定 */
	stBulletCollision.vecCapsuleBottom = VAdd(stBulletCollision.vecCapsuleTop, this->vecMove);

	/* 作成した弾にコリジョンを設定 */
	pBulletMeleeStrong->SetCollision_Capsule(stBulletCollision);

	/* バレットリストに追加 */
	this->ObjectList->SetBullet(pBulletMeleeStrong);
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */
		
/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 近距離攻撃(強)エフェクト生成
void CharacterPlayer::CreateChargeAttackEffect()
{
	std::shared_ptr<EffectSelfDelete> pAddEffect = std::make_shared<EffectSelfDelete>();
	pAddEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_iai_dash/FX_iai_dash")));
	pAddEffect->SetDeleteCount(PLAYER_MELEE_CHARGE_EFFECT_FRAME);
	pAddEffect->SetPosition(VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT / 2.f, 0)));
	pAddEffect->SetRotation(VGet(this->vecRotation.x, this->vecRotation.y, this->vecRotation.z * -1));
	pAddEffect->Initialization();
	this->ObjectList->SetEffect(pAddEffect);	
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 近接攻撃(強)連続敵探索処理
void CharacterPlayer::HandleContinuousChargeSearch()
{
	// 近接攻撃(強)で敵を倒した後、次の敵を探す
	/* プレイヤーが近接攻撃(強)で敵を倒した後かのフラグを確認 */
	if (this->PlayerStatusList->bGetPlayerMeleeStrongEnemyAttackFlg() == true)
	{
		// 近接攻撃(強)で敵を倒した後の場合
		// 次の敵を探す処理
		this->Player_Continuous_Charge_Attack_Enemy_Search();
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.10.15 菊池雅道	近距離攻撃(強)処理修正		開始 */
// 近距離攻撃(強)ロックオン処理
void CharacterPlayer::Player_Charge_Attack_RockOn()
{
	/* カメラモードを"構え(近接攻撃構え)"に変更 */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_AIM_MELEE);

	/* プレイヤーの向きをカメラの向きに固定 */
	this->PlayerStatusList->SetPlayerAngleX(this->StageStatusList->fGetCameraAngleX());

	/* ロックオン範囲のコリジョン作成 */
	COLLISION_CAPSULE stMeleeSearchCollision;

	/* ロックオン範囲の半径を取得 */
	stMeleeSearchCollision.fCapsuleRadius = this->PlayerStatusList->fGetPlayerRockOnRadius();

	/* 片方は現在のプレイヤーの中心に設定 */
	stMeleeSearchCollision.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT / 2.f, 0));

	/* もう片方は移動後(推定)のプレイヤーの中心に設定 */
	stMeleeSearchCollision.vecCapsuleBottom = VAdd(stMeleeSearchCollision.vecCapsuleTop, this->PlayerStatusList->vecGetPlayerChargeAttakTargetMove());

	/* ロックオン範囲のコリジョンを設定 */
	this->PlayerStatusList->SetMeleeSearchCollision(stMeleeSearchCollision);

	/* ロックオン範囲コリジョン使用フラグを有効化 */
	this->PlayerStatusList->SetMeleeSearchCollisionUseFlg(true);
}
/* 2025.10.15 菊池雅道	近距離攻撃(強)処理修正		終了 */

/* 2025.07.19 菊池雅道	チャージ攻撃後の索敵処理関数化	開始 */
// 近距離攻撃(強)で敵を倒した後、次の敵を探す処理
void CharacterPlayer::Player_Continuous_Charge_Attack_Enemy_Search()
{
	/* プレイヤーのモーションが"近距離攻撃(強)(終了)"になったタイミングとする */
	if (this->PlayerStatusList->iGetPlayerMotion_Attack() != MOTION_ID_ATTACK_STRONG_END)
	{
		return;
	}
	
	/* 索敵範囲の設定値を取得 */
	float fSearchRange = this->PlayerStatusList->fGetPlayerMeleeStrongNextSearchRange();

	/* 索敵範囲を設定 */
	COLLISION_SQHERE stSearchSqere{ this->vecPosition, fSearchRange };

	/* 最も近いエネミー情報 */
	NearEnemy stNearEnemy{ nullptr, 0.f };

	/* エネミーリストを取得 */
	auto& EnemyList = ObjectList->GetEnemyList();

	/* 最小距離を索敵範囲で初期化 */
	float fMinDistance = fSearchRange;

	/* 索敵範囲内のエネミーのうち最もプレイヤーに近いエネミーを対象に設定 */
	for (auto& enemy : EnemyList)
	{
		/* 対象のエネミーの死亡フラグが有効であるか確認 */
		if (enemy->bGetDeadFlg())
		{
			continue;
		}

		/* 索敵範囲に接触しているか確認 */
		if (!enemy->HitCheck(stSearchSqere))
		{
			continue;
		}

			/* コアのワールド座標を取得 */
		VECTOR vecCoreWorld = MV1GetFramePosition(enemy->iGetModelHandle(),enemy->iGetCoreFrameNo());

		/* プレイヤーとエネミーの間を確認する線分コリジョンを設定 */
		COLLISION_LINE stCollisionLine;
		stCollisionLine.vecLineStart = this->vecPosition;
		stCollisionLine.vecLineStart.y += PLAYER_HEIGHT;
		stCollisionLine.vecLineEnd = vecCoreWorld;

		/* プラットフォームを取得 */
		auto& PlatformList = ObjectList->GetPlatformList();

		/* 射線上にプラットフォームが存在するか確認 */
		bool bPlatformHitFlag = false;
		for (auto& platform : PlatformList)
		{
			if (platform->HitCheck_Line(stCollisionLine).HitFlag)
			{
				bPlatformHitFlag = true;
				break;
			}
		}

		/* プラットフォームに遮られている場合は対象外 */
		if (bPlatformHitFlag)
		{
			continue;
		}

		/* プレイヤーからエネミーの距離を算出 */
		float fDistance = VSize(VSub(vecCoreWorld, this->vecPosition));

		/* より近いエネミーであれば更新 */
		if (fDistance <= fMinDistance)
		{
			stNearEnemy.pEnemy = enemy;
			stNearEnemy.fDistance = fDistance;
			fMinDistance = fDistance;
		}
	}

	/* 最もプレイヤーに近いエネミーを対象に指定 */
	if (stNearEnemy.pEnemy != nullptr)
	{
		/* プレイヤーから見た敵の向きを取得 */
		VECTOR vecNearEnemy = VSub(this->vecPosition, stNearEnemy.pEnemy->vecGetPosition());
		vecNearEnemy = VNorm(vecNearEnemy);

		/* プレイヤーから見た敵の角度(XZ) */
		float fNearEnemyRotate_xz = -atan2f(vecNearEnemy.x, vecNearEnemy.z);

		/* プレイヤーから見た敵の角度(Y) */
		float fNearEnemyRotate_y = -atan2f(vecNearEnemy.y,sqrtf(vecNearEnemy.x * vecNearEnemy.x + vecNearEnemy.z * vecNearEnemy.z));

		/* プレイヤーの向きを設定 */
		this->PlayerStatusList->SetPlayerAngleX(fNearEnemyRotate_xz);

		/* 敵の向きにカメラを固定 */
		this->StageStatusList->SetCameraAngleX(fNearEnemyRotate_xz);
		this->StageStatusList->SetCameraAngleY(fNearEnemyRotate_y);

		/* 連続近距離攻撃(強)可能フラグを設定 */
		this->PlayerStatusList->SetPlayerMeleeStrongContinuousFlg(true);

		/* ロックオン中のエネミーを設定 */
		this->PlayerStatusList->SetPlayerLockOnEnemy(stNearEnemy.pEnemy);
	}
	else
	{
		/* 対象が存在しない場合 */
		this->PlayerStatusList->SetPlayerMeleeStrongEnemyAttackFlg(false);
		this->PlayerStatusList->SetPlayerMeleeStrongContinuousFlg(false);
		this->PlayerStatusList->SetMeleeStrongDestroyCount(0);
	}
}
/* 2025.07.19 菊池雅道	チャージ攻撃後の索敵処理関数化	終了 */

/* 2025.07.19 菊池雅道	連続チャージ攻撃可能な場合の処理関数化	開始 */
// 連続チャージ攻撃が可能な場合の処理
void CharacterPlayer::Player_Continuous_Charge_Attack_Enabled_Process()
{
	/* プレイヤーが近接攻撃(強)で敵を倒した後のカウントを取得 */
	int iPlayerMeleeStrongAfterCount = this->PlayerStatusList->iGetPlayerMeleeStrongAfterCount();

	/* 近距離攻撃(強)後の初回処理 */
	if (iPlayerMeleeStrongAfterCount == 0)
	{
		/* チャージ完了時の処理 */
		OnChargeComplete();
	}
	/* 近距離攻撃(強)後の受付時間内 */
	else if (iPlayerMeleeStrongAfterCount < PLAYER_STRONG_MELEE_AFTER_COUNT_MAX)
	{
		/* カメラモードを"構え(近接攻撃構え)"に変更 */
		this->StageStatusList->SetCameraMode(CAMERA_MODE_AIM_MELEE);

		/* 空中にいるか確認 */
		if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
		{
			/* スローモーションが無効であるか確認 */
			if (this->StageStatusList->bGetGameSlowFlg() == false)
			{
				/* 画面エフェクト(被ダメージ)作成 */
				this->StageStatusList->SetScreenEffect(std::make_shared<ScreenEffect_Damage>());

				/* スローモーションを有効化 */
				this->StageStatusList->SetGameSlowFlg(true);

				/* スローモーションカウントをリセット */
				this->PlayerStatusList->SetPlayerSlowMotionCount(0);
			}
		}
		else
		{
			/* 地上にいる場合はスローモーション終了 */
			this->Player_SlowMotion_Stop();
		}
	}
	/* 近距離攻撃(強)後の受付時間終了 */
	else
	{
		/* カメラモードを"自由"に変更 */
		this->StageStatusList->SetCameraMode(CAMERA_MODE_NORMAL);

		/* ロックオン中のエネミーをリセット */
		this->PlayerStatusList->SetPlayerLockOnEnemy(nullptr);
		
		/* 各種フラグ・カウントをリセット */
		this->PlayerStatusList->SetPlayerMeleeStrongAfterCount(0);
		this->PlayerStatusList->SetPlayerMeleeStrongEnemyAttackFlg(false);
		this->PlayerStatusList->SetMeleeStrongDestroyCount(0);

		/* 溜め完了後エフェクトを削除 */
		if (this->pChargeHoldEffect != nullptr)
		{
			this->pChargeHoldEffect->SetDeleteFlg(true);
			this->pChargeHoldEffect = nullptr;
		}

		/* スローモーション終了 */
		this->Player_SlowMotion_Stop();

		return;
	}

	/* 近距離攻撃(強)後のカウントを加算 */
	this->PlayerStatusList->SetPlayerMeleeStrongAfterCount(iPlayerMeleeStrongAfterCount + 1);
}
/* 2025.07.19 菊池雅道	連続チャージ攻撃可能な場合の処理関数化	終了 */

/* 2025.02.12 菊池雅道	遠距離攻撃処理追加 開始 */
/* 2025.02.26 菊池雅道	クールタイム処理追加	開始 */
/* 2025.03.04 菊池雅道	スローモーション処理追加	開始 */
/* 2025.03.06 菊池雅道	スローモーション処理修正	開始 */
/* 2025.03.12 菊池雅道	スローモーション処理修正	開始 */
/* 2025.03.13 駒沢風助	クナイ弾数設定				開始 */
/* 2025.03.26 菊池雅道	遠距離攻撃処理修正			開始 */
// 遠距離攻撃(構え)
void CharacterPlayer::Player_Projectile_Posture()
{
	/* エイム(構え)入力がされていない場合 */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_AIM) != true)
	{
		/* キャンセル処理 */
		this->Player_Projectile_Posture_Cancel();
		return;
	}

	/* プレイヤーの向きをカメラの向きに固定 */
	this->PlayerStatusList->SetPlayerAngleX(this->StageStatusList->fGetCameraAngleX());
		
	/* カメラモードを"構え(クナイ攻撃)"に変更 */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_AIM_KUNAI);

	/* スローモーション処理 */
	this->Player_Projectile_Posture_SlowMotion();

	/* モーション設定 */
	this->Player_Projectile_Posture_SetMotion();

	/* 攻撃入力処理 */
	if (this->bPlayer_Projectile_Posture_AttackInput())
	{
		return;
	}

	/* キャンセル入力処理 */
	this->Player_Projectile_Posture_CancelInput();
}
/* 2025.02.12 菊池雅道	遠距離攻撃処理追加			終了 */
/* 2025.02.26 菊池雅道	クールタイム処理追加		終了 */
/* 2025.03.04 菊池雅道	スローモーション処理追加	終了 */
/* 2025.03.06 菊池雅道	スローモーション処理修正	終了 */
/* 2025.03.12 菊池雅道	スローモーション処理修正	終了 */
/* 2025.03.13 駒沢風助	クナイ弾数設定				終了 */
/* 2025.03.26 菊池雅道	遠距離攻撃処理修正			終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 遠距離攻撃(構え)スローモーション処理
void CharacterPlayer::Player_Projectile_Posture_SlowMotion()
{
	/* ジャンプ中もしくは空中にいるか確認 */
	bool bInAir = this->PlayerStatusList->bGetPlayerJumpingFlag() == true || this->PlayerStatusList->bGetPlayerLandingFlg() == false;

	if (bInAir)
	{
		/* スローモーションカウントを取得 */
		int iNowSlowMotionCount = this->PlayerStatusList->iGetPlayerSlowMotionCount();
		
		/* スローモーションフラグが無効であるか確認 */
		if (this->StageStatusList->bGetGameSlowFlg() == false)
		{
			/* スローモーションカウントが一定値以下か確認 */
			if (iNowSlowMotionCount <= PLAYER_SLOWMOTION_COUNT_MAX)
			{
				/* 画面エフェクト(被ダメージ)作成 */
				this->StageStatusList->SetScreenEffect(std::make_shared<ScreenEffect_Damage>());

				/* スローモーションフラグを有効化 */
				this->StageStatusList->SetGameSlowFlg(true);
			}
		}

		/* スローモーションカウントが一定値を超えているか確認 */
		if (iNowSlowMotionCount > PLAYER_SLOWMOTION_COUNT_MAX)
		{
			/* スローモーション終了 */
			this->Player_SlowMotion_Stop();
		}

		/* スローモーションカウントを加算 */
		this->PlayerStatusList->SetPlayerSlowMotionCount(
			iNowSlowMotionCount + 1);
	}
	else
	{
		/* スローモーション終了 */
		this->Player_SlowMotion_Stop();
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 遠距離攻撃(構え)モーション設定
void CharacterPlayer::Player_Projectile_Posture_SetMotion()
{
	/* プレイヤーのモーションが投擲でないか確認 */
	if (this->PlayerStatusList->iGetPlayerMotion_Attack()!= MOTION_ID_ATTACK_THROW)
	{
		/* プレイヤーのモーションを投擲(準備)に設定 */
		this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_THROW_READY);
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 遠距離攻撃(構え)攻撃入力判定処理　※成功したら true を返す
bool CharacterPlayer::bPlayer_Projectile_Posture_AttackInput()
{
	/* 攻撃入力がされているか確認 */
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK) != true)
	{
		return false;
	}

		/* カメラの補完カウントを取得 */
	int CameraLeapCount =
		this->StageStatusList->iGetCameraTargetLeapCount();

	/* カメラ補完が完了していない場合 */
	if (CameraLeapCount < CAMERA_POSITION_LEAP_COUNT_MAX_PROJECTILE)
		{
		return true;
	}

			/* 遠距離攻撃のクールタイムを確認 */
	if (this->iProjectileNowCoolTime != 0)
			{
		return true;
	}

				/* 現在のクナイの所持数を取得 */
	int iNowKunaiCount =
		this->PlayerStatusList->iGetNowHaveKunai();

	/* クナイを所持していない場合 */
	if (iNowKunaiCount <= 0)
				{
		return true;
	}

					/* クナイ消費無効率(%)を取得 */
	int iKeepProbability =
		this->PlayerStatusList->iGetAddKunaiKeepProbability();

	/* 消費判定 */
	if (GetRand(100) > iKeepProbability)
	{
		iNowKunaiCount--;
	}

	/* クナイの所持数を設定 */
	this->PlayerStatusList->SetNowHaveKunai(iNowKunaiCount);

	/* プレイヤーのモーションを投擲に設定 */
	this->PlayerStatusList->SetPlayerMotion_Attack(
		MOTION_ID_ATTACK_THROW);

	/* プレイヤーの攻撃状態を"遠距離攻撃中"に遷移 */
	this->PlayerStatusList->SetPlayerAttackState(
	PLAYER_ATTACKSTATUS_PROJECTILE);

	return true;
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 遠距離攻撃(構え)キャンセル入力処理
void CharacterPlayer::Player_Projectile_Posture_CancelInput()
{
	/* ジャンプ入力がされた場合 */
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP))
	{
		/* 遠距離攻撃構え状態キャンセルフラグを設定 */
		this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
			
		/* キャンセル処理 */
		this->Player_Projectile_Posture_Cancel();
		return;
	}

	/* 回避入力がされた場合 */
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE))
	{
		/* 遠距離攻撃構え状態キャンセルフラグを設定 */
		this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
			
		/* キャンセル処理 */
		this->Player_Projectile_Posture_Cancel();
		return;
	}		
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.02.14 菊池雅道	遠距離攻撃処理追加 開始 */
/* 2025.02.21 菊池雅道	遠距離攻撃修正 開始 */
/* 2025.02.26 菊池雅道	クールタイム処理追加	開始 */
/* 2025.03.10 菊池雅道	エフェクト処理追加		開始 */
/* 2025.03.13 菊池雅道	クナイ処理変更 開始 */
/* 2025.03.18 菊池雅道	エディットによる処理追加	開始 */
// 遠距離攻撃
void CharacterPlayer::Player_Projectile()
{
	/* プレイヤーの向きをカメラの向きに固定 */
	this->PlayerStatusList->SetPlayerAngleX(this->StageStatusList->fGetCameraAngleX());

	/* カメラモードを"構え(クナイ攻撃)"に変更 */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_AIM_KUNAI);
	
	/* カメラ座標からカメラの注視点に向かうベクトルを取得 */
	VECTOR vecKunaiTarget = VSub(this->StageStatusList->vecGetCameraTarget(), this->StageStatusList->vecGetCameraPosition());

	/* ベクトルを正規化 */
	vecKunaiTarget = VNorm(vecKunaiTarget);

	/* ベクトルを射程距離までスケーリング */
	vecKunaiTarget = VScale(vecKunaiTarget, KUNAI_RANGE);

	/* ターゲット座標の座標ベクトルを取得 */
	vecKunaiTarget = VAdd(this->StageStatusList->vecGetCameraPosition(), vecKunaiTarget);

	/* ロックオン中のエネミーを取得 */
	std::shared_ptr<Enemy_Basic> pLockOnEnemy = this->PlayerStatusList->pGetPlayerLockOnEnemy();

	// エディットの内容よって処理を変える
	/* クナイワープ化フラグが有効か確認する */
	if (this->PlayerStatusList->bGetKunaiWarp() == true)
	{
		// クナイワープ化フラグが無効である場合
		/* クナイ(爆発)を作成 */
		this->pBulletKunaiExplosion = std::make_shared<BulletPlayerKunaiExplosion>();

		/* クナイ(爆発)生成座標を設定 */
		this->pBulletKunaiExplosion->SetPosition(VGet(this->vecPosition.x, this->vecPosition.y + PLAYER_HEIGHT / 2, this->vecPosition.z));

		/* ロックオン中のエネミーが存在するか */
		if (pLockOnEnemy != nullptr)
		{
			// 存在する場合
			/* クナイ(爆発)のターゲット座標をロックオン中のエネミーに設定 */
			this->pBulletKunaiExplosion->SetKunaiTargetPosition(pLockOnEnemy->vecGetPosition());
		}
		else
		{
			// 存在しない場合
			// クナイ(爆発)のターゲット座標をカメラの注視点の先に設定
			/* クナイ(爆発)にターゲット座標を設定 */
			this->pBulletKunaiExplosion->SetKunaiTargetPosition(vecKunaiTarget);
		}

		/* 初期化を行う */
		this->pBulletKunaiExplosion->Initialization();

		/* バレットリストに追加 */
		ObjectList->SetBullet(this->pBulletKunaiExplosion);
	}
	else
	{
		// クナイワープ化フラグが有効な場合
		/* クナイ(ワープ)を作成 */
		this->pBulletKunaiWarp = std::make_shared<BulletPlayerKunaiWarp>();

		/* クナイ(ワープ)生成座標を設定 */
		this->pBulletKunaiWarp->SetPosition(VGet(this->vecPosition.x, this->vecPosition.y + PLAYER_HEIGHT / 2, this->vecPosition.z));
	
		/* ロックオン中のエネミーが存在するか */
		if (pLockOnEnemy != nullptr)
		{
			// 存在する場合
			/* クナイ(ワープ)のターゲット座標をロックオン中のエネミーに設定 */
			this->pBulletKunaiWarp->SetKunaiTargetPosition(pLockOnEnemy->vecGetPosition());

			/* ロックオン中のエネミーのポインタをクナイ(ワープ)に渡す */
			this->pBulletKunaiWarp->SetKunaiTargetEnemy(pLockOnEnemy);
		}
		else
		{
			// 存在しない場合
			// クナイ(ワープ)のターゲット座標をカメラの注視点の先に設定
			// クナイ(ワープ)にターゲット座標を設定
			this->pBulletKunaiWarp->SetKunaiTargetPosition(vecKunaiTarget);
		}

		/* 初期化を行う */
		this->pBulletKunaiWarp->Initialization();
	
		/* バレットリストに追加 */
		ObjectList->SetBullet(this->pBulletKunaiWarp);
	}

	/* 遠距離攻撃のSEを再生 */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_KUNAI);

	/* 遠距離攻撃ボイスを再生 */
	gpDataList_Sound->VOICE_PlaySound(VOICE_PLAYER_PROJECTILE);

	/* 遠距離攻撃エフェクトを生成 */
	std::shared_ptr<EffectSelfDelete> pProjectileEffect = std::make_shared<EffectSelfDelete>();
	pProjectileEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_seath_unseath/FX_seath_unseath")));
	pProjectileEffect->Initialization();
	pProjectileEffect->SetDeleteCount(PLAYER_PROJECTILE_FRAME);
	VECTOR vecKunaiHand = MV1GetFramePosition(this->iModelHandle, iKunaiEffectFrameNo);
	pProjectileEffect->SetPosition(vecKunaiHand);
	this->ObjectList->SetEffect(pProjectileEffect);

	/* 遠距離攻撃のクールタイム設定値を取得 */
	int iProjectileCoolTime = this->PlayerStatusList->iGetPlayerKunaiCoolTime();

	/* 遠距離攻撃のクールタイムを設定 */
	this->iProjectileNowCoolTime = iProjectileCoolTime;

	/* 遠距離攻撃構え状態に戻す */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE);
}
/* 2025.02.14 菊池雅道	遠距離攻撃処理追加 終了 */
/* 2025.02.21 菊池雅道	遠距離攻撃修正			終了 */
/* 2025.02.26 菊池雅道	クールタイム処理追加	終了 */
/* 2025.03.10 菊池雅道	エフェクト処理追加		終了 */
/* 2025.03.13 菊池雅道	クナイ処理変更				終了 */
/* 2025.03.18 菊池雅道	エディットによる処理追加	終了 */

// プレイヤーの遠距離攻撃構え状態をキャンセルする際の処理
void CharacterPlayer::Player_Projectile_Posture_Cancel()
{
	/* プレイヤーのモーションを無しに設定 */
	this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);

	/* プレイヤー攻撃状態を"自由状態"に設定 */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

	/* スローモーション終了 */
	this->Player_SlowMotion_Stop();
}

// プレイヤーのスローモーションを停止する際の処理
void CharacterPlayer::Player_SlowMotion_Stop()
{
	/* スローモーションフラグが有効であるか確認 */
	if (this->StageStatusList->bGetGameSlowFlg() == true)
	{
		// 有効である場合
		/* スローモーションフラグを無効化 */
		this->StageStatusList->SetGameSlowFlg(false);

		/* スローモーションカウントをリセットする */
		this->PlayerStatusList->SetPlayerSlowMotionCount(0);
	}
}
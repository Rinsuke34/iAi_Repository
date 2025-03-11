/* 2025.02.04 菊池雅道	ファイル作成 */
/* 2025.01.09 菊池雅道	移動処理追加 */
/* 2025.01.27 菊池雅道	エフェクト処理追加 */
/* 2025.02.05 菊池雅道	ステータス関連修正 */
/* 2025.02.06 菊池雅道	エフェクト処理修正 */
/* 2025.02.07 菊池雅道	衝突判定処理修正 */
/* 2025.02.10 菊池雅道	振り向き処理修正 */
/* 2025.02.10 菊池雅道	回避処理修正 */
/* 2025.02.14 菊池雅道	振り向き処理修正 */
/* 2025.02.22 菊池雅道	壁キック処理追加 */
/* 2025.02.26 菊池雅道	クールタイムの処理追加 */
/* 2025.02.26 菊池雅道	近距離攻撃(強)関連の処理追加 */
/* 2025.03.04 菊池雅道	回避の処理修正 */
/* 2025.03.05 菊池雅道	衝突判定処理修正 */
/* 2025.03.10 駒沢風助	移動床実装 */
/* 2025.03.08 菊池雅道	移動処理修正 */
/* 2025.03.11 菊池雅道	モーション関連の処理追加 */
/* 2025.03.11 菊池雅道	回避の処理修正 */

#include "CharacterPlayer.h"

// 移動
void CharacterPlayer::Player_Move()
{
	/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */

	/* プレイヤー移動量取得 */
	float fStickTiltMagnitude	= this->InputList->fGetGameInputMove();				// スティックを倒した強さ
	VECTOR vecInput				= this->InputList->vecGetGameInputMoveDirection();	// 移動方向
	VECTOR vecAddMove			= VGet(0, 0, 0);									// 移動量(加算用)

	/* プレイヤーの状態を取得 */
	int iPlayerMoveState	= this->PlayerStatusList->iGetPlayerMoveState();
	int iPlayerAttackState	= this->PlayerStatusList->iGetPlayerAttackState();

	/* プレイヤーの状態に応じて移動速度の倍率等を設定 */
	float	fMoveSpeedRatio		= 1.f;		// 移動速度(倍率)
	bool	bPlayerAngleSetFlg	= true;		// プレイヤーの向きを移動方向に合わせるかのフラグ
	bool	bPlayerMoveFlg		= true;		// プレイヤーの移動を行うかのフラグ	
	
	/* プレイヤーの移動状態が移動処理を行う状態であるか確認 */
	switch (iPlayerMoveState)
	{
		/* 移動処理を通常通りに行う状態 */
		case PLAYER_MOVESTATUS_FREE:				// 自由状態

			/* 移動処理を行う */
			bPlayerMoveFlg = true;
		
			/* 移動速度補正無しにする */
			fMoveSpeedRatio = 1.f;

			/* プレイヤーの向きを移動方向に合わせる */
			bPlayerAngleSetFlg = true;
		
			break;

		/* 移動処理を行わない状態 */
		case PLAYER_MOVESTATUS_EVENT:				// イベント状態(操作不可)
		case PLAYER_MOVESTATUS_DODGING:				// 回避状態中
		case PLYAER_MOVESTATUS_DEAD:				// 死亡状態(操作不可)
	
			// 移動処理を行わない
			bPlayerMoveFlg = false;
		
			break;
	}

	/* プレイヤーの移動状態が移動処理を行う場合であるか確認 */
	if (bPlayerMoveFlg == true)
	{
		// 移動処理を行う場合
		/* プレイヤーの攻撃状態が移動処理を行う状態であるか確認 */
		switch (iPlayerAttackState)
		{

			/* 移動処理を通常通りに行う状態 */
			case PLAYER_ATTACKSTATUS_FREE:	// 自由状態

				/* 移動速度補正無しにする */
				fMoveSpeedRatio = 1.f;

				/* プレイヤーの向きを移動方向に合わせる */
				bPlayerAngleSetFlg = true;
				break;

			/* 移動処理を速度を抑えて行う状態 */
			case PLAYER_ATTACKSTATUS_MELEE_POSTURE:			// 近接攻撃構え中
			case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:	// 遠距離攻撃構え中

				/* 移動速度補正0.5倍にする */
				// ※仮の値
				fMoveSpeedRatio = 0.5f;

				/* プレイヤーの向きを移動方向に合わせない */
				bPlayerAngleSetFlg = false;
				break;

			/* 移動処理を行わない状態 */
			case PLAYER_ATTACKSTATUS_MELEE_WEEK:		// 近接攻撃中(弱)
			case PLAYER_ATTACKSTATUS_MELEE_STRONG:		// 近接攻撃中(強)
			case PLAYER_ATTACKSTATUS_PROJECTILE:		// 遠距離攻撃中
				break;
		}
	}
	/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */

	/* 2025.01.09 菊池雅道	移動処理追加	   開始 */
	/* 2025.01.30 菊池雅道	モーション処理追加 開始 */
	/* 2025.03.08 菊池雅道	移動処理修正 開始 */

	/* 移動処理を行える状態かつ、入力がされているか確認 */
	if ((vecInput.x != 0 || vecInput.z != 0) && (bPlayerMoveFlg == true))
	{
		// 移動入力がされている場合
		/* 現在の移動速度取得 */
		float fSpeed = this->PlayerStatusList->fGetPlayerNowMoveSpeed();

		/* 移動速度を設定 */
		fSpeed = PLAER_DASH_SPEED * fMoveSpeedRatio;

		/* モーションが"ジャンプ(開始)"以外であるか確認 */
		if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_JUMP_START)
		{
			// ジャンプ(開始)以外であるなら
			/* モーション設定(歩行) */
			this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_WALK);

			/* プレイヤーの攻撃側モーションが強攻撃(終了)であるか確認 */
			if (this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
			{
				// 強攻撃(終了)であるなら
				/* プレイヤーの攻撃側モーションを"無し"に設定 */
				this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);
			}
		}

		/* 2025.01.09 菊池雅道	移動処理追加 終了 */
		/* 2025.03.08 菊池雅道	移動処理修正 終了 */

		/* 現在速度を更新 */
		this->PlayerStatusList->SetPlayerNowMoveSpeed(fSpeed);

		/* カメラの水平方向の向きを移動用の向きに設定 */
		float fAngleX = this->StageStatusList->fGetCameraAngleX();

		/* 移動量を算出 */
		vecAddMove.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
		vecAddMove.y = 0.0f;
		vecAddMove.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
		vecAddMove = VScale(vecAddMove, fSpeed);

		/* 2025.02.10 菊池雅道	振り向き処理修正 開始*/
		/* 2025.02.14 菊池雅道	振り向き処理修正 開始 */
		/* プレイヤーの向きを移動方向に合わせるか確認 */
		if (bPlayerAngleSetFlg == true)
		{
			// 合わせる場合
			/* プレイヤーの向きを移動方向に合わせる */
			/* 入力方向を取得 */
			float fMoveAngle = atan2f(vecInput.x, vecInput.z);
			
			/* カメラの水平方向の向きが一周の範囲(0~2π)を超えた場合、補正を行う */
			this->RadianLimitAdjustment(fAngleX);
			
			/* 補正したカメラ角度を設定 */
			this->StageStatusList->SetCameraAngleX(fAngleX);

			/* 入力方向とカメラの向きを合成し移動方向とする */
			fMoveAngle = fAngleX - fMoveAngle;

			/* プレイヤーの移動方向(ラジアン)が一周の範囲(0~2π)を超えた場合、補正を行う */
			this->RadianLimitAdjustment(fMoveAngle);

			/* プレイヤーの現在の向き(ラジアン)を取得 */
			float fCurrentAngle = this->PlayerStatusList->fGetPlayerAngleX();

			/* プレイヤーの現在の向き(ラジアン)が一周の範囲(0~2π)を超えた場合、補正を行う */
			this->RadianLimitAdjustment(fCurrentAngle);

			/* 現在のプレイヤーの向きと移動方向の差を求める */
			float fDifferrenceAngle = fMoveAngle - fCurrentAngle;

			//プレイヤーの向きと移動方向の差が半周(π)を超えた場合、より少ない角度で回転するように補正を行う
			/* 左回りで半周を超えたら */
			if (fDifferrenceAngle > DX_PI_F)
			{
				/* 角度を一周(2π)分補正する */
				fDifferrenceAngle -= PLAYER_TURN_LIMIT;
			}
			/* 右回りで半周を超えたら */
			else if (fDifferrenceAngle < -DX_PI_F)
			{
				/* 角度を一周(2π)分補正する */
				fDifferrenceAngle += PLAYER_TURN_LIMIT;
			}

			/* 振り向き速度に応じて段階的に移動方向を向く */ 
			float fNewAngle = fCurrentAngle + fDifferrenceAngle * this->PlayerStatusList->fGetPlayerTurnSpeed();

			/* プレイヤーの向きを更新 */
			this->PlayerStatusList->SetPlayerAngleX(fNewAngle);

			/* 2025.02.10 菊池雅道	振り向き処理修正 終了 */
			/* 2025.02.14 菊池雅道	振り向き処理修正 終了 */
		}
	}
	else
	{
		// 移動入力がされていない場合
		/* 移動速度を0にする */
		this->PlayerStatusList->SetPlayerNowMoveSpeed(0);

		// 近距離攻撃(強)(終了)モーション中以外なら待機モーションに遷移 ※バグ対策のため、以下ような書き方になってます
		if(this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
		{

		}
		else
		{
			/* 現在のモーションが"着地"、あるいは"死亡"でないか確認 */
			int iMotionMove = this->PlayerStatusList->iGetPlayerMotion_Move();
			if ((iMotionMove != MOTION_ID_MOVE_LAND) && (iMotionMove != MOTION_ID_MOVE_DIE))
			{
				// "着地","死亡"以外である場合
				/* モーションが"ジャンプ(開始)"でないか確認 */
				if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_JUMP_START)
				{
					// ジャンプ(開始)以外である場合
					/* 現在のモーションが"着地"でないか確認 */
					if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_LAND)
					{
						// "着地"でない場合		
						/* 現在のモーションが"回避"でないか確認 */
						if (this->PlayerStatusList->iGetPlayerMoveState() != PLAYER_MOVESTATUS_DODGING)
						{
							/* 待機モーション設定 */
							this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_WAIT);
						
						}		
					}
				}
			}
		}
	}
	/* 2025.02.22 菊池雅道	壁キック処理追加 開始*/
	// 壁キックの横移動処理
	/* 壁キックフラグが有効か確認 */
	if (this->PlayerStatusList->bGetPlayerKickWallFlg() == true)
	{
		// 壁キックフラグが有効な場合
		/* 壁キックしてからの経過フレーム数を取得 */
		int iNowAfterKickWallCount = this->PlayerStatusList->iGetPlayerAfterKickWallCount();

		/* 経過フレーム数を確認 */
		if (iNowAfterKickWallCount <= PLAYER_WALL_KICK_MOVE_FLAME)
		{
			// 経過フレーム数が設定フレーム数を超えていない場合

			/* 壁キックの横移動速度を設定 */
			/* 経過フレーム数に応じて、速度が減衰する(1.0fを最大として減衰していく) */
			float fWallKickSpeed = PLAYER_WALL_KICK_HORIZONTAL_SPEED * (1.0f - (float)(iNowAfterKickWallCount / PLAYER_WALL_KICK_MOVE_FLAME));
			
			/* 壁の法線方向(水平成分のみ)へ移動する */
			this->vecMove.x += vecNormalSum.x * fWallKickSpeed;
			this->vecMove.z += vecNormalSum.z * fWallKickSpeed;

		}
		else
		{
			// 経過フレーム数が設定フレーム数を超えた場合

			/* 経過フレーム数をリセット */
			this->PlayerStatusList->SetPlayerAfterKickWallCount(0);

			/* 壁キックフラグを無効にする */
			this->PlayerStatusList->SetPlayerKickWallFlg(false);
		}
	}
	/* 2025.02.22 菊池雅道	壁キック処理追加 終了 */

	/* 移動量を加算 */
	this->vecMove = VAdd(this->vecMove, vecAddMove);

	/* デバッグ描写用の移動量を設定 */
	this->vecMoveSize = vecAddMove;
}

/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */
/* 2025.02.22 菊池雅道	壁キック処理追加	開始*/
// ジャンプ
void CharacterPlayer::Player_Jump()
{
	/* プレイヤーの移動を取得 */
	int iPlayerMoveState	= this->PlayerStatusList->iGetPlayerMoveState();
	int iPlayerAttackState	= this->PlayerStatusList->iGetPlayerAttackState();
	/* ジャンプ処理を行うかのフラグ */
	bool bJumpFlag = true;

	/* プレイヤーの移動状態がジャンプ可能であるか確認 */
	switch (iPlayerMoveState)
	{
		/* ジャンプ可能な状態 */
		case PLAYER_MOVESTATUS_FREE:				// 自由状態
		
			/* ジャンプ処理を行う */
			bJumpFlag = true;
	
			break;

		/* ジャンプ不可能な状態 */
		case PLAYER_MOVESTATUS_EVENT:				// イベント状態(操作不可)
		case PLAYER_MOVESTATUS_DODGING:				// 回避状態中
		case PLYAER_MOVESTATUS_DEAD:				// 死亡状態(操作不可)
		
			/* ジャンプ処理を行う */
			bJumpFlag = false;
		
			break;
	}

	/* プレイヤーの移動状態がジャンプ可能であったか確認 */	
	if (bJumpFlag == true)
	{
		// ジャンプ可能である場合
		/* プレイヤーの攻撃状態がジャンプ可能であるか確認 */
		switch (iPlayerAttackState)
		{
			/* ジャンプ可能な状態 */
			case PLAYER_ATTACKSTATUS_MELEE_POSTURE:			// 近接攻撃構え中
			case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:	// 遠距離攻撃構え中
			case PLAYER_ATTACKSTATUS_PROJECTILE:			// 遠距離攻撃中

				/* ジャンプ処理を行う */
				bJumpFlag = true;
				break;

			/* ジャンプ不可能な状態 */
			case PLAYER_ATTACKSTATUS_MELEE_WEEK:		// 近接攻撃中(弱)
			case PLAYER_ATTACKSTATUS_MELEE_STRONG:		// 近接攻撃中(強)
			case PLAYER_ATTACKSTATUS_DEAD:				// 死亡状態(操作不可)
				/* ジャンプ処理を行わない */
				bJumpFlag = false;
				break;
		}
	}
	// 壁キックの上方向処理(壁キック可能時はジャンプより壁キックを優先するため、ジャンプよりも先に処理する)
	/* 壁キックフラグが有効か確認 */
	if (this->PlayerStatusList->bGetPlayerKickWallFlg() == true)
	{
		/* 壁キック後の経過フレーム数が0の場合 */
		if (this->PlayerStatusList->iGetPlayerAfterKickWallCount() == 0)
		{
			/*上方向に移動 */
			this->PlayerStatusList->SetPlayerNowFallSpeed(PLAYER_WALL_KICK_VERTICAL_SPEED);
			
			/* SEを再生 */
			gpDataList_Sound->SE_PlaySound(SE_PLAYER_JUMP);
			
			/* モーションを"ジャンプ(開始)"に設定 */
			PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_START);

			/* 壁キック後のフラグを有効にする */
			this->PlayerStatusList->SetPlayerAfterKickWallFlg(true);
		}

		/* 壁キック後の経過フレーム数を進める */
		this->PlayerStatusList->SetPlayerAfterKickWallCount(this->PlayerStatusList->iGetPlayerAfterKickWallCount() + 1);

	}
	// ジャンプ処理
	/* ジャンプ処理を行う状態か確認 */
	if (bJumpFlag == true)
	{
		// ジャンプ処理を行う場合
		/* ジャンプ回数が最大数を超えていないか確認 */
		int iNowJumpCount = this->PlayerStatusList->iGetPlayerNowJumpCount();
		int iMaxJumpCount = this->PlayerStatusList->iGetPlayerMaxJumpCount();
		if (iNowJumpCount < iMaxJumpCount)
		{
			/* ジャンプ入力がされているか確認 */
			if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
			{
				// ジャンプ入力がされている場合
				// 壁キックを行った後かを確認(壁キックとジャンプの重複防止のため)
				if (this->PlayerStatusList->bGetPlayerAfterKickWallFlg() == false)
				{ 
					// 壁キック後のフラグが有効ではない場合
					/* ジャンプ処理 */
					// 仮で落下速度を-にする処理を行う
					//this->PlayerStatusList->SetPlayerNowFallSpeed(-20.0f);
					this->PlayerStatusList->SetPlayerNowFallSpeed(-30.0f);

					/* ジャンプ回数を更新 */
					this->PlayerStatusList->SetPlayerNowJumpCount(iNowJumpCount + 1);

					/* ジャンプフラグを有効にする */
					this->PlayerStatusList->SetPlayerJumpingFlag(true);

					/* ジャンプのSEを再生 */
					gpDataList_Sound->SE_PlaySound(SE_PLAYER_JUMP);

					//空中でジャンプした場合、空中ジャンプエフェクトを出現させる

					/* 地面にいない事を確認 */
					if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
					{
						/*空中ジャンプエフェクト追加 */
						{
							/* 空中ジャンプエフェクトを生成 */
							EffectSelfDelete* pAirJumpEffect = new EffectSelfDelete();

							/* 空中ジャンプエフェクトの読み込み */
							pAirJumpEffect->SetEffectHandle(this->EffectList->iGetEffect("FX_airjump/FX_airjump"));

							/* 空中ジャンプエフェクトの時間を設定 */
							pAirJumpEffect->SetDeleteCount(30);

							/* 空中ジャンプエフェクトの座標設定 */
							pAirJumpEffect->SetPosition(VGet(this->vecPosition.x, this->vecPosition.y - this->PlayerStatusList->fGetPlayerNowFallSpeed()+PLAYER_HEIGHT , this->vecPosition.z));

							/* 空中ジャンプエフェクトの回転量設定 */
							pAirJumpEffect->SetRotation(this->vecRotation);

							/* 空中ジャンプエフェクトの初期化 */
							pAirJumpEffect->Initialization();

							/* 空中ジャンプエフェクトをリストに登録 */
							{
								/* 空中ジャンプエフェクトをリストに登録 */
								this->ObjectList->SetEffect(pAirJumpEffect);
							}
						}
					}

					/* プレイヤーのモーションが"近距離攻撃(強)(終了)"であるか確認 */
					if (this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
					{
						// 近距離攻撃(強)(終了)モーション中の場合
						/* プレイヤーのモーションを"無し"に変更 */
						this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);
					}

					/* モーションを"ジャンプ(開始)"に設定 */
					PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_START);
				}
				else
				{ 
					// 壁キック後のフラグが有効な場合
					// ジャンプ入力がされている場合
					if (this->InputList->bGetGameInputAction(INPUT_REL, GAME_JUMP) == false)
					{
						/* 壁キック後のフラグを解除 */
						this->PlayerStatusList->SetPlayerAfterKickWallFlg(false);
					}
				}		
			}
		}
	}
}
/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */
/* 2025.02.22 菊池雅道	壁キック処理追加	終了*/

/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */
// 重力処理
void CharacterPlayer::Player_Gravity()
{
	/* プレイヤーの移動状態を取得 */
	int iPlayerMoveState = this->PlayerStatusList->iGetPlayerMoveState();
	/* プレイヤーの移動状態を取得 */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();
	/* プレイヤーの重力処理を行うかのフラグ */
	bool bGravityFlag = true;

	/* プレイヤーが重力処理を行う移動状態であるか確認 */
	switch (iPlayerMoveState)
	{
		/* 重力処理を行う状態 */
		case PLAYER_MOVESTATUS_FREE:			// 自由状態
		case PLYAER_MOVESTATUS_DEAD:			// 死亡状態(操作不可)

			/* 重力処理を行う */
			bGravityFlag = true;
			break;

		/* 重力処理を行わない状態 */
		case PLAYER_MOVESTATUS_EVENT:			// イベント状態(操作不可)
		case PLAYER_MOVESTATUS_DODGING:			// 回避状態中

			/* 重力処理を行わない(重力処理を終了) */
			bGravityFlag = false;
			break;
	}

	/* プレイヤーの移動状態が重力処理を行う状態であったか確認 */
	if (bGravityFlag == true)
	{
		// 重力処理を行う場合
		/* プレイヤーが重力処理を行う攻撃状態であるか確認 */
		switch (iPlayerAttackState)
		{
			/* 重力処理を行う状態 */
			case PLAYER_ATTACKSTATUS_FREE:					// 自由状態
			case PLAYER_ATTACKSTATUS_MELEE_WEEK:			// 近接攻撃中(弱)
			case PLAYER_ATTACKSTATUS_MELEE_POSTURE:			// 近接攻撃構え中
			case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:	// 遠距離攻撃構え中
			case PLAYER_ATTACKSTATUS_DEAD:					// 死亡状態(操作不可)
				/* 重力処理を行う */
				bGravityFlag = true;
				break;

			/* 重力処理を行わない状態 */
			case PLAYER_ATTACKSTATUS_MELEE_STRONG:			// 近接攻撃中(強)
			case PLAYER_ATTACKSTATUS_PROJECTILE:			// 遠距離攻撃中
				/* 重力処理を行わない(重力処理を終了) */
				bGravityFlag = false;
				break;
		}
	}

	/* 重力処理実行フラグの確認 */
	if(bGravityFlag == true)
	{
		// 重力処理を行う場合
		/* 落下量取得 */
		float fFallSpeed = this->PlayerStatusList->fGetPlayerNowFallSpeed();		// 現時点での加速量取得
		fFallSpeed += this->PlayerStatusList->fGetPlayerFallAcceleration();	// 加速度を加算

		/* 落下の加速度を更新 */
		this->PlayerStatusList->SetPlayerNowFallSpeed(fFallSpeed);

		/* 重力による移動後の座標を取得 */
		this->vecMove.y -= this->PlayerStatusList->fGetPlayerNowFallSpeed();	
	}
}
/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */


// 回避
void CharacterPlayer::Player_Dodg()
{
	/* 2025.01.09 菊池雅道	移動処理追加		開始 */
	/* 2025.01.26 駒沢風助	コード修正		開始*/
	/* 2025.01.27 菊池雅道	エフェクト処理追加 開始 */
	/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */
	/* 2025.02.06 菊池雅道	エフェクト処理修正 開始 */
	/* 2025.02.10 菊池雅道	回避処理修正 開始 */
	/* 2025.02.26 菊池雅道	クールタイム処理追加 開始 */
	/* 2025.03.04 菊池雅道	回避の処理修正 開始 */
	/* 2025.03.11 菊池雅道	回避の処理修正 開始 */

	/* プレイヤーの移動状態を取得 */
	int iPlayerMoveState = this->PlayerStatusList->iGetPlayerMoveState();
	/* プレイヤーの攻撃状態を取得 */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

	/* プレイヤーの回避処理を行うかのフラグ */
	bool bDodgeFlag = true;

	/* プレイヤーが回避処理を行う移動状態であるか確認 */
	// ※攻撃状態は考慮しない
	switch (iPlayerMoveState)
	{
		/* 回避処理を行う状態 */
		case PLAYER_MOVESTATUS_DODGING:			// 回避状態中
		case PLAYER_MOVESTATUS_FREE:			// 自由状態
			/* 回避処理を行う */
			bDodgeFlag = true;
			break;

		/* 回避処理を行わない状態 */
		case PLAYER_MOVESTATUS_EVENT:			// イベント状態(操作不可)
		case PLYAER_MOVESTATUS_DEAD:			// 死亡状態(操作不可)

			/* 回避処理を行わない(回避処理を終了) */
			bDodgeFlag = false;
			break;
	}

	/* 回避処理を行うか確認 */
	if (bDodgeFlag == true)
	{
		// 回避処理を行う場合
		/* プレイヤー場外が"回避状態中"であるか確認 */
		if (iPlayerMoveState == PLAYER_MOVESTATUS_DODGING)
		{
			// 回避中である場合
			/* 回避状態が維持される時間を超えていないか確認 */
			if (this->PlayerStatusList->iGetPlayerNowDodgeFlame() <= PLAYER_DODGE_FLAME)
			{
				// 超えていない(回避状態を継続する)場合
				/* プレイヤーの攻撃状態が近距離攻撃(強)中か確認 */
				if (iPlayerAttackState == PLAYER_ATTACKSTATUS_MELEE_STRONG)
				{
					// 近距離攻撃(強)中である場合
					/* 回避処理を行わない */
					return;
				}

				/* 回避による移動方向を設定し、移動する */
				/* 経過フレーム数に応じて、回避速度が減衰する(1.0fを最大として減衰していく) */
				this->vecMove = VScale(this->PlayerStatusList->vecGetPlayerDodgeDirection(), PLAYER_DODGE_SPEED * (1.0f - (float)this->PlayerStatusList->iGetPlayerNowDodgeFlame() / (float)PLAYER_DODGE_FLAME));

				/* 回避の経過時間を進める */
				this->PlayerStatusList->SetPlayerNowDodgeFlame(this->PlayerStatusList->iGetPlayerNowDodgeFlame() + 1);

			}
			else
			{
				// 超えている(回避状態を終了する)場合

				/* プレイヤー状態を"自由状態"に設定 */
				this->PlayerStatusList->SetPlayerMoveState(PLAYER_MOVESTATUS_FREE);

				/* 回避エフェクトを削除 */
				this->pDodgeEffect->SetDeleteFlg(true);
				/* 回避エフェクトのポインタを削除 */
				this->pDodgeEffect = nullptr;
			}
		}
		else
		{
			// 回避中でない場合
			/* 回避が入力されているか確認 */
			if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE) == true)
			{
				// 回避が入力されている場合
				/* プレイヤーの攻撃状態が近距離攻撃(強)中でないことを確認 */
				if (iPlayerAttackState != PLAYER_ATTACKSTATUS_MELEE_STRONG)
				{
					// 近距離攻撃(強)中でない場合
					/* 空中での回避回数制限を超えていないか */
					if (this->PlayerStatusList->iGetPlayerDodgeWhileJumpingCount() < PLAYER_DODGE_IN_AIR_LIMIT)
					{
						/* 回避のクールタイムが残っているか確認 */
						if (this->iDodgeCoolTime > 0)
						{
							// クールタイムが残っている場合
							/* 回避を行わない */
							return;
						}

						/* 回避開始時の時間をリセット */
						this->PlayerStatusList->SetPlayerNowDodgeFlame(0);

						/* 回避方向設定 */
						{
							/* 入力による移動量を取得 */
							VECTOR vecInput = this->InputList->vecGetGameInputMoveDirection();

							/* カメラの水平方向の向きを移動用の向きに設定 */
							float fAngleX = this->StageStatusList->fGetCameraAngleX();

							/* 回避方向ベクトル */
							VECTOR vecDodgMove;

							/* スティック入力がされているか確認 */
							if (vecInput.x != 0 || vecInput.z != 0)
							{
								// スティック入力がされている場合
								/* スティック入力による回避方向を設定 */
								vecDodgMove.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
								vecDodgMove.y = 0.0f;
								vecDodgMove.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
							}
							else
							{
								// スティック入力がされていない場合
								//プレイヤーが向いている方向に回避する
								/* プレイヤーモデルの初期の向きがZ軸に対してマイナス方向を向いているとする */
								vecDodgMove = { 0,0,-1 };

								/* プレイヤーの角度からY軸の回転行列を求める */
								MATRIX matPlayerRotation = MGetRotY(-(this->PlayerStatusList->fGetPlayerAngleX()));

								/* プレイヤーの向きによる回避方向を設定 */
								vecDodgMove = VTransform(vecDodgMove, matPlayerRotation);
							}

							/* 回避方向を正規化 */
							vecDodgMove = VNorm(vecDodgMove);

							/* 現在の回避方向をセットする */
							this->PlayerStatusList->SetPlayerDodgeDirection(vecDodgMove);
						}

						/* 回避状態の進行率をリセット */
						this->PlayerStatusList->SetPlayerDodgeProgress(0.0f);

						/* 落下の加速度を初期化 */
						this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);

						/* プレイヤー状態を"回避状態中"に設定 */
						this->PlayerStatusList->SetPlayerMoveState(PLAYER_MOVESTATUS_DODGING);

						/* プレイヤーのモーションを回避に設定 */
						this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_DODGE);

						/* プレイヤーが着地していないかを確認 */
						if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
						{
							// 着地していない場合
							/* 空中での回避回数のカウントを進める */
							this->PlayerStatusList->SetPlayerDodgeWhileJumpingCount(PlayerStatusList->iGetPlayerDodgeWhileJumpingCount() + 1);
						}

						/* 回避のSEを再生 */
						gpDataList_Sound->SE_PlaySound(SE_PLAYER_DODGE);

						/* 回避エフェクト追加 */
						{
							/* 回避エフェクトを生成 */
							this->pDodgeEffect = new EffectManualDelete_PlayerFollow(true);

							/* 回避エフェクトの読み込み */
							this->pDodgeEffect->SetEffectHandle(this->EffectList->iGetEffect("FX_dash/FX_dash"));

							/* エフェクトの回転量設定 */
							this->pDodgeEffect->SetRotation(VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

							/* 回避エフェクトの初期化 */
							this->pDodgeEffect->Initialization();

							/* 回避エフェクトをリストに登録 */
							{
								/* 回避エフェクトをリストに登録 */
								this->ObjectList->SetEffect(this->pDodgeEffect);
							}
						}
						/* 回避クールタイムを設定 */
						this->iDodgeCoolTime = PLAYER_DODGE_COOLTIME;
					}
				}
			}
		}
	}
}

/* 2025.01.09 菊池雅道	移動処理追加 終了 */
/* 2025.01.26 駒沢風助	コード修正 終了 */
/* 2025.01.27 菊池雅道　エフェクト処理追加 終了 */
/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */
/* 2025.02.06 菊池雅道	エフェクト処理修正 終了 */
/* 2025.02.10 菊池雅道	回避処理修正 終了 */
/* 2025.02.26 菊池雅道	クールタイム処理追加	終了 */
/* 2025.03.04 菊池雅道	回避の処理修正 終了 */
/* 2025.03.11 菊池雅道	回避の処理修正 終了 */

/* 2025.01.09 菊池雅道　移動処理追加					追加 */
/* 2025.01.27 菊池雅道	エフェクト処理追加				開始 */
/* 2025.02.05 菊池雅道	ステータス関連修正				開始 */
/* 2025.02.26 菊池雅道	近距離攻撃(強)関連の処理追加	開始 */
/* 2025.03.10 駒沢風助	移動床実装						開始 */
/* 2025.03.11 菊池雅道	モーション関連の処理追加		開始 */

// 移動処理(垂直方向)
void CharacterPlayer::Movement_Vertical()
{
	/* 移動後の座標を取得(垂直方向) */
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x;
	vecNextPosition.y = this->vecPosition.y + this->vecMove.y;
	vecNextPosition.z = this->vecPosition.z;

	/* 主人公の上部分の当たり判定から下方向へ向けた線分を作成 */
	this->stVerticalCollision.vecLineStart = this->vecPosition;
	this->stVerticalCollision.vecLineStart.y += PLAYER_HEIGHT;
	this->stVerticalCollision.vecLineEnd = stVerticalCollision.vecLineStart;
	this->stVerticalCollision.vecLineEnd.y -= 9999;

	/* 以下、仮処理(近いオブジェクトのみ対象にするようにする) */
	/* 足場を取得 */
	auto& PlatformList = ObjectList->GetCollisionList();

	/* 着地する座標 */
	// ※初期値を移動後の座標に設定
	float	fStandPosY = vecNextPosition.y;

	/* 現在のジャンプフラグを保持 */
	bool bjumppingFlg = this->PlayerStatusList->bGetPlayerJumpingFlag();

	/* プレイヤーの着地フラグを無効にする */
	this->PlayerStatusList->SetPlayerLanding(false);

	/* 足場と接触するか確認 */
	for (auto* platform : PlatformList)
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stVerticalCollision);

		/* 接触しているか確認 */
		if (stHitPolyDim.HitFlag == 1)
		{
			// 接触している場合
			/* ヒットした座標が現在の着地座標より高い位置であるか確認 */
			if (stHitPolyDim.HitPosition.y >= fStandPosY)
			{
				// 現在の着地座標より高い位置である場合
				/* 落下の加速度を初期化 */
				this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);

				/* ヒットした座標がプレイヤーが歩いて登れる位置より低い位置であるか確認 */
				if (fStandPosY < this->vecPosition.y + PLAYER_CLIMBED_HEIGHT)
				{
					// 着地座標がプレイヤーの現在位置より低い場合
					// ※ 地面に着地したと判定する
					/* 着地座標を着地した座標に更新 */
					fStandPosY = stHitPolyDim.HitPosition.y;

					/* ジャンプ回数を初期化する */
					this->PlayerStatusList->SetPlayerNowJumpCount(0);

					/* プレイヤーの着地フラグを有効にする */
					this->PlayerStatusList->SetPlayerLanding(true);

					/* ジャンプ中のフラグをリセット */
					this->PlayerStatusList->SetPlayerJumpingFlag(false);

					/* ジャンプ中の回避回数をリセット */
					this->PlayerStatusList->SetPlayerDodgeWhileJumpingCount(0);

					/* 空中での近距離攻撃(強)回数をリセット */
					this->PlayerStatusList->SetPlayerMeleeStrongAirCount(0);

					/* 落下状態になってからのフレーム数をリセット */
					iFallingFrame = 0;

					/* 着地したプラットフォームの移動量をプレイヤー移動量に加算 */
					vecNextPosition = VAdd(this->vecPosition, platform->vecGetPlatformMove());
				}
				else
				{
					// 着地座標がプレイヤーの現在位置より高い場合
					/* 着地座標をプレイヤーが天井にめり込まない高さに更新 */
					fStandPosY = stHitPolyDim.HitPosition.y - PLAYER_HEIGHT - PLAYER_CLIMBED_HEIGHT;

					/* ループを抜ける */
					break;
				}
			}
		}
	}

	/* 着地フラグが無効→有効になったか確認 */
	if (bjumppingFlg == true && this->PlayerStatusList->bGetPlayerJumpingFlag() == false)
	{
		/* プレイヤーの状態を取得 */
		int iPlayerMoveState = this->PlayerStatusList->iGetPlayerMoveState();

		/* 回避中にエフェクトが出ないようにする */
		if (iPlayerMoveState != PLAYER_MOVESTATUS_DODGING)
		{
			/* エフェクト追加 */
			{
				/* 着地のエフェクトを生成 */
				EffectSelfDelete* pAddEffect = new EffectSelfDelete;

				/* 着地エフェクトの読み込み */
				pAddEffect->SetEffectHandle(this->EffectList->iGetEffect("FX_land/FX_land"));

				/* 着地エフェクトの時間を設定 */
				pAddEffect->SetDeleteCount(30);

				/* 着地エフェクトの座標設定 */
				pAddEffect->SetPosition(this->vecPosition);

				/* 着地エフェクトの回転量設定 */
				pAddEffect->SetRotation(this->vecRotation);

				/* 着地エフェクトの初期化 */
				pAddEffect->Initialization();

				/* 着地エフェクトをリストに登録 */
				{
					/* 着地エフェクトをリストに登録 */
					this->ObjectList->SetEffect(pAddEffect);
				}
			}

			/* 着地モーション設定 */
			this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_LAND);
		}
	}

	/* 着地座標を更新 */
	vecNextPosition.y = fStandPosY;

	/* プレイヤー座標を更新 */
	this->vecPosition = vecNextPosition;

	/* 現在のプレイヤー状態を取得 */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

	/* モーションを更新 */
	{
		/* 着地フラグが無効である(空中にいる)か確認 */
		if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
		{
			// 無効である(空中にいる)場合
			/* プレイヤーの移動モーションが"回避"でないか確認 */
			if (this->PlayerStatusList->iGetPlayerMoveState() != PLAYER_MOVESTATUS_DODGING)
			{
				// 回避モーションでない場合
				/* 上昇しているか確認 */
				if (this->PlayerStatusList->fGetPlayerNowFallSpeed() < 0)
				{
					// 上昇している場合
					/* モーションが"ジャンプ(開始)"でないことを確認 */
					if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_JUMP_START)
					{
						/* モーションを"ジャンプ(上昇)"に設定 */
						PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_UP);
					}
				}
				else
				{
					// 下降している場合
					/* プレイヤーがジャンプ中であるか確認 */
					if (this->PlayerStatusList->bGetPlayerJumpingFlag() == true)
					{
						/* モーションを"ジャンプ(下降)"に設定 */
						PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_DOWN);

					}
					else
					{
						// ジャンプ中でない場合
						/* 落下状態になってからのフレーム数が一定数を超えているか確認 */
						if (iFallingFrame > PLAYER_JUNP_DOWN_MOTION_SWITCH_FRAME)
						{
							// 一定数を超えている場合
							/* モーションを"ジャンプ(下降)"に設定 */
							PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_DOWN);
						}					
					}

					/* 落下状態になってからのフレーム数を加算 */
					iFallingFrame++;
				}
					
			}
		}
	}
}
/* 2025.01.09 菊池雅道　移動処理追加					終了 */
/* 2025.01.27 菊池雅道	エフェクト処理追加				終了 */
/* 2025.02.05 菊池雅道	ステータス関連修正				終了 */
/* 2025.02.26 菊池雅道	近距離攻撃(強)関連の処理追加	終了 */
/* 2025.03.10 駒沢風助	移動床実装						終了 */
/* 2025.03.11 菊池雅道	モーション関連の処理追加		終了 */

/* 2025.02.07 菊池雅道	衝突判定処理修正	開始 */
/* 2025.02.22 菊池雅道	壁キック処理追加	開始 */
/* 2025.03.05 菊池雅道	衝突判定処理修正	開始 */

// 移動処理(水平方向)
void CharacterPlayer::Movement_Horizontal()
{
	/* 移動後の座標を取得(水平方向) */
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x + this->vecMove.x;
	vecNextPosition.y = this->vecPosition.y;
	vecNextPosition.z = this->vecPosition.z + this->vecMove.z;

	/* 1フレームでの移動量を分割して判定する回数 */
	/* ※移動量に応じて分割を設定する */
	int iMoveHitCheckCount = (int)VSize(VGet(this->vecMove.x,0,this->vecMove.z));
	
	/* 分割した移動量 */
	VECTOR vecDevisionMove = VScale(this->vecMove, 1.0f / iMoveHitCheckCount);

	/* 分割して移動した先の座標 */
	VECTOR vecDevisionMovePosition = this->vecPosition;

	/* 道中でオブジェクトに接触しているか判定 */
	
	{
		/* 現在位置から移動後座標へ向けたカプセルコリジョンを作成 */
		// ※ 元の位置から移動後の位置へ向けたカプセルコリジョンを作成
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].vecCapsuleBottom = VAdd(this->vecPosition, VGet(0.f, PLAYER_HEIGHT - PLAYER_WIDE, 0.f));
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].vecCapsuleTop = VAdd(vecNextPosition, VGet(0.f, PLAYER_HEIGHT - PLAYER_WIDE, 0.f));
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].fCapsuleRadius = PLAYER_WIDE;
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].vecCapsuleBottom = VAdd(this->vecPosition, VGet(0.f, PLAYER_WIDE + PLAYER_CLIMBED_HEIGHT, 0.f));
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].vecCapsuleTop = VAdd(vecNextPosition, VGet(0.f, PLAYER_WIDE + PLAYER_CLIMBED_HEIGHT, 0.f));
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].fCapsuleRadius = PLAYER_WIDE;
		

		/* 足場を取得 */
		auto& PlatformList = ObjectList->GetCollisionList();

		/* 足場と接触するか確認 */
		for (auto* platform : PlatformList)
		{
			/* 足場との接触判定 */
			for (int i = 0; i < PLAYER_MOVE_COLLISION_MAX; i++)
			{
				/* オブジェクトと接触しているか確認 */
				MV1_COLL_RESULT_POLY_DIM stHitPolyDim = platform->HitCheck_Capsule(this->stHorizontalCollision[i]);

				/* 接触しているか確認 */
				if (stHitPolyDim.HitNum > 0)
				{
					// 1つ以上のポリゴンが接触している場合

						/* 接触したポリゴンから法線ベクトルを取得し加算する */
						for (int j = 0; j < stHitPolyDim.HitNum; j++)
						{
							/* 法線ベクトルを取得 */
							// ※ 法線ベクトルが0であるならば、加算しない
							if (VSize(stHitPolyDim.Dim[j].Normal) > 0.f)
							{
								// 法線ベクトルが0でない場合
								/* 法線ベクトルのY軸を初期化 */
								stHitPolyDim.Dim[j].Normal.y = 0.f;

								/* 法線ベクトルを正規化 */
								VECTOR vecNormal = VNorm(stHitPolyDim.Dim[j].Normal);

								/* 法線ベクトルを合計に加算 */
								vecNormalSum = VAdd(vecNormalSum, vecNormal);
							}
						}

						/* 取得した法線ベクトルを正規化 */
						// ※ 取得した法線ベクトルの平均を取得
						vecNormalSum = VNorm(vecNormalSum);

					// プレイヤーが移動しているかによって処理を分岐
					/* プレイヤーの移動量を分割して判定する回数を確認 */
					if (iMoveHitCheckCount > 0)
					{
						// 移動量を分割して判定する回数が1以上の場合(移動している場合)
						/* 移動量を分割して衝突判定する */
						for (int i = 0; i < iMoveHitCheckCount; i++)
						{
							/* 移動後座標に球体ポリゴンを作成 */
							vecDevisionMovePosition = VAdd(vecDevisionMovePosition, vecDevisionMove);

						/* 移動後座標に球体ポリゴンを作成 */
						COLLISION_SQHERE stSphere;
						stSphere.vecSqhere = vecDevisionMovePosition;
						stSphere.fSqhereRadius = PLAYER_WIDE;

						/* 法線の方向にプレイヤーを押し出す */
						// ※ 対象のコリジョンと接触しなくなるまで押し出す
						bool bHitFlag = true;
						while (bHitFlag)
						{
							/* 球体ポリゴンを法線ベクトルの方向へ移動 */
							stSphere.vecSqhere = VAdd(stSphere.vecSqhere, VScale(vecNormalSum, 1.f));

							/* 球体とポリゴンの接触判定 */
							bHitFlag = platform->HitCheck(stSphere);
						}

						/* 球体コリジョンが接触しなくなった位置を移動後座標に設定 */
						vecNextPosition = stSphere.vecSqhere;

						// 球体コリジョンと衝突があった場合、分割移動処理を終了する
						if (stHitPolyDim.HitNum > 0)
						{
							break;
						}
					}

					//壁キック処理
					/* オブジェクトと接触している状態でジャンプボタンを押した場合 */
					if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
					{
						/* 壁キックフラグを有効にする */
						this->PlayerStatusList->SetPlayerKickWallFlg(true);
					}
					
					}
					else
					{
						// 移動量を分割して判定する回数が0の場合(移動していない場合)
						/* 法線ベクトルの方向へ押し出し処理を行う */
						vecNextPosition = VAdd(this->vecPosition, VScale(vecNormalSum, 1.f));
				}
			}
				
			}	
		}
	}

	/* プレイヤーの座標を移動させる */
	this->vecPosition = vecNextPosition;
}
/* 2025.02.07 菊池雅道	衝突判定処理修正	終了 */
/* 2025.02.22 菊池雅道	壁キック処理追加	終了 */
/* 2025.03.05 菊池雅道	衝突判定処理修正	終了 */
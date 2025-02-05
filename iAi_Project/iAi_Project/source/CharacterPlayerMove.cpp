/* 2025.02.04 菊池雅道	ファイル作成 */
/* 2025.01.09 菊池雅道	移動処理追加 */
/* 2025.02.05 菊池雅道	ステータス関連修正 */

#include "CharacterPlayer.h"

// 移動
void CharacterPlayer::Player_Move()
{
	/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */

	/* プレイヤー移動量取得 */
	float fStickTiltMagnitude = this->InputList->fGetGameInputMove();				// スティックを倒した強さ
	VECTOR vecInput = this->InputList->vecGetGameInputMoveDirection();	// 移動方向
	VECTOR vecAddMove = VGet(0, 0, 0);									// 移動量(加算用)

	/* プレイヤーの移動状態を取得 */
	int iPlayerMoveState	= this->PlayerStatusList->iGetPlayerMoveState();
	/* プレイヤーの攻撃状態を取得 */
	int iPlayerAttackState	= this->PlayerStatusList->iGetPlayerAttackState();

	/* プレイヤーの状態に応じて移動速度の倍率等を設定 */
	float	fMoveSpeedRatio = 1.f;			// 移動速度(倍率)
	bool	bPlayerAngleSetFlg = true;		// プレイヤーの向きを移動方向に合わせるかのフラグ
	bool	bPlayerMoveFlg = true;			// プレイヤーの移動を行うかのフラグ	
	
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
	case PLAYER_MOVESTATUS_DODGING:				// 回避状態中
	
		// 移動処理を行わない
		bPlayerMoveFlg = false;
		
		break;
	}

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
	/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */

	/* 2025.01.09 菊池雅道	移動処理追加		開始	*/
	/* 2025.01.27 菊池雅道	エフェクト処理追加 開始	*/
	/* 2025.01.30 菊池雅道	モーション処理追加 開始 */
	/* 移動入力がされているか確認 */
	if ((vecInput.x != 0 || vecInput.z != 0))
	{
		/* 移動処理を行う状態か確認 */
		if (bPlayerMoveFlg = true)
		{
			// 移動入力がされている場合
			/* 現在の移動速度取得 */
			float fSpeed = this->PlayerStatusList->fGetPlayerNowMoveSpeed();

			// 回避後フラグがtrueなら最大ダッシュ状態になる
			if (this->PlayerStatusList->bGetPlayerAfterDodgeFlag() == true)
			{
				fSpeed = PLAER_DASH_MAX_SPEED * fMoveSpeedRatio;

				/* モーション設定 */
				this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_RUN_HIGH);
			}

			// スティックの倒し具合で速度を変化
			else if (fStickTiltMagnitude > STICK_TILT_PLAER_DASH)
			{
				//走り（通常）
				fSpeed = PLAER_DASH_NOMAL_SPEED * fMoveSpeedRatio;
				//フレーム数をカウント
				this->PlayerStatusList->SetPlayerNormalDashFlameCount(PlayerStatusList->iGetPlayerNormalDashFlameCount() + 1);

				//一定フレームがたったら走り（最大）へ
				this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_RUN_LOW);

				//一定フレームに達した時、ダッシュエフェクトを出現させる
				if (this->PlayerStatusList->iGetPlayerNormalDashFlameCount() == FLAME_COUNT_TO_MAX_SPEED)
				{
					/* エフェクト追加 */
					{
						/* ダッシュエフェクトを生成 */
						EffectSelfDelete* pAddEffect = new EffectSelfDelete;

						/* ダッシュエフェクト読み込み */
						pAddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_dash/FX_dash")));

						/* ダッシュエフェクトの時間設定 */
						pAddEffect->SetDeleteCount(30);

						/* エフェクトの生成方向の設定 */
						// ※プレイヤーの前に出す
						VECTOR vecInput = VGet(0.f, 0.f, 1.f);

						/* カメラの水平方向の向きを移動用の向きに設定 */
						float fAngleX = this->PlayerStatusList->fGetPlayerAngleX();

						/* エフェクトの座標を算出 */
						VECTOR vecAdd;

						// 方向
						vecAdd.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
						vecAdd.y = 0.f;
						vecAdd.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
						vecAdd = VNorm(vecAdd);

						// 回避時の速度分離す
						vecAdd = VScale(vecAdd, PLAYER_DODGE_SPEED);

						// 高さ
						vecAdd.y = PLAYER_HEIGHT / 2.f;

						/* ダッシュエフェクトの座標設定 */
						pAddEffect->SetPosition(VAdd(this->vecPosition, vecAdd));

						/* ダッシュエフェクトの回転量設定 */
						pAddEffect->SetRotation(VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

						/* ダッシュエフェクトの初期化 */
						pAddEffect->Initialization();

						/* ダッシュエフェクトをリストに登録 */
						{
							/* ダッシュエフェクトをリストに登録 */
							this->ObjectList->SetEffect(pAddEffect);
						}
					}
				}
				//一定フレーム以上になったら走り（最大）へ
				else if (this->PlayerStatusList->iGetPlayerNormalDashFlameCount() >= FLAME_COUNT_TO_MAX_SPEED)
				{
					fSpeed = PLAER_DASH_MAX_SPEED * fMoveSpeedRatio;

					/* 走行(高速)モーション設定 */
					this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_RUN_HIGH);
				}
			}
			else
			{
				//歩き
				this->PlayerStatusList->SetPlayerNowMoveSpeed(PLAYER_WALK_MOVE_SPEED);
				this->PlayerStatusList->SetPlayerNormalDashFlameCount(0);
				fSpeed = PLAYER_WALK_MOVE_SPEED * fMoveSpeedRatio;

				/* 歩行モーション設定 */
				this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_WALK);
			}

			/* 2025.01.09 菊池雅道	移動処理追加		終了	*/
			/* 2025.01.27 菊池雅道	エフェクト処理追加 終了	*/

			/* 現在速度を更新 */
			this->PlayerStatusList->SetPlayerNowMoveSpeed(fSpeed);

			/* カメラの水平方向の向きを移動用の向きに設定 */
			float fAngleX = this->PlayerStatusList->fGetCameraAngleX();

			/* 移動量を算出 */
			vecAddMove.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
			vecAddMove.y = 0.0f;
			vecAddMove.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
			vecAddMove = VScale(vecAddMove, fSpeed);

			/* プレイヤーの向きを移動方向に合わせるか確認 */
			if (bPlayerAngleSetFlg == true)
			{
				// 合わせる場合
				/* プレイヤーの向きを移動方向に合わせる */
				float fPlayerAngle = atan2f(vecInput.x, vecInput.z);	// 移動方向の角度(ラジアン)を取得
				fPlayerAngle = fAngleX - fPlayerAngle;			// カメラの向きと合成
				this->PlayerStatusList->SetPlayerAngleX(fPlayerAngle);	// プレイヤーの向きを設定
			}
		}
	}
	else
	{
		// 移動入力がされていない場合
		/* 移動速度を0にする */
		this->PlayerStatusList->SetPlayerNowMoveSpeed(0);
		//回避後フラグをリセット
		this->PlayerStatusList->SetPlayerAfterDodgeFlag(false);

		// 居合(強)(終了)モーション中以外なら待機モーションに遷移 ※バグ対策のため、以下ような書き方になってます
		if (this->PlayerStatusList->iGetPlayerMotion() == PLAYER_MOTION_DRAW_SWORD_END)
		{
		}
		else
		{
			/* 待機モーション設定 */
			this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_IDLE);
		}
	}

	/* 移動量を加算 */
	this->vecMove = VAdd(this->vecMove, vecAddMove);
}

/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */
// ジャンプ
void CharacterPlayer::Player_Jump()
{
	/* プレイヤーの移動状態を取得 */
	int iPlayerMoveState = this->PlayerStatusList->iGetPlayerMoveState();
	/* プレイヤーの攻撃状態を取得 */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();
	/* ジャンプ処理を行うかのフラグ */
	bool bJumpFlag = true;

	/* プレイヤーの移動状態がジャンプ可能であるか確認 */
	// ※要相談
	switch (iPlayerMoveState)
	{
	/* ジャンプ可能な状態 */
	case PLAYER_MOVESTATUS_FREE:				// 自由状態
		
		/* ジャンプ処理を行う */
		bJumpFlag = true;
	
		break;

	/* ジャンプ不可能な状態 */
	case PLAYER_MOVESTATUS_DODGING:				// 回避状態中
		
		/* ジャンプ処理を行う */
		bJumpFlag = false;
		
		break;
	}

	/* プレイヤーの攻撃状態がジャンプ可能であるか確認 */
	// ※要相談
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
		
		/* ジャンプ処理を行わない */
		bJumpFlag = false;
		break;
	}

	/* プレイヤーのジャンプ処理 */
	/* 移動処理を行う状態か確認 */
	if (bJumpFlag == true)
	{
		/* ジャンプ回数が最大数を超えていないか確認 */
		int iNowJumpCount = this->PlayerStatusList->iGetPlayerNowJumpCount();
		int iMaxJumpCount = this->PlayerStatusList->iGetPlayerMaxJumpCount();
		if (iNowJumpCount < iMaxJumpCount)
		{
			/* ジャンプ入力がされているか確認 */
			if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
			{
				// ジャンプ入力がされている場合
				/* ジャンプ処理 */
				// 仮で落下速度を-にする処理を行う
				//this->PlayerStatusList->SetPlayerNowFallSpeed(-20.0f);
				this->PlayerStatusList->SetPlayerNowFallSpeed(-30.0f);

				/* ジャンプ回数を更新 */
				this->PlayerStatusList->SetPlayerNowJumpCount(iNowJumpCount + 1);

				this->PlayerStatusList->SetPlayerJumpingFlag(true);

				/* ジャンプのSEを再生 */
				gpDataList_Sound->SE_PlaySound(SE_PLAYER_JUMP);
			}
		}
	}
}
/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */

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
	// ※要相談
	switch (iPlayerMoveState)
	{
		/* 重力処理を行う状態 */
	case PLAYER_MOVESTATUS_FREE:				// 自由状態

		/* 重力処理を行う */
		bGravityFlag = true;
		break;

		/* 重力処理を行わない状態 */
	case PLAYER_MOVESTATUS_DODGING:			// 回避状態中

		/* 重力処理を行わない(重力処理を終了) */
		bGravityFlag = true;
		break;
	}

	/* プレイヤーが重力処理を行う攻撃状態であるか確認 */
	// ※要相談
	switch (iPlayerAttackState)
	{
		/* 重力処理を行う状態 */
	case PLAYER_ATTACKSTATUS_FREE:					// 自由状態		
	case PLAYER_ATTACKSTATUS_MELEE_POSTURE:			// 近接攻撃構え中		
	case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:	// 遠距離攻撃構え中
		/* 重力処理を行う */
		bGravityFlag = true;
		break;

		/* 重力処理を行わない状態 */
	case PLAYER_ATTACKSTATUS_MELEE_WEEK:			// 近接攻撃中(弱)
	case PLAYER_ATTACKSTATUS_MELEE_STRONG:			// 近接攻撃中(強)
	case PLAYER_ATTACKSTATUS_PROJECTILE:			// 遠距離攻撃中
		/* 重力処理を行わない(重力処理を終了) */
		bGravityFlag = false;
		break;
	}

	// ※現在bGravityFlagで重力処理は分けていない（要相談）

	/* 落下量取得 */
	float fFallSpeed = this->PlayerStatusList->fGetPlayerNowFallSpeed();		// 現時点での加速量取得
	fFallSpeed += this->PlayerStatusList->fGetPlayerFallAcceleration();	// 加速度を加算

	/* 落下の加速度を更新 */
	this->PlayerStatusList->SetPlayerNowFallSpeed(fFallSpeed);

	/* 重力による移動後の座標を取得 */
	this->vecMove.y -= this->PlayerStatusList->fGetPlayerNowFallSpeed();
}
/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */


// 回避
void CharacterPlayer::Player_Dodg()
{
	/* 2025.01.09 菊池雅道　	移動処理追加		開始 */
	/* 2025.01.26 駒沢風助	コード修正		開始 */
	/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */

	/* プレイヤーの移動状態を取得 */
	int iPlayerMoveState = this->PlayerStatusList->iGetPlayerMoveState();

	/* プレイヤー場外が"回避状態中"であるか確認 */
	if (iPlayerMoveState == PLAYER_MOVESTATUS_DODGING)
	{
		// 回避中である場合
		/* 回避状態が維持される時間を超えていないか確認 */
		if (this->PlayerStatusList->iGetPlayerNowDodgeFlame() <= PLAYER_DODGE_FLAME)
		{
			// 超えていない(回避状態を継続する)場合
			/* 回避による移動方向を設定 */
			this->vecMove = VScale(this->PlayerStatusList->vecGetPlayerDodgeDirection(), PLAYER_DODGE_SPEED);

			/* 回避の経過時間を進める */
			this->PlayerStatusList->SetPlayerNowDodgeFlame(this->PlayerStatusList->iGetPlayerNowDodgeFlame() + 1);

		}
		else
		{
			// 超えている(回避状態を終了する)場合
			/* 回避完了直後フラグを有効にする */
			this->PlayerStatusList->SetPlayerAfterDodgeFlag(true);

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
			/* 空中での回避回数制限を超えていないか */
			if (this->PlayerStatusList->iGetPlayerDodgeWhileJumpingCount() < PLAYER_DODGE_IN_AIR_LIMIT)
			{
				/* 回避開始時の時間をリセット */
				this->PlayerStatusList->SetPlayerNowDodgeFlame(0);

				/* 回避方向設定 */
				{
					/* 入力による移動量を取得 */
					VECTOR vecInput = this->InputList->vecGetGameInputMoveDirection();

					/* カメラの水平方向の向きを移動用の向きに設定 */
					float fAngleX = this->PlayerStatusList->fGetCameraAngleX();

					/* 移動量を算出 */
					VECTOR vecMove;
					vecMove.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
					vecMove.y = 0.0f;
					vecMove.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);

					/* 回避の移動方向を現在の移動用の向きに設定 */
					this->PlayerStatusList->SetPlayerDodgeDirection(VNorm(vecMove));
				}

				/* 回避状態の進行率をリセット */
				this->PlayerStatusList->SetPlayerDodgeProgress(0.0f);

				/* 落下の加速度を初期化 */
				this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);

				/* プレイヤー状態を"回避状態中"に設定 */
				this->PlayerStatusList->SetPlayerMoveState(PLAYER_MOVESTATUS_DODGING);

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
					this->pDodgeEffect = new EffectManualDelete;

					/* 回避エフェクトの読み込み */
					this->pDodgeEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_dash/FX_dash")));

					/* エフェクトの座標設定 */
					this->pDodgeEffect->SetPosition(this->vecPosition);

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
			}
		}
	}

	/* 2025.01.09 菊池雅道	移動処理追加		終了 */
	/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */

	/* 回避エフェクトが存在している場合 */
	if (pDodgeEffect != nullptr)
	{
		/* エフェクトの生成方向の設定 */
		// ※プレイヤーの前に出す
		VECTOR vecInput = VGet(0.f, 0.f, 1.f);

		/* カメラの水平方向の向きを移動用の向きに設定 */
		float fAngleX = this->PlayerStatusList->fGetPlayerAngleX();

		/* エフェクトの座標を算出 */
		VECTOR vecAdd;
		
		// 方向
		vecAdd.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
		vecAdd.y = 0.f;
		vecAdd.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
		vecAdd = VNorm(vecAdd);
		
		// 回避時の速度分離す
		vecAdd = VScale(vecAdd, PLAYER_DODGE_SPEED);
		
		// 高さ
		vecAdd.y = PLAYER_HEIGHT / 2.f;

		/* エフェクトの座標設定 */
		this->pDodgeEffect->SetPosition(VAdd(this->vecPosition, vecAdd));

		/* エフェクトの回転量設定 */
		this->pDodgeEffect->SetRotation(VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));
	}

	/* 2025.01.09 菊池雅道	移動処理追加		終了 */
	/* 2025.01.26 駒沢風助	コード修正		終了*/
	/* 2025.01.29 菊池雅道　	エフェクト処理追加	開始 */
}

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

					/* 2025.01.09 菊池雅道　移動処理追加 追加 */

					//ジャンプ中のフラグをリセット
					this->PlayerStatusList->SetPlayerJumpingFlag(false);

					//ジャンプ中の回避回数をリセット
					this->PlayerStatusList->SetPlayerDodgeWhileJumpingCount(0);
					/* 2025.01.09 菊池雅道　移動処理追加 終了 */
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

	/* 2025.01.27 菊池雅道	エフェクト処理追加	開始*/
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
				pAddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_land/FX_land")));

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
		}
	}
	/* 2025.01.27 菊池雅道	エフェクト処理追加	終了*/

	/* 着地座標を更新 */
	vecNextPosition.y = fStandPosY;

	/* プレイヤー座標を更新 */
	this->vecPosition = vecNextPosition;

	/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */
	/* 現在のプレイヤー状態を取得 */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

	/* モーションを更新 */
	{
		/* 空中にいる(着地していない)か確認 */
		if (this->PlayerStatusList->bGetPlayerJumpingFlag() == true)
		{	
			/* 攻撃を構えていない状態であるか確認 */
			// ※構えている最中は落下モーションに遷移させない
			/* 近接攻撃構え中でないか確認 */
			if (iPlayerAttackState != PLAYER_ATTACKSTATUS_MELEE_POSTURE)
			{
				/* 遠距離攻撃構え中でないか確認 */
				if (iPlayerAttackState != PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE)
				{
					/* 強攻撃(近接)中でないか確認 */
					if (iPlayerAttackState != PLAYER_ATTACKSTATUS_MELEE_STRONG)
					{
						/* 上昇しているか確認 */
						if (this->PlayerStatusList->fGetPlayerFallAcceleration() < 0)
						{
							// 上昇している場合
							/* モーションを"ジャンプ(上昇)"に設定 */
							PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_JUMP_UP);
						}
						else
						{
							// 下降している場合
							/* モーションを"ジャンプ(下降)"に設定 */
							PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_JUMP_DOWN);
						}

					}
				}
			}
		}
	}
}
/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */

// 移動処理(水平方向)
void CharacterPlayer::Movement_Horizontal()
{
	/* 移動後の座標を取得(水平方向) */
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x + this->vecMove.x;
	vecNextPosition.y = this->vecPosition.y;
	vecNextPosition.z = this->vecPosition.z + this->vecMove.z;

	/* 道中でオブジェクトに接触しているか判定 */
	{
		/* 現在位置から移動後座標へ向けたカプセルコリジョンを作成 */
		// ※ 元の位置から移動後の位置へ向けたカプセルコリジョンを作成
		stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].vecCapsuleBottom = VAdd(this->vecPosition, VGet(0.f, PLAYER_HEIGHT - PLAYER_WIDE, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].vecCapsuleTop = VAdd(vecNextPosition, VGet(0.f, PLAYER_HEIGHT - PLAYER_WIDE, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].fCapsuleRadius = PLAYER_WIDE;
		stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].vecCapsuleBottom = VAdd(this->vecPosition, VGet(0.f, PLAYER_WIDE + PLAYER_CLIMBED_HEIGHT, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].vecCapsuleTop = VAdd(vecNextPosition, VGet(0.f, PLAYER_WIDE + PLAYER_CLIMBED_HEIGHT, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].fCapsuleRadius = PLAYER_WIDE;

		/* 足場を取得 */
		auto& PlatformList = ObjectList->GetCollisionList();

		/* 足場と接触するか確認 */
		for (auto* platform : PlatformList)
		{
			/* 足場との接触判定 */
			for (int i = 0; i < PLAYER_MOVE_COLLISION_MAX; i++)
			{
				/* オブジェクトと接触しているか確認 */
				MV1_COLL_RESULT_POLY_DIM stHitPolyDim = platform->HitCheck_Capsule(stHorizontalCollision[i]);

				/* 接触しているか確認 */
				if (stHitPolyDim.HitNum > 0)
				{
					// 1つ以上のポリゴンが接触している場合
					/* 法線ベクトルの作成 */
					VECTOR vecNormalSum = VGet(0.f, 0.f, 0.f);

					/* ポリゴンと接触した座標 */
					VECTOR vecHitPos = VGet(0.f, 0.f, 0.f);

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

					/* 移動後座標に球体ポリゴンを作成 */
					COLLISION_SQHERE stSphere;
					stSphere.vecSqhere = vecNextPosition;
					stSphere.fSqhereRadius = PLAYER_WIDE;

					/* 法線の方向にプレイヤーを押し出す */
					// ※ 対象のコリジョンと接触しなくなるまで押し出す
					// ※ このやり方では、高速で移動した場合にコリジョンが押し出されない可能性があるので修正予定
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
				}
			}
		}
	}

	/* プレイヤーの座標を移動させる */
	this->vecPosition = vecNextPosition;

	/* モーションを更新 */
	{
		// ※移動量とかでモーションを変更する処理を追加
	}
}
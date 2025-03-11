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


#include "CharacterPlayer.h"

/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */
/* 2025.03.03 菊池雅道	近距離攻撃(強)処理修正 開始 */
/* 2025.03.04 菊池雅道	スローモーション処理追加	開始 */
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
			/* 攻撃入力がされているか確認 */
			if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK) == true)
			{
				// 攻撃入力がされている場合
				/* プレイヤー状態を"近接攻撃構え中"に設定 */
				this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_MELEE_POSTURE);
			}
			/* エイム(構え)入力がされているか確認 */
			else if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_AIM) == true)
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
				if (this->InputList->bGetGameInputAction(INPUT_REL, GAME_AIM) == false)
				{
					/* エイム(構え)キャンセルフラグを解除 */
					this->PlayerStatusList->SetPlayerAimCancelledFlg(false);
				}
			}

			// 近距離攻撃(強)で敵を倒した後の処理
			/* 近距離攻撃(強)で敵を倒した後のフラグを確認 */
			if(this->PlayerStatusList->bGetPlayerMeleeStrongEnemyAttackFlg() == true)
			{
				// 近距離攻撃(強)で敵を倒した後の場合

				/* 近距離攻撃(強)後のカウントを取得 */
				int iPlayerMeleeStrongAfterCount = this->PlayerStatusList->iGetPlayerMeleeStrongAfterCount();

				/* 近距離攻撃(強)後のカウントを加算 */
				this->PlayerStatusList->SetPlayerMeleeStrongAfterCount(iPlayerMeleeStrongAfterCount + 1);

				/* 近距離攻撃(強)後のカウントが一定数を超えていないか確認 */
				if (iPlayerMeleeStrongAfterCount < PLAYER_STRONG_MELEE_AFTER_COUNT_MAX)
				{
					// 近距離攻撃(強)後のカウントが一定数を超えていない場合
					/* スローモーションフラグを有効化 */
					this->StageStatusList->SetGameSlowFlg(true);
				}
				else
				{
					// 近距離攻撃(強)後のカウントが一定数を超えた場合
					/* 近距離攻撃(強)後のカウントをリセット */
					this->PlayerStatusList->SetPlayerMeleeStrongAfterCount(0);

					/* スローモーションフラグを無効化 */
					this->StageStatusList->SetGameSlowFlg(false);

					/* 近距離攻撃(強)で敵を倒した後のフラグを解除 */
					this->PlayerStatusList->SetPlayerMeleeStrongEnemyAttackFlg(false);
				}
			}
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

	/* 2025.01.24 菊池雅道	攻撃処理追加		開始 */
	/* 2025.01.26 駒沢風助	コード修正		開始*/
	/* 2025.01.27 菊池雅道	エフェクト処理追加 開始 */
	/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */
	/* 2025.02.07 菊池雅道	エフェクト処理修正 開始 */
	/* 2025.02.19 菊池雅道	エフェクト処理修正 開始 */
/* 2025.02.26 菊池雅道	近距離攻撃(強)処理修正	開始 */
/* 2025.03.03 菊池雅道	近距離攻撃(強)処理修正 開始 */

// 近接攻撃(構え)
void CharacterPlayer::Player_Melee_Posture()
{
	/* プレイヤーの現在の攻撃チャージフレームの取得 */
	int iNowAttakChargeFlame = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame();

	/* プレイヤーの空中での近接攻撃(強)の回数を取得 */
	int iNowMeleeStrongAirCount = this->PlayerStatusList->iGetPlayerMeleeStrongAirCount();

	/* プレイヤーが近接攻撃(強)で敵を倒した後のカウントを取得 */
	int iPlayerMeleeStrongAfterCount = this->PlayerStatusList->iGetPlayerMeleeStrongAfterCount();

	/* 攻撃入力がされているか確認 */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK) == true)
	{
		// 近接攻撃(強)で敵を倒した後、一定時間内であれば攻撃チャージフレーム数を最大にする 
		/* プレイヤーが近接攻撃(強)で敵を倒した後かのフラグを確認 */
		if (this->PlayerStatusList->bGetPlayerMeleeStrongEnemyAttackFlg() == true)
		{
			// 近接攻撃(強)で敵を倒した後の場合
			/* 近接攻撃(強)で敵を倒した後のカウントが一定値以下か確認 */
			if (iPlayerMeleeStrongAfterCount <= PLAYER_STRONG_MELEE_AFTER_COUNT_MAX)
			{
					/* 近接攻撃(強)の攻撃チャージフレーム数を最大に設定 */
					this->PlayerStatusList->SetPlayerNowAttakChargeFlame(PLAYER_MELEE_CHARGE_MAX);

					/* 現在の攻撃チャージフレームを取得 */
					iNowAttakChargeFlame = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame();

					/* 近接攻撃(強)で敵を倒した後のカウントをリセット */
					this->PlayerStatusList->SetPlayerMeleeStrongAfterCount(0);

					/* 近接攻撃(強)で敵を倒した後のフラグを解除 */
					this->PlayerStatusList->SetPlayerMeleeStrongEnemyAttackFlg(false);
							
			}				
		}

		// 攻撃チャージフレームが強攻撃の切り替わりに達したら
		if (iNowAttakChargeFlame == PLAYER_CHARGE_TO_STRONG_TIME)
		{
			/* 空中での近接攻撃(強)の回数が最大数が超えていないか確認 */
			if (iNowMeleeStrongAirCount >= this->PlayerStatusList->iGetPlayerMeleeStrongAirMaxCount())
			{
				// 超えている場合
				/* 近接攻撃(強)の処理を行わない */
				return;
			}

			/* プレイヤーモーションを"居合(溜め)"に変更 */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_CHARGE);

			/* 溜めのエフェクトを刀の位置に生成 */
			this->pChargeEffect = new EffectManualDelete_PlayerFollow_Frame(this->iKatanaFrameNo);

			/* 溜めエフェクトの読み込み */
			this->pChargeEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_charge/FX_charge")));

			/* 溜めエフェクトの回転量設定 */
			this->pChargeEffect->SetRotation(this->vecRotation);

			/* 溜めエフェクトの初期化 */
			this->pChargeEffect->Initialization();

			/* 溜めエフェクトをリストに登録 */
			{
				/* 溜めエフェクトをリストに登録 */
				this->ObjectList->SetEffect(this->pChargeEffect);
			}
		}

		/* 近接攻撃(強)チャージ処理 */
		{
			/* チャージフレームが最大値を超えていないか確認 */
			if (iNowAttakChargeFlame <= PLAYER_MELEE_CHARGE_MAX)
			{
				// 超えていない場合
				/* プレイヤーの現在の攻撃チャージフレームを加算 */
				PlayerStatusList->SetPlayerNowAttakChargeFlame(iNowAttakChargeFlame + 1);

				/* 加算によりチャージフレームが最大値に達したか確認 */
				if ((iNowAttakChargeFlame + 1) == PLAYER_MELEE_CHARGE_MAX)
				{
					// 最大値に達した場合
					/* 溜め居合チャージ完了のSEを再生 */
					gpDataList_Sound->SE_PlaySound(SE_PLAYER_CHARGE_COMPLETE);

					/* 溜めエフェクトは削除 */
					this->pChargeEffect->SetDeleteFlg(true);
					this->pChargeEffect = nullptr;

					/* 溜め完了エフェクトを生成 */
					EffectSelfDelete_PlayerFollow_Frame* pAddEffect = new EffectSelfDelete_PlayerFollow_Frame(iKatanaFrameNo);

					/* 溜め完了エフェクトの読み込み */
					pAddEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_charge_finish/FX_charge_finish")));

					/* 溜め完了エフェクトの初期化 */
					pAddEffect->Initialization();

					/* 溜め完了エフェクトの時間を設定 */
					pAddEffect->SetDeleteCount(20);

					/* 溜め完了エフェクトをリストに登録 */
					{
						/* 溜め完了エフェクトをリストに登録 */
						this->ObjectList->SetEffect(pAddEffect);
					}

					/* 溜め完了後エフェクトを生成 */
					this->pChargeHoldEffect = new EffectManualDelete_PlayerFollow_Frame(iKatanaFrameNo);
					
					/* 溜め完了後エフェクトの読み込み */
					this->pChargeHoldEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_charge_hold/FX_charge_hold")));
					
					/* 溜め完了後エフェクトの回転量設定 */
					this->pChargeHoldEffect->SetRotation(this->vecRotation);

					/* 溜め完了後エフェクトの初期化 */
					this->pChargeHoldEffect->Initialization();

					/* 溜め完了後エフェクトをリストに登録 */
					{
						/* 溜め完了後エフェクトをリストに登録 */
						this->ObjectList->SetEffect(this->pChargeHoldEffect);
					}
				}
			}
		
			/* 移動量算出 */
			//float fMove = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() * 2.7f;
			// 臨時でちょっと長めにする
			//float fMove = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() * 5.f;
			float fMove = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() * 5.f * 3.f;

			/* 移動方向算出 */
			VECTOR vecMoveDirection = VNorm(VSub(this->StageStatusList->vecGetCameraTarget(), this->StageStatusList->vecGetCameraPosition()));

			/* 縦方向には移動しないように設定 */
			vecMoveDirection.y = 0;

			/* 近接攻撃(強)による移動量を設定 */
			this->PlayerStatusList->SetPlayerChargeAttakTargetMove(VScale(vecMoveDirection, fMove));

			/* 攻撃チャージフレームが強攻撃に派生しているか確認 */
			if (iNowAttakChargeFlame >= PLAYER_CHARGE_TO_STRONG_TIME)
			{
				/* カメラモードを"構え(近接攻撃構え)"に変更 */
				this->StageStatusList->SetCameraMode(CAMERA_MODE_AIM_MELEE);

				/* プレイヤーの向きをカメラの向きに固定 */
				this->PlayerStatusList->SetPlayerAngleX(this->StageStatusList->fGetCameraAngleX());
				
				/* ロックオン範囲のコリジョン作成 */
				{
					/* ロックオン範囲コリジョン */
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
			}

			/* デバッグ用処理 */
			{
				/* デバッグ用移動後座標を設定 */
				this->stMeleeStrongMoveCollsion.vecCapsuleTop = VAdd(VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT - PLAYER_WIDE, 0)), VScale(vecMoveDirection, fMove));
				this->stMeleeStrongMoveCollsion.vecCapsuleBottom = VAdd(VAdd(this->vecPosition, VGet(0, PLAYER_WIDE, 0)), VScale(vecMoveDirection, fMove));
				this->stMeleeStrongMoveCollsion.fCapsuleRadius = PLAYER_WIDE;
			}
		}
	}
	else
	{
		// 攻撃入力がされていない場合
		/* 攻撃チャージフレームに応じて処理を変更 */
		if (iNowAttakChargeFlame < PLAYER_CHARGE_TO_STRONG_TIME)
		{
			// 強攻撃に切り替わる前の場合
			/* プレイヤーの状態を"近接攻撃中(弱)"に設定 */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_MELEE_WEEK);
		}
		else
		{
			// 強攻撃になる場合
			/* 空中での近接攻撃(強)の回数が最大数が超えていないか確認 */
			if (iNowMeleeStrongAirCount >= this->PlayerStatusList->iGetPlayerMeleeStrongAirMaxCount())
			{
				// 超えている場合
				/*近接攻撃(強)の処理を行わない */
				return;
			}

			/* プレイヤーの状態を"近接攻撃中(強)"に設定 */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_MELEE_STRONG);

			/* プレイヤーのため攻撃用のカウントを初期化 */
			this->PlayerStatusList->SetPlayerMeleeStrongChargeCount(0);

			/* 落下の加速度を初期化 */
			this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);

		}

		/* プレイヤーの現在の攻撃チャージフレームをリセット */
		this->PlayerStatusList->SetPlayerNowAttakChargeFlame(0);
	}

	//エフェクトの削除
	//近接攻撃構え状態が解除された場合
	if (this->PlayerStatusList->iGetPlayerAttackState() != PLAYER_ATTACKSTATUS_MELEE_POSTURE)
	{
		this->PlayerStatusList->SetPlayerNowAttakChargeFlame(0);

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
}
/* 2025.01.24 菊池雅道	攻撃処理追加			終了*/
/* 2025.01.26 駒沢風助	コード修正				終了*/
/* 2025.01.27 菊池雅道	エフェクト処理追加 終了 */
/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */
/* 2025.02.07 菊池雅道	エフェクト処理修正 終了 */
/* 2025.02.19 菊池雅道	エフェクト処理修正 終了 */
/* 2025.02.26 菊池雅道	近距離攻撃(強)処理修正	終了 */

// 近接攻撃(弱)
void CharacterPlayer::Player_Melee_Weak()
{
	/* 2025.01.22 菊池雅道	攻撃処理追加		開始 */
	/* 2025.01.26 駒沢風助	コード修正		開始*/
	/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */
	/* 2025.02.26 菊池雅道	クールタイム処理追加 開始 */
	/* 2025.03.06 菊池雅道	エフェクト処理追加		開始 */

	// クールタイムが残っている場合攻撃しない
	/* 近接攻撃(弱)のクールタイムを確認 */
	if (this->iMeleeWeakCoolTime > 0)
	{
		// クールタイムが残っている場合
		/* 近距離攻撃(弱)処理を行わない */
		return;
	}

	// 近接攻撃(弱)でない場合
	/* プレイヤーのモーションを近接攻撃(弱)に設定 */
	this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_WEAK);

	/* 近接攻撃として扱う弾を作成 */
	// ※現在のプレイヤーの向きに弾を作成
	this->pBulletMeleeWeak = new BulletPlayerMeleeWeak;

	/* 攻撃の向きを設定 */
	this->pBulletMeleeWeak->SetRotation(VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

	/* 初期化を行う */
	this->pBulletMeleeWeak->Initialization();

	/* バレットリストに追加 */
	ObjectList->SetBullet(this->pBulletMeleeWeak);

	/* 近接攻撃(弱)のSEを再生 */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_NIAI);

	/* 抜刀エフェクトを生成 */
	EffectSelfDelete_PlayerFollow_Frame* pSeathEffect = new EffectSelfDelete_PlayerFollow_Frame(iKatanaFrameNo);

	/* 抜刀エフェクトの読み込み */
	pSeathEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_seath_unseath/FX_seath_unseath")));

	/* 抜刀エフェクトの初期化 */
	pSeathEffect->Initialization();

	/* 抜刀エフェクトの時間を設定 */
	pSeathEffect->SetDeleteCount(20);

	/* 抜刀エフェクトをリストに登録 */
	{
		/* 抜刀エフェクトをリストに登録 */
		this->ObjectList->SetEffect(pSeathEffect);
	}

	/* 近接攻撃(弱)のクールタイム設定 */
	this->iMeleeWeakCoolTime = PLAYER_MELEE_WEAK_COLLTIME;

	/* 自由状態に戻す */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
}
/* 2025.01.22 菊池雅道　攻撃処理追加	終了 */
/* 2025.01.26 駒沢風助	コード修正		終了 */
/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */
/* 2025.02.26 菊池雅道	クールタイム処理追加 終了 */
/* 2025.03.06 菊池雅道	エフェクト処理追加		終了 */

/* 2025.01.22 菊池雅道	攻撃処理追加		開始 */
/* 2025.01.26 駒沢風助	コード修正		開始 */
/* 2025.02.03 菊池雅道	近距離攻撃(強)後の処理追加	開始 */
/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */
/* 2025.02.26 菊池雅道	近距離攻撃(強)処理修正		開始 */
/* 2025.03.03 菊池雅道	近距離攻撃(強)処理修正		開始 */
/* 2025.03.04 菊池雅道	近距離攻撃(強)処理修正		開始 */
/* 2025.03.06 菊池雅道	近距離攻撃(強)処理修正		開始 */
// 近距離攻撃(強)
void CharacterPlayer::Player_Charge_Attack()
{
	//近距離攻撃(強)中はスローモーションを行わない
	/* スローモーションフラグを確認 */
	if (this->StageStatusList->bGetGameSlowFlg() == true)
	{
		// スローモーション中の場合
		/* スローモーションフラグを無効化 */
		this->StageStatusList->SetGameSlowFlg(false);
	}

	/* 近距離攻撃(強)状態でのチャージフレーム数を取得 */
	int iMeleeStrongChargeCount = this->PlayerStatusList->iGetPlayerMeleeStrongChargeCount();

	/* カウントを確認 */
	if (iMeleeStrongChargeCount == 0)
	{
		// 0である場合
		// ※モーション遷移直後である場合
		/* プレイヤーのモーションを近接攻撃(強)に変更する */
		this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_STRONG);

		/* 溜め居合攻撃のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_PLAYER_SPIAI);

		// 空中で攻撃した場合の処理
		/* プレイヤーの着地フラグを確認 */
		if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
		{
			// 着地していない場合
			/* 現在の空中での近距離攻撃(強)回数を取得 */
			int iNowMelleeStrongAirCount = this->PlayerStatusList->iGetPlayerMeleeStrongAirCount();

			/* 空中での近距離攻撃(強)回数を加算 */
			this->PlayerStatusList->SetPlayerMeleeStrongAirCount(iNowMelleeStrongAirCount + 1);
		}

			/* ロックオン中のエネミーを取得 */
			Enemy_Basic* pLockOnEnemy = this->PlayerStatusList->pGetPlayerLockOnEnemy();

			/* 近接攻撃(強)による移動量を取得 */
			VECTOR vecMoveDirection = this->PlayerStatusList->vecGetPlayerChargeAttakTargetMove();

		// ※ロックオン中のエネミーが存在するかで処理を分岐させる
			/* ロックオン中のエネミーが存在するか */
			if (pLockOnEnemy != nullptr)
			{
				// 存在する場合(敵に攻撃する場合)
				/* 空中での近接攻撃(強)の回数をリセット */
				this->PlayerStatusList->SetPlayerMeleeStrongAirCount(0);

				// 存在する場合
				/* 移動量をプレイヤーの現在位置からロックオン中のエネミーの位置に修正 */
				vecMoveDirection = VSub(pLockOnEnemy->vecGetPosition(), this->vecPosition);

				/* エネミーの位置から追加で移動(突き抜ける感じを出すため) */
				vecMoveDirection = VAdd(vecMoveDirection, VScale(VNorm(vecMoveDirection), 500.f));

				/* 敵を攻撃したフラグを設定 */
				this->PlayerStatusList->SetPlayerMeleeStrongEnemyAttackFlg(true);

			/* 近接攻撃(強)による移動量を取得 */
			this->PlayerStatusList->SetPlayerChargeAttakTargetMove(vecMoveDirection);
			}

	}
	else
	{
		// 1以上である場合
		/* 攻撃＆移動処理 */
		{
			/* 近接攻撃(強)による移動量を取得 */
			VECTOR vecMoveDirection = this->PlayerStatusList->vecGetPlayerChargeAttakTargetMove();

			/* 移動量をfloat型で取得 */
			float fMove = VSize(vecMoveDirection);
			
			/* 攻撃＆移動処理に入ってからのカウントを取得 */
			int iCount = iMeleeStrongChargeCount;

			/* 移動量を移動速度で割ってこの処理を行う回数を算出する */
			int	iMoveCount = (int)(fMove / PLAYER_MELEE_STRONG_MOVESPEED);

			/* プレイヤー移動 */
			if (iCount <= iMoveCount)
			{
				// 現在のカウントが移動回数以下である場合
				/* 移動量分プレイヤーを移動させる */
				this->vecMove = VAdd(this->vecMove, VScale(VNorm(vecMoveDirection), PLAYER_MELEE_STRONG_MOVESPEED));
			}
			else
			{
				// 最後の移動の場合
				/* 最後の移動量を取得 */
				float	iLastMove = fMove - (iMoveCount * PLAYER_MELEE_STRONG_MOVESPEED);

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

			/* 近接攻撃として扱う弾を作成 */
			// ※通常の弾とは違いカプセル型で作成する
			{
				BulletPlayerMeleeStrong* pBulletMeleeStrong = new BulletPlayerMeleeStrong;

				/* 弾に使用するカプセルを作成 */
				COLLISION_CAPSULE stBulletCollision;

				/* コリジョンの算出 */
				{
					/* 当たり判定は大きめに取る(仮で半径をプレイヤーの全長に設定) */
					stBulletCollision.fCapsuleRadius = PLAYER_HEIGHT;

					/* 片方は現在のプレイヤーの中心に設定 */
					stBulletCollision.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT / 2.f, 0));

					/* もう片方は移動後(推定)のプレイヤーの中心に設定 */
					stBulletCollision.vecCapsuleBottom = VAdd(stBulletCollision.vecCapsuleTop, this->vecMove);
				}

				/* 作成した弾にコリジョンを設定 */
				pBulletMeleeStrong->SetCollision_Capsule(stBulletCollision);

				/* バレットリストに追加 */
				ObjectList->SetBullet(pBulletMeleeStrong);
			}

			/* エフェクト追加 */
			{
				/* 近距離攻撃(強)のエフェクトを生成 */
				EffectSelfDelete* pAddEffect = new EffectSelfDelete();

				/* 近距離攻撃(強)エフェクトの読み込み */
				pAddEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_iai_dash/FX_iai_dash")));

				/* 近距離攻撃(強)エフェクトの再生時間を設定 */
				pAddEffect->SetDeleteCount(30);

				/* 近距離攻撃(強)エフェクトの座標設定 */
				pAddEffect->SetPosition(VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT / 2.f, 0)));

				/* 近距離攻撃(強)エフェクトの回転量設定 */
				pAddEffect->SetRotation(VGet(this->vecRotation.x, this->vecRotation.y, this->vecRotation.z * -1));

				/*近距離攻撃(強) エフェクトの初期化 */
				pAddEffect->Initialization();

				/* 近距離攻撃(強)エフェクトをリストに登録 */
				this->ObjectList->SetEffect(pAddEffect);
			}
		}
	}

	// 近接攻撃(強)で敵を倒した後、次の敵を探す
	/* プレイヤーが近接攻撃(強)で敵を倒した後かのフラグを確認 */
	if (this->PlayerStatusList->bGetPlayerMeleeStrongEnemyAttackFlg() == true)
	{
		// 近接攻撃(強)で敵を倒した後の場合
		// 次の敵を探す処理
		/* プレイヤーのモーションが"近距離攻撃(強)(終了)"になったタイミングとする */ 
	if(this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
	{
			// モーションが"近距離攻撃(強)(終了)"になった場合
			/* 索敵範囲を設定 */
		COLLISION_SQHERE stSearchSqere{ this->vecPosition, PLAYER_SEARCH_RANGE_AFTER_MELEE };

		/* プレイヤーに近いエネミーを取得する */
		NearEnemy stNearEnemy = { nullptr, 0.f };

		/* エネミーリストを取得 */
		auto& EnemyList = ObjectList->GetEnemyList();

			/* プレイヤーからエネミーの最小ベクトルを保持する変数 */
			VECTOR vecMinDirection = VGet(PLAYER_SEARCH_RANGE_AFTER_MELEE, PLAYER_SEARCH_RANGE_AFTER_MELEE, PLAYER_SEARCH_RANGE_AFTER_MELEE);

			/* プレイヤーからエネミーの最小距離を保持する変数 */
			float fMinDistance = VSize(vecMinDirection);

		/* 索敵範囲内のエネミーのうち最もプレイヤーに近いエネミーを対象に設定 */
		for (auto* enemy : EnemyList)
		{
			/* 索敵範囲に接触しているか確認 */
			if (enemy->HitCheck(stSearchSqere) == true)
			{
				// 索敵範囲内である場合
				/* コアのワールド座標を取得 */
					VECTOR vecCoreWorld = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

					/* プレイヤーとエネミーの間を確認する線分コリジョンを設定 */
					COLLISION_LINE stCollisionLine;

					/* 線分コリジョンの開始点を設定(プレイヤー) */
					stCollisionLine.vecLineStart = this->vecPosition;

					/* 線分コリジョン終了点を設定(エネミー) */
					stCollisionLine.vecLineEnd = vecCoreWorld;

					/* プラットフォームを取得 */
					auto& PlatformList = ObjectList->GetCollisionList();

					/* プラットフォームとの接触フラグ */
					bool bPlatformHitFlag = false;

					// 射線上にプラットフォームが存在するか確認する
					for (auto* platform : PlatformList)
					{
						/* プラットフォームと接触しているか確認 */
						MV1_COLL_RESULT_POLY stHitPoly = platform->HitCheck_Line(stCollisionLine);

						/* 接触している場合 */
						if (stHitPoly.HitFlag == true)
						{
							/* プラットフォームとの接触フラグを設定 */
							bPlatformHitFlag = true;

							/* ループを抜ける(次の敵に移る) */
							break;						
						}

					}

					// プレイヤーとエネミーの間にプラットフォームが存在しない場合、距離を確認する
					/* プラットフォームとの接触フラグが立っていないか確認 */
					if (bPlatformHitFlag == false)
					{
						// 接触フラグが立っていない場合
						/* プレイヤーからエネミーのベクトルを設定 */
						VECTOR vecDirection = VSub(vecCoreWorld, this->vecPosition);

						/* プレイヤーからエネミーの距離を設定 */
						float fDistance = VSize(vecDirection);

				/* 現在の最もプレイヤーから近いエネミーよりもプレイヤーに近いか確認 */
						if (fMinDistance >= fDistance)
				{
					// 近い場合
					/* プレイヤーから近いエネミーを更新 */
					stNearEnemy.pEnemy = enemy;
					stNearEnemy.fDistance = fDistance;

							/* プレイヤーからエネミーの最小距離を更新 */
							fMinDistance = fDistance;
						}	
				}
			}
		}

		/* 最もプレイヤー近いエネミーを対象に指定 */
		if (stNearEnemy.pEnemy != nullptr)
		{
			//対象が存在する場合
			/* プレイヤーから見た敵の向きを取得 */
			VECTOR vecNearEnemy = VSub(this->vecPosition, stNearEnemy.pEnemy->vecGetPosition());

			/* プレイヤーから見た敵の向きを正規化 */
			vecNearEnemy = VNorm(vecNearEnemy);

			/* プレイヤーから見た敵の角度を取得 */
			float fNearEnemyRotate = -atan2f(vecNearEnemy.x, vecNearEnemy.z);

			/* プレイヤーの向きを設定 */
			this->PlayerStatusList->SetPlayerAngleX(fNearEnemyRotate);

			/* プレイヤーの向きにカメラの向きを固定 */
				this->StageStatusList->SetCameraAngleX(fNearEnemyRotate);
		}
			else
			{
				// 対象が存在しない場合

				/* 敵を攻撃したフラグを解除(スローモーション解除のため) */
				this->PlayerStatusList->SetPlayerMeleeStrongEnemyAttackFlg(false);
			}

	}
	}
	/* 溜め攻撃のチャージフレーム数を+1する */
	this->PlayerStatusList->SetPlayerMeleeStrongChargeCount(iMeleeStrongChargeCount + 1);
}
/* 2025.01.22 菊池雅道	攻撃処理追加				終了 */
/* 2025.01.26 駒沢風助	コード修正		終了 */
/* 2025.02.03 菊池雅道	近距離攻撃(強)後の処理追加	終了 */
/* 2025.02.05 菊池雅道	ステータス関連修正			終了 */
/* 2025.02.26 菊池雅道	近距離攻撃(強)処理修正		終了 */
/* 2025.03.03 菊池雅道	近距離攻撃(強)処理修正		終了 */
/* 2025.03.04 菊池雅道	近距離攻撃(強)処理修正		終了 */
/* 2025.03.06 菊池雅道	近距離攻撃(強)処理修正		終了 */

/* 2025.02.12 菊池雅道	遠距離攻撃処理追加 開始 */
/* 2025.02.26 菊池雅道	クールタイム処理追加	開始 */
/* 2025.03.04 菊池雅道	スローモーション処理追加	開始 */
/* 2025.03.06 菊池雅道	スローモーション処理修正	開始 */
// 遠距離攻撃(構え)
void CharacterPlayer::Player_Projectile_Posture()
{
	/* エイム(構え)入力がされているか確認 */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_AIM) == true)
	{
		/* プレイヤーの向きをカメラの向きに固定 */
		this->PlayerStatusList->SetPlayerAngleX(this->StageStatusList->fGetCameraAngleX());
		
		/* カメラモードを"構え(クナイ攻撃)"に変更 */
		this->StageStatusList->SetCameraMode(CAMERA_MODE_AIM_KUNAI);

		/* プレイヤーのモーションが投擲でないか確認 */
		if (this->PlayerStatusList->iGetPlayerMotion_Attack() != MOTION_ID_ATTACK_THROW)
		{
			// プレイヤーのモーションが投擲でない場合
			/* プレイヤーのモーションを投擲(準備)に設定 */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_THROW_READY);
		}

		//入力されたボタンに応じて処理を変える
		/* 攻撃入力がされた場合 */
		if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK) == true)
		{
			/* 遠距離攻撃のクールタイムを確認 */
			if (this->iProjectileCoolTime == 0)
			{
				/* プレイヤーのモーションを投擲に設定 */
				this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_THROW);
				// クールタイムが0の場合
				/* プレイヤーの攻撃状態を"遠距離攻撃中"に遷移 */
				this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_PROJECTILE);
			}
		}
		/* ジャンプ入力がされた場合 */
		else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
		{
			// 遠距離攻撃構え状態をキャンセルする
			/* 遠距離攻撃構え状態キャンセルフラグをたてる */
			this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
			
			/* プレイヤーのモーションを無しに設定 */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);

			/* プレイヤー攻撃状態を"自由状態"に設定 */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

		}
		/* 回避入力がされた場合 */
		else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE) == true)
		{
			// 遠距離攻撃構え状態をキャンセルする
			/* 遠距離攻撃構え状態キャンセルフラグをたてる */
			this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
			
			/* プレイヤーのモーションを無しに設定 */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);

			/* プレイヤー攻撃状態を"自由状態"に設定 */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
		}
		
		// ジャンプ中であればスローモーションを行う
		/* ジャンプ中のフラグを確認 */
		if (this->PlayerStatusList->bGetPlayerJumpingFlag() == true)
		{
			// ジャンプ中の場合
			/* スローモーションフラグを有効化 */ 
			this->StageStatusList->SetGameSlowFlg(true);
		}
		/* ジャンプ中の場合 */
		else
		{
			// ジャンプ中でない場合
			/* スローモーションフラグを解除 */
			this->StageStatusList->SetGameSlowFlg(false);
		}
		
	}
	/* エイム(構え)入力がされていない場合 */
	else 
	{
		/* プレイヤー攻撃状態を"自由状態"に設定 */
		this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

		/* プレイヤーのモーションを無しに設定 */
		this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);

		/* スローモーションフラグを無効化 */
		this->StageStatusList->SetGameSlowFlg(false);
	}
}
/* 2025.02.12 菊池雅道	遠距離攻撃処理追加 終了 */
/* 2025.02.26 菊池雅道	クールタイム処理追加 終了 */
/* 2025.03.04 菊池雅道	スローモーション処理追加	終了 */
/* 2025.03.06 菊池雅道	スローモーション処理修正	終了 */

/* 2025.02.14 菊池雅道	遠距離攻撃処理追加 開始 */
/* 2025.02.21 菊池雅道	遠距離攻撃修正 開始 */
/* 2025.02.26 菊池雅道	クールタイム処理追加	開始 */
/* 2025.03.10 菊池雅道	エフェクト処理追加		開始 */
// 遠距離攻撃
void CharacterPlayer::Player_Projectile()
{
	/* プレイヤーの向きをカメラの向きに固定 */
	this->PlayerStatusList->SetPlayerAngleX(this->StageStatusList->fGetCameraAngleX());

	/* カメラモードを"構え(クナイ攻撃)"に変更 */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_AIM_KUNAI);
	
	/* クナイ(エフェクト)を作成 */
	this->pBulletKunaiEffect = new BulletPlayerKunaiEffect;

	/* クナイ(エフェクト)生成座標を設定 */
	this->pBulletKunaiEffect->SetPosition(VGet(this->vecPosition.x, this->vecPosition.y + PLAYER_HEIGHT / 2, this->vecPosition.z));
	
	/* ロックオン中のエネミーを取得 */
	Enemy_Basic* pLockOnEnemy = this->PlayerStatusList->pGetPlayerLockOnEnemy();

	/* ロックオン中のエネミーが存在するか */
	if (pLockOnEnemy != nullptr)
	{
		// 存在する場合
		/* クナイ(エフェクト)のターゲット座標をロックオン中のエネミーに設定 */
		this->pBulletKunaiEffect->SetKunaiTargetPosition(pLockOnEnemy->vecGetPosition());
}
	else
	{
		// 存在しない場合
		// クナイ(エフェクト)のターゲット座標をカメラの注視点の先に設定

		/* カメラ座標からカメラの注視点に向かうベクトルを取得 */
		VECTOR vecKunaiTarget = VSub(this->StageStatusList->vecGetCameraTarget(), this->StageStatusList->vecGetCameraPosition());
		
		/* ベクトルを正規化 */
		vecKunaiTarget = VNorm(vecKunaiTarget);

		/* ベクトルを射程距離までスケーリング */
		vecKunaiTarget = VScale(vecKunaiTarget, KUNAI_RANGE);

		/* ターゲット座標の座標ベクトルを取得 */
		vecKunaiTarget = VAdd(this->StageStatusList->vecGetCameraPosition(), vecKunaiTarget);

		// クナイ(エフェクト)にターゲット座標を設定
		this->pBulletKunaiEffect->SetKunaiTargetPosition(vecKunaiTarget);
	}

	/* 初期化を行う */
	this->pBulletKunaiEffect->Initialization();
	
	/* バレットリストに追加 */
	ObjectList->SetBullet(this->pBulletKunaiEffect);

	/* 遠距離攻撃エフェクトを生成 */
	EffectSelfDelete* pProjectileEffect = new EffectSelfDelete();

	/* 遠距離攻撃エフェクトの読み込み */
	pProjectileEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_seath_unseath/FX_seath_unseath")));

	/* 遠距離攻撃エフェクトの初期化 */
	pProjectileEffect->Initialization();

	/* 遠距離攻撃エフェクトの時間を設定 */
	pProjectileEffect->SetDeleteCount(20);

	/* クナイの手の座標を取得 */
	VECTOR vecKunaiHand = MV1GetFramePosition(this->iModelHandle, iKunaiHandFrameNo);

	/* 遠距離攻撃エフェクトの座標を設定 */
	pProjectileEffect->SetPosition(vecKunaiHand);

	/* 遠距離攻撃エフェクトをリストに登録 */
	{
		/* 遠距離攻撃エフェクトをリストに登録 */
		this->ObjectList->SetEffect(pProjectileEffect);
	}

	/* 遠距離攻撃のクールタイムを設定 */
	this->iProjectileCoolTime = PLAYER_PROJECTILE_COLLTIME;

	/* 遠距離攻撃構え状態に戻す */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE);
}
/* 2025.02.14 菊池雅道	遠距離攻撃処理追加 終了 */
/* 2025.02.21 菊池雅道	遠距離攻撃修正			終了 */
/* 2025.02.26 菊池雅道	クールタイム処理追加	終了 */
/* 2025.03.10 菊池雅道	エフェクト処理追加		終了 */
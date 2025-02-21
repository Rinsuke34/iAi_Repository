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

#include "CharacterPlayer.h"

/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */
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

// 近接攻撃(構え)
void CharacterPlayer::Player_Melee_Posture()
{
	/* プレイヤーの現在の攻撃チャージフレームの取得 */
	int iNowAttakChargeFlame = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame();

	/* 2025.01.24 菊池雅道	攻撃処理追加		開始 */
	/* 2025.01.26 駒沢風助	コード修正		開始*/
	/* 2025.01.27 菊池雅道	エフェクト処理追加 開始 */
	/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */
	/* 2025.02.07 菊池雅道	エフェクト処理修正 開始 */
	/* 2025.02.19 菊池雅道	エフェクト処理修正 開始 */

	/* 攻撃入力がされているか確認 */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK) == true)
	{
		// 攻撃チャージフレームが強攻撃の切り替わりに達したら
		if (iNowAttakChargeFlame == PLAYER_CHARGE_TO_STRONG_TIME)
		{
			/* プレイヤーモーションを"居合(溜め)"に変更 */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_CHARGE);

			/* 溜めのエフェクトを刀の位置に生成 */
			this->pChargeEffect = new EffectManualDelete_PlayerFollow_Frame(this->iKatanaFrameNo);

			/* 溜めエフェクトの読み込み */
			this->pChargeEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_charge/FX_charge")));

			/* 溜めエフェクトの座標設定(仮座標) */
			this->pChargeEffect->SetPosition(VAdd(this->vecPosition, VGet(0, 100, 0)));

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
			if (iNowAttakChargeFlame < PLAYER_MELEE_CHARGE_MAX)
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
					pAddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_charge_finish/FX_charge_finish")));

					/* 溜め完了エフェクトの初期化 */
					pAddEffect->Initialization();

					/* 溜め完了エフェクトの時間を設定 */
					pAddEffect->SetDeleteCount(20);

					/* 溜め完了エフェクトをリストに登録 */
					{
						/* 溜め完了エフェクトをリストに登録 */
						this->ObjectList->SetEffect(pAddEffect);
					}

					/* 溜め完了エフェクトの座標設定(仮) */
					pAddEffect->SetPosition(VAdd(this->vecPosition, VGet(0, 100, 0)));

					/* 溜め完了後エフェクトを生成 */
					this->pChargeHoldEffect = new EffectManualDelete_PlayerFollow_Frame(iKatanaFrameNo);
					
					/* 溜め完了後エフェクトの読み込み */
					this->pChargeHoldEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_charge_hold/FX_charge_hold")));
					
					/* 溜め完了後エフェクトの座標設定(仮座標) */
					this->pChargeHoldEffect->SetPosition(VAdd(this->vecPosition, VGet(0, 100, 0)));
					
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
			VECTOR vecMoveDirection = VNorm(VSub(this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraPosition()));

			/* 縦方向には移動しないように設定 */
			vecMoveDirection.y = 0;

			/* 近接攻撃(強)による移動量を設定 */
			this->PlayerStatusList->SetPlayerChargeAttakTargetMove(VScale(vecMoveDirection, fMove));

			/* 攻撃チャージフレームが強攻撃に派生しているか確認 */
			if (iNowAttakChargeFlame >= PLAYER_CHARGE_TO_STRONG_TIME)
			{
				/* カメラモードを"構え(近接攻撃構え)"に変更 */
				this->PlayerStatusList->SetCameraMode(CAMERA_MODE_AIM_MELEE);

				/* プレイヤーの向きをカメラの向きに固定 */
				this->PlayerStatusList->SetPlayerAngleX(this->PlayerStatusList->fGetCameraAngleX());
				
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

		/* 2025.01.24 菊池雅道	攻撃処理追加		終了*/
		/* 2025.01.26 駒沢風助	コード修正		終了*/
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
			/* プレイヤーの状態を"近接攻撃中(強)"に設定 */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_MELEE_STRONG);

			/* プレイヤーのため攻撃用のカウントを初期化 */
			this->PlayerStatusList->SetPlayerChargeAttackCount(0);

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
/* 2025.01.27 菊池雅道	エフェクト処理追加 終了 */
/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */
/* 2025.02.07 菊池雅道	エフェクト処理修正 終了 */
/* 2025.02.19 菊池雅道	エフェクト処理修正 終了 */

// 近接攻撃(弱)
void CharacterPlayer::Player_Melee_Weak()
{
	/* 2025.01.22 菊池雅道	攻撃処理追加		開始 */
	/* 2025.01.26 駒沢風助	コード修正		開始*/
	/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */

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

	/* 2025.01.22 菊池雅道　攻撃処理追加	終了 */
	/* 2025.01.26 駒沢風助	コード修正		終了 */

	/* 近接攻撃(弱)のSEを再生 */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_NIAI);

	/* 未完成なのでとりあえず自由状態に戻す */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
}
/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */


// 近距離攻撃(強)
void CharacterPlayer::Player_Charge_Attack()
{
	/* 2025.01.22 菊池雅道	攻撃処理追加		開始 */
	/* 2025.01.26 駒沢風助	コード修正		開始 */
	/* 2025.02.03 菊池雅道	近距離攻撃(強)後の処理追加	開始 */
	/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */

	/* 溜め攻撃用のカウントを取得 */
	int iChargeAttackCount = this->PlayerStatusList->iGetPlayerChargeAttackCount();

	/* カウントを確認 */
	if (iChargeAttackCount == 0)
	{
		// 0である場合
		// ※モーション遷移直後である場合
		/* プレイヤーのモーションを近接攻撃(強)に変更する */
		this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_STRONG);

		/* 溜め居合攻撃のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_PLAYER_SPIAI);
	}
	else
	{
		// 1以上である場合
		/* 攻撃＆移動処理 */
		// ※ロックオン中のエネミーが存在するかで処理を分岐させる
		{
			/* ロックオン中のエネミーを取得 */
			EnemyBasic* pLockOnEnemy = this->PlayerStatusList->pGetPlayerLockOnEnemy();

			/* 近接攻撃(強)による移動量を取得 */
			VECTOR vecMoveDirection = this->PlayerStatusList->vecGetPlayerChargeAttakTargetMove();

			/* 移動量をfloat型で取得 */
			float fMove = VSize(vecMoveDirection);

			/* ロックオン中のエネミーが存在するか */
			if (pLockOnEnemy != nullptr)
			{
				// 存在する場合
				/* 移動量をプレイヤーの現在位置からロックオン中のエネミーの位置に修正 */
				vecMoveDirection = VSub(pLockOnEnemy->vecGetPosition(), this->vecPosition);

				/* エネミーの位置から追加で移動(突き抜ける感じを出すため) */
				vecMoveDirection = VAdd(vecMoveDirection, VScale(VNorm(vecMoveDirection), 1000.f));
			}

			/* 攻撃＆移動処理に入ってからのカウントを取得 */
			//int iCount	= iChargeAttackCount - 20;
			int iCount = iChargeAttackCount;

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

				/* プレイヤーのモーションを"居合(強)(終了)"に変更 */
				this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_STRONG_END);
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
				/* 居合(強)のエフェクトを生成 */
				EffectSelfDelete* pAddEffect = new EffectSelfDelete();

				/* 居合(強)エフェクトの読み込み */
				pAddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_iai_dash/FX_iai_dash")));

				/* 居合(強)エフェクトの再生時間を設定 */
				pAddEffect->SetDeleteCount(30);

				/* 居合(強)エフェクトの座標設定 */
				pAddEffect->SetPosition(VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT / 2.f, 0)));

				/* 居合(強)エフェクトの回転量設定 */
				pAddEffect->SetRotation(VGet(this->vecRotation.x, this->vecRotation.y, this->vecRotation.z * -1));

				/*居合(強) エフェクトの初期化 */
				pAddEffect->Initialization();

				/* 居合(強)エフェクトをリストに登録 */
				this->ObjectList->SetEffect(pAddEffect);
			}
		}
	}

	// 溜め攻撃後、次の敵を探す処理
	// 仮でプレイヤーのモーションが"居合(強)(終了)"になったタイミングとする
	if(this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
	{
		/* 索敵範囲を設定※値は仮 */
		COLLISION_SQHERE stSearchSqere{ this->vecPosition, PLAYER_SEARCH_RANGE_AFTER_MELEE };

		/* プレイヤーに近いエネミーを取得する */
		NearEnemy stNearEnemy = { nullptr, 0.f };

		/* エネミーリストを取得 */
		auto& EnemyList = ObjectList->GetEnemyList();

		/* 索敵範囲内のエネミーのうち最もプレイヤーに近いエネミーを対象に設定 */
		for (auto* enemy : EnemyList)
		{
			/* 索敵範囲に接触しているか確認 */
			if (enemy->HitCheck(stSearchSqere) == true)
			{
				// 索敵範囲内である場合
				/* コアのワールド座標を取得 */
				VECTOR vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

				/* プレイヤーとの差を求める */
				float fx = vecCoreWord.x - this->vecPosition.x;
				float fy = vecCoreWord.y - this->vecPosition.y;
				float fDistance = (fx * fx) + (fy * fy);

				/* 現在の最もプレイヤーから近いエネミーよりもプレイヤーに近いか確認 */
				if (fDistance < stNearEnemy.fDistance || stNearEnemy.pEnemy == nullptr)
				{
					// 近い場合
					/* プレイヤーから近いエネミーを更新 */
					stNearEnemy.pEnemy = enemy;
					stNearEnemy.fDistance = fDistance;
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
			this->PlayerStatusList->SetCameraAngleX(this->PlayerStatusList->fGetPlayerAngleX());
		}

	}
	/* 溜め攻撃用のカウントを+1する */
	this->PlayerStatusList->SetPlayerChargeAttackCount(iChargeAttackCount + 1);

	/* 2025.01.22 菊池雅道	攻撃処理追加				終了 */
	/* 2025.01.26 駒沢風助	コード修正		終了 */
	/* 2025.02.03 菊池雅道	近距離攻撃(強)後の処理追加	終了 */
	/* 2025.02.05 菊池雅道	ステータス関連修正			終了 */
}

/* 2025.02.12 菊池雅道	遠距離攻撃処理追加 開始 */
// 遠距離攻撃(構え)
void CharacterPlayer::Player_Projectile_Posture()
{
	/* エイム(構え)入力がされているか確認 */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_AIM) == true)
	{
		/* プレイヤーの向きをカメラの向きに固定 */
		this->PlayerStatusList->SetPlayerAngleX(this->PlayerStatusList->fGetCameraAngleX());
		
		/* カメラモードを"構え(クナイ攻撃)"に変更 */
		this->PlayerStatusList->SetCameraMode(CAMERA_MODE_AIM_KUNAI);

		/* 攻撃入力がされた場合 */
		if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK) == true)
		{
			/* プレイヤーの攻撃状態を"遠距離攻撃中"に遷移 */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_PROJECTILE);
		}
		/* ジャンプ入力がされた場合 */
		else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
		{
			// 遠距離攻撃構え状態をキャンセルする
			/* 遠距離攻撃構え状態キャンセルフラグをたてる */
			this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
			
			/* プレイヤー攻撃状態を"自由状態"に設定 */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

		}
		/* ジャンプ中の場合 */
		else if (this->PlayerStatusList->bGetPlayerJumpingFlag() == true)
		{
			/* スローモーション処理を行う(仮) */ 
		}
		/* 回避入力がされた場合 */
		else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE) == true)
		{
			// 遠距離攻撃構え状態をキャンセルする
			/* 遠距離攻撃構え状態キャンセルフラグをたてる */
			this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
			
			/* プレイヤー攻撃状態を"自由状態"に設定 */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
		}
	}
	/* エイム(構え)入力がされていない場合 */
	else 
	{
		/* プレイヤー攻撃状態を"自由状態"に設定 */
		this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
	}
}
/* 2025.02.12 菊池雅道	遠距離攻撃処理追加 終了 */

/* 2025.02.14 菊池雅道	遠距離攻撃処理追加 開始 */
/* 2025.02.21 菊池雅道	遠距離攻撃修正 開始 */
// 遠距離攻撃
void CharacterPlayer::Player_Projectile()
{
	/* プレイヤーの向きをカメラの向きに固定 */
	this->PlayerStatusList->SetPlayerAngleX(this->PlayerStatusList->fGetCameraAngleX());

	/* カメラモードを"構え(クナイ攻撃)"に変更 */
	this->PlayerStatusList->SetCameraMode(CAMERA_MODE_AIM_KUNAI);
	
	/* クナイ(エフェクト)を作成 */
	this->pBulletKunaiEffect = new BulletPlayerKunaiEffect;

	/* クナイ(エフェクト)生成座標を設定 */
	this->pBulletKunaiEffect->SetPosition(VGet(this->vecPosition.x, this->vecPosition.y + PLAYER_HEIGHT / 2, this->vecPosition.z));
	
	/* ロックオン中のエネミーを取得 */
	EnemyBasic* pLockOnEnemy = this->PlayerStatusList->pGetPlayerLockOnEnemy();

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
		VECTOR vecKunaiTarget = VSub(this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraPosition());
		
		/* ベクトルを正規化 */
		vecKunaiTarget = VNorm(vecKunaiTarget);

		/* ベクトルを射程距離までスケーリング */
		vecKunaiTarget = VScale(vecKunaiTarget, KUNAI_RANGE);

		/* ターゲット座標の座標ベクトルを取得 */
		vecKunaiTarget = VAdd(this->PlayerStatusList->vecGetCameraPosition(), vecKunaiTarget);

		// クナイ(エフェクト)にターゲット座標を設定
		this->pBulletKunaiEffect->SetKunaiTargetPosition(vecKunaiTarget);
	}

	/* 初期化を行う */
	this->pBulletKunaiEffect->Initialization();
	
	/* バレットリストに追加 */
	ObjectList->SetBullet(this->pBulletKunaiEffect);

	/* 遠距離攻撃構え状態に戻す */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE);
}
/* 2025.02.14 菊池雅道	遠距離攻撃処理追加 終了 */
/* 2025.02.21 菊池雅道	遠距離攻撃修正 終了 */
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
/* 2025.03.12 菊池雅道	スローモーション処理追加 */
/* 2025.03.18 菊池雅道	エディットによる処理追加 */
/* 2025.03.27 菊池雅道	衝突判定処理修正 */
/* 2025.10.15 菊池雅道	近距離攻撃(強)時の処理修正 */
/* 2025.12.13 菊池雅道	コードリファクタリング */

#include "CharacterPlayer.h"

/* 2025.02.05 菊池雅道	ステータス関連修正			開始 */
/* 2025.03.12 菊池雅道	スローモーション処理追加	開始 */
/* 2025.03.18 菊池雅道	エディットによる処理追加	開始 */
/* 2025.01.09 菊池雅道	移動処理追加				開始 */
/* 2025.01.30 菊池雅道	モーション処理追加			開始 */
/* 2025.02.22 菊池雅道	壁キック処理追加			開始 */
/* 2025.03.08 菊池雅道	移動処理修正				開始 */
/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 移動
void CharacterPlayer::Player_Move()
{
	/* 入力取得 */
	float  fStickTiltMagnitude = InputList->fGetGameInputMove();
	VECTOR vecInput = InputList->vecGetGameInputMoveDirection();
	VECTOR vecAddMove = VGet(0, 0, 0);

	/* プレイヤー状態取得 */
	int iPlayerMoveState = PlayerStatusList->iGetPlayerMoveState();
	int iPlayerAttackState = PlayerStatusList->iGetPlayerAttackState();

	/* 移動制御用パラメータ */
	float fMoveSpeedRatio = 1.f;
	float fEditAddSpeed = PlayerStatusList->fGetAddMoveSpeedUp();
	bool  bPlayerAngleSetFlg = true;
	bool  bPlayerMoveFlg = true;

	/* 状態に応じた移動可否・倍率設定 */
	SetupMoveStateByStatus(iPlayerMoveState,iPlayerAttackState,fMoveSpeedRatio,bPlayerAngleSetFlg,bPlayerMoveFlg);

	/* 移動入力があるか確認 */
	if (bIsMoveInput(vecInput) && bPlayerMoveFlg)
	{
		//移動入力がある場合
		/* 移動量算出 */
		vecAddMove = vecCalculateMove(vecInput, fMoveSpeedRatio, fEditAddSpeed, bPlayerAngleSetFlg);
	}
	else
	{
		// 移動入力が無い場合
		/* 移動しない */
		HandleNoMoveInput();
	}

	/* 壁キックフラグが立っているか確認 */
	if (PlayerStatusList->bGetPlayerKickWallFlg())
	{
		/* 壁キック横移動処理 */
		Player_WallKick_Movement_Horizontal();
	}

	/* 移動量を加算 */
	vecMove = VAdd(vecMove, vecAddMove);
}
/* 2025.02.05 菊池雅道	ステータス関連修正			終了 */
/* 2025.03.12 菊池雅道	スローモーション処理追加	終了 */
/* 2025.01.09 菊池雅道	移動処理追加				終了 */
/* 2025.02.22 菊池雅道	壁キック処理追加			終了 */
/* 2025.03.08 菊池雅道	移動処理修正				終了 */
/* 2025.03.18 菊池雅道	エディットによる処理追加	終了 */
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */
	
/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 移動状態・攻撃状態に応じた移動制御設定
void CharacterPlayer::SetupMoveStateByStatus(int iPlayerMoveState,int iPlayerAttackState,float& fMoveSpeedRatio,bool& bPlayerAngleSetFlg,bool& bPlayerMoveFlg)
{
	/* プレイヤーの移動状態が移動処理を行う状態であるか確認 */
	switch (iPlayerMoveState)
	{
		/* 移動状態による制御 */
		case PLAYER_MOVESTATUS_FREE:				// 自由状態

			/* 移動処理を行う */
			bPlayerMoveFlg = true;
			/* 移動速度補正無しにする */
			fMoveSpeedRatio = 1.f;
			/* プレイヤーの向きを移動方向に合わせる */
			bPlayerAngleSetFlg = true;
			break;

		case PLAYER_MOVESTATUS_EVENT:				// イベント状態(操作不可)
		case PLAYER_MOVESTATUS_DODGING:				// 回避状態中
		case PLYAER_MOVESTATUS_DEAD:				// 死亡状態(操作不可)
	
			// 移動処理を行わない
			bPlayerMoveFlg = false;
			return;
	}

	/* 攻撃状態による制御 */
	switch (iPlayerAttackState)
	{
		/* 移動処理を通常通りに行う状態 */
		case PLAYER_ATTACKSTATUS_FREE:				// 自由状態
		case PLAYER_ATTACKSTATUS_MELEE_WEEK:		// 近接攻撃中(弱)

			/* 移動速度補正無しにする */
			fMoveSpeedRatio = 1.f;

			/* プレイヤーの向きを移動方向に合わせる */
			bPlayerAngleSetFlg = true;
			break;

		/* 移動処理を速度を抑えて行う状態 */
		case PLAYER_ATTACKSTATUS_MELEE_POSTURE:			// 近接攻撃構え中

			/* 移動速度補正0.5倍にする */
			fMoveSpeedRatio = 0.5f;

			/* プレイヤーの向きを移動方向に合わせない */
			bPlayerAngleSetFlg = false;
			break;

		case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:	// 遠距離攻撃構え中
				
		/* スローモーション中であるか確認 */
		if (this->StageStatusList->bGetGameSlowFlg() == true)
		{
			// スローモーション中である場合
			/* 移動速度補正0.1倍にする */
			fMoveSpeedRatio = 0.1f;
		}
		else
		{
			// スローモーション中でない場合
			/* 移動速度補正0.5倍にする */
			fMoveSpeedRatio = 0.5f;
		}
				
		/* プレイヤーの向きを移動方向に合わせない */
		bPlayerAngleSetFlg = false;
		break;

		/* 移動処理を行わない状態 */
		case PLAYER_ATTACKSTATUS_MELEE_STRONG:		// 近接攻撃中(強)
		case PLAYER_ATTACKSTATUS_PROJECTILE:		// 遠距離攻撃中
			
		// 移動処理を行わない
		bPlayerMoveFlg = false;
		break;
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 移動入力判定
bool CharacterPlayer::bIsMoveInput(const VECTOR& vecInput) const
{
	return (vecInput.x != 0 || vecInput.z != 0);
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 移動量算出
VECTOR CharacterPlayer::vecCalculateMove(const VECTOR& vecInput,float fMoveSpeedRatio,float fEditAddSpeed,bool bPlayerAngleSetFlg)
{
	/* 現在速度取得 */
	float fSpeed = this->PlayerStatusList->fGetPlayerNowMoveSpeed();

	/* 移動速度の設定値を取得 */
	float fBaseSpeed = this->PlayerStatusList->fGetPlayerMoveAcceleration();

	/* 最終的な移動速度を計算 */
	fSpeed = (fBaseSpeed + fEditAddSpeed) * fMoveSpeedRatio;

	/* 現在速度を更新 */
	this->PlayerStatusList->SetPlayerNowMoveSpeed(fSpeed);

	/* モーション設定 */
		/* モーションが"ジャンプ(開始)"以外であるか確認 */
	if (PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_JUMP_START)
	{
		// ジャンプ(開始)以外であるなら
		/* モーション設定(歩行) */
		PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_WALK);

		/* プレイヤーの攻撃側モーションが強攻撃(終了)であるか確認 */
		if (PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
		{
			// 強攻撃(終了)であるなら
			/* プレイヤーの攻撃側モーションを"無し"に設定 */
			PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);
		}
	}

	/* カメラの水平方向の向きを移動用の向きに設定 */
	float fAngleX = StageStatusList->fGetCameraAngleX();

	/* 移動量を算出 */
	VECTOR vecAddMove;
	vecAddMove.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
	vecAddMove.y = 0.0f;
	vecAddMove.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
	vecAddMove = VScale(vecAddMove, fSpeed);

		/* プレイヤーの向きを移動方向に合わせるか確認 */
	if (bPlayerAngleSetFlg)
	{
		// 合わせる場合
		/* プレイヤーの向きを移動方向に合わせる */
		AngleIterpolation(vecInput.x, vecInput.z, fAngleX);
	}

	/* 移動量を返す */
	return vecAddMove;
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 移動入力が無い場合の処理
void CharacterPlayer::HandleNoMoveInput()
{
		/* 移動速度を0にする */
	PlayerStatusList->SetPlayerNowMoveSpeed(0);

	/* 強攻撃(終了)中は何もしない */
	if (PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
	{
		return;
	}

	// 着地・死亡・ジャンプ開始・回避中は待機モーションにしない
	int iMotionMove = PlayerStatusList->iGetPlayerMotion_Move();
	int iMoveState = PlayerStatusList->iGetPlayerMoveState();
	bool bIsInvalidState =(iMotionMove == MOTION_ID_MOVE_LAND) ||(iMotionMove == MOTION_ID_MOVE_DIE) ||(iMotionMove == MOTION_ID_MOVE_JUMP_START) ||(iMoveState == PLAYER_MOVESTATUS_DODGING);
	if (!bIsInvalidState)
	{
		PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_WAIT);
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */
			
/* 2025.02.05 菊池雅道	ステータス関連修正			開始 */
/* 2025.02.22 菊池雅道	壁キック処理追加			開始 */
/* 2025.03.18 菊池雅道	エディットによる処理追加	開始 */
// ジャンプ
void CharacterPlayer::Player_Jump()
{
	/* ジャンプ可能状態か確認 */
	if (!bIsJumpableState())
	{
		return;
	}
			
	/* 壁キックの上方向処理(壁キック可能時はジャンプより壁キックを優先するため、ジャンプよりも先に処理する) */
	if (this->PlayerStatusList->bGetPlayerKickWallFlg() == true)
	{
		Player_WallKick_Movement_Vertical();
	}

	/* ジャンプ処理を行う状態でなければ処理を行わない */
	if (!bCanExecuteJump())
	{
		return;
	}

	/* ジャンプ入力がされていない場合は処理を行わない */
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) != true)
	{
		return;
	}
	
	/* 壁キックを行った後かを確認(壁キックとジャンプの重複防止のため) */
	if (this->PlayerStatusList->bGetPlayerAfterKickWallFlg() == true)
	{
		HandleAfterWallKickJumpInput();
		return;
	}

	// 壁キックを行った後かを確認(壁キックとジャンプの重複防止のため)
	if (this->PlayerStatusList->bGetPlayerAfterKickWallFlg() == false)
	{
		// 壁キック後のフラグが有効ではない場合
		/* ジャンプ処理 */
		ExecuteJump();	
	}
	else
	{
		// 壁キック後のフラグが有効な場合
		/* 壁キック後のジャンプ入力処理 */
		HandleAfterWallKickJumpInput();
	}	
}
/* 2025.02.05 菊池雅道	ステータス関連修正			終了 */
/* 2025.02.22 菊池雅道	壁キック処理追加			終了 */
/* 2025.03.18 菊池雅道	エディットによる処理追加	終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// ジャンプ可能状態判定処理
bool CharacterPlayer::bIsJumpableState()
{
	/* プレイヤーの状態を取得 */
	int iPlayerMoveState	= this->PlayerStatusList->iGetPlayerMoveState();
	int iPlayerAttackState	= this->PlayerStatusList->iGetPlayerAttackState();

	/* 移動状態の確認 */
	switch (iPlayerMoveState)
	{
		/* ジャンプ可能な状態 */
		case PLAYER_MOVESTATUS_FREE:				// 自由状態
			return true;
			break;

		/* ジャンプ不可能な状態 */
		case PLAYER_MOVESTATUS_EVENT:				// イベント状態(操作不可)
		case PLAYER_MOVESTATUS_DODGING:				// 回避状態中
		case PLYAER_MOVESTATUS_DEAD:				// 死亡状態(操作不可)
			return false;
			break;
	}

	/* 攻撃状態の確認 */
	switch (iPlayerAttackState)
	{
		/* ジャンプ可能な状態 */
		case PLAYER_ATTACKSTATUS_MELEE_POSTURE:			// 近接攻撃構え中
		case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:	// 遠距離攻撃構え中
		case PLAYER_ATTACKSTATUS_PROJECTILE:			// 遠距離攻撃中
			return true;
			break;

		/* ジャンプ不可能な状態 */
		case PLAYER_ATTACKSTATUS_MELEE_WEEK:		// 近接攻撃中(弱)
		case PLAYER_ATTACKSTATUS_MELEE_STRONG:		// 近接攻撃中(強)
		case PLAYER_ATTACKSTATUS_DEAD:				// 死亡状態(操作不可)
			return false;
			break;
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */
		
/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// ジャンプ実行条件判定処理（回数・クールタイム）
bool CharacterPlayer::bCanExecuteJump()
{
	/* ジャンプのクールタイム確認 */
	if (this->iJumpNowCoolTime > 0)
	{
		return false;
	}
		
	/* 現在のジャンプ回数を取得 */
	int iNowJumpCount = this->PlayerStatusList->iGetPlayerNowJumpCount();
		
	/* エディットによるジャンプ回数加算数を取得 */
	int iEditAddJumpCount = this->PlayerStatusList->iGetAddJumpCount();

	/* 最大ジャンプ回数を取得 */
	int iMaxJumpCount = this->PlayerStatusList->iGetPlayerMaxJumpCount() + iEditAddJumpCount;

	/* ジャンプ回数が最大数を超えていないか確認 */
	if (iNowJumpCount >= iMaxJumpCount)
	{
		return false;
	}
			
	return true;
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 壁キック直後のジャンプ入力処理
void CharacterPlayer::HandleAfterWallKickJumpInput()
{
	/* ジャンプ入力が離されたか確認 */
	if (this->InputList->bGetGameInputAction(INPUT_REL, GAME_JUMP) == false)
	{
		/* 壁キック後フラグを解除 */
		this->PlayerStatusList->SetPlayerAfterKickWallFlg(false);
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// ジャンプ処理
void CharacterPlayer::ExecuteJump()
{
	/* 現在のジャンプ回数を取得 */
	int iNowJumpCount = this->PlayerStatusList->iGetPlayerNowJumpCount();
			
	/* ジャンプ速度を取得 */
	float fJumpSpeed = this->PlayerStatusList->fGetPlayerJumpSpeed();
					
	/* ジャンプ速度を設定（マイナス方向） */
	this->PlayerStatusList->SetPlayerNowFallSpeed(-fJumpSpeed);

	/* ジャンプ回数を更新 */
	this->PlayerStatusList->SetPlayerNowJumpCount(iNowJumpCount + 1);

	/* ジャンプフラグを有効にする */
	this->PlayerStatusList->SetPlayerJumpingFlag(true);

	/* ジャンプSE・ボイス */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_JUMP);
	gpDataList_Sound->VOICE_PlaySound(VOICE_PLAYER_ACTION);
					
	/* 空中ジャンプエフェクト生成 */
	CreateAirJumpEffectIfNeeded();

	/* 強攻撃終了モーション中なら解除 */
	if (this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
	{
		this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);
	}

	/* ジャンプ開始モーション */
	this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_START);

	/* ジャンプクールタイム設定 */
	this->iJumpNowCoolTime = this->PlayerStatusList->iGetPlayerJumpCoolTime();
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 空中ジャンプエフェクト生成処理
void CharacterPlayer::CreateAirJumpEffectIfNeeded()
{
	/* 地面にいない場合のみ生成 */
	if (this->PlayerStatusList->bGetPlayerLandingFlg() == true)
	{						
		return;
	}

	/* 空中ジャンプエフェクトを生成 */
	std::shared_ptr<EffectSelfDelete> pAirJumpEffect = std::make_shared<EffectSelfDelete>();

	/* 空中ジャンプエフェクトの読み込み */
	pAirJumpEffect->SetEffectHandle(this->EffectList->iGetEffect("FX_airjump/FX_airjump"));

	/* 空中ジャンプエフェクトの時間を設定 */
	pAirJumpEffect->SetDeleteCount(30);

	/* 空中ジャンプエフェクトの座標設定 */
	pAirJumpEffect->SetPosition(VGet(this->vecPosition.x, this->vecPosition.y - this->PlayerStatusList->fGetPlayerNowFallSpeed() + PLAYER_HEIGHT, this->vecPosition.z));

	/* 空中ジャンプエフェクトの回転量設定 */
	pAirJumpEffect->SetRotation(this->vecRotation);

	/* 空中ジャンプエフェクトの初期化 */
	pAirJumpEffect->Initialization();
							
	/* 空中ジャンプエフェクトをリストに登録 */
	this->ObjectList->SetEffect(pAirJumpEffect);
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */
						
/* 2025.02.05 菊池雅道	ステータス関連修正			開始 */
/* 2025.03.12 菊池雅道	スローモーション処理追加	開始 */
// 重力処理
void CharacterPlayer::Player_Gravity()
{
	/* 重力処理を行う状態か確認 */
	if (!bIsGravityExecutable())
	{
		return;
	}

	/* 重力処理（落下速度更新）*/
	ApplyGravity();

	/* 重力による移動量を反映 */
	this->vecMove.y -= this->PlayerStatusList->fGetPlayerNowFallSpeed();
}
/* 2025.02.05 菊池雅道	ステータス関連修正			終了 */
/* 2025.03.12 菊池雅道	スローモーション処理追加	終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 重力処理を行う状態判定
bool CharacterPlayer::bIsGravityExecutable()
{
	/* プレイヤーの移動状態を取得 */
	int iPlayerMoveState = this->PlayerStatusList->iGetPlayerMoveState();
	/* プレイヤーの攻撃状態を取得 */
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

	return bGravityFlag;
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 重力処理（落下速度更新）
void CharacterPlayer::ApplyGravity()
{
	/* 現在の落下速度を取得 */
	float fFallSpeed = this->PlayerStatusList->fGetPlayerNowFallSpeed();
		
	/* 加速度を加算 */
	fFallSpeed += this->PlayerStatusList->fGetPlayerFallAcceleration();

	/* 最大落下速度を取得 */
	float fFallSpeedMax = this->PlayerStatusList->fGetPlayerMaxFallSpeed();

	/* 落下速度低下値を取得 */
	int iFallSpeedDown = this->PlayerStatusList->iGetAddFallSpeedDown();

	/* 落下速度低下値が設定されている場合 */
	if (iFallSpeedDown != 0)
	{
		/* 最大落下速度を落下速度低下値に設定 */
		fFallSpeedMax = static_cast<float>(iFallSpeedDown);
	}

	/* 最大落下速度制限 */
	/* 現在の落下速度が最大落下速度を超えているか(下回っているか)確認 */
	if (fFallSpeedMax < fFallSpeed)
	{
		// 超えている場合
		/* 最大落下速度に設定 */
		fFallSpeed = fFallSpeedMax;	
	}

	/* スローモーション中の落下補正 */
	if (this->StageStatusList->bGetGameSlowFlg() == true)
	{
		// スローモーション中の場合
		/* 落下中であれば 加速度を少なくする */
		if (fFallSpeed > 0)
		{
			fFallSpeed = fFallSpeed * 0.5f;
		}
	}

	/* 落下速度を更新 */
	this->PlayerStatusList->SetPlayerNowFallSpeed(fFallSpeed);
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.01.09 菊池雅道	移動処理追加			開始 */
/* 2025.01.26 駒沢風助	コード修正				開始 */
/* 2025.01.27 菊池雅道	エフェクト処理追加		開始 */
/* 2025.02.05 菊池雅道	ステータス関連修正		開始 */
/* 2025.02.06 菊池雅道	エフェクト処理修正		開始 */
/* 2025.02.10 菊池雅道	回避処理修正			開始 */
/* 2025.02.26 菊池雅道	クールタイム処理追加	開始 */
/* 2025.03.04 菊池雅道	回避の処理修正			開始 */
/* 2025.03.11 菊池雅道	回避の処理修正			開始 */
/* 2025.03.17 駒沢風助	画面エフェクト追加		開始 */
// 回避
void CharacterPlayer::Player_Dodge()
{
	/* 回避処理を行う状態か確認 */
	if (!bIsDodgeExecutable())
	{
		return;
	}

	/* 回避状態中の処理 */
	if (this->PlayerStatusList->iGetPlayerMoveState() == PLAYER_MOVESTATUS_DODGING)
	{
		UpdateDodging();
		return;
	}

	/* 回避開始条件を満たしているか確認 */
	if (!bCanStartDodge())
	{
		return;
	}

	/* 回避開始処理 */
	StartDodge();
}
/* 2025.01.09 菊池雅道	移動処理追加			終了 */
/* 2025.01.26 駒沢風助	コード修正				終了 */
/* 2025.01.27 菊池雅道　エフェクト処理追加		終了 */
/* 2025.02.05 菊池雅道	ステータス関連修正		終了 */
/* 2025.02.06 菊池雅道	エフェクト処理修正		終了 */
/* 2025.02.10 菊池雅道	回避処理修正			終了 */
/* 2025.02.26 菊池雅道	クールタイム処理追加	終了 */
/* 2025.03.04 菊池雅道	回避の処理修正			終了 */
/* 2025.03.11 菊池雅道	回避の処理修正			終了 */
/* 2025.03.17 駒沢風助	画面エフェクト追加		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 回避処理を行う状態判定
bool CharacterPlayer::bIsDodgeExecutable()
{
	/* プレイヤーの移動状態を取得 */
	int iPlayerMoveState = this->PlayerStatusList->iGetPlayerMoveState();

	/* プレイヤーが回避処理を行う移動状態であるか確認 */
	// ※攻撃状態は考慮しない
	switch (iPlayerMoveState)
	{
		/* 回避処理を行う状態 */
		case PLAYER_MOVESTATUS_DODGING:			// 回避状態中
		case PLAYER_MOVESTATUS_FREE:			// 自由状態
			return true;

		/* 回避処理を行わない状態 */
		case PLAYER_MOVESTATUS_EVENT:			// イベント状態(操作不可)
		case PLYAER_MOVESTATUS_DEAD:			// 死亡状態(操作不可)
			return false;
	}

	return false;
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 回避中の更新処理
void CharacterPlayer::UpdateDodging()
{
	/* プレイヤーの攻撃状態を取得 */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();
	
	/* 回避状態の最大フレーム数を取得 */
	int iDodgeMaxFrame = this->PlayerStatusList->iGetPlayerMaxDodgeFlame();

		/* 現在の回避状態フレーム数を取得 */
	int iNowDodgeFrame = this->PlayerStatusList->iGetPlayerNowDodgeFlame();

		/* 回避状態が維持される時間を超えていないか確認 */
	if (iNowDodgeFrame <= iDodgeMaxFrame)
	{
		/* 近距離攻撃(強)中は回避を継続しない */
		if (iPlayerAttackState == PLAYER_ATTACKSTATUS_MELEE_STRONG)
		{
			return;
		}

		/* 回避速度を取得 */
		float fPlayerDodgeSpeed = this->PlayerStatusList->fGetPlayerDodgeSpeed();

		/* 経過フレームに応じて減衰 */
		float fSpeedRate = 1.0f - (float)iNowDodgeFrame / (float)iDodgeMaxFrame;

			/* 回避による移動方向を設定し、移動する */
		this->vecMove = VScale(this->PlayerStatusList->vecGetPlayerDodgeDirection(),fPlayerDodgeSpeed * fSpeedRate);

		/* 回避の経過時間を進める */
		this->PlayerStatusList->SetPlayerNowDodgeFlame(iNowDodgeFrame + 1);
				
		return;
	}
			
	/* 回避終了処理 */
	EndDodge();
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */
		
/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 回避開始条件判定
bool CharacterPlayer::bCanStartDodge()
{
	/* 回避入力がされているか確認 */
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE) == false)
	{
		return false;
	}
			
	/* 攻撃状態が近距離攻撃(強)中か確認 */
	if (this->PlayerStatusList->iGetPlayerAttackState() == PLAYER_ATTACKSTATUS_MELEE_STRONG)
	{
		return false;
	}		
					
	/* 空中回避回数制限を確認 */
	if (this->PlayerStatusList->iGetPlayerDodgeWhileJumpingCount() >= PLAYER_DODGE_IN_AIR_LIMIT)
	{
		return false;
	}
		
	/* クールタイム確認 */
	if (this->iDodgeNowCoolTime > 0)			
	{
		return false;
	}
			
	return true;
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 回避終了処理
void CharacterPlayer::EndDodge()
{
	/* プレイヤー状態を"自由状態"に設定 */
	this->PlayerStatusList->SetPlayerMoveState(PLAYER_MOVESTATUS_FREE);

	/* 回避エフェクトを削除 */
	if (this->pDodgeEffect != nullptr)
	{
		this->pDodgeEffect->SetDeleteFlg(true);
		this->pDodgeEffect = nullptr;
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 回避開始処理
void CharacterPlayer::StartDodge()
{
	/* 回避開始フレームをリセット */
	this->PlayerStatusList->SetPlayerNowDodgeFlame(0);
			
	/* 画面エフェクト生成 */
	CreateScreenEffectLine();

	/* 回避方向を設定 */
	SetDodgeDirection();

	/* 落下加速度を初期化 */
	this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);

	/* プレイヤー状態を"回避状態中"に設定 */
	this->PlayerStatusList->SetPlayerMoveState(PLAYER_MOVESTATUS_DODGING);

	/* 回避モーション設定 */
	this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_DODGE);

	/* 着地していない場合,空中での回避回数のカウントを進める */
	if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
	{
		this->PlayerStatusList->SetPlayerDodgeWhileJumpingCount(this->PlayerStatusList->iGetPlayerDodgeWhileJumpingCount() + 1);
	}

	/* 回避SE・ボイス */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_DODGE);
	gpDataList_Sound->VOICE_PlaySound(VOICE_PLAYER_ACTION);

	/* 回避エフェクト生成 */
	CreateDodgeEffect();
				
	/* クールタイム設定 */
	this->iDodgeNowCoolTime =
	this->PlayerStatusList->iGetPlayerDodgeCoolTime();
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 回避方向設定処理
void CharacterPlayer::SetDodgeDirection()
{
	/* 入力による移動量を取得 */				
	VECTOR vecInput = this->InputList->vecGetGameInputMoveDirection();
				
	/* カメラの水平方向の向きを移動用の向きに設定 */				
	float fAngleX = this->StageStatusList->fGetCameraAngleX();
				
	/* 回避方向ベクトル */				
	VECTOR vecDodgeMove;
							
	/* スティック入力がされているか確認 */				
	if (vecInput.x != 0 || vecInput.z != 0)				
	{
		// スティック入力がされている場合					
		/* スティック入力による回避方向を設定 */					
		vecDodgeMove.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
		vecDodgeMove.y = 0.0f;
		vecDodgeMove.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
	}			
	else
	{			
		// スティック入力がされていない場合					
		//プレイヤーが向いている方向に回避する					
		/* プレイヤーモデルの初期の向きがZ軸に対してマイナス方向を向いているとする */					
		vecDodgeMove = { 0,0,-1 };
		MATRIX matPlayerRotation = MGetRotY(-(this->PlayerStatusList->fGetPlayerAngleX()));
		vecDodgeMove = VTransform(vecDodgeMove, matPlayerRotation);
	}

	/* 回避方向を正規化して設定 */
	this->PlayerStatusList->SetPlayerDodgeDirection(VNorm(vecDodgeMove));
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */
						
/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 回避エフェクト生成
void CharacterPlayer::CreateDodgeEffect()
{
	this->pDodgeEffect = std::make_shared<EffectManualDelete_PlayerFollow>(true);
	this->pDodgeEffect->SetEffectHandle(this->EffectList->iGetEffect("FX_dash/FX_dash"));
	this->pDodgeEffect->SetRotation(VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));
	this->pDodgeEffect->Initialization();
	this->ObjectList->SetEffect(this->pDodgeEffect);
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 画面エフェクト(集中線)作成
void CharacterPlayer::CreateScreenEffectLine()
{
	std::shared_ptr<ScreenEffect_Base> pScreenEffect = std::make_shared<ScreenEffect_ConcentrationLine>();
	this->StageStatusList->SetScreenEffect(pScreenEffect);
	pScreenEffect->SetDeleteTime(this->PlayerStatusList->iGetPlayerMaxDodgeFlame());
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.01.09 菊池雅道　移動処理追加					追加 */
/* 2025.01.27 菊池雅道	エフェクト処理追加				開始 */
/* 2025.02.05 菊池雅道	ステータス関連修正				開始 */
/* 2025.02.26 菊池雅道	近距離攻撃(強)関連の処理追加	開始 */
/* 2025.03.10 駒沢風助	移動床実装						開始 */
/* 2025.03.11 菊池雅道	モーション関連の処理追加		開始 */
/* 2025.03.18 駒沢風助	移動床ガタガタ対策				開始 */
/* 2025.10.15 菊池雅道	近距離攻撃(強)時の処理修正		開始 */
// 移動処理(垂直方向)
void CharacterPlayer::Movement_Vertical()
{
	/* 移動後の座標を取得(垂直方向) */
	VECTOR vecNextPosition = vecGetNextVerticalPosition();

	/* 垂直方向の線分コリジョンを作成 */
	SetupVerticalCollisionLine();

	/* 着地座標(初期値は移動後座標) */
	float fStandPosY = vecNextPosition.y;

	/* 現在のジャンプフラグを保持 */
	bool bJumpingFlg = this->PlayerStatusList->bGetPlayerJumpingFlag();

	/* プレイヤーの着地フラグを無効にする */
	this->PlayerStatusList->SetPlayerLanding(false);

	/* 足場判定と着地処理 */
	ResolveVerticalPlatformCollision(vecNextPosition, fStandPosY);

	/* 着地時のSE・エフェクト処理 */
	HandleLandingEvent(bJumpingFlg);

	/* 着地座標を反映 */
	vecNextPosition.y = fStandPosY;
	vecPosition = vecNextPosition;

	/* 空中モーション更新 */
	UpdateAirMotion();
}
/* 2025.01.09 菊池雅道　移動処理追加					終了 */
/* 2025.01.27 菊池雅道	エフェクト処理追加				終了 */
/* 2025.02.05 菊池雅道	ステータス関連修正				終了 */
/* 2025.02.26 菊池雅道	近距離攻撃(強)関連の処理追加	終了 */
/* 2025.03.10 駒沢風助	移動床実装						終了 */
/* 2025.03.11 菊池雅道	モーション関連の処理追加		終了 */
/* 2025.03.18 駒沢風助	移動床ガタガタ対策				終了 */
/* 2025.10.15 菊池雅道	近距離攻撃(強)時の処理修正		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 移動後の座標取得(垂直方向)
VECTOR CharacterPlayer::vecGetNextVerticalPosition() const
{
	VECTOR vecNextPosition;
	vecNextPosition.x = vecPosition.x;
	vecNextPosition.y = vecPosition.y + vecMove.y;
	vecNextPosition.z = vecPosition.z;
	return vecNextPosition;
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 垂直方向の線分コリジョン設定
void CharacterPlayer::SetupVerticalCollisionLine()
{
	this->stVerticalCollision.vecLineStart = this->vecPosition;
	this->stVerticalCollision.vecLineStart.y += PLAYER_HEIGHT;
	this->stVerticalCollision.vecLineEnd = stVerticalCollision.vecLineStart;
	this->stVerticalCollision.vecLineEnd.y -= 9999;
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 垂直方向の足場判定と着地処理
void CharacterPlayer::ResolveVerticalPlatformCollision(VECTOR& vecNextPosition, float& fStandPosY)
{
	/* 足場を取得 */
	auto& PlatformList = ObjectList->GetPlatformList();

	/* 近距離攻撃(強)中かつ敵にロックオンしているか確認 */
	bool bIsMeleeStrong = (this->PlayerStatusList->iGetPlayerAttackState() == PLAYER_ATTACKSTATUS_MELEE_STRONG);
	bool bIsLockOnEnemy = (this->PlayerStatusList->pGetPlayerLockOnEnemy() != nullptr);
	bool bIsMeleeStrongToLockOnEnemy = (bIsMeleeStrong && bIsLockOnEnemy);

	/* 足場と接触するか確認 */
	for (auto& platform : PlatformList)
	{
		/* 足場と線分の接触判定 */
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stVerticalCollision);

		/* 接触しているか確認 */
		if (stHitPolyDim.HitFlag != 1)
		{
			// 接触していない場合
			/* 次のプラットフォームを確認*/
			continue;
		}
			
		/* 接触位置が現在の立ち位置より下か確認 */
		// ※判定値は少し余裕を持たせる(移動床に搭乗中に床から離れないようにするため)
		if (stHitPolyDim.HitPosition.y < fStandPosY + PLAYER_PLATFORM_RAND_CORRECTION)
		{
			// 現在の着地座標より低い位置である場合
			/* 次のプラットフォームを確認*/
			continue;
		}

		/* 落下加速度リセット */
		this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);

		/* ヒットした座標がプレイヤーが歩いて登れる位置より低い位置であるか確認　※近距離攻撃(強)中かつ敵にロックオンしている場合は、特別な設定値を使用 */
		float fClimbHeight = bIsMeleeStrongToLockOnEnemy ? PLAYER_CLIMBED_HEIGHT_STRONG_MELEE : PLAYER_CLIMBED_HEIGHT;
		if (fStandPosY < vecPosition.y + fClimbHeight)
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
			vecNextPosition = VAdd(vecPosition, platform->vecGetPlatformMove());

			/* プレイヤーのスローモーションカウントをリセット */
			this->PlayerStatusList->SetPlayerSlowMotionCount(0);

			/* 対象のプラットフォームをプレイヤーが乗っている状態にする */
			platform->SetRidePlayerFlg(true);
		}
		else
		{
			// 着地座標がプレイヤーの現在位置より高い場合
			/* 着地座標をプレイヤーが天井にめり込まない高さに更新 */
			fStandPosY = stHitPolyDim.HitPosition.y - PLAYER_HEIGHT - PLAYER_CLIMBED_HEIGHT;

			/* 対象のプラットフォームをプレイヤーが乗っていない状態にする */
			platform->SetRidePlayerFlg(false);

			/* ループを抜ける */
			break;
		}
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */
		
/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 着地時のSE・エフェクト処理
void CharacterPlayer::HandleLandingEvent(bool bPrevJumpingFlg)
{
	/* 着地フラグが無効→有効になったタイミングで処理を行う */
	if (bPrevJumpingFlg == false)
	{
		return;
	}
	if (PlayerStatusList->bGetPlayerJumpingFlag() == true)
	{
		return;
	}

	/* 回避中はSEとエフェクトを出さない */
	if (PlayerStatusList->iGetPlayerMoveState() == PLAYER_MOVESTATUS_DODGING)
		{
		return;
	}

	/* 着地SE */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_LANDING);
		
	/* 着地エフェクト */
	std::shared_ptr<EffectSelfDelete> pAddEffect = std::make_shared<EffectSelfDelete>();
	pAddEffect->SetEffectHandle(EffectList->iGetEffect("FX_land/FX_land"));
	pAddEffect->SetDeleteCount(PLAYER_LAND_EFFECT_FRAME);
	pAddEffect->SetPosition(vecPosition);
	pAddEffect->SetRotation(vecRotation);
	pAddEffect->Initialization();
	ObjectList->SetEffect(pAddEffect);

	/* 着地モーション */
	PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_LAND);
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
// 空中モーション更新
void CharacterPlayer::UpdateAirMotion()
{
	/* 着地している場合は何もしない */
	if (PlayerStatusList->bGetPlayerLandingFlg())
	{
		return;
	}
		
	/* 回避中はモーションを変えない */
	if (PlayerStatusList->iGetPlayerMoveState() == PLAYER_MOVESTATUS_DODGING)
	{
		return;		
	}
			
	/* 上昇しているか確認 */
	if (PlayerStatusList->fGetPlayerNowFallSpeed() < 0)
	{
		// 上昇している場合
		// 攻撃モーションが投げ(準備)の場合は何もしない
		if (PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_THROW_READY)
		{
			return; 
		}
		
			// 移動モーションがジャンプ(開始)の場合は何もしない
		if (PlayerStatusList->iGetPlayerMotion_Move() == MOTION_ID_MOVE_JUMP_START)
		{
			return;
		}
		
		/* モーションを"ジャンプ(上昇)"に設定 */
		PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_UP);
	}
	else
	{
		// 下降している場合
		/* プレイヤーがジャンプ中の場合 */
		if (PlayerStatusList->bGetPlayerJumpingFlag())
		{
			/* モーションを"ジャンプ(下降)"に設定 */
			PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_DOWN);
		}
		/* 落下状態になってからのフレーム数が一定数を超えている場合 */
		else if (iFallingFrame > PLAYER_JUNP_DOWN_MOTION_SWITCH_FRAME)
			{
				/* モーションを"ジャンプ(下降)"に設定 */
			PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_DOWN);
		}

		/* 落下状態になってからのフレーム数を加算 */
		iFallingFrame++;
	}					
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.02.07 菊池雅道	衝突判定処理修正	開始 */
/* 2025.02.22 菊池雅道	壁キック処理追加	開始 */
/* 2025.03.05 菊池雅道	衝突判定処理修正	開始 */
/* 2025.03.27 菊池雅道	衝突判定処理修正	開始 */
// 移動処理(水平方向)
void CharacterPlayer::Movement_Horizontal()
{
	/* 移動後の座標を取得(水平方向) */
	VECTOR vecNextPosition = vecGetNextHorizontalPosition();

	/* 1フレームでの移動量を分割して判定する回数 */
	/* ※移動量に応じて分割を設定する */
	int iMoveHitCheckCount = (int)VSize(VGet(this->vecMove.x, 0, this->vecMove.z));
	
	/* 分割した移動量 */
	// ※元コードの挙動差を避けるため計算は残す(実質未使用)
	VECTOR vecDevisionMove = VScale(this->vecMove, 1.0f / iMoveHitCheckCount);

	/* 分割して移動した先の座標 */
	// ※元コードの挙動差を避けるため変数は残す(実質未使用)
	VECTOR vecDevisionMovePosition = this->vecPosition;

	/* 現在位置から移動後座標へ向けたカプセルコリジョンを作成 */
	SetupHorizontalMoveCollision(vecNextPosition);

	/* 法線ベクトル取得用のカプセルコリジョン */
	COLLISION_CAPSULE stNormalCollision = stCreateNormalCollision();

	/* 足場を取得 */
	auto& PlatformList = ObjectList->GetPlatformList();

	/* プレイヤーの接触する法線ベクトル合計 */
	VECTOR vecNormalSum = VGet(0.f, 0.f, 0.f);

	/* 足場と接触するか確認 */
	ResolveHorizontalPlatformCollision(PlatformList, stNormalCollision, vecNormalSum, vecNextPosition);

	/* 壁との接触フラグを取得 */
	bool bWallTouch = this->PlayerStatusList->bGetPlayerWallTouchFlg();

	/* 壁と接触していた場合、条件を満たしたら壁キックを行う */
	if (bWallTouch == true)
	{
		JudgeWallKickTime();
	}

	/* プレイヤーの座標を移動させる */
	this->vecPosition = vecNextPosition;
}
/* 2025.02.07 菊池雅道	衝突判定処理修正	終了 */
/* 2025.02.22 菊池雅道	壁キック処理追加	終了 */
/* 2025.03.05 菊池雅道	衝突判定処理修正	終了 */
/* 2025.03.27 菊池雅道	衝突判定処理修正	終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
/* 移動後の座標を取得(水平方向) */
VECTOR CharacterPlayer::vecGetNextHorizontalPosition() const
{
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x + this->vecMove.x;
	vecNextPosition.y = this->vecPosition.y;
	vecNextPosition.z = this->vecPosition.z + this->vecMove.z;
	return vecNextPosition;
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
/* 現在位置から移動後座標へ向けたカプセルコリジョンを作成(水平方向) */
void CharacterPlayer::SetupHorizontalMoveCollision(const VECTOR& vecNextPosition)
{
	// ※ 元の位置から移動後の位置へ向けたカプセルコリジョンを作成
	this->stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].vecCapsuleBottom =VAdd(this->vecPosition, VGet(0.f, PLAYER_HEIGHT - PLAYER_WIDE, 0.f));
	this->stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].vecCapsuleTop =VAdd(vecNextPosition, VGet(0.f, PLAYER_HEIGHT - PLAYER_WIDE, 0.f));
	this->stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].fCapsuleRadius = PLAYER_WIDE;

	this->stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].vecCapsuleBottom =VAdd(this->vecPosition, VGet(0.f, PLAYER_WIDE + PLAYER_CLIMBED_HEIGHT, 0.f));
	this->stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].vecCapsuleTop =VAdd(vecNextPosition, VGet(0.f, PLAYER_WIDE + PLAYER_CLIMBED_HEIGHT, 0.f));
	this->stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].fCapsuleRadius = PLAYER_WIDE;
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */
		
/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
/* 壁キック入力猶予内であれば壁キック可能にする */
void CharacterPlayer::JudgeWallKickTime()
{
	/* 壁に接触してからの経過フレーム数を取得 */
	int iNowAfterWallTouchCount = this->PlayerStatusList->iGetPlayerAfterWallTouchCount();

	/* 壁に接触してからの経過フレーム数を加算 */
	this->PlayerStatusList->SetPlayerAfterWallTouchCount(iNowAfterWallTouchCount + 1);

	/* 壁キックの入力猶予フレーム数を取得 */
	int iWallKickInputMaxFlame = this->PlayerStatusList->iGetPlayerKickWallInputMaxFlame();

	/* 壁に接触してからの経過フレーム数が一定値以下か確認する */
	if (iNowAfterWallTouchCount <= iWallKickInputMaxFlame)
	{
		//壁に接触してからの経過フレーム数が一定値以下の場合
		/* 壁キック入力処理を行う */
		HandleWallKickInput();
	}
	else
	{
		//壁に接触してからの経過フレーム数が一定値以上の場合
		/* 壁との接触フラグを解除する */
		this->PlayerStatusList->SetPlayerWallTouchFlg(false);

		/* 壁に接触してからの経過フレーム数をリセット */
		this->PlayerStatusList->SetPlayerAfterWallTouchCount(0);
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
/* 法線ベクトル取得用のカプセルコリジョンを作成 */
COLLISION_CAPSULE CharacterPlayer::stCreateNormalCollision() const
{
	COLLISION_CAPSULE stNormalCollision;

	/* 法線ベクトル取得用のカプセルコリジョンは移動前のプレイヤーの位置に作成 */
	stNormalCollision.vecCapsuleTop = VAdd(this->vecPosition, VGet(0.f, PLAYER_HEIGHT - PLAYER_WIDE, 0.f));
	stNormalCollision.vecCapsuleBottom = VAdd(this->vecPosition, VGet(0.f, PLAYER_WIDE + PLAYER_CLIMBED_HEIGHT, 0.f));

	/* プラットフォームに接触するように半径はプレイヤーより大きめにとる */
	stNormalCollision.fCapsuleRadius = PLAYER_WIDE + 10.0f;

	return stNormalCollision;
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */
	
/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
/* 足場との接触処理(水平方向) */
void CharacterPlayer::ResolveHorizontalPlatformCollision(const std::vector<std::shared_ptr<PlatformBase>>& PlatformList,const COLLISION_CAPSULE& stNormalCollision,VECTOR& vecNormalSum,VECTOR& vecNextPosition)
{
	/* 足場と接触するか確認 */
	for (auto& platform : PlatformList)
	{
		/* 足場との接触判定 */
		for (int i = 0; i < PLAYER_MOVE_COLLISION_MAX; i++)
		{
			/* 移動時にプラットフォームに接触しているか確認 */
			MV1_COLL_RESULT_POLY_DIM stHitPolyDim = platform->HitCheck_Capsule(this->stHorizontalCollision[i]);

			/* プラットフォームの法線ベクトルを取得する */
			MV1_COLL_RESULT_POLY_DIM stHitPolyDimNormal = platform->HitCheck_Capsule(stNormalCollision);

			/* 接触しているか確認 */
			if (stHitPolyDim.HitNum > 0)
			{
				// 1つ以上のポリゴンが接触している場合

				/* 壁キック中に壁にぶつかったら止まるようにする */
				HandleKickWallStopOnHit();

				// 押し出し処理用の法線ベクトル
				/* 接触したポリゴンから法線ベクトルを取得し加算する */
				AddNormalSumForPushOut(stHitPolyDimNormal, vecNormalSum);

				// 壁キック用の法線ベクトル
				/* 接触したポリゴンから法線ベクトルを取得し加算する */
				AddNormalSumForWallKick(stHitPolyDim);

				/* 取得した法線ベクトルを正規化 */
				// ※ 取得した法線ベクトルの平均を取得
				vecWallKickNormalSum = VNorm(vecWallKickNormalSum);

				/* 壁の接触フラグを設定 */
				this->PlayerStatusList->SetPlayerWallTouchFlg(true);

				/* 壁に接触してからの経過フレーム数をリセット */
				this->PlayerStatusList->SetPlayerAfterWallTouchCount(0);

				/* 法線の方向にプレイヤーを押し出す */
				PushOutPlayerByNormal(platform, vecNormalSum, vecNextPosition);

				// 球体コリジョンと衝突があった場合、分割移動処理を終了する
				if (stHitPolyDim.HitNum > 0)
				{
					break;
				}
			}
		}
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
/* 壁キック中に壁にぶつかった場合の停止処理 */
void CharacterPlayer::HandleKickWallStopOnHit()
{
	/* 壁キックフラグが有効が確認 */
	if (this->PlayerStatusList->bGetPlayerKickWallFlg() == true)
	{
		/* 壁キックフラグを解除 */
		this->PlayerStatusList->SetPlayerKickWallFlg(false);
						
		/* 経過フレーム数をリセット */
		this->PlayerStatusList->SetPlayerAfterKickWallCount(0);
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
/* 押し出し処理用の法線ベクトルを加算 */
void CharacterPlayer::AddNormalSumForPushOut(MV1_COLL_RESULT_POLY_DIM& stHitPolyDimNormal,VECTOR& vecNormalSum)
{
	for (int j = 0; j < stHitPolyDimNormal.HitNum; j++)
	{
		/* 法線ベクトルが0であるならば、加算しない */
		if (VSize(stHitPolyDimNormal.Dim[j].Normal) > 0.f)
		{
			/* 法線ベクトルのY軸を初期化 */
			stHitPolyDimNormal.Dim[j].Normal.y = 0.f;

			/* 法線ベクトルを正規化 */
			VECTOR vecNormal = VNorm(stHitPolyDimNormal.Dim[j].Normal);

			/* 法線ベクトルを合計に加算 */
			vecNormalSum = VAdd(vecNormalSum, vecNormal);
		}
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
/* 壁キック用の法線ベクトルを加算 */
void CharacterPlayer::AddNormalSumForWallKick(MV1_COLL_RESULT_POLY_DIM& stHitPolyDim)
{
	for (int j = 0; j < stHitPolyDim.HitNum; j++)
	{
		/* 法線ベクトルが0であるならば、加算しない */
		if (VSize(stHitPolyDim.Dim[j].Normal) > 0.f)
		{
			/* 法線ベクトルのY軸を初期化 */
			stHitPolyDim.Dim[j].Normal.y = 0.f;

			/* 法線ベクトルを正規化 */
			VECTOR vecNormal = VNorm(stHitPolyDim.Dim[j].Normal);

			/* 法線ベクトルを合計に加算 */
			vecWallKickNormalSum = VAdd(vecWallKickNormalSum, vecNormal);
		}
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
/* 壁キック入力猶予内の処理 */
void CharacterPlayer::HandleWallKickInput()
{
	/* スティックの入力を取得 */
	VECTOR vecInput = this->InputList->vecGetGameInputMoveDirection();

	/* スティック入力方向を求める */
	float fMoveAngle = atan2f(vecInput.x, vecInput.z);

	/* カメラの水平方向の向きを取得 */
	float fAngleX = this->StageStatusList->fGetCameraAngleX();

	/* カメラの水平方向の向きが一周の範囲(0~2π)を超えた場合、補正を行う */
	this->RadianLimitAdjustment(fAngleX);

	/* 補正したカメラ角度を設定 */
	this->StageStatusList->SetCameraAngleX(fAngleX);

	/* 入力方向とカメラの向きを合成し移動方向とする */
	fMoveAngle = fAngleX - fMoveAngle;

	/* スティック入力方向 */
	VECTOR vecInputDerection = VGet(0.0f, 0.0f, 0.0f);

	/* スティック入力に方向を設定 */
	vecInputDerection.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
	vecInputDerection.y = 0.0f;
	vecInputDerection.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);

	/* 壁の法線ベクトルとスティック入力方向の内積を求める */
	float fWallInputDot = VDot(vecWallKickNormalSum, vecInputDerection);

	/* 壁の法線ベクトルとスティック入力方向の内積が正(同じ向き)か確認する */
	if (fWallInputDot > 0)
	{
		/* ジャンプボタンを押したか確認する */
		if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
		{
			/* 壁キックフラグを有効にする */
			this->PlayerStatusList->SetPlayerKickWallFlg(true);
					
			/* 壁との接触フラグを解除する */
			this->PlayerStatusList->SetPlayerWallTouchFlg(false);

			/* 壁に接触してからの経過フレーム数をリセット */
			this->PlayerStatusList->SetPlayerAfterWallTouchCount(0);
		}
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング		開始 */
/* 法線の方向にプレイヤーを押し出す */
void CharacterPlayer::PushOutPlayerByNormal(const std::shared_ptr<PlatformBase>& platform,const VECTOR& vecNormalSum,VECTOR& vecNextPosition)
{
	/* プレイヤー座標に球体ポリゴンを作成 */
	COLLISION_SQHERE stSphere;
	stSphere.vecSqhere = this->vecPosition;
	stSphere.vecSqhere.y = stSphere.vecSqhere.y + PLAYER_HEIGHT / 2;
	stSphere.fSqhereRadius = PLAYER_WIDE;
		
	/* 対象のコリジョンと接触しなくなるまで押し出す */
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
	vecNextPosition.y = this->vecPosition.y;
}
/* 2025.12.13 菊池雅道	コードリファクタリング		終了 */

/* 2025.02.10 菊池雅道	振り向き処理修正 開始 */
/* 2025.03.14 菊池雅道	振り向き処理修正 開始 */
// 向き変化時の補間
void CharacterPlayer::AngleIterpolation(float vecInputX, float vecInputZ, float& fAngleX)
{
	/* プレイヤーの向きを移動方向に合わせる */
	/* 入力方向を取得 */
	float fMoveAngle = atan2f(vecInputX,vecInputZ);

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
}
/* 2025.02.10 菊池雅道	振り向き処理修正 終了 */
/* 2025.03.14 菊池雅道	振り向き処理修正 終了 */

// 壁キック後の垂直移動処理
void CharacterPlayer::Player_WallKick_Movement_Vertical()
{
	/* 壁キック後の経過フレーム数が0の場合 */
	if (this->PlayerStatusList->iGetPlayerAfterKickWallCount() == 0)
	{
		/* 壁キックの移動速度(垂直成分)を取得 */
		float fKickWallVerticalSpeed = this->PlayerStatusList->fGetPlayerKickWallVerticalSpeed();

		/*上方向に移動 */
		this->PlayerStatusList->SetPlayerNowFallSpeed(-fKickWallVerticalSpeed);

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

/* 2025.02.22 菊池雅道	壁キック処理追加	開始 */
// 壁キック後の横移動処理
void CharacterPlayer::Player_WallKick_Movement_Horizontal()
{
	/* 壁キックしてからの経過フレーム数を取得 */
	int iNowAfterKickWallFlame = this->PlayerStatusList->iGetPlayerAfterKickWallCount();

	/* 壁キックの横移動速度を取得 */
	float fKickWallHorizontalSpeed = this->PlayerStatusList->fGetPlayerKickWallHorizontalSpeed();

	/* 壁キック継続フレーム数を取得 */
	int iKickWallFlame = this->PlayerStatusList->iGetPlayerKickWallFlame();

	/* 経過フレーム数を確認 */
	if (iNowAfterKickWallFlame <= iKickWallFlame)
	{
		// 経過フレーム数が設定フレーム数を超えていない場合
		/* 壁キックの横移動速度を設定 */
		/* 経過フレーム数に応じて、速度が減衰する(1.0fを最大として減衰していく) */
		float fKickWallSpeed = fKickWallHorizontalSpeed * (1.0f - (float)(iNowAfterKickWallFlame / iKickWallFlame));

		/* 壁の法線方向(水平成分のみ)へ移動する */
		this->vecMove.x += vecWallKickNormalSum.x * fKickWallSpeed;
		this->vecMove.z += vecWallKickNormalSum.z * fKickWallSpeed;

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
/* 2025.02.22 菊池雅道	壁キック処理追加	終了 */
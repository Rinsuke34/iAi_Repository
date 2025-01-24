/* 2024.12.15 駒沢風助 ファイル作成 */

#include "CharacterPlayer.h"

/* プレイヤークラスの定義 */
VECTOR vecTest;
// コンストラクタ
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* 初期化 */
	/* データリスト取得 */
	this->InputList = dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

	this->vecMove				= VGet(0.f, 0.f, 0.f);	// 移動量
	this->vecMove				= {};					// 移動量
	this->stVerticalCollision	= {};					// 垂直方向のコリジョン
	this->vecLandingPos			= VGet(0.f, 0.f, 0.f);	// 垂直方向のコリジョンが地面に着地する位置
	this->stHorizontalCollision	= {};					// 水平方向コリジョン
}

// 初期化
void CharacterPlayer::Initialization()
{
	CharacterBase::Initialization();

	/* コリジョンを更新 */
	CollisionUpdate();
}

// 更新
void CharacterPlayer::Update()
{
	/* 接触確認 */
	{
		// ※攻撃やオブジェクトに対する当たり判定処理を行う
	}

	/* 移動量をリセット */
	this->vecMove = VGet(0, 0, 0);		// 移動量

	/* 攻撃系アクション処理 */
	{
		/* 攻撃状態遷移管理 */
		// ※プレイヤーの入力に応じて攻撃状態を遷移
		Player_Attack_Transition();
	}

	/* 上下方向(Y軸)移動処理 */
	{
		/* ジャンプ処理 */
		Player_Jump();

		/* 重力処理 */
		Player_Gravity();

		/* 移動処理(垂直方向) */
		Movement_Vertical();
	}

	/* 平行方向(X軸)移動処理 */
	{
		/* 移動処理 */
		Player_Move();

		/* 回避処理 */
		Player_Dodg();

		/* 移動処理(水平方向) */
		Movement_Horizontal();
	}

	/* コリジョンを更新 */
	CollisionUpdate();
}

// 描写
void CharacterPlayer::Draw()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転 */
	MV1SetRotationXYZ(this->iModelHandle, VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);

	/* テスト用描写 */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_JUMP) == true)
	{
		DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "JUMP");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK) == true)
	{
		DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "ATTACK");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_AIM) == true)
	{
		DrawFormatString(500, 16 * 2, GetColor(255, 255, 255), "AIM");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_RESET) == true)
	{
		DrawFormatString(500, 16 * 3, GetColor(255, 255, 255), "RESET");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_DODGE) == true)
	{
		DrawFormatString(500, 16 * 4, GetColor(255, 255, 255), "DODGE");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_FORWARD) == true)
	{
		DrawFormatString(500, 16 * 5, GetColor(255, 255, 255), "FORWARD");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_BACK) == true)
	{
		DrawFormatString(500, 16 * 6, GetColor(255, 255, 255), "BACK");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_LEFT) == true)
	{
		DrawFormatString(500, 16 * 7, GetColor(255, 255, 255), "LEFT");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_RIGHT) == true)
	{
		DrawFormatString(500, 16 * 8, GetColor(255, 255, 255), "RIGHT");
	}

	XINPUT_STATE stXInputState;
	GetJoypadXInputState(DX_INPUT_PAD1, &stXInputState);

	DrawFormatString(500, 16 * 10, GetColor(255, 255, 255), "左トリガ : %u", stXInputState.LeftTrigger);
	DrawFormatString(500, 16 * 11, GetColor(255, 255, 255), "右トリガ : %u", stXInputState.RightTrigger);

	float fSpeed = this->PlayerStatusList->fGetPlayerNowMoveSpeed();
	DrawFormatString(500, 16 * 12, GetColor(255, 255, 255), "移動速度 : %f", fSpeed);
	
	DrawFormatString(500, 16 * 14, GetColor(255, 255, 255), "フレーム数 : %d", this->PlayerStatusList->iPlayerNowAttakChargeFlame);

	DrawFormatString(500, 16 * 16, GetColor(255, 255, 255), "X : %f Y : %f Z : %f", vecTest.x, vecTest.y, vecTest.z);

	DrawSphere3D(vecTest, 80.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
}

// 当たり判定描写
void CharacterPlayer::CollisionDraw()
{
	CharacterBase::CollisionDraw();

	/* 垂直方向のコリジョン */
	int iColor	= GetColor(0, 255, 0);
	DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, iColor);
	DrawSphere3D(this->vecLandingPos, 10.f, 16, iColor, iColor, FALSE);

	/* 並行方向のコリジョン */
	iColor	= GetColor(0, 0, 255);
	DrawCapsule3D(this->stHorizontalCollision.vecCapsuleTop, this->stHorizontalCollision.vecCapsuleBottom, this->stHorizontalCollision.fCapsuleRadius, 16, iColor, iColor, FALSE);
}

// 移動
void CharacterPlayer::Player_Move()
{
	/* プレイヤー移動量取得 */
	float fStickTiltMagnitude	= this->InputList->fGetGameInputMove();				// スティックを倒した強さ
	VECTOR vecInput				= this->InputList->vecGetGameInputMoveDirection();	// 移動方向
	VECTOR vecAddMove			= VGet(0, 0, 0);									// 移動量(加算用)

	/* 移動入力がされているか確認 */
	if (vecInput.x != 0 || vecInput.z != 0)
	{
		// 移動入力がされている場合
		/* 現在の移動速度取得 */
		float fSpeed	= this->PlayerStatusList->fGetPlayerNowMoveSpeed();

		/* 最大速度を超えていないか確認 */
		if (this->PlayerStatusList->bGetPlayerAfterDodgeFlag() == true)
		{
			fSpeed = PLAER_DASH_MAX_SPEED;
		}

		// スティックの倒し具合で速度を変化
		else if (fStickTiltMagnitude > STICK_TILT_PLAER_DASH) 
		{
			//走り（通常）
			fSpeed = PLAER_DASH_NOMAL_SPEED;
			//フレーム数をカウント
			this->PlayerStatusList->SetPlayerNormalDashFlameCount(PlayerStatusList->iGetPlayerNormalDashFlameCount() + 1);

			//一定フレームがたったら走り（最大）へ
			if (this->PlayerStatusList->iGetPlayerNormalDashFlameCount() >= FLAME_COUNT_TO_MAX_SPEED)
			{
				fSpeed = PLAER_DASH_MAX_SPEED;
			}
		}
		else
		{
			//歩き
			this->PlayerStatusList->SetPlayerNowMoveSpeed(PLAYER_WALK_MOVE_SPEED);
			this->PlayerStatusList->SetPlayerNormalDashFlameCount(0);
			fSpeed = PLAYER_WALK_MOVE_SPEED;
		}
		/* 2025.01.09 菊池雅道　移動処理追加 終了 */

		/* 現在速度を更新 */
		this->PlayerStatusList->SetPlayerNowMoveSpeed(fSpeed);

		/* カメラの水平方向の向きを移動用の向きに設定 */
		float fAngleX = this->PlayerStatusList->fGetCameraAngleX();

		/* 移動量を算出 */
		vecAddMove.x	= +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
		vecAddMove.y	= 0.0f;
		vecAddMove.z	= -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
		vecAddMove		= VScale(vecAddMove, fSpeed);

		/* プレイヤーの向きを移動方向に合わせる */
		float fPlayerAngle	= atan2f(vecInput.x, vecInput.z);	// 移動方向の角度(ラジアン)を取得
		fPlayerAngle		= fAngleX - fPlayerAngle;			// カメラの向きと合成
		this->PlayerStatusList->SetPlayerAngleX(fPlayerAngle);	// プレイヤーの向きを設定
	}
	else
	{
		// 移動入力がされていない場合
		/* 移動速度を0にする */
		this->PlayerStatusList->SetPlayerNowMoveSpeed(0);
		//回避後フラグをリセット
		this->PlayerStatusList->SetPlayerAfterDodgeFlag(false);
	}

	/* 移動量を加算 */
	this->vecMove = VAdd(this->vecMove, vecAddMove);
}

// ジャンプ
void CharacterPlayer::Player_Jump()
{
	/* プレイヤーの状態を取得 */
	int iPlayerState = this->PlayerStatusList->iGetPlayerState();

	/* プレイヤーの状態がジャンプ可能であるか確認 */
	// ※要相談
	switch (iPlayerState)
	{
		/* ジャンプ可能な状態 */
		case PLAYER_STATUS_FREE:				// 自由状態
		case PLAYER_STATUS_MELEE_POSTURE:		// 近接攻撃構え中			
		case PLAYER_STATUS_PROJECTILE_POSTURE:	// 遠距離攻撃構え中
		case PLAYER_STATUS_PROJECTILE:			// 遠距離攻撃中
			/* プレイヤーのジャンプ処理 */
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
						this->PlayerStatusList->SetPlayerNowFallSpeed(-50.0f);

						/* ジャンプ回数を更新 */
						this->PlayerStatusList->SetPlayerNowJumpCount(iNowJumpCount + 1);

						this->PlayerStatusList->SetPlayerJumpingFlag(true);
					}
				}
			}
			break;

		/* ジャンプ不可能な状態 */
		case PLAYER_STATUS_DODGING:			// 回避状態中
		case PLAYER_STATUS_MELEE_WEEK:		// 近接攻撃中(弱)
		case PLAYER_STATUS_MELEE_STRONG:	// 近接攻撃中(強)
			break;
	}
}

// 重力処理
void CharacterPlayer::Player_Gravity()
{
	/* プレイヤーの状態を取得 */
	int iPlayerState = this->PlayerStatusList->iGetPlayerState();

	/* プレイヤーが重力処理を行う状態であるか確認 */
	// ※要相談
	switch (iPlayerState)
	{
		/* 重力処理を行う状態 */
		case PLAYER_STATUS_FREE:				// 自由状態		
		case PLAYER_STATUS_MELEE_POSTURE:		// 近接攻撃構え中		
		case PLAYER_STATUS_PROJECTILE_POSTURE:	// 遠距離攻撃構え中
			/* 重力処理を実行 */
			break;

		/* 重力処理を行わない状態 */
		case PLAYER_STATUS_DODGING:			// 回避状態中
		case PLAYER_STATUS_MELEE_WEEK:		// 近接攻撃中(弱)
		case PLAYER_STATUS_MELEE_STRONG:	// 近接攻撃中(強)
		case PLAYER_STATUS_PROJECTILE:		// 遠距離攻撃中
			/* 重力処理を行わない(重力処理を終了) */
			return;
	}

	/* 落下量取得 */
	float fFallSpeed	=	this->PlayerStatusList->fGetPlayerNowFallSpeed();		// 現時点での加速量取得
	fFallSpeed			+=	this->PlayerStatusList->fGetPlayerFallAcceleration();	// 加速度を加算

	/* 落下の加速度を更新 */
	this->PlayerStatusList->SetPlayerNowFallSpeed(fFallSpeed);

	/* 重力による移動後の座標を取得 */
	this->vecMove.y		-= this->PlayerStatusList->fGetPlayerNowFallSpeed();
}

// 回避
void CharacterPlayer::Player_Dodg()
{
	/* 2025.01.09 菊池雅道　移動処理追加 開始 */
	/* 入力による移動量を取得 */
	VECTOR vecInput = this->InputList->vecGetGameInputMoveDirection();

	/* カメラの水平方向の向きを移動用の向きに設定 */
	float fAngleX = this->PlayerStatusList->fGetCameraAngleX();

	/* 移動量を算出 */
	VECTOR vecMove;
	vecMove.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
	vecMove.y = 0.0f;
	vecMove.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
	
	//回避フラグがたっておらず、（ジャンプ中であれば）回避回数制限以内の状態で、回避ボタンが押された
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE) == true && this->PlayerStatusList->bGetPlayerDodgingFlag() == false && this->PlayerStatusList->iGetPlayerDodgeWhileJumpingCount() < PLAYER_DODGE_IN_AIR_LIMIT)
	{	
		// 回避フラグをセット
		this->PlayerStatusList->SetPlayerDodgingFlag(true);
		// 回避開始時の時間をリセット
		this->PlayerStatusList->SetPlayerNowDodgeFlame(0.0f);
		//現在の移動方向へ回避
		this->PlayerStatusList->SetPlayerDodgeDirection(VNorm(vecMove));
	
		//回避状態の進行率をリセット
		this->PlayerStatusList->SetPlayerDodgeProgress(0.0f);
	}

	//回避フラグが有効であれば回避処理を行う
	if (this->PlayerStatusList->bGetPlayerDodgingFlag() == true)
	{
		//ジャンプ中であれば回避回数をカウント
		if (this->PlayerStatusList->bGetPlayerJumpingFlag() == true)
		{
			this->PlayerStatusList->SetPlayerDodgeWhileJumpingCount(PlayerStatusList->iGetPlayerDodgeWhileJumpingCount() + 1);
		}

		// 時間経過を加算
		this->PlayerStatusList->SetPlayerNowDodgeFlame(this->PlayerStatusList->iGetPlayerNowDodgeFlame() + 1);

		// 回避中（設定時間の間）
		if (this->PlayerStatusList->iGetPlayerNowDodgeFlame() <= PLAYER_DODGE_FLAME)
		{
			//設定時間かけて回避移動を行う
			// 回避中（設定時間の間）
			vecMove = VScale(vecMove, PLAYER_DODGE_SPEED);

			/* 移動後の座標を算出 */
			VECTOR vecNextPosition = VAdd(this->vecPosition, vecMove);

			/* 道中でオブジェクトに接触しているか判定 */
			// 制作予定

			/* プレイヤーの座標を移動させる */
			this->vecPosition = vecNextPosition;
		}
		// 回避終了
		else
		{
			this->PlayerStatusList->SetPlayerDodgingFlag(false);
			this->PlayerStatusList->SetPlayerAfterDodgeFlag(true);
		}
	}

	/* プレイヤーの向きを移動方向に合わせる */
	float fPlayerAngle = atan2f(vecInput.x, vecInput.z);	// 移動方向の角度(ラジアン)を取得
	fPlayerAngle = fAngleX - fPlayerAngle;					// カメラの向きと合成
	this->PlayerStatusList->SetPlayerAngleX(fPlayerAngle);	// プレイヤーの向きを設定
	/* 2025.01.09 菊池雅道　移動処理追加 終了 */
}

// 移動処理(垂直方向)
void CharacterPlayer::Movement_Vertical()
{
	/* 移動後の座標を取得(垂直方向) */
	VECTOR vecNextPosition;
	vecNextPosition.x		= this->vecPosition.x;
	vecNextPosition.y		= this->vecPosition.y + this->vecMove.y;
	vecNextPosition.z		= this->vecPosition.z;

	/* 主人公の上部分の当たり判定から下方向へ向けた線分を作成 */
	this->stVerticalCollision.vecLineStart		=	this->vecPosition;
	this->stVerticalCollision.vecLineStart.y	+=	160;		// ※頭があたる高さ

	this->stVerticalCollision.vecLineEnd		=	stVerticalCollision.vecLineStart;
	this->stVerticalCollision.vecLineEnd.y		-=	9999;

	/* 以下、仮処理(近いオブジェクトのみ対象にするようにする) */
	/* 足場を取得 */
	auto& PlatformList = ObjectList->GetCollisionList();

	/* 着地する座標 */
	// ※初期値を移動後の座標に設定
	float	fStandPosY = vecNextPosition.y;

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
			if (stHitPolyDim.HitPosition.y > fStandPosY)
			{
				// 現在の着地座標より高い位置である場合
				/* 着地座標を更新 */
				fStandPosY = stHitPolyDim.HitPosition.y;

				/* 落下の加速度を更新 */
				this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);

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

			/* ヒットした座標を保存 */
			this->vecLandingPos = stHitPolyDim.HitPosition;
		}
	}

	/* 着地座標を更新 */
	vecNextPosition.y = fStandPosY;

	/* プレイヤー座標を更新 */
	this->vecPosition = vecNextPosition;

	/* 現在のプレイヤー状態を取得 */
	int iPlayerState = this->PlayerStatusList->iGetPlayerState();

	/* モーションを更新 */
	{
		/* 空中にいる(着地していない)か確認 */
		if (this->PlayerStatusList->bGetPlayerJumpingFlag() == false)
		{
			// 空中にいる(着地していない)場合
			/* 攻撃を構えていない状態であるか確認 */
			// ※構えている最中は落下モーションに遷移させない
			if ((iPlayerState != PLAYER_STATUS_MELEE_POSTURE) && (iPlayerState != PLAYER_STATUS_PROJECTILE_POSTURE))
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
		// カプセルコリジョン
		stHorizontalCollision.vecCapsuleBottom	= VAdd(this->vecPosition,	VGet(0.f, 45.f, 0.f));	// 現在の座標
		stHorizontalCollision.vecCapsuleTop		= VAdd(vecNextPosition,		VGet(0.f, 45.f, 0.f));	// 移動後の座標
		stHorizontalCollision.fCapsuleRadius	= 15.f;

		/* 足場を取得 */
		auto& PlatformList = ObjectList->GetCollisionList();

		/* 足場と接触するか確認 */
		for (auto* platform : PlatformList)
		{
			/* 足場との接触判定 */
			bool bHitFlg = platform->HitCheck(stHorizontalCollision);

			/* 接触しているか確認 */
			if (bHitFlg == true)
			{
				/* 接触している場合 */
				vecNextPosition = this->vecPosition;
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

// コリジョン更新
void CharacterPlayer::CollisionUpdate()
{
	/* プレイヤーのコリジョンを更新 */
	this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0, 135, 0));
	this->stCollisionCapsule.vecCapsuleBottom	= VAdd(this->vecPosition, VGet(0, 15, 0));
	this->stCollisionCapsule.fCapsuleRadius		= 15.f;
}

// 攻撃状態遷移管理
void CharacterPlayer::Player_Attack_Transition()
{
	/* 攻撃状態の遷移は下記とする */
	//           --> 構え(近接)   ---> 弱攻撃(近接) --
	//           |                 |                 |
	// 自由状態 -|                 --> 強攻撃(近接) ---> 自由状態
	//           |                                   |
	//           --> 構え(遠距離) ---> 攻撃(遠距離) --

	/* プレイヤーの状態を取得 */
	int iPlayerState = this->PlayerStatusList->iGetPlayerState();

	/* プレイヤー状態に応じて処理を変更 */
	switch (iPlayerState)
	{
		/* 自由状態 */
		case PLAYER_STATUS_FREE:
			/* 攻撃入力がされているか確認 */
			if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK) == true)
			{
				// 攻撃入力がされている場合
				/* プレイヤー状態を"近接攻撃構え中"に設定 */
				this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_MELEE_POSTURE);
			}
			/* エイム(構え)入力がされているか確認 */
			else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_AIM) == true)
			{
				// エイム(構え)入力がされている場合
				/* プレイヤー状態を"遠距離攻撃構え中"に設定 */
				this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_PROJECTILE_POSTURE);
			}
			break;

		/* 近接攻撃構え中 */
		case PLAYER_STATUS_MELEE_POSTURE:
			/* 近接攻撃(構え) */
			Player_Melee_Posture();
			break;

		/* 近接攻撃中(弱) */
		case PLAYER_STATUS_MELEE_WEEK:
			/* 近接攻撃(弱) */
			Player_Melee_Weak();
			break;

		/* 近接攻撃中(強) */
		case PLAYER_STATUS_MELEE_STRONG:
			/* 近距離攻撃(強) */
			Player_Charge_Attack();
			break;

		/* 遠距離攻撃構え中 */
		case PLAYER_STATUS_PROJECTILE_POSTURE:
			/* 遠距離攻撃(構え) */
			Player_Projectile_Posture();
			break;

		/* 遠距離攻撃中 */
		case PLAYER_STATUS_PROJECTILE:
			/* 遠距離攻撃 */
			Player_Projectile();
			break;
	}
}

// 近接攻撃(構え)
void CharacterPlayer::Player_Melee_Posture()
{
	/* プレイヤーの現在の攻撃チャージフレームの取得 */
	int iNowAttakChargeFlame = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame();

	/* 攻撃入力がされているか確認 */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK) == true)
	{
		// 攻撃入力がされている場合
		/* プレイヤーの現在の攻撃チャージフレームを加算 */
		PlayerStatusList->SetPlayerNowAttakChargeFlame(iNowAttakChargeFlame + 1);
	}
	else
	{
		// 攻撃入力がされていない場合
		/* 攻撃チャージフレームに応じて処理を変更 */
		if (iNowAttakChargeFlame < 5)
		{
			// 5フレーム未満の場合
			/* プレイヤーの状態を"近接攻撃中(弱)"に設定 */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_MELEE_WEEK);
		}
		else
		{
			// 5フレーム以上の場合
			/* プレイヤーの状態を"近接攻撃中(強)"に設定 */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_MELEE_STRONG);

			/* 未完成なのでとりあえず自由状態に戻す */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);
		}

		/* プレイヤーの現在の攻撃チャージフレームをリセット */
		PlayerStatusList->SetPlayerNowAttakChargeFlame(0);
	}
}

// 近接攻撃(弱)
void CharacterPlayer::Player_Melee_Weak()
{
	/* 攻撃モーションを確認 */
	// ※攻撃モーションが終了したら、自由状態に遷移するようにする

	/* プレイヤーの向きの方向にエフェクトを出す */
	EffectPlayerMeleeWeak* pAddEffect = new EffectPlayerMeleeWeak();
	ObjectList->SetEffect(pAddEffect);
	pAddEffect->Effect_Load("FX_slash/FX_slash");
	pAddEffect->SetPosition(this->vecPosition);
	pAddEffect->Initialization();

	/* 未完成なのでとりあえず自由状態に戻す */
	this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);
}

/* 2025.01.22 菊池雅道　攻撃処理追加 開始 */
// プレイヤー溜め攻撃
void CharacterPlayer::Player_Charge_Attack()
{
	/* 仮ターゲットを設定 */
	VECTOR vecTarget = VSub(this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraPosition());
	vecTarget = VNorm(vecTarget);
	vecTarget = VScale(vecTarget, 2000);
	vecTarget = VAdd(this->vecPosition, vecTarget);
	vecTest = vecTarget;
	int iFlamecount = 0;
	if (this->PlayerStatusList->iGetPlayerState() == PLAYER_STATUS_MELEE_POSTURE)
	{		
		this->PlayerStatusList->iPlayerNowAttakChargeFlame += 1;	
	}
	else if(this->InputList->bGetGameInputAction(INPUT_REL, GAME_ATTACK) == true)
	{
		/* 現在の移動速度取得 */
		VECTOR vecMove;
		vecMove = VSub(vecTarget, this->vecPosition);
		vecMove = VNorm(vecMove);
		vecMove = VScale(vecMove, this->PlayerStatusList->iPlayerNowAttakChargeFlame);
		/* 移動後の座標を算出 */
		VECTOR vecNextPosition = VAdd(this->vecPosition, vecMove);
		/* プレイヤーの座標を移動させる */
		this->vecPosition = vecNextPosition;

		this->PlayerStatusList->iPlayerNowAttakChargeFlame = 0;
	}
}

// 遠距離攻撃(構え)
void CharacterPlayer::Player_Projectile_Posture()
{
	/* 未完成なのでとりあえず自由状態に戻す */
	this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);
}

// 遠距離攻撃
void CharacterPlayer::Player_Projectile()
{
	/* 未完成なのでとりあえず自由状態に戻す */
	this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);
}

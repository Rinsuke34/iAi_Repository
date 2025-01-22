/* 2024.12.15 駒沢風助 ファイル作成 */

#include "CharacterPlayer.h"

/* オブジェクト */
#include "EffectTest.h"

/* プレイヤークラスの定義 */
VECTOR vecTest;
// コンストラクタ
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* 初期化 */
	/* データリスト取得 */
	this->InputList			= dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	this->ObjectList		= dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

	/* コリジョンを更新 */
	CollisionUpdate();
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
	/* プレイヤーの更新処理 */

	/* プレイヤーの状態に応じて処理を変更 */
	int iInput = this->PlayerStatusList->iGetPlayerState();
	switch (iInput)
	{
		/* 基本状態(行動に制約のない状態の総称) */
		case PLAYER_STATE_IDLE:			// 待機
		case PLAYER_STATE_WALK:			// 歩行
		case PLAYER_STATE_RUN_LOW:		// 走行(低速)
		case PLAYER_STATE_RUN_HIGH:		// 走行(高速)
		case PLAYER_STATE_JUMP_UP:		// 空中(上昇)
		case PLAYER_STATE_JUMP_DOWN:	// 空中(下降)
			/* 重力処理 */
			Player_Gravity();

			/* ジャンプ処理 */
			Player_Jump();

			/* 移動処理 */
			Player_Move();

			/* 回避処理 */
			Player_Dodg();

			Player_Charge_Attack();

			/* 入力取得 */
			if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK))
			{
				/* 居合(構え)状態へ遷移 */
				this->PlayerStatusList->SetPlayerState(PLAYER_STATE_DRAW_SWORD_CHARGE);
			}
			else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_AIM))
			{
				/* クナイ(構え)状態へ遷移 */
				this->PlayerStatusList->SetPlayerState(PLAYER_STATE_THROW_KUNAI_AIM);
			}
			else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE))
			{
				/* 回避状態に遷移 */
				this->PlayerStatusList->SetPlayerState(PLAYER_STATE_DODGE);
			}
			break;

		/* 行動制限状態(一部行動に制約あり) */
		case PLAYER_STATE_DRAW_SWORD_CHARGE:	// 居合(溜め)
		case PLAYER_STATE_THROW_KUNAI_AIM:		// クナイ(構え)
			/* 重力処理 */
			Player_Gravity();

			/* 移動処理 */
			Player_Move();

			/* 入力取得 */
			switch (iInput)
			{
				case PLAYER_STATE_DRAW_SWORD_CHARGE:	// 居合(溜め)
					/* 攻撃ボタンを離したか */
					if (this->InputList->bGetGameInputAction(INPUT_REL, GAME_ATTACK))
					{
						/* 居合(弱)状態に遷移 */
						this->PlayerStatusList->SetPlayerState(PLAYER_STATE_DRAW_SWORD_WEAK);
					}
					/* 回避を入力したか */
					else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE))
					{
						/* 回避状態に遷移 */
						this->PlayerStatusList->SetPlayerState(PLAYER_STATE_DODGE);
					}
					break;

				case PLAYER_STATE_THROW_KUNAI_AIM:		// クナイ(構え)
					/* 攻撃ボタンを押したか */
					if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK))
					{
						/* クナイ(投げ)状態に遷移 */
						this->PlayerStatusList->SetPlayerState(PLAYER_STATE_THROW_KUNAI_THROW);
					}
					/* 構えを解除したか */
					else if (this->InputList->bGetGameInputAction(INPUT_REL, GAME_AIM))
					{
						/* 待機状態に遷移 */
						this->PlayerStatusList->SetPlayerState(PLAYER_STATE_IDLE);
					}
					/* 回避を入力したか */
					else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE))
					{
						/* 回避状態に遷移 */
						this->PlayerStatusList->SetPlayerState(PLAYER_STATE_DODGE);
					}
					break;
			}
			break;

		/* 攻撃状態 */
		// 居合系
		case PLAYER_STATE_DRAW_SWORD_WEAK:		// 居合(弱)
		case PLAYER_STATE_DRAW_SWORD_STRONG:	// 居合(強)
			/* 攻撃処理(テスト) */
			Player_Attack();

			/* 待機状態に戻す(仮) */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATE_IDLE);
			break;

		// クナイ系
		case PLAYER_STATE_THROW_KUNAI_THROW:	// クナイ(投げ)
			/* 攻撃処理(テスト) */
			Player_Attack();

			/* 待機状態に戻す(仮) */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATE_IDLE);
			break;

		/* 回避状態 */
		case PLAYER_STATE_DODGE:				// 回避
			/* 移動処理 */
			Player_Move();

			/* 待機状態に戻す(仮) */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATE_IDLE);
			break;
	}
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

// 移動
void CharacterPlayer::Player_Move()
{
	/* プレイヤーの移動処理 */

	float fStickTiltMagnitude	= this->InputList->fGetGameInputMove();
	VECTOR vecInput				= this->InputList->vecGetGameInputMoveDirection();

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
		VECTOR vecMove;
		vecMove.x	= +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
		vecMove.y	= 0.0f;
		vecMove.z	= -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
		vecMove		= VScale(vecMove, fSpeed);

		/* 移動後の座標を算出 */
		VECTOR vecNextPosition = VAdd(this->vecPosition, vecMove);

		/* 道中でオブジェクトに接触しているか判定 */
		// 制作予定

		/* プレイヤーの座標を移動させる */
		this->vecPosition = vecNextPosition;

		/* プレイヤーの向きを移動方向に合わせる */
		float fPlayerAngle = atan2f(vecInput.x, vecInput.z);	// 移動方向の角度(ラジアン)を取得
		fPlayerAngle = fAngleX - fPlayerAngle;					// カメラの向きと合成
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
	/* コリジョンを更新 */
	CollisionUpdate();
}

// ジャンプ
void CharacterPlayer::Player_Jump()
{
	/* プレイヤーのジャンプ処理 */

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
			/* 空中(上昇)へ遷移 */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATE_JUMP_UP);
		}
	}

	/* コリジョンを更新 */
	CollisionUpdate();
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

// 重力
void CharacterPlayer::Player_Gravity()
{
	/* プレイヤーの重力処理 */
	// ※プレイヤーのY方向への移動処理をまとめて行う

	/* 落下量取得 */
	float fFallSpeed	=	this->PlayerStatusList->fGetPlayerNowFallSpeed();		// 現時点での加速量取得
	fFallSpeed			+=	this->PlayerStatusList->fGetPlayerFallAcceleration();	// 加速度を加算

	/* 重力による移動後の座標を取得 */
	VECTOR vecNextPosition	=	this->vecPosition;
	vecNextPosition.y		-=	this->PlayerStatusList->fGetPlayerNowFallSpeed();

	/* 主人公の上部分の当たり判定から下方向へ向けた線分を作成 */
	COLLISION_LINE stCollision;
	stCollision.vecLineStart	=	this->vecPosition;
	stCollision.vecLineStart.y	+=	100;		// 歩きで登れる高さの上限

	stCollision.vecLineEnd		=	stCollision.vecLineStart;
	stCollision.vecLineEnd.y	-=	9999;

	/* 以下、仮処理(近いオブジェクトのみ対象にするようにする) */
	/* 足場を取得 */
	auto& PlatformList = ObjectList->GetPlatformList();

	/* 着地する座標 */
	float	fStandPosY		= vecNextPosition.y;	// 初期値を移動後の座標に設定

	/* プレイヤーの着地フラグを無効にする */
	this->PlayerStatusList->SetPlayerLanding(false);

	/* 足場と接触するか確認 */
	for (auto* platform : PlatformList)
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stCollision);

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

				/* 落下の加速度を初期化する */
				fFallSpeed = 0.f;

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
		}
	}

	/* 着地座標を更新 */
	vecNextPosition.y = fStandPosY;

	/* プレイヤー座標を更新 */
	this->vecPosition = vecNextPosition;

	/* 落下速度を更新 */
	this->PlayerStatusList->SetPlayerNowFallSpeed(fFallSpeed);

	/* 落下速度が+であるなら空中(下降)に遷移 */
	if (fFallSpeed < 0)
	{
		// 落下速度が+である場合
		/* 空中(下降)に遷移 */
		this->PlayerStatusList->SetPlayerState(PLAYER_STATE_JUMP_DOWN);
	}

	/* コリジョンを更新 */
	CollisionUpdate();
}

// コリジョン更新
void CharacterPlayer::CollisionUpdate()
{
	/* プレイヤーのコリジョン更新処理 */

	/* プレイヤーのコリジョンを更新 */
	COLLISION_CAPSULE stCapsule;
	stCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0, 100, 0));
	stCapsule.vecCapsuleBottom	= VAdd(this->vecPosition, VGet(0, 0, 0));
	stCapsule.fCapsuleRadius	= 50.0f;

	/* コリジョンを設定 */
	this->SetCollision_Capsule(stCapsule);
}

// プレイヤー攻撃(仮)
void CharacterPlayer::Player_Attack()
{
	/* テスト用攻撃処理 */

	/* 攻撃が入力されているか確認 */
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK) == true)
	{
		EffectBase* Effect_Test = new TestEffect();
		Effect_Test->Effect_Load("FX_e_bullet");
		Effect_Test->SetPosition(VAdd(this->vecPosition, VGet(0.f, 10.f, 0.f)));

		dynamic_cast<TestEffect*>(Effect_Test)->Initialization();

		
		ObjectList->SetEffect(Effect_Test);
	}
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
	if (this->PlayerStatusList->iGetPlayerState() == PLAYER_STATE_DRAW_SWORD_CHARGE)
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

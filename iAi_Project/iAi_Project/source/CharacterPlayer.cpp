/* 2024.12.15 駒沢風助	ファイル作成 */
/* 2025.01.09 菊池雅道　移動処理追加 */
/* 2025.01.22 菊池雅道　攻撃処理追加 */
/* 2025.01.24 菊池雅道　攻撃処理追加 */

#include "CharacterPlayer.h"

// デバッグ用 後で削除
/* 強攻撃目的地点表示用 */
VECTOR vecTest;
/* 弱攻撃攻撃範囲表示用 */
COLLISION_SQHERE stTestCollision;

/* プレイヤークラスの定義 */
// コンストラクタ
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* 初期化 */
	{
		/* オブジェクトのハンドル */
		this->pBulletMeleeWeak	=	nullptr;	// 近接攻撃(弱)の弾

		/* 変数 */
		this->vecMove		= VGet(0.f, 0.f, 0.f);	// 移動量
		this->iObjectType	= OBJECT_TYPE_PLAYER;	// オブジェクトの種類

		/* 変数(デバッグ用) */
		this->stVerticalCollision								= {};		// 垂直方向のコリジョン
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_UP]	= {};		// 水平方向コリジョン(上側)
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN]	= {};		// 水平方向コリジョン(下側)
		this->stMeleeStrongMoveCollsion							= {};		// 近接攻撃(強)のコリジョン(移動後の座標)
	}

	/* データリスト取得 */
	{
		/* "入力管理"を取得 */
		this->InputList			= dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));

		/* "オブジェクト管理"を取得 */
		this->ObjectList		= dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "エフェクトリソース管理"を取得 */
		this->EffectList		= dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"));
	}

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Player/Models/Player");
	}
}

// 初期化
void CharacterPlayer::Initialization()
{
	CharacterBase::Initialization();

	/* コリジョンを更新 */
	CollisionUpdate();

	/* カメラモードを"フリーモード"に変更 */
	this->PlayerStatusList->SetCameraMode(CAMERA_MODE_FREE);
}

// 更新
void CharacterPlayer::Update()
{
	/* カメラモードを"フリーモード"に変更 */
	this->PlayerStatusList->SetCameraMode(CAMERA_MODE_FREE);

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
	iColor	= GetColor(0, 255, 0);
	DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, iColor);

	/* 並行方向のコリジョン */
	iColor	= GetColor(0, 0, 255);
	DrawCapsule3D(this->stHorizontalCollision[0].vecCapsuleTop, this->stHorizontalCollision[0].vecCapsuleBottom, this->stHorizontalCollision[0].fCapsuleRadius, 16, iColor, iColor, FALSE);
	DrawCapsule3D(this->stHorizontalCollision[1].vecCapsuleTop, this->stHorizontalCollision[1].vecCapsuleBottom, this->stHorizontalCollision[1].fCapsuleRadius, 16, iColor, iColor, FALSE);

	/* 強攻撃移動後座標 */
	iColor = GetColor(255, 255, 0);
	DrawCapsule3D(this->stMeleeStrongMoveCollsion.vecCapsuleTop, this->stMeleeStrongMoveCollsion.vecCapsuleBottom, this->stMeleeStrongMoveCollsion.fCapsuleRadius, 16, iColor, iColor, FALSE);

	/* 強攻撃ロックオン範囲 */
	iColor = GetColor(255, 0, 255);
	COLLISION_CAPSULE stMeleeCollision = this->PlayerStatusList->stGetMeleeSearchCollision();
	DrawCapsule3D(stMeleeCollision.vecCapsuleTop, stMeleeCollision.vecCapsuleBottom, stMeleeCollision.fCapsuleRadius, 16, iColor, iColor, FALSE);

	/* カメラ注視点 */
	iColor = GetColor(0, 255, 255);
	DrawLine3D(VAdd(this->PlayerStatusList->vecGetCameraTarget(), VGet(+50, 0, 0)), VAdd(this->PlayerStatusList->vecGetCameraTarget(), VGet(-50, 0, 0)), iColor);
	DrawLine3D(VAdd(this->PlayerStatusList->vecGetCameraTarget(), VGet(0, 0, +50)), VAdd(this->PlayerStatusList->vecGetCameraTarget(), VGet(0, 0, -50)), iColor);
}

// 移動
void CharacterPlayer::Player_Move()
{
	/* プレイヤー移動量取得 */
	float fStickTiltMagnitude	= this->InputList->fGetGameInputMove();				// スティックを倒した強さ
	VECTOR vecInput				= this->InputList->vecGetGameInputMoveDirection();	// 移動方向
	VECTOR vecAddMove			= VGet(0, 0, 0);									// 移動量(加算用)

	/* プレイヤーの状態を取得 */
	int iPlayerState = this->PlayerStatusList->iGetPlayerState();

	/* プレイヤーの状態に応じて移動速度の倍率等を設定 */
	float	fMoveSpeedRatio		= 1.f;		// 移動速度(倍率)
	bool	bPlayerAngleSetFlg	= true;		// プレイヤーの向きを移動方向に合わせるかのフラグ
	switch (iPlayerState)
	{
		/* 移動処理を通常通りに行う状態 */
		case PLAYER_STATUS_FREE:				// 自由状態
			/* 補正無しにする */
			fMoveSpeedRatio		= 1.f;
			bPlayerAngleSetFlg	= true;
			break;

		/* 移動処理を速度を抑えて行う状態 */
		case PLAYER_STATUS_MELEE_POSTURE:		// 近接攻撃構え中
		case PLAYER_STATUS_PROJECTILE_POSTURE:	// 遠距離攻撃構え中
			/* 移動速度補正0.5倍にする */
			// ※仮の値
			fMoveSpeedRatio		= 0.5f;
			bPlayerAngleSetFlg	= false;
			break;

		/* 移動処理を行わない状態 */
		case PLAYER_STATUS_DODGING:				// 回避状態中
		case PLAYER_STATUS_MELEE_WEEK:			// 近接攻撃中(弱)
		case PLAYER_STATUS_MELEE_STRONG:		// 近接攻撃中(強)
		case PLAYER_STATUS_PROJECTILE:			// 遠距離攻撃中
			/* 移動処理を終了する */
			// ※これらの状態では移動処理を行わない
			return;
	}

	/* 移動入力がされているか確認 */
	if (vecInput.x != 0 || vecInput.z != 0)
	{
		// 移動入力がされている場合
		/* 現在の移動速度取得 */
		float fSpeed = this->PlayerStatusList->fGetPlayerNowMoveSpeed();
			
		// 回避後フラグがtrueなら最大ダッシュ状態になる
		if (this->PlayerStatusList->bGetPlayerAfterDodgeFlag() == true)
		{
			fSpeed = PLAER_DASH_MAX_SPEED * fMoveSpeedRatio;
		}

		// スティックの倒し具合で速度を変化
		else if (fStickTiltMagnitude > STICK_TILT_PLAER_DASH) 
		{
			//走り（通常）
			fSpeed = PLAER_DASH_NOMAL_SPEED * fMoveSpeedRatio;
			//フレーム数をカウント
			this->PlayerStatusList->SetPlayerNormalDashFlameCount(PlayerStatusList->iGetPlayerNormalDashFlameCount() + 1);

			//一定フレームがたったら走り（最大）へ
			if (this->PlayerStatusList->iGetPlayerNormalDashFlameCount() >= FLAME_COUNT_TO_MAX_SPEED)
			{
				fSpeed = PLAER_DASH_MAX_SPEED * fMoveSpeedRatio;
			}
		}
		else
		{
			//歩き
			this->PlayerStatusList->SetPlayerNowMoveSpeed(PLAYER_WALK_MOVE_SPEED);
			this->PlayerStatusList->SetPlayerNormalDashFlameCount(0);
			fSpeed = PLAYER_WALK_MOVE_SPEED * fMoveSpeedRatio;
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

		/* プレイヤーの向きを移動方向に合わせるか確認 */
		if (bPlayerAngleSetFlg == true)
		{
			// 合わせる場合
			/* プレイヤーの向きを移動方向に合わせる */
			float fPlayerAngle	= atan2f(vecInput.x, vecInput.z);	// 移動方向の角度(ラジアン)を取得
			fPlayerAngle		= fAngleX - fPlayerAngle;			// カメラの向きと合成
			this->PlayerStatusList->SetPlayerAngleX(fPlayerAngle);	// プレイヤーの向きを設定
		}
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
						this->PlayerStatusList->SetPlayerNowFallSpeed(-20.0f);

						/* ジャンプ回数を更新 */
						this->PlayerStatusList->SetPlayerNowJumpCount(iNowJumpCount + 1);

						this->PlayerStatusList->SetPlayerJumpingFlag(true);

						/* ジャンプのSEを再生 */
						gpDataList_Sound->SE_PlaySound(SE_PLAYER_JUMP);
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
	/* 2025.01.09 菊池雅道　移動処理追加	開始 */
	/* 2025.01.26 駒沢風助	コード修正		開始*/
	
	/* プレイヤーの状態を取得 */
	int iPlayerState = this->PlayerStatusList->iGetPlayerState();

	/* プレイヤー場外が"回避状態中"であるか確認 */
	if (iPlayerState == PLAYER_STATUS_DODGING)
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
			this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);
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
				this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_DODGING);

				/* プレイヤーが着地していないかを確認 */
				if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
				{
					// 着地していない場合
					/* 空中での回避回数のカウントを進める */
					this->PlayerStatusList->SetPlayerDodgeWhileJumpingCount(PlayerStatusList->iGetPlayerDodgeWhileJumpingCount() + 1);
				}

				/* 回避のSEを再生 */
				gpDataList_Sound->SE_PlaySound(SE_PLAYER_DODGE);
			}
		}
	}

	/* 2025.01.09 菊池雅道　移動処理追加	終了 */
	/* 2025.01.26 駒沢風助	コード修正		終了*/
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
	this->stVerticalCollision.vecLineStart.y	+=	PLAYER_HEIGHT;
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
		// ※ 元の位置から移動後の位置へ向けたカプセルコリジョンを作成
		stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].vecCapsuleBottom	= VAdd(this->vecPosition,	VGet(0.f, PLAYER_HEIGHT - PLAYER_WIDE, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].vecCapsuleTop		= VAdd(vecNextPosition,		VGet(0.f, PLAYER_HEIGHT - PLAYER_WIDE, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].fCapsuleRadius		= PLAYER_WIDE;
		stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].vecCapsuleBottom	= VAdd(this->vecPosition,	VGet(0.f, PLAYER_WIDE + PLAYER_CLIMBED_HEIGHT, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].vecCapsuleTop		= VAdd(vecNextPosition,		VGet(0.f, PLAYER_WIDE + PLAYER_CLIMBED_HEIGHT, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].fCapsuleRadius	= PLAYER_WIDE;

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
					VECTOR vecNormalSum		= VGet(0.f, 0.f, 0.f);

					/* ポリゴンと接触した座標 */
					VECTOR vecHitPos		= VGet(0.f, 0.f, 0.f);

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
					stSphere.vecSqhere		= vecNextPosition;
					stSphere.fSqhereRadius	= PLAYER_WIDE;

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

// コリジョン更新
void CharacterPlayer::CollisionUpdate()
{
	/* プレイヤーのコリジョンを更新 */
	this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT - PLAYER_WIDE, 0));
	this->stCollisionCapsule.vecCapsuleBottom	= VAdd(this->vecPosition, VGet(0, PLAYER_WIDE, 0));
	this->stCollisionCapsule.fCapsuleRadius		= PLAYER_WIDE;
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

	/* 2025.01.24 菊池雅道　攻撃処理追加	開始 */
	/* 2025.01.26 駒沢風助	コード修正		開始*/

	/* 攻撃入力がされているか確認 */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK) == true)
	{
		// 攻撃入力がされている場合
		/* プレイヤーモーションが"居合(溜め)"以外であるか確認 */
		// if
		{
			// 居合(溜め)以外である場合
			/* プレイヤーモーションを"居合(溜め)"に変更 */
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
				}
			}

			/* プレイヤーの向きをカメラの向きに固定 */
			this->PlayerStatusList->SetPlayerAngleX(this->PlayerStatusList->fGetCameraAngleX());

			/* 移動量算出 */
			//float fMove = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() * 2.7f;
			// 臨時でちょっと長めにする
			float fMove = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() * 5.f;

			/* 移動方向算出 */
			VECTOR vecMoveDirection = VNorm(VSub(this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraPosition()));

			/* 縦方向には移動しないように設定 */
			vecMoveDirection.y = 0;

			/* 近接攻撃(強)による移動量を設定 */
			this->PlayerStatusList->SetPlayerChargeAttakTargetMove(VScale(vecMoveDirection, fMove));

			/* 攻撃チャージフレームが強攻撃に派生しているか確認 */
			if (iNowAttakChargeFlame >= PLAYER_CHARGE_TO_STRONG_TIME)
			{
				/* カメラモードを"構え(ズーム)"に変更 */
				this->PlayerStatusList->SetCameraMode(CAMERA_MODE_AIM);

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
					//// 臨時でプレイヤーの注視点に設定
					//stMeleeSearchCollision.vecCapsuleBottom = this->PlayerStatusList->vecGetCameraTarget();
					//stMeleeSearchCollision.vecCapsuleBottom.y = stMeleeSearchCollision.vecCapsuleTop.y;

					/* ロックオン範囲のコリジョンを設定 */
					this->PlayerStatusList->SetMeleeSearchCollision(stMeleeSearchCollision);
				}
			}

			/* デバッグ用処理 */
			{
				/* デバッグ用移動後座標を設定 */
				this->stMeleeStrongMoveCollsion.vecCapsuleTop		= VAdd(VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT - PLAYER_WIDE, 0)), VScale(vecMoveDirection, fMove));
				this->stMeleeStrongMoveCollsion.vecCapsuleBottom	= VAdd(VAdd(this->vecPosition, VGet(0, PLAYER_WIDE, 0)), VScale(vecMoveDirection, fMove));
				this->stMeleeStrongMoveCollsion.fCapsuleRadius		= PLAYER_WIDE;
			}
		}

		/* 2025.01.24 菊池雅道　攻撃処理追加	終了 */
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
			this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_MELEE_WEEK);
		}
		else
		{
			// 強攻撃にならない場合
			/* プレイヤーの状態を"近接攻撃中(強)"に設定 */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_MELEE_STRONG);

			/* プレイヤーのため攻撃用のカウントを初期化 */
			this->PlayerStatusList->SetPlayerChargeAttackCount(0);

			/* 落下の加速度を初期化 */
			this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);
		}

		/* プレイヤーの現在の攻撃チャージフレームをリセット */
		this->PlayerStatusList->SetPlayerNowAttakChargeFlame(0);
	}
}

// 近接攻撃(弱)
void CharacterPlayer::Player_Melee_Weak()
{
	/* 2025.01.22 菊池雅道　攻撃処理追加	開始 */
	/* 2025.01.26 駒沢風助	コード修正		開始*/

	/* 攻撃モーションを確認 */
	// ※現在のモーションが近接攻撃(弱)であるか確認
	// if
	{
		// 近接攻撃(弱)である場合
		/* プレイヤーモーションの現在のカウントを進める */

		/* 現在のモーションの総時間を取得 */

		/* 現在のモーションの総時間を超えているか */
		// if
		{
			// 超えている場合
			/* プレイヤー状態を"自由状態"に変更 */
			//this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);

			/* プレイヤーのモーションを"待機"に設定 */
			//this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_WAIT);

			/* プレイヤーのモーションの現在のカウントを初期化 */

			/* バレットクラス"近接攻撃(弱)"の削除フラグを有効 */
			//this->pAddBullet->SetDeleteFlag(true);

			/* このクラスで所持するバレットクラス"近接攻撃(弱)"のハンドルを初期化 */
			//this->pBulletMeleeWeak = nullptr;
		}
	}
	// else
	{
		// 近接攻撃(弱)でない場合
		/* プレイヤーのモーションを近接攻撃(弱)に設定 */
		
		/* プレイヤーのモーションの現在のカウントを初期化 */

		/* 近接攻撃として扱う弾を作成 */
		// ※現在のプレイヤーの向きに弾を作成
		this->pBulletMeleeWeak = new BulletPlayerMeleeWeak;

		/* 生成座標を取得 */
		{
			/* 攻撃の生成方向の設定 */
			// ※プレイヤーの向きではなくカメラの向きとする
			VECTOR vecInput = VGet(0.f, 0.f, 1.f);

			/* カメラの水平方向の向きを移動用の向きに設定 */
			float fAngleX = this->PlayerStatusList->fGetCameraAngleX();

			/* 攻撃座標を算出 */
			VECTOR vecAdd;
			// 方向
			vecAdd.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
			vecAdd.y = 0.f;
			vecAdd.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
			vecAdd = VNorm(vecAdd);
			vecAdd = VScale(vecAdd, PLAYER_WIDE);
			// 高さ
			vecAdd.y = PLAYER_HEIGHT / 2.f;

			/* 攻撃生成座標を設定 */
			this->pBulletMeleeWeak->SetPosition(VAdd(this->vecPosition, vecAdd));
		}

		/* 攻撃の向きを設定 */
		this->pBulletMeleeWeak->SetRotation(VGet(0.0f, -(this->PlayerStatusList->fGetCameraAngleX()), 0.0f));

		/* 初期化を行う */
		this->pBulletMeleeWeak->Initialization();

		/* バレットリストに追加 */
		ObjectList->SetBullet(this->pBulletMeleeWeak);
	}

	/* 2025.01.22 菊池雅道　攻撃処理追加	終了 */
	/* 2025.01.26 駒沢風助	コード修正		終了 */

	/* 近接攻撃(弱)のSEを再生 */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_NIAI);

	/* 未完成なのでとりあえず自由状態に戻す */
	this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);
}

// 近距離攻撃(強)
void CharacterPlayer::Player_Charge_Attack()
{
	/* 2025.01.22 菊池雅道　攻撃処理追加	開始 */
	/* 2025.01.26 駒沢風助	コード修正		開始 */

	/* 溜め攻撃用のカウントを取得 */
	int iChargeAttackCount = this->PlayerStatusList->iGetPlayerChargeAttackCount();

	/* カウントを確認 */
	if (iChargeAttackCount == 0)
	{
		// 0である場合
		// ※モーション遷移直後である場合
		/* プレイヤーのモーションを近接攻撃(強)に変更する */

		/* 溜め居合攻撃のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_PLAYER_SPIAI);
	}
	//else if(iChargeAttackCount <= 20)
	//{
	//	// 20以下である場合
	//	/* モーションの初期動作中?なのでこの状態では攻撃しない */
	//}
	else
	{
		// 21以上である場合
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
				fMove += 500.f;
				vecMoveDirection = VAdd(vecMoveDirection, VScale(VNorm(vecMoveDirection), 500.f));
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
				this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);

				/* プレイヤーのモーションを"居合(強)(終了)"に変更 */
				this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_DRAW_SWORD_END);
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
		}
	}

	/* 溜め攻撃用のカウントを+1する */
	this->PlayerStatusList->SetPlayerChargeAttackCount(iChargeAttackCount + 1);

	/* 2025.01.22 菊池雅道　攻撃処理追加	終了 */
	/* 2025.01.26 駒沢風助	コード修正		終了 */	
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

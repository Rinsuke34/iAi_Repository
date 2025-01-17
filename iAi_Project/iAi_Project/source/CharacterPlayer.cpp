/* 2024.12.15 駒沢風助 ファイル作成 */
/* 2025.01.09 菊池雅道　移動処理追加 */

#include "CharacterPlayer.h"

/* プレイヤークラスの定義 */

// コンストラクタ
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* 初期化 */
	/* データリスト取得 */
	this->InputList			= dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	this->ObjectList		= dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

	/* 仮初期化処理開始 */
	this->iModelHandle = MV1LoadModel("resource/ModelData/Test/Player/Karisotai_1217.mv1");

	/* コリジョンを更新 */
	CollisionUpdate();
}

// 更新
void CharacterPlayer::Update()
{

	/* 重力処理 */
	Player_Gravity();

	
	/* 移動処理 */
	Player_Move();

	/* 2025.01.09 菊池雅道　移動処理追加 開始 */
	
	/* 回避処理 */
	Player_Dodg();

	/* 2025.01.09 菊池雅道　移動処理追加 終了 */

	/* ジャンプ処理 */
	Player_Jump();


	/* 攻撃処理 */
	Player_Attack();


	
	// 移動量をそのままキャラの向きにする
	//if (VSize(VGet(this->PlayerStatusList -> vecGetPlayerMoveVector().x, 0, this->PlayerStatusList->vecGetPlayerMoveVector().z)) > 0.f) {		// 移動していない時は無視するため
		//this->PlayerStatusList -> vecPlayerDirection = vecPlayerMove;
	//}
	
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

	/*VECTOR vecMove = this->InputList->vecGetGameInputMove();
	DrawFormatString(500, 16 * 9, GetColor(255, 255, 255), "X:%f, Z:%f", vecMove.x, vecMove.z);*/


	GetJoypadXInputState(DX_INPUT_PAD1, &stXInputState);

	DrawFormatString(500, 16 * 10, GetColor(255, 255, 255), "左トリガ : %u", stXInputState.LeftTrigger);
	DrawFormatString(500, 16 * 11, GetColor(255, 255, 255), "右トリガ : %u", stXInputState.RightTrigger);

	float fSpeed = this->PlayerStatusList->fGetPlayerNowMoveSpeed();
	DrawFormatString(500, 16 * 12, GetColor(255, 255, 255), "移動速度 : %f", fSpeed);
	DrawFormatString(500, 16 * 15, GetColor(255, 255, 255), "位置 x: %f y:%f z::%f",this -> vecPosition.x, this->vecPosition.y, this->vecPosition.z);
	VECTOR vecMove = this->PlayerStatusList->vecGetPlayerMoveVector();
	DrawFormatString(500, 16 * 17, GetColor(255, 255, 255), " 移動 x: %f y:%f z::%f", this->PlayerStatusList->vecGetPlayerMoveVector().x, this->PlayerStatusList->vecGetPlayerMoveVector().y, this->PlayerStatusList->vecGetPlayerMoveVector().z);
	DrawFormatString(500, 16 * 20, GetColor(255, 255, 255), "ジャンプ : %d", this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP));
	DrawSphere3D(this->PlayerStatusList->stPlayerAttackCollisionSqhere.vecSqhere, this->PlayerStatusList->stPlayerAttackCollisionSqhere.fSqhereRadius, 32,GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
	
	DrawFormatString(500, 16 * 22, GetColor(255, 255, 255), "敵HP : %d", this->PlayerStatusList->iEnemyHP);
	DrawFormatString(500, 16 * 24, GetColor(255, 255, 255), "回避時間 : %f", this->PlayerStatusList->fGetPlayerDodgeTime());
	
	
}

// 移動
void CharacterPlayer::Player_Move()
{
	/* 2025.01.09 菊池雅道　移動処理追加 開始 */
	/* プレイヤーの移動処理 */
	// キャラ移動(カメラ設定に合わせて)

		// カメラの向いている角度を取得(仮)
	VECTOR stVecCameraPosition = this->PlayerStatusList->vecGetCameraPosition();
	VECTOR stVecCameraTarget = this->PlayerStatusList->vecGetCameraTarget();
	VECTOR stVecCameraUp = this->PlayerStatusList->vecGetCameraUp();
	this->PlayerStatusList->fGetCameraAngleX();
	float sx = stVecCameraPosition.x - stVecCameraTarget.x;
	float sz = stVecCameraPosition.z - stVecCameraTarget.z;
	float camrad = atan2(sz, -sx);

	VECTOR vecPlayerMove = { 0,0,0 }; //プレイヤーの移動ベクトル

	//地上にいる場合の処理
	if (this->PlayerStatusList->bGetPlayerJumpingFlag() == false) {

		// アナログスティックの入力を正規化して移動方向を計算
		float fStickTiltMagnitude = sqrt(gstJoypadInputData.sAnalogStickX[INPUT_LEFT] * gstJoypadInputData.sAnalogStickX[INPUT_LEFT] + gstJoypadInputData.sAnalogStickY[INPUT_LEFT] * gstJoypadInputData.sAnalogStickY[INPUT_LEFT]);
		// デッドゾーンを設定
		
		if (fStickTiltMagnitude > STICK_DEAD_ZONE)
		{
			//正規化した入力方向を取得
			float fNormalizedInputX = gstJoypadInputData.sAnalogStickY[INPUT_LEFT] / fStickTiltMagnitude;
			float fNormalizedInputY = gstJoypadInputData.sAnalogStickX[INPUT_LEFT] / fStickTiltMagnitude;

			// カメラ方向を考慮して移動ベクトルを回転
			float fInputAngle = atan2(fNormalizedInputY, fNormalizedInputX);
			float fPlayerMoveAngle = fInputAngle + camrad;

			// 回避後フラグがtrueなら最大ダッシュ状態になる
			if (this->PlayerStatusList->bGetPlayerAfterDodgeFlag() == true)
			{
				this->PlayerStatusList-> SetPlayerNowMoveSpeed(PLAER_DASH_MAX_SPEED);
				
			}
			// スティックの倒し具合で速度を変化
			else if (fStickTiltMagnitude > STICK_TILT_PLAER_DASH) {
				//走り（通常）
				this->PlayerStatusList->SetPlayerNowMoveSpeed(PLAER_DASH_NOMAL_SPEED);
				this->PlayerStatusList->SetPlayerNormalDashFlameCount(PlayerStatusList->iGetPlayerNormalDashFlameCount() + 1);

				//一定フレームがたったら走り（最大）へ
				if (this->PlayerStatusList->iGetPlayerNormalDashFlameCount() >= FLAME_COUNT_TO_MAX_SPEED)
				{
					this->PlayerStatusList->SetPlayerNowMoveSpeed(PLAER_DASH_MAX_SPEED);
				}
			}
			else
			{
				//歩き
				this->PlayerStatusList->SetPlayerNowMoveSpeed(PLAYER_WALK_MOVE_SPEED);
				this->PlayerStatusList->SetPlayerNormalDashFlameCount(0);
			}
			//移動の方向と速度をベクトルに設定
			vecPlayerMove.z = -cos(fPlayerMoveAngle) * this->PlayerStatusList->fGetPlayerNowMoveSpeed();
			vecPlayerMove.x = -sin(fPlayerMoveAngle) * this->PlayerStatusList->fGetPlayerNowMoveSpeed();

			//移動の角度を保存する（後の処理に使用）
			this->PlayerStatusList->SetPlayerOldRadian(fPlayerMoveAngle);
			this->PlayerStatusList->SetPlayerAngleX(fPlayerMoveAngle);
		}
		//スティックの傾きがデッドゾーン以下
		else
		{
			//回避後フラグをリセット
			this->PlayerStatusList->SetPlayerAfterDodgeFlag(false);
	
			// 移動入力がされていない場合
			// 移動速度を0にする //
			this->PlayerStatusList->SetPlayerNowMoveSpeed(0);

		}

		

	}
	//空中にいる場合の処理
	else
	{

		// アナログスティックの入力を正規化して移動方向を計算
		float fStickTiltMagnitude = sqrt(stXInputState.ThumbLX * stXInputState.ThumbLX + stXInputState.ThumbLY * stXInputState.ThumbLY);

		// デッドゾーンを設定
		if (fStickTiltMagnitude > STICK_DEAD_ZONE)
		{
			//正規化した入力方向を取得
			float fNormalizedX = stXInputState.ThumbLY / fStickTiltMagnitude;
			float fNormalizedY = stXInputState.ThumbLX / fStickTiltMagnitude;

			// カメラ方向を考慮して移動ベクトルを回転
			float fInputAngle = atan2(fNormalizedY, fNormalizedX);
			float fPlayerMoveAngle = fInputAngle + camrad;

			//空中での移動速度を設定
			this->PlayerStatusList->SetPlayerNowMoveSpeed(PLAER_DASH_MAX_SPEED);

			//移動の方向と速度をベクトルに設定
			vecPlayerMove.z = -cos(fPlayerMoveAngle) * this->PlayerStatusList->fGetPlayerNowMoveSpeed();
			vecPlayerMove.x = -sin(fPlayerMoveAngle) * this->PlayerStatusList->fGetPlayerNowMoveSpeed();
			//移動の角度を保存する（後の処理に使用）
			this->PlayerStatusList->SetPlayerOldRadian(fPlayerMoveAngle);
			this->PlayerStatusList->SetPlayerAngleX(fPlayerMoveAngle);
		}
	}
	//移動のベクトルを保存する（後の処理に使用）
	this->PlayerStatusList->SetPlayerOldVector(vecPlayerMove);
	this->PlayerStatusList->SetPlayerMoveVector(vecPlayerMove);
	this->vecPosition = VAdd(this->vecPosition, this->PlayerStatusList->vecGetPlayerMoveVector());
	//}

	/* 入力による移動量を取得 */
	//VECTOR vecInput = this->InputList->vecGetGameInputMove();

	/* 移動入力がされているか確認 */
	//if (vecInput.x != 0 || vecInput.z != 0)
	//{
	//	// 移動入力がされている場合
	//	/* 現在の移動速度取得 */
	//	float fSpeed = this->PlayerStatusList->fGetPlayerNowMoveSpeed();

	//	/* 加速度を適用 */
	//	fSpeed += this->PlayerStatusList->fGetPlayerMoveAcceleration();

	//	/* 最大速度を超えていないか確認 */
	//	float fMaxSpeed = this->PlayerStatusList->fGetPlayerMaxMoveSpeed();
	//	if (fSpeed > fMaxSpeed)
	//	{
	//		// 最大速度を超えている場合
	//		/* 最大速度に設定 */
	//		fSpeed = fMaxSpeed;
	//	}

	//	/* 現在速度を更新 */
	//	this->PlayerStatusList->SetPlayerNowMoveSpeed(fSpeed);

	//	/* カメラの水平方向の向きを移動用の向きに設定 */
	//	float fAngleX = this->PlayerStatusList->fGetCameraAngleX();

	//	/* 移動量を算出 */
	//	VECTOR vecMove;
	//	vecMove.x	= +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
	//	vecMove.y	= 0.0f;
	//	vecMove.z	= -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
	//	vecMove		= VScale(vecMove, fSpeed);

	//	/* 移動後の座標を算出 */
	//	VECTOR vecNextPosition = VAdd(this->vecPosition, vecMove);

	//	/* 道中でオブジェクトに接触しているか判定 */
	//	// 制作予定

	//	/* プレイヤーの座標を移動させる */
	//	this->vecPosition = vecNextPosition;

		/* プレイヤーの向きを移動方向に合わせる */
		//float fPlayerAngle = atan2f(vecInput.x, vecInput.z);	// 移動方向の角度(ラジアン)を取得
		//fPlayerAngle = fAngleX - fPlayerAngle;					// カメラの向きと合成
		//this->PlayerStatusList->SetPlayerAngleX(fPlayerAngle);	// プレイヤーの向きを設定
	//}
	

	/* コリジョンを更新 */
	CollisionUpdate();
}

// ジャンプ
void CharacterPlayer::Player_Jump()
{
	/* プレイヤーのジャンプ処理 */

	/* ジャンプ入力がされているか確認 */
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
	{

		// ジャンプ入力がされている場合
		//ジャンプ
		//連続ジャンプ回数の制限以内
		if (this->PlayerStatusList->iGetPlayerJumpCount() <= PLAYER_JUMPING_IN_AIR_LIMIT)
		{
			//ジャンプ速度リセット
			this->PlayerStatusList->SetPlayerJumpSpeed(0);
			//ジャンプの加速度を与える
			this->PlayerStatusList->SetPlayerJumpSpeed(PlayerStatusList->fGetPlayerJumpSpeed() + ACCELERATION(PLAYER_JUMP_SPEED)) ;
			//ジャンプ中のフラグtrue
			this->PlayerStatusList->SetPlayerJumpingFlag(true);
			//連続ジャンプ回数を加算
			this->PlayerStatusList->SetPlayerJumpCount(PlayerStatusList->iGetPlayerJumpCount()+1);
		}

	//	//ジャンプの移動ベクトルを位置ベクトルに反映
		/*this->vecPosition = VAdd(this->vecPosition, vecMove);*/

	//	// 仮で落下速度を-にする処理を行う
	//this->PlayerStatusList->SetPlayerNowFallSpeed(-100.0f);
	}

	//ジャンプ中かつ回避中ではない
	if (this->PlayerStatusList->bGetPlayerJumpingFlag() == true && this->PlayerStatusList->bGetPlayerDodgingFlag() == false)
	{
		//ジャンプ速度に地上の影響を与える
		this->PlayerStatusList->SetPlayerJumpSpeed(this->PlayerStatusList->fGetPlayerJumpSpeed() + ACCELERATION(GRAVITY_SREED * GRAVITY_BUFFER));
		//移動していた方向へ向く
		this->PlayerStatusList->SetPlayerMoveVector(VGet(this->PlayerStatusList->vecGetPlayerOldVector().x, 0 ,this->PlayerStatusList->vecGetPlayerOldVector().z));
		
	}
	//ジャンプ速度をプレイヤー移動ベクトルにセット
	this->PlayerStatusList->SetPlayerMoveVector(VGet(0, this->PlayerStatusList->fGetPlayerJumpSpeed(), 0));
	this->vecPosition = VAdd(this->vecPosition, this->PlayerStatusList->vecGetPlayerMoveVector());
	/* コリジョンを更新 */
	CollisionUpdate();
}

// 重力
void CharacterPlayer::Player_Gravity()
{
	/* プレイヤーの重力処理 */

	/* 落下量取得 */
	float fFallSpeed	=	this->PlayerStatusList->fGetPlayerNowFallSpeed();		// 現時点での加速量取得
	fFallSpeed			+=	this->PlayerStatusList->fGetPlayerFallAcceleration();	// 加速度を加算
	
	/* 重力による移動後の座標を取得 */
	VECTOR vecNextPosition	=	this->vecPosition;
	//vecNextPosition.y		=	this->PlayerStatusList->vecGetPlayerMoveVector().y;
	//vecNextPosition.y = vecNextPosition.y + this->PlayerStatusList->vecGetPlayerMoveVector().y;
	vecNextPosition.y -= this->PlayerStatusList->fGetPlayerNowFallSpeed();
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
				//ジャンプ中のフラグをリセット
				this->PlayerStatusList->SetPlayerJumpingFlag(false);
				//連続ジャンプ回数をリセット
				this->PlayerStatusList->SetPlayerJumpCount(0);
				//ジャンプ中の回避回数をリセット
				this->PlayerStatusList->SetPlayerDodgeWhileJumpingCount(0);

				//ジャンプ速度リセット
				this->PlayerStatusList->SetPlayerJumpSpeed(0);
			}
		}
	}

	/* 着地座標を更新 */
	vecNextPosition.y = fStandPosY;

	/* プレイヤー座標を更新 */
	this->vecPosition = vecNextPosition;

	/* 落下速度を更新 */
	this->PlayerStatusList->SetPlayerNowFallSpeed(fFallSpeed);

	/* コリジョンを更新 */
	CollisionUpdate();
}

// 回避
void CharacterPlayer::Player_Dodg()
{
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE) == true && this->PlayerStatusList->bGetPlayerDodgingFlag() == false && this->PlayerStatusList->iGetPlayerDodgeWhileJumpingCount()< PLAYER_DODGE_IN_AIR_LIMIT)
	{
		//回避

		// 回避フラグをセット
		this->PlayerStatusList->SetPlayerDodgingFlag(true);
		// 回避開始時の時間をリセット
		this->PlayerStatusList->SetPlayerDodgeTime(0.0f);
		//現在の移動方向へ回避
		this->PlayerStatusList->SetPlayerDodgeDirection(VNorm(VGet(this->PlayerStatusList->vecGetPlayerMoveVector().x,0, this->PlayerStatusList->vecGetPlayerMoveVector().z)));
		//回避速度設定
		this->PlayerStatusList->SetPlayerDodgeSpeed(PLAYER_DODGE_SPEED);
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
		this->PlayerStatusList->SetPlayerDodgeTime(this->PlayerStatusList->fGetPlayerDodgeTime() + SECONDS_PER_FRAME);

		// 回避中（設定時間の間）
		if (this->PlayerStatusList->fGetPlayerDodgeTime() <= PLAYER_DODGE_TIME)
		{
			//設定時間かけて回避移動を行う
		// 回避中（設定時間の間）
			VECTOR vecPlayerDodgeMove = VScale(this->PlayerStatusList->vecGetPlayerDodgeDirection(), PLAYER_DODGE_SPEED * (PLAYER_DODGE_TIME - this->PlayerStatusList->fGetPlayerDodgeTime()));
			this->PlayerStatusList->SetPlayerMoveVector(vecPlayerDodgeMove);		
		}
		// 回避終了
		else
		{
			this->PlayerStatusList->SetPlayerDodgingFlag(false);
			this->PlayerStatusList->SetPlayerAfterDodgeFlag(true);

		}
		this->vecPosition = VAdd(this->vecPosition, this->PlayerStatusList->vecGetPlayerMoveVector());
	}
}

void CharacterPlayer::Player_Attack()
{
	/* プレイヤーの攻撃処理 */

	/* 攻撃入力がされているか確認 */
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK) == true)
	{
		this->PlayerStatusList->stPlayerAttackCollisionSqhere.vecSqhere = this->vecPosition;
		// 攻撃入力がされている場合
		// 攻撃処理を行う
		auto& PlatformList = ObjectList->GetEnemyList();

		for (auto* platform : PlatformList)
		{
			if (platform->HitCheck(this->PlayerStatusList->stPlayerAttackCollisionSqhere))
			{
				platform->SetNowHP(platform->iGetNowHP() -1);
			}
			this->PlayerStatusList->iEnemyHP = platform->iGetNowHP();

		}
	}
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
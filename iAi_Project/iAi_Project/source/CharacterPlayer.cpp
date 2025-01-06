/* 2024.12.15 駒沢風助 ファイル作成 */

#include "CharacterPlayer.h"

/* プレイヤークラスの定義 */

// コンストラクタ
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* 初期化 */
	/* データリスト取得 */
	this->InputList			= dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

	/* 仮初期化処理開始 */
	this->iModelHandle = MV1LoadModel("resource/ModelData/Test/Player/Karisotai_1217.mv1");
}

// 更新
void CharacterPlayer::Update()
{
	/* 重力処理 */
	Player_Gravity();

	/* ジャンプ処理 */
	Player_Jump();

	/* 移動処理 */
	Player_Move();
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

	VECTOR vecMove = this->InputList->vecGetGameInputMove();
	DrawFormatString(500, 16 * 9, GetColor(255, 255, 255), "X:%f, Z:%f", vecMove.x, vecMove.z);

	XINPUT_STATE stXInputState;
	GetJoypadXInputState(DX_INPUT_PAD1, &stXInputState);

	DrawFormatString(500, 16 * 10, GetColor(255, 255, 255), "左トリガ : %u", stXInputState.LeftTrigger);
	DrawFormatString(500, 16 * 11, GetColor(255, 255, 255), "右トリガ : %u", stXInputState.RightTrigger);

	float fSpeed = this->PlayerStatusList->fGetPlayerNowMoveSpeed();
	DrawFormatString(500, 16 * 12, GetColor(255, 255, 255), "移動速度 : %f", fSpeed);
}

// 移動
void CharacterPlayer::Player_Move()
{
	/* プレイヤーの移動処理 */

	/* 入力による移動量を取得 */
	VECTOR vecInput = this->InputList->vecGetGameInputMove();

	/* 移動入力がされているか確認 */
	if (vecInput.x != 0 || vecInput.z != 0)
	{
		// 移動入力がされている場合
		/* 現在の移動速度取得 */
		float fSpeed	= this->PlayerStatusList->fGetPlayerNowMoveSpeed();

		/* 加速度を適用 */
		fSpeed += this->PlayerStatusList->fGetPlayerMoveAcceleration();

		/* 最大速度を超えていないか確認 */
		float fMaxSpeed = this->PlayerStatusList->fGetPlayerMaxMoveSpeed();
		if (fSpeed > fMaxSpeed)
		{
			// 最大速度を超えている場合
			/* 最大速度に設定 */
			fSpeed = fMaxSpeed;
		}

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
	}
}

// ジャンプ
void CharacterPlayer::Player_Jump()
{
	/* プレイヤーのジャンプ処理 */

	/* ジャンプ入力がされているか確認 */
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
	{
		// ジャンプ入力がされている場合
		/* ジャンプ処理 */
	}
}

// 重力
void CharacterPlayer::Player_Gravity()
{
	/* プレイヤーの重力処理 */

}
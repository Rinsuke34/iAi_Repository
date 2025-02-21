/* 2025.02.02 ファイル作成 駒沢風助 */

#include "SceneStage.h"

/* ステージクラスの定義(カメラ制御部分) */

// カメラ設定
void SceneStage::SetCamera()
{
	/* グローバルアンビエントライトカラーを赤色に設定 */
	// ※デフォルトの黒色だと暗すぎるので赤色に変更
	SetGlobalAmbientLight(GetColorF(1.0f, 0.0f, 0.0f, 0.0f));

	/* カメラの手前と奥のクリップ距離を設定 */
	// ※スカイスフィア半径(25000)から余裕を少し持たせた値に仮設定
	SetCameraNearFar(100.0f, 30000.f);

	///* フォグを有効化 */
	//SetFogEnable(TRUE);

	///* フォグの色を紫色にする */
	//SetFogColor(126, 0, 126);

	///* フォグの距離を設定 */
	//SetFogStartEnd(15000.f, 20000.f);

	/* カメラモードが変更されているか確認 */
	if (this->PlayerStatusList->iGetCameraMode() != this->PlayerStatusList->iGetCameraMode_Old())
	{
		// 変更されている場合
		/* カメラ座標の線形保管用カウントを初期化する */
		this->PlayerStatusList->SetCameraPositionLeapCount(0);

		/* 現在のカメラの座標を移動前座標として設定する */
		this->PlayerStatusList->SetCameraPosition_Start(this->PlayerStatusList->vecGetCameraPosition());
	}

	/* カメラ設定で使用する変数の定義 */
	float fChangeCameraRatio = 1.f;	// 入力によるカメラ回転倍率

	/* カメラモードに応じて処理を変更 */
	switch (this->PlayerStatusList->iGetCameraMode())
	{
		/* フリー */
		case CAMERA_MODE_FREE:
			/* カメラ設定 */
			SetCamera_Free();
			break;

		/* 固定 */
		case CAMERA_MODE_LOCK:
			/* カメラ回転倍率を変更 */
			fChangeCameraRatio = 0.f;
			break;

		/* 構え(ズーム) */
		case CAMERA_MODE_AIM_MELEE:
			/* カメラ回転倍率を変更 */
			fChangeCameraRatio = 0.5f;

			/* カメラ設定 */
			SetCamera_Aim_Melee();
			break;

		/* 構え(クナイ構え) */
		case CAMERA_MODE_AIM_KUNAI:
			/* カメラ回転倍率を変更 */
			fChangeCameraRatio = 0.5f;

			/* カメラ設定 */
			SetCamera_Aim_Kunai();
			break;
	}

	/* 入力によるカメラ回転の取得処理を実施 */
	CameraRotateUpdata(fChangeCameraRatio);

	/* カメラ座標の補正 */
	// ※一瞬で切り替わると違和感があるため、カメラ座標に補間処理を行う
	CameraSmoothing();

	/* カメラ設定 */
	SetCameraPositionAndTargetAndUpVec(this->PlayerStatusList->vecGetCameraPosition(), this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraUp());

	/* 現時点でのカメラモードを保存 */
	this->PlayerStatusList->SetCameraMode_Old(this->PlayerStatusList->iGetCameraMode());
}

// 入力によるカメラ回転量取得
void SceneStage::CameraRotateUpdata(float fRate)
{
	// 引数
	// fRate	:	回転量倍率(オプション設定による倍率とは別物)

	/* 現在の回転量等を取得 */
	float fCameraAngleX						= this->PlayerStatusList->fGetCameraAngleX();						// X軸回転量
	float fCameraAngleY						= this->PlayerStatusList->fGetCameraAngleY();						// Y軸回転量
	float fCameraRotationalSpeed_Controller	= this->PlayerStatusList->fGetCameraRotationalSpeed_Controller();	// 回転速度(コントローラー)
	float fCameraRotationalSpeed_Mouse		= this->PlayerStatusList->fGetCameraRotationalSpeed_Mouse();		// 回転速度(マウス)

	/* 入力からカメラ回転量を取得 */
	/* マウス */
	fCameraAngleX -= gstKeyboardInputData.iMouseMoveX * fCameraRotationalSpeed_Mouse * fRate;
	fCameraAngleY -= gstKeyboardInputData.iMouseMoveY * fCameraRotationalSpeed_Mouse * fRate;

	/* コントローラー */
	fCameraAngleX += fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickX[INPUT_RIGHT]) * fRate;
	fCameraAngleY += fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickY[INPUT_RIGHT]) * fRate;

	/* Y軸の回転角度制限 */
	float fAngleLimitUp		= this->PlayerStatusList->fGetCameraAngleLimitUp();		// 上方向の制限角度
	float fAngleLimitDown	= this->PlayerStatusList->fGetCameraAngleLimitDown();	// 下方向の制限角度

	if (fCameraAngleY > fAngleLimitUp)		{ fCameraAngleY = fAngleLimitUp; }		// 上方向の制限角度を超えたら制限角度に設定
	if (fCameraAngleY < fAngleLimitDown)	{ fCameraAngleY = fAngleLimitDown; }	// 下方向の制限角度を超えたら制限角度に設定

	/* 回転量を更新 */
	this->PlayerStatusList->SetCameraAngleX(fCameraAngleX);
	this->PlayerStatusList->SetCameraAngleY(fCameraAngleY);
}

// カメラ設定(フリーモード)
void SceneStage::SetCamera_Free()
{
	/* 現在の回転量等を取得 */
	float fCameraAngleX = this->PlayerStatusList->fGetCameraAngleX();						// X軸回転量
	float fCameraAngleY = this->PlayerStatusList->fGetCameraAngleY();						// Y軸回転量

	/* プレイヤー座標取得 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* カメラ注視点設定 */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, PLAYER_HEIGHT, 0));
	this->PlayerStatusList->SetCameraTarget(vecCameraTarget);

	vecCameraTarget.y += 20.f;

	/* カメラ座標設定 */
	float fRadius	= this->PlayerStatusList->fGetCameraRadius();			// 注視点からの距離
	float fCameraX	= fRadius * -sinf(fCameraAngleX) + vecCameraTarget.x;	// X座標
	float fCameraY	= fRadius * -sinf(fCameraAngleY) + vecCameraTarget.y;	// Y座標
	float fCameraZ	= fRadius * +cosf(fCameraAngleX) + vecCameraTarget.z;	// Z座標

	this->PlayerStatusList->SetCameraPosition_Target(VGet(fCameraX, fCameraY, fCameraZ));
}

// カメラ設定(構え(近接攻撃構え))
void SceneStage::SetCamera_Aim_Melee()
{
	/* 現在の回転量等を取得 */
	float fCameraAngleX = this->PlayerStatusList->fGetCameraAngleX();						// X軸回転量
	float fCameraAngleY = this->PlayerStatusList->fGetCameraAngleY();						// Y軸回転量

	/* プレイヤー座標取得 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* カメラ注視点設定 */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, PLAYER_HEIGHT, 0));
	this->PlayerStatusList->SetCameraTarget(vecCameraTarget);

	vecCameraTarget.y += 20.f;

	/* カメラ座標設定 */
	//float fRadius = this->PlayerStatusList->fGetCameraRadius();			// 注視点からの距離
	float fRadius = 200.f;			// 注視点からの距離
	float fCameraX = fRadius * -sinf(fCameraAngleX) + vecCameraTarget.x;	// X座標
	float fCameraY = fRadius * -sinf(fCameraAngleY) + vecCameraTarget.y;	// Y座標
	float fCameraZ = fRadius * +cosf(fCameraAngleX) + vecCameraTarget.z;	// Z座標

	this->PlayerStatusList->SetCameraPosition_Target(VGet(fCameraX, fCameraY, fCameraZ));
}

// カメラ設定(構え(クナイ構え))
void SceneStage::SetCamera_Aim_Kunai()
{
	/* 現在の回転量等を取得 */
	float fCameraAngleX = this->PlayerStatusList->fGetCameraAngleX();		// X軸回転量
	float fCameraAngleY = this->PlayerStatusList->fGetCameraAngleY();		// Y軸回転量

	/* プレイヤー座標取得 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* カメラ注視点設定 */
	float fRadius	= 1000;				// 注視点からの距離
	float fCameraX	= fRadius * +sinf(fCameraAngleX) + vecPlayerPos.x;	// X座標
	float fCameraY	= fRadius * +sinf(fCameraAngleY) + vecPlayerPos.y;	// Y座標
	float fCameraZ	= fRadius * -cosf(fCameraAngleX) + vecPlayerPos.z;	// Z座標

	this->PlayerStatusList->SetCameraTarget(VGet(fCameraX, fCameraY, fCameraZ));

	/* カメラ座標設定 */
	this->PlayerStatusList->SetCameraPosition_Target(VAdd(vecPlayerPos, VGet(0, PLAYER_HEIGHT, 0)));
}

// カメラ補正
void SceneStage::CameraSmoothing()
{
	/* カメラ線形補間用カウントを取得 */
	int iCameraPositionLeapCount = this->PlayerStatusList->iGetCameraPositionLeapCount();

	/* カメラ線形補完用カウントが最大値に達しているか */
	if (iCameraPositionLeapCount < CAMERA_POSITION_LEAP_COUNT_MAX)
	{
		// 最大値に達していない場合
		/* カメラ線形補間の割合を取得 */
		float fLeapRatio = ((float)iCameraPositionLeapCount / (float)CAMERA_POSITION_LEAP_COUNT_MAX);

		/* カメラの座標(線形補間後)を算出 */
		VECTOR vecStart		= this->PlayerStatusList->vecGetCameraPosition_Start();		// 線形補完の移動前座標
		VECTOR vecTarget	= this->PlayerStatusList->vecGetCameraPosition_Target();	// 線形補完の移動後座標
		VECTOR vecCameraPosition;
		vecCameraPosition.x = vecStart.x + (vecTarget.x - vecStart.x) * fLeapRatio;
		vecCameraPosition.y = vecStart.y + (vecTarget.y - vecStart.y) * fLeapRatio;
		vecCameraPosition.z = vecStart.z + (vecTarget.z - vecStart.z) * fLeapRatio;

		/* カメラの座標(線形補間後)を現在のカメラ座標に設定 */
		this->PlayerStatusList->SetCameraPosition(vecCameraPosition);

		/* カウントを加算して設定する */
		this->PlayerStatusList->SetCameraPositionLeapCount(iCameraPositionLeapCount + 1);
	}
	else
	{
		// 最大値に達している場合
		/* カメラの座標(移動後)を現在のカメラ座標に設定 */
		this->PlayerStatusList->SetCameraPosition(this->PlayerStatusList->vecGetCameraPosition_Target());

		this->PlayerStatusList->SetCameraPosition_Start(this->PlayerStatusList->vecGetCameraPosition_Target());
	}
}

/* 2025.02.02 ファイル作成 駒沢風助 */
/* 2025.02.23 菊池雅道	カメラ制御処理修正 */
/* 2025.03.06 菊池雅道	カメラ制御処理修正 */
/* 2025.03.16 駒沢風助	カメラ制御処理修正 */

#include "SceneStage.h"

/* ステージクラスの定義(カメラ制御部分) */

/* 2025.03.06 菊池雅道	カメラ制御処理修正 開始 */
// カメラ設定準備
void SceneStage::SetCamera_Setup()
{
	/* カメラモードが変更、あるいはカメラ固定座標が変更されているか確認 */
	if ((this->StageStatusList->iGetCameraMode() != this->StageStatusList->iGetCameraMode_Old()) ||
		(this->iNowCameraFixedPositionNo != this->iOldCameraFixedPositionNo))
	{
		// 変更されている場合
		/* カメラの線形保管用カウントを初期化する */
		this->StageStatusList->SetCameraPositionLeapCount(0);
		this->StageStatusList->SetCameraTargetLeapCount(0);

		/* 現在のカメラの座標を移動前座標として設定する */
		this->StageStatusList->SetCameraPosition_Start(this->StageStatusList->vecGetCameraPosition());
		this->StageStatusList->SetCameraTarget_Start(this->StageStatusList->vecGetCameraTarget());
	}

	/* カメラ設定で使用する変数の定義 */
	int iCameraType			= INPUT_CAMERA_NORMAL;						// カメラ移動タイプ
	int iCameraLeapCountMax	= CAMERA_POSITION_LEAP_COUNT_MAX_NORMAL;	// カメラ座標の補間カウント最大値

	/* カメラモードに応じて処理を変更 */
	switch (this->StageStatusList->iGetCameraMode())
	{
		/* フリー */
		case CAMERA_MODE_NORMAL:
			/* カメラ設定 */
			SetCamera_Free();
			
			/* カメラ座標の補間カウント最大値をフリーの値に設定 */
			iCameraLeapCountMax = CAMERA_POSITION_LEAP_COUNT_MAX_NORMAL;
			break;

		/* 固定 */
		case CAMERA_MODE_LOCK:
			/* カメラ移動タイプを"無し"に設定 */
			iCameraType = INPUT_CAMERA_NONE;
			break;

		/* 構え(ズーム) */
		case CAMERA_MODE_AIM_MELEE:
			/* カメラ移動タイプを"エイム"に設定 */
			iCameraType = INPUT_CAMERA_AIM;

			/* カメラ座標の補間カウント最大値を近距離攻撃(強)の値に設定 */
			iCameraLeapCountMax = CAMERA_POSITION_LEAP_COUNT_MAX_MELEE;
			
			/* カメラ設定 */
			SetCamera_Aim_Melee();
			break;

		/* 構え(クナイ構え) */
		case CAMERA_MODE_AIM_KUNAI:
			/* カメラ移動タイプを"エイム"に設定 */
			iCameraType = INPUT_CAMERA_AIM;

			/* カメラ座標の補間カウント最大値を遠距離攻撃の値に設定 */
			iCameraLeapCountMax = CAMERA_POSITION_LEAP_COUNT_MAX_PROJECTILE;

			/* カメラ設定 */
			SetCamera_Aim_Kunai();
			break;

		/* タイトル */
		case CAMERA_MODE_TITLE:
			/* カメラ移動タイプを"無し"に設定 */
			iCameraType = INPUT_CAMERA_NONE;

			/* カメラ座標の補間カウント最大値をタイトルの値に設定 */
			iCameraLeapCountMax = CAMERA_POSITION_LEAP_CONT_MAX_TITLE;
			/* カメラ設定 */
			SetCamera_Title();
			break;

		/* ステージクリア */
		case CAMERA_MODE_STAGECLEAR:
			/* カメラ移動タイプを"無し"に設定 */
			iCameraType = INPUT_CAMERA_NONE;

			/* カメラ座標の補間カウント最大値をステージクリアの値に設定 */
			iCameraLeapCountMax = CAMERA_POSITION_LEAP_COUNT_MAX_STAGECLEAR;

			/* カメラ設定 */
			SetCamera_StageClear();
			break;

		/* ステージ開始 */
		case CAMERA_MODE_STAGESTART:
			/* カメラ移動タイプを"無し"に設定 */
			iCameraType = INPUT_CAMERA_NONE;

			/* カメラ座標の補間カウント最大値をステージクリアの値に設定 */
			iCameraLeapCountMax = CAMERA_POSITION_LEAP_COUNT_MAX_STAGESTART;

			/* カメラ設定 */
			SetCamera_StageStart();
			break;

		/* ステージ開始(プレイヤークローズアップ) */
		case CAMERA_MODE_STAGESTART_CLOSE_UP:
			/* カメラ移動タイプを"無し"に設定 */
			iCameraType = INPUT_CAMERA_NONE;

			/* カメラ設定 */
			SetCamera_StageStart_CloseUp();
			break;

		/* 落下 */
		case CAMERA_MODE_FALL:
			/* カメラ移動タイプを"無し"に設定 */
			iCameraType = INPUT_CAMERA_NONE;

			/* カメラ設定 */
			SetCamera_Fall();
			break;
	}

	// 反映する場合
	/* 入力によるカメラ回転の取得処理を実施 */
	CameraRotateUpdata(iCameraType);

	/* カメラ座標の補正 */
	// ※一瞬で切り替わると違和感があるため、カメラ座標に補間処理を行う
	CameraSmoothing(iCameraLeapCountMax);

	/* 現時点でのカメラモードを保存 */
	this->StageStatusList->SetCameraMode_Old(this->StageStatusList->iGetCameraMode());

	/* 現時点でのカメラ固定座標番号を保存 */
	this->iOldCameraFixedPositionNo = this->iNowCameraFixedPositionNo;
}
/* 2025.03.06 菊池雅道	カメラ制御処理修正 終了 */

// カメラ設定
void SceneStage::SetCmaera()
{
	/* グローバルアンビエントライトカラーを赤色に設定 */
	// ※デフォルトの黒色だと暗すぎるので赤色に変更
	SetGlobalAmbientLight(GetColorF(0.5f, 0.5f, 0.5f, 0.0f));

	/* カメラの手前と奥のクリップ距離を設定 */
	// ※スカイスフィア半径(25000)から余裕を少し持たせた値に仮設定
	SetCameraNearFar(INIT_CAMERA_NEAR, INIT_CAMERA_FAR);

	/* フォグの範囲を設定 */
	SetFogEnable(TRUE);
	SetFogColor(256, 44, 42);
	SetFogStartEnd(INIT_CAMERA_FOG_START, INIT_CAMERA_FOG_END);

	/* カメラ設定 */
	SetCameraPositionAndTargetAndUpVec(this->StageStatusList->vecGetCameraPosition(), this->StageStatusList->vecGetCameraTarget(), this->StageStatusList->vecGetCameraUp());

	/* 3Dサウンドのリスナー位置とリスナー前方位置を設定 */
	Set3DSoundListenerPosAndFrontPos_UpVecY(this->StageStatusList->vecGetCameraPosition(), this->StageStatusList->vecGetCameraTarget());
}

// 入力によるカメラ回転量取得
void SceneStage::CameraRotateUpdata(int iCameraType)
{
	// 引数
	// iCameraType	:	カメラ移動タイプ

	/* 現在の回転量等を取得 */
	float fCameraAngleX						= this->StageStatusList->fGetCameraAngleX();						// X軸回転量
	float fCameraAngleY						= this->StageStatusList->fGetCameraAngleY();						// Y軸回転量
	float fCameraRotationalSpeed_Controller	= this->StageStatusList->fGetCameraRotationalSpeed_Controller();	// 回転速度(コントローラー)
	float fCameraRotationalSpeed_Mouse		= this->StageStatusList->fGetCameraRotationalSpeed_Mouse();			// 回転速度(マウス)

	/* オプションから回転倍率を取得 */
	float	fCameraSensitive[INPUT_TYPE_MAX];	// 回転量倍率
	switch (iCameraType)
	{
		// ノーマル状態
		case INPUT_CAMERA_NORMAL:
			/* 入力感度をオプションから取得 */
			fCameraSensitive[INPUT_TYPE_CONTROLLER]	= OptionList->fGetCameraSensitivity(INPUT_TYPE_CONTROLLER,	INPUT_CAMERA_MODE_NORMAL);
			fCameraSensitive[INPUT_TYPE_MOUSE]		= OptionList->fGetCameraSensitivity(INPUT_TYPE_MOUSE,		INPUT_CAMERA_MODE_NORMAL);
			break;

		// エイム状態
		case INPUT_CAMERA_AIM:
			/* 入力感度をオプションから取得 */
			fCameraSensitive[INPUT_TYPE_CONTROLLER]	= OptionList->fGetCameraSensitivity(INPUT_TYPE_CONTROLLER,	INPUT_CAMERA_MODE_AIM);
			fCameraSensitive[INPUT_TYPE_MOUSE]		= OptionList->fGetCameraSensitivity(INPUT_TYPE_MOUSE,		INPUT_CAMERA_MODE_AIM);
			break;

		// 無し(入力受付無し)状態
		case INPUT_CAMERA_NONE:
			/* 入力感度を0に設定 */
			fCameraSensitive[INPUT_TYPE_CONTROLLER]	= 0.f;
			fCameraSensitive[INPUT_TYPE_MOUSE]		= 0.f;
			break;
	}

	/* オプションから反転設定を取得 */
	int		iCameraReverse[INPUT_TYPE_MAX][AXIS_MAX];	// 反転設定(1なら通常、-1なら反転)
	for (int i = 0; i < INPUT_TYPE_MAX; ++i)
	{
		for (int j = 0; j < AXIS_MAX; ++j)
		{
			/* 反転設定であるか確認 */
			// ※iは入力タイプ,jは軸
			if (OptionList->bGetCameraInversion(i, j) == true)
			{
				// 反転設定である場合
				iCameraReverse[i][j] = -1;
			}
			else
			{
				// 通常設定である場合
				iCameraReverse[i][j] = 1;
			}
		}
	}

	/* 入力からカメラ回転量を取得 */
	/* マウス */
	fCameraAngleX -= gstKeyboardInputData.iMouseMoveX * fCameraRotationalSpeed_Mouse * fCameraSensitive[INPUT_TYPE_MOUSE] * iCameraReverse[INPUT_TYPE_MOUSE][AXIS_X];
	fCameraAngleY -= gstKeyboardInputData.iMouseMoveY * fCameraRotationalSpeed_Mouse * fCameraSensitive[INPUT_TYPE_MOUSE] * iCameraReverse[INPUT_TYPE_MOUSE][AXIS_Y];

	/* コントローラー */
	fCameraAngleX -= fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickX[INPUT_RIGHT]) * fCameraSensitive[INPUT_TYPE_CONTROLLER] * iCameraReverse[INPUT_TYPE_CONTROLLER][AXIS_X];
	fCameraAngleY += fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickY[INPUT_RIGHT]) * fCameraSensitive[INPUT_TYPE_CONTROLLER] * iCameraReverse[INPUT_TYPE_CONTROLLER][AXIS_Y];

	/* Y軸の回転角度制限 */
	float fAngleLimitUp		= this->StageStatusList->fGetCameraAngleLimitUp();		// 上方向の制限角度
	float fAngleLimitDown	= this->StageStatusList->fGetCameraAngleLimitDown();	// 下方向の制限角度

	if (fCameraAngleY > fAngleLimitUp)		{ fCameraAngleY = fAngleLimitUp; }		// 上方向の制限角度を超えたら制限角度に設定
	if (fCameraAngleY < fAngleLimitDown)	{ fCameraAngleY = fAngleLimitDown; }	// 下方向の制限角度を超えたら制限角度に設定

	/* 回転量を更新 */
	this->StageStatusList->SetCameraAngleX(fCameraAngleX);
	this->StageStatusList->SetCameraAngleY(fCameraAngleY);
}

// カメラ設定(フリーモード)
void SceneStage::SetCamera_Free()
{
	/* 現在の回転量等を取得 */
	float fCameraAngleX = this->StageStatusList->fGetCameraAngleX();						// X軸回転量
	float fCameraAngleY = this->StageStatusList->fGetCameraAngleY();						// Y軸回転量

	/* プレイヤー座標取得 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* カメラ注視点算出 */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, PLAYER_HEIGHT, 0));

	/* カメラ座標算出 */
	VECTOR vecCameraPosition;
	float fRadius		= this->StageStatusList->fGetCameraRadius();			// 注視点からの距離
	vecCameraTarget.y	+= 20.f;
	vecCameraPosition.x	= fRadius * -sinf(fCameraAngleX) + vecCameraTarget.x;	// X座標
	vecCameraPosition.y	= fRadius * -sinf(fCameraAngleY) + vecCameraTarget.y;	// Y座標
	vecCameraPosition.z	= fRadius * +cosf(fCameraAngleX) + vecCameraTarget.z;	// Z座標

	/* カメラ注視点からカメラ座標までの線分をコリジョンとして作成 */
	COLLISION_LINE stVerticalCollision;
	stVerticalCollision.vecLineStart	= vecCameraTarget;
	stVerticalCollision.vecLineEnd		= vecCameraPosition;

	/* 最長距離 */
	// カメラ注視点からカメラ座標までの距離
	float fDistance = VSize(VSub(vecCameraPosition, vecCameraTarget));

	/* プラットフォームと接触するか確認 */
	for (auto* platform : ObjectList->GetPlatformList())
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stVerticalCollision);

		/* 接触しているか確認 */
		if (stHitPolyDim.HitFlag == TRUE)
		{
			// 接触している場合
			/* 接触した座標を取得 */
			VECTOR vecHitPosition = stHitPolyDim.HitPosition;

			/* カメラ注視点から接触した座標までの距離を取得 */
			float fHitDistance = VSize(VSub(vecHitPosition, vecCameraTarget));

			/* 接触した座標までの距離が最長距離より短いか確認 */
			if (fHitDistance < fDistance)
			{
				// 接触した座標までの距離が最長距離より短い場合
				/* カメラ座標を接触した座標に設定 */
				vecCameraPosition = vecHitPosition;

				/* 最長距離を更新 */
				fDistance = fHitDistance;
			}
		}
	}

	/* カメラ注視点を設定 */
	this->StageStatusList->SetCameraTarget_Target(vecCameraTarget);

	/* カメラ座標を設定 */
	this->StageStatusList->SetCameraPosition_Target(vecCameraPosition);
}

// カメラ設定(構え(近接攻撃構え))
void SceneStage::SetCamera_Aim_Melee()
{
	/* 現在の回転量等を取得 */
	float fCameraAngleX = this->StageStatusList->fGetCameraAngleX();						// X軸回転量
	float fCameraAngleY = this->StageStatusList->fGetCameraAngleY();						// Y軸回転量

	/* プレイヤー座標取得 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* カメラ注視点設定 */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, PLAYER_HEIGHT, 0));
	this->StageStatusList->SetCameraTarget_Target(vecCameraTarget);

	/* カメラ座標設定 */
	float fRadius = 200.f;			// 注視点からの距離

	/* カメラ線形補間用カウントを取得 */
	int iCameraPositionLeapCount = this->StageStatusList->iGetCameraPositionLeapCount();

	/* カメラ座標のX,Z軸を設定 */
	float fCameraX = fRadius * -sinf(fCameraAngleX) + vecCameraTarget.x;	// X座標
	float fCameraZ = fRadius * +cosf(fCameraAngleX) + vecCameraTarget.z;	// Z座標

	float fCameraY = 0;

	/* カメラY座標を設定 */
	{
		/* カメラ線形補完用カウントが最大値に達しているか確認 */
		if (iCameraPositionLeapCount < CAMERA_POSITION_LEAP_COUNT_MAX_MELEE)
		{
			// 達していない場合
			/* Y座標を固定の値に設定 */
			fCameraY = vecCameraTarget.y;

			/* Y軸の回転量を初期化 */
			this->StageStatusList->SetCameraAngleY(0.f);
		}
		else
		{
			// 達している場合
			/* Y座標を回転量に合わせて設定 */
			fCameraY = fRadius * -sinf(fCameraAngleY) + vecCameraTarget.y;
		}
	}

	/* カメラ座標設定 */
	this->StageStatusList->SetCameraPosition_Target(VGet(fCameraX, fCameraY, fCameraZ));
}

/* 2025.02.23 菊池雅道	カメラ制御処理修正 開始 */
// カメラ設定(構え(クナイ構え))
void SceneStage::SetCamera_Aim_Kunai()
{
	/* 現在の回転量等を取得 */
	float fCameraAngleX = this->StageStatusList->fGetCameraAngleX();		// X軸回転量
	float fCameraAngleY = this->StageStatusList->fGetCameraAngleY();		// Y軸回転量

	/* プレイヤー座標取得 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* カメラ注視点設定 */
	float fRadius	= 1000;				// 注視点からの距離
	float fCameraX	= fRadius * +sinf(fCameraAngleX) + vecPlayerPos.x;	// X座標
	float fCameraY	= fRadius * +sinf(fCameraAngleY) + vecPlayerPos.y;	// Y座標
	float fCameraZ	= fRadius * -cosf(fCameraAngleX) + vecPlayerPos.z;	// Z座標

	this->StageStatusList->SetCameraTarget_Target(VGet(fCameraX, fCameraY, fCameraZ));

	
	// プレイヤーの右斜め後ろにカメラを配置する

	/* カメラの基本の高さ */ 
	float fHeightOffset = 120.0f; 
	
	// プレイヤーが見切れないように角度に応じて高さを変化させる
	/* 上下角度に応じた補正 */ 
	float fHeightCorrection = fHeightOffset + 100.0f * -sinf(fCameraAngleY);

	// プレイヤーの向きに応じてカメラの位置を設定する
	/* プレイヤーモデルの初期の向きがZ軸に対してマイナス方向を向いているとする */
	/* カメラの位置ベクトル */
	VECTOR vecCameraPos = { 0,0,-1 };
	
	/* プレイヤーの角度からY軸の回転行列を求める */
	MATRIX matPlayerRotation = MGetRotY(-(this->PlayerStatusList->fGetPlayerAngleX()));

	/* カメラ位置の水平方向の平行移動行列 */
	MATRIX matHorizontalOffset = MGetTranslate(VGet(-100.0f, 0, 150.0f));

	/* 行列を乗算しカメラ位置の行列を求める */
	MATRIX matCameraPos = MMult(matHorizontalOffset, matPlayerRotation);

	/* 行列をベクトルに変換 */
	vecCameraPos = VTransform(vecCameraPos, matCameraPos);

	/* カメラの高さを設定 */
	vecCameraPos.y = fHeightCorrection;

	/* カメラ座標設定 */
	this->StageStatusList->SetCameraPosition_Target(VAdd(vecPlayerPos, vecCameraPos));
}
/* 2025.02.23 菊池雅道	カメラ制御処理修正 終了 */

// カメラ設定(タイトル)
void SceneStage::SetCamera_Title()
{
	/* カメラの注視点設定 */
	this->StageStatusList->SetCameraTarget_Target(this->vecCameraPositionInfo[iNowCameraFixedPositionNo].vecTarget);

	/* カメラの座標設定 */
	this->StageStatusList->SetCameraPosition_Target(this->vecCameraPositionInfo[iNowCameraFixedPositionNo].vecPosition);
}

// カメラ設定(ステージクリア)
void SceneStage::SetCamera_StageClear()
{
	/* プレイヤー座標取得 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* カメラ注視点取得 */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, CAMERA_CLOSEUP_POSITION_HEIGHT, 0));

	/* クリア時カウントが"カメラ回転"に設定されたカウントであるか確認 */
	if ((STAGECLEAR_COUNT_CAMERA_TRUN_FAST <= this->iStageClear_Count) && (this->iStageClear_Count <= STAGECLEAR_COUNT_CAMERA_TRUN_LAST))
	{
		/* カメラ注視点設定 */
		this->StageStatusList->SetCameraTarget(vecCameraTarget);
		this->StageStatusList->SetCameraTarget_Start(vecCameraTarget);
		this->StageStatusList->SetCameraTarget_Target(vecCameraTarget);

		float fRadius = 200.f;
		float fCameraX = fRadius * +sinf(PI / 4) + vecPlayerPos.x;	// X座標
		float fCameraY = fRadius * +sinf(PI / 8) + vecPlayerPos.y;	// Y座標
		float fCameraZ = fRadius * -cosf(PI / 4) + vecPlayerPos.z;	// Z座標

		this->StageStatusList->SetCameraPosition(VGet(fCameraX, fCameraY, fCameraZ));
		this->StageStatusList->SetCameraPosition_Start(VGet(fCameraX, fCameraY, fCameraZ));
		this->StageStatusList->SetCameraPosition_Target(VGet(fCameraX, fCameraY, fCameraZ));

	}
	else if (this->iStageClear_Count > STAGECLEAR_COUNT_CAMERA_TRUN_LAST)
	{
		/* カメラ注視点設定 */
		this->StageStatusList->SetCameraTarget(vecCameraTarget);
		this->StageStatusList->SetCameraTarget_Start(vecCameraTarget);
		this->StageStatusList->SetCameraTarget_Target(vecCameraTarget);

		float fRadius = 170.f;
		float fCameraX = fRadius * +sinf(PI * 3 / 3)		+ vecPlayerPos.x;	// X座標
		float fCameraY = fRadius * +sinf(0) + PLAYER_HEIGHT + vecPlayerPos.y;	// Y座標
		float fCameraZ = fRadius * -cosf(PI * 3 / 4)		+ vecPlayerPos.z;	// Z座標

		this->StageStatusList->SetCameraPosition(VGet(fCameraX, fCameraY, fCameraZ));
		this->StageStatusList->SetCameraPosition_Start(VGet(fCameraX, fCameraY, fCameraZ));
		this->StageStatusList->SetCameraPosition_Target(VGet(fCameraX, fCameraY, fCameraZ));
	}
}

/* カメラ設定(ステージ開始) */
void SceneStage::SetCamera_StageStart()
{
	/* 現在のカメラ固定座標番号に対しての補間が完了しているか確認 */
	if (this->StageStatusList->iGetCameraPositionLeapCount() >= CAMERA_POSITION_LEAP_COUNT_MAX_STAGESTART)
	{
		// 完了している場合
		/* ターゲットとするカメラ固定座標番号を更新 */
		/* ターゲットとしているカメラ固定座標番号を保存 */
		this->iNowCameraFixedPositionNo += 1;

		/* 現在の座標を補間の移動前地点に設定する */
		this->StageStatusList->SetCameraPosition_Start(this->StageStatusList->vecGetCameraPosition());
		this->StageStatusList->SetCameraTarget_Start(this->StageStatusList->vecGetCameraTarget());

		/* カメラの線形保管用カウントを初期化する */
		this->StageStatusList->SetCameraPositionLeapCount(0);
		this->StageStatusList->SetCameraTargetLeapCount(0);
	}

	/* カメラ固定座標の値が最大値を超えていないか確認 */
	if (this->iNowCameraFixedPositionNo <= this->iMaxCameraFixedPositionNo )
	{
		// 超えている場合
		/* カメラの注視点設定 */
		this->StageStatusList->SetCameraTarget_Target(this->vecCameraPositionInfo[iNowCameraFixedPositionNo + 1].vecTarget);

		/* カメラの座標設定 */
		this->StageStatusList->SetCameraPosition_Target(this->vecCameraPositionInfo[iNowCameraFixedPositionNo + 1].vecPosition);
	}
}

// カメラ設定(ステージ開始(プレイヤークローズアップ))
void SceneStage::SetCamera_StageStart_CloseUp()
{
	/* プレイヤー座標取得 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* カメラ注視点設定 */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, CAMERA_CLOSEUP_POSITION_HEIGHT, 0));
	this->StageStatusList->SetCameraTarget_Target(vecCameraTarget);

	float fRadius = 200.f;
	float fCameraX	= fRadius * +sinf(0) + vecCameraTarget.x;	// X座標
	float fCameraY	= fRadius * -sinf(0) + vecCameraTarget.y;	// Y座標
	float fCameraZ	= fRadius * -cosf(0) + vecCameraTarget.z;	// Z座標

	/* カメラ座標設定 */
	this->StageStatusList->SetCameraPosition_Target(VGet(fCameraX, fCameraY, fCameraZ));
}

// カメラ設定(プレイヤー落下時)
void SceneStage::SetCamera_Fall()
{
	/* プレイヤー座標取得 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* カメラ注視点算出 */
	// ※カメラ座標の変更は行わない
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, PLAYER_HEIGHT, 0));
	this->StageStatusList->SetCameraTarget_Target(vecCameraTarget);
}

/* 2025.03.06 菊池雅道	カメラ制御処理修正 開始 */
/* 2025.03.16 駒沢風助	カメラ制御処理修正 開始 */
// カメラ補正
void SceneStage::CameraSmoothing(int iCameraLeapCountMax)
{
	/* カメラ位置 */
	{
		/* カメラ線形補間用カウントを取得 */
		int iCameraPositionLeapCount = this->StageStatusList->iGetCameraPositionLeapCount();

		/* カメラ線形補完用カウントが最大値に達しているか */
		if (iCameraPositionLeapCount < iCameraLeapCountMax)
		{
			// 最大値に達していない場合
			/* カメラ線形補間の割合を取得 */
			float fLeapRatio = ((float)iCameraPositionLeapCount / (float)iCameraLeapCountMax);

			/* カメラの座標(線形補間後)を算出 */
			VECTOR vecStart		= this->StageStatusList->vecGetCameraPosition_Start();		// 線形補完の移動前座標
			VECTOR vecTarget	= this->StageStatusList->vecGetCameraPosition_Target();		// 線形補完の移動後座標
			VECTOR vecCameraPosition;
			vecCameraPosition.x = vecStart.x + (vecTarget.x - vecStart.x) * fLeapRatio;
			vecCameraPosition.y = vecStart.y + (vecTarget.y - vecStart.y) * fLeapRatio;
			vecCameraPosition.z = vecStart.z + (vecTarget.z - vecStart.z) * fLeapRatio;

			/* カメラの座標(線形補間後)を現在のカメラ座標に設定 */
			this->StageStatusList->SetCameraPosition(vecCameraPosition);

			/* カウントを加算して設定する */
			this->StageStatusList->SetCameraPositionLeapCount(iCameraPositionLeapCount + 1);
		}
		else
		{
			// 最大値に達している場合
			/* カメラの座標(移動後)を現在のカメラ座標に設定 */
			this->StageStatusList->SetCameraPosition(this->StageStatusList->vecGetCameraPosition_Target());

			this->StageStatusList->SetCameraPosition_Start(this->StageStatusList->vecGetCameraPosition_Target());
		}
	}

	/* カメラ注視点 */
	{
		/* カメラ線形補間用カウントを取得 */
		int iCameraTargetLeapCount = this->StageStatusList->iGetCameraTargetLeapCount();

		/* カメラ線形補完用カウントが最大値に達しているか */
		if (iCameraTargetLeapCount < iCameraLeapCountMax)
		{
			// 最大値に達していない場合
			/* カメラ線形補間の割合を取得 */
			float fLeapRatio = ((float)iCameraTargetLeapCount / (float)iCameraLeapCountMax);

			/* カメラの座標(線形補間後)を算出 */
			VECTOR vecStart = this->StageStatusList->vecGetCameraTarget_Start();		// 線形補完の移動前座標
			VECTOR vecTarget = this->StageStatusList->vecGetCameraTarget_Target();		// 線形補完の移動後座標
			VECTOR vecCameraTarget;
			vecCameraTarget.x = vecStart.x + (vecTarget.x - vecStart.x) * fLeapRatio;
			vecCameraTarget.y = vecStart.y + (vecTarget.y - vecStart.y) * fLeapRatio;
			vecCameraTarget.z = vecStart.z + (vecTarget.z - vecStart.z) * fLeapRatio;

			/* カメラの注視点(線形補間後)を現在のカメラ注視点に設定 */
			this->StageStatusList->SetCameraTarget(vecCameraTarget);

			/* カウントを加算して設定する */
			this->StageStatusList->SetCameraTargetLeapCount(iCameraTargetLeapCount + 1);
		}
		else
		{
			// 最大値に達している場合
			/* カメラの注視点(移動後)を現在のカメラ注視点に設定 */
			this->StageStatusList->SetCameraTarget(this->StageStatusList->vecGetCameraTarget_Target());

			this->StageStatusList->SetCameraTarget_Start(this->StageStatusList->vecGetCameraTarget_Target());
		}
	}
}
/* 2025.03.06 菊池雅道	カメラ制御処理修正  */
/* 2025.03.16 駒沢風助	カメラ制御処理修正 終了 */

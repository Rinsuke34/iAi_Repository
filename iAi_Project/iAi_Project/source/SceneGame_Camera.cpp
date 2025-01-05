/* 2024.01.02 駒沢風助 ファイル追加 */

#include "SceneGame_Camera.h"

/* シーン「ゲーム - カメラ」の宣言 */

// コンストラクタ
SceneGame_Camera::SceneGame_Camera() : SceneBase("Game_Camera", 1, false)
{
	/* 非同期読み込みを有効化する */
	SetUseASyncLoadFlag(true);

	/* "オブジェクト管理"を取得 */
	this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

	/* "プレイヤー状態"を取得 */
	this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

	/* 非同期読み込みを無効化する */
	SetUseASyncLoadFlag(false);
}

// デストラクタ
SceneGame_Camera::~SceneGame_Camera()
{

}

// 計算
void SceneGame_Camera::Process()
{
	/* 3D基本設定 */
	{
		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);
		SetUseBackCulling(TRUE);
	}
	
	/* プレイヤー座標取得 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();	

	/* カメラ注視点設定 */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, 100, 0));
	this->PlayerStatusList->SetCameraTarget(vecCameraTarget);

	/* 視点変更に必要なデータ取得 */
	float fCameraAngleX				= this->PlayerStatusList->fGetCameraAngleX();			// X軸回転量
	float fCameraAngleY				= this->PlayerStatusList->fGetCameraAngleY();			// Y軸回転量
	float fCameraRotationalSpeed	= this->PlayerStatusList->fGetCameraRotationalSpeed();	// 回転速度

	/* 入力からカメラ回転量を取得 */
	/* マウス */
	{
		fCameraAngleX += gstKeyboardInputData.iMouseMoveX * fCameraRotationalSpeed;
		fCameraAngleY += gstKeyboardInputData.iMouseMoveY * fCameraRotationalSpeed;
	}
	
	/* コントローラー */
	{
		float fCameraSensitivity = 0.1f;	// カメラ感度

		fCameraAngleX += fCameraSensitivity * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickX[INPUT_RIGHT]);
		fCameraAngleY += fCameraSensitivity * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickY[INPUT_RIGHT]);
	}

	/* Y軸の回転角度制限 */
	{
		float fAngleLimitUp		= this->PlayerStatusList->fGetCameraAngleLimitUp();		// 上方向の制限角度
		float fAngleLimitDown	= this->PlayerStatusList->fGetCameraAngleLimitDown();	// 下方向の制限角度

		if (fCameraAngleY > fAngleLimitUp)		{ fCameraAngleY = fAngleLimitUp; }		// 上方向の制限角度を超えたら制限角度に設定
		if (fCameraAngleY < fAngleLimitDown)	{ fCameraAngleY = fAngleLimitDown; }	// 下方向の制限角度を超えたら制限角度に設定
	}

	/* 回転量を更新 */
	{
		this->PlayerStatusList->SetCameraAngleX(fCameraAngleX);
		this->PlayerStatusList->SetCameraAngleY(fCameraAngleY);
	}

	/* カメラ座標設定 */
	{
		float fRadius	= this->PlayerStatusList->fGetCameraRadius();				// 注視点からの距離
		float fCameraX	= fRadius * +cosf(fCameraAngleX)	+ vecCameraTarget.x;	// X座標
		float fCameraY	= fRadius * -sinf(fCameraAngleY)	+ vecCameraTarget.y;	// Y座標
		float fCameraZ	= fRadius * +sinf(fCameraAngleX)	+ vecCameraTarget.z;	// Z座標

		this->PlayerStatusList->SetCameraPosition(VGet(fCameraX, fCameraY, fCameraZ));
	}

	/* カメラ設定 */
	{
		SetCameraPositionAndTargetAndUpVec(this->PlayerStatusList->vecGetCameraPosition(), this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraUp());
	}
}

// 描画
void SceneGame_Camera::Draw()
{
	/* テスト用 */
	VECTOR vecTest;

	// カメラの上方向取得
	vecTest = this->PlayerStatusList->vecGetCameraUp();
	DrawFormatString(800, 16 * 0, GetColor(255, 255, 255), "カメラ上方向 X:%f, Y:%f, Z:%f", vecTest.x, vecTest.y, vecTest.z);

	// カメラの座標取得
	vecTest = this->PlayerStatusList->vecGetCameraPosition();
	DrawFormatString(800, 16 * 1, GetColor(255, 255, 255), "カメラ座標 X:%f, Y:%f, Z:%f", vecTest.x, vecTest.y, vecTest.z);

	// カメラの注視点取得
	vecTest = this->PlayerStatusList->vecGetCameraTarget();
	DrawFormatString(800, 16 * 2, GetColor(255, 255, 255), "カメラ注視点 X:%f, Y:%f, Z:%f", vecTest.x, vecTest.y, vecTest.z);

	// カメラの中心点からの距離取得
	DrawFormatString(800, 16 * 3, GetColor(255, 255, 255), "中心からの距離:%f", this->PlayerStatusList->fGetCameraRadius());

	// カメラのX軸回転量取得
	DrawFormatString(800, 16 * 4, GetColor(255, 255, 255), "カメラのX軸回転量:%f", this->PlayerStatusList->fGetCameraAngleX());

	// カメラのY軸回転量取得
	DrawFormatString(800, 16 * 5, GetColor(255, 255, 255), "カメラのY軸回転量:%f", this->PlayerStatusList->fGetCameraAngleY());

	// カメラの回転速度取得
	DrawFormatString(800, 16 * 6, GetColor(255, 255, 255), "カメラの回転速度:%f", this->PlayerStatusList->fGetCameraRotationalSpeed());

	// マウス移動量
	DrawFormatString(800, 16 * 7, GetColor(255, 255, 255), "マウス移動量X:%d", gstKeyboardInputData.iMouseMoveX);
	DrawFormatString(800, 16 * 8, GetColor(255, 255, 255), "マウス移動量Y:%d", gstKeyboardInputData.iMouseMoveY);


	/* 注視点座標取得 */
	VECTOR vecTargetPos = this->PlayerStatusList->vecGetCameraTarget();

	/* 視点中心描写 */
	DrawLine3D(VAdd(vecTargetPos, VGet(-50, 0, 0)), VAdd(vecTargetPos, VGet(50, 0, 0)), GetColor(255, 0, 0));
	DrawLine3D(VAdd(vecTargetPos, VGet(0, -50, 0)), VAdd(vecTargetPos, VGet(0, 50, 0)), GetColor(0, 255, 0));
	DrawLine3D(VAdd(vecTargetPos, VGet(0, 0, -50)), VAdd(vecTargetPos, VGet(0, 0, 50)), GetColor(0, 0, 255));

	/* 視点中心描写 */
	DrawLine3D(VGet(-50, 0, 0), VGet(50, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -50, 0), VGet(0, 50, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -50), VGet(0, 0, 50), GetColor(0, 0, 255));
}

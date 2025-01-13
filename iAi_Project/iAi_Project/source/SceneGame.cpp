/* 2024.12.XX YYYY ZZZZ */

#include "SceneGame.h"

/* シーン「ゲーム」の定義 */

// コンストラクタ
SceneGame::SceneGame() : SceneBase("Game", 0, false)
{
	/* 非同期読み込みを有効化する */
	SetUseASyncLoadFlag(true);

	/* テスト用処理 開始 */

	/* データリスト作成 */
	{
		/* データリストサーバーに"オブジェクト管理"を追加 */
		gpDataListServer->AddDataList(new DataList_Object());

		/* データリストサーバーに"プレイヤー状態"を追加 */
		gpDataListServer->AddDataList(new DataList_PlayerStatus());

		/* データリストサーバーに"3Dモデル管理"を追加 */
		gpDataListServer->AddDataList(new DataList_Model());
	}
	
	/* データリスト取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "3Dモデル管理"を取得 */
		this->ModelList = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));
	}

	/* マップデータ読み込み */
	LoadMapData();

	/* テスト用処理 終了 */

	/* 非同期読み込みを無効化する */
	SetUseASyncLoadFlag(false);

	/* マップハンドル作成 */
	this->iShadowMapScreenHandle	= MakeShadowMap(SCREEN_SIZE_WIDE * 2, SCREEN_SIZE_HEIGHT * 2);	// シャドウマップ(画面の2倍のサイズで作成)
	this->iLightMapScreenHandle		= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
}

// デストラクタ
SceneGame::~SceneGame()
{
	/* データリスト削除 */
	gpDataListServer->DeleteDataList("DataList_Object");		// オブジェクト管理
	gpDataListServer->DeleteDataList("DataList_PlayerStatus");	// プレイヤー状態
	gpDataListServer->DeleteDataList("DataList_Model");			// 3Dモデル管理

	/* マップハンドル削除 */
	DeleteShadowMap(iShadowMapScreenHandle);	// シャドウマップ
	DeleteGraph(iLightMapScreenHandle);			// ライトマップ
}

// 計算
void SceneGame::Process()
{
	/* すべてのオブジェクトの更新 */
	ObjectList->UpdateAll();
}

// 描画
void SceneGame::Draw()
{
	/* 透明度に関係なく描写するよう設定　*/
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_ALWAYS);

	/* シャドウマップ作成 */
	SetupShadowMap();

	/* ライトマップ作成 */
	SetupLightMap();

	/* カメラの設定 */
	SetCamera();

	/* 描写に使用するシャドウマップの設定 */
	SetUseShadowMap(0, this->iShadowMapScreenHandle);

	/* 半透明部分を描写しないよう設定 */
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_NOT_SEMITRANS_ONLY);

	/* 半透明部分のないすべてのオブジェクトを描写 */
	ObjectList->DrawAll();

	/* 描写に使用するシャドウマップの設定を解除 */
	SetUseShadowMap(this->iShadowMapScreenHandle, -1);

	/* 半透明部分のみ描写するように設定 */
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_SEMITRANS_ONLY);

	/* 半透明部分のすべてのオブジェクトを描写 */
	ObjectList->DrawAll();

	/* ライトマップ描写 */
	//DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, this->iLightMapScreenHandle, FALSE);

	/* デバッグ描写 */
	DrawDebug();
}

// シャドウマップの設定
void SceneGame::SetupShadowMap()
{
	/* ライト方向設定 */
	SetShadowMapLightDirection(this->iShadowMapScreenHandle, VGet(0, -1.f, -1.f));

	/* シャドウマップの描写範囲設定 */
	{
		/* カメラのターゲット座標を取得 */
		VECTOR vecTargetPos = this->PlayerStatusList->vecGetCameraTarget();

		/* シャドウマップ範囲設定 */
		// ※カメラのターゲット座標を中心に描写
		SetShadowMapDrawArea(this->iShadowMapScreenHandle, VAdd(vecTargetPos, VGet(-SHADOWMAP_RANGE, -SHADOWMAP_RANGE, -SHADOWMAP_RANGE)), VAdd(vecTargetPos, VGet(SHADOWMAP_RANGE, SHADOWMAP_RANGE, SHADOWMAP_RANGE)));
	}

	/* シャドウマップへの描写を開始 */
	ShadowMap_DrawSetup(this->iShadowMapScreenHandle);

	/* すべてのオブジェクトの描写 */
	ObjectList->DrawAll();

	/* シャドウマップへの描写を終了 */
	ShadowMap_DrawEnd();
}

// ライトマップの設定
void SceneGame::SetupLightMap()
{
	/* ライトマップへの描写を開始 */
	SetDrawScreen(this->iLightMapScreenHandle);

	/* 画面クリア */
	ClearDrawScreen();

	/* カメラの設定 */
	SetCamera();

	/* すべてのオブジェクトの発光部分の描写 */
	ObjectList->BloomDrawAll();

	/* ライトマップへの描写を終了 */
	SetDrawScreen(DX_SCREEN_BACK);
}

// カメラ設定
void SceneGame::SetCamera()
{
	/* カメラモードに応じて処理を変更 */
	switch (this->PlayerStatusList->iGetCameraMode())
	{
		/* フリーモード */
		case CAMERA_MODE_FREE:
			SetCamera_Free();
			break;
	}
}

// カメラ設定(フリーモード)
void SceneGame::SetCamera_Free()
{
	/* プレイヤー座標取得 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* カメラ注視点設定 */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, 100, 0));
	this->PlayerStatusList->SetCameraTarget(vecCameraTarget);

	/* 視点変更に必要なデータ取得 */
	float fCameraAngleX						= this->PlayerStatusList->fGetCameraAngleX();						// X軸回転量
	float fCameraAngleY						= this->PlayerStatusList->fGetCameraAngleY();						// Y軸回転量
	float fCameraRotationalSpeed_Controller	= this->PlayerStatusList->fGetCameraRotationalSpeed_Controller();	// 回転速度(コントローラー)
	float fCameraRotationalSpeed_Mouse		= this->PlayerStatusList->fGetCameraRotationalSpeed_Mouse();		// 回転速度(マウス)

	/* 入力からカメラ回転量を取得 */
	/* マウス */
	{
		fCameraAngleX -= gstKeyboardInputData.iMouseMoveX * fCameraRotationalSpeed_Mouse;
		fCameraAngleY -= gstKeyboardInputData.iMouseMoveY * fCameraRotationalSpeed_Mouse;
	}

	/* コントローラー */
	{
		fCameraAngleX += fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickX[INPUT_RIGHT]);
		fCameraAngleY += fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickY[INPUT_RIGHT]);
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
		float fRadius	= this->PlayerStatusList->fGetCameraRadius();			// 注視点からの距離
		float fCameraX	= fRadius * -sinf(fCameraAngleX) + vecCameraTarget.x;	// X座標
		float fCameraY	= fRadius * -sinf(fCameraAngleY) + vecCameraTarget.y;	// Y座標
		float fCameraZ	= fRadius * +cosf(fCameraAngleX) + vecCameraTarget.z;	// Z座標

		this->PlayerStatusList->SetCameraPosition(VGet(fCameraX, fCameraY, fCameraZ));
	}

	/* カメラ設定 */
	{
		SetCameraPositionAndTargetAndUpVec(this->PlayerStatusList->vecGetCameraPosition(), this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraUp());
	}
}

// デバッグ描写
void SceneGame::DrawDebug()
{
	/* シャドウマップ描写 */
	if (gbDrawShadowMapFlg == true)
	{
		TestDrawShadowMap(iShadowMapScreenHandle, SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, 0, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT);
	}

	/* ライトマップ描写 */
	if (gbDrawLightMapFlg == true)
	{
		DrawExtendGraph(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * 2, this->iLightMapScreenHandle, FALSE);
	}
}

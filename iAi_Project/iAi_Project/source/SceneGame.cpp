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
	}
	
	/* データリスト取得 */
	{
		/* "オブジェクト管理"を取得 */
		ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}
	
	/* 要素追加 */
	{
		/* "オブジェクト管理"にプレイヤーを追加 */
		ObjectList->SetCharacterPlayer(new CharacterPlayer());
	}

	/* テスト用処理 終了 */

	/* 非同期読み込みを無効化する */
	SetUseASyncLoadFlag(false);
}

// デストラクタ
SceneGame::~SceneGame()
{
	/* データリスト削除 */
	gpDataListServer->DeleteDataList("DataList_Object");		// オブジェクト管理
	gpDataListServer->DeleteDataList("DataList_PlayerStatus");	// プレイヤー状態
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
	/* すべてのオブジェクトの描写 */
	ObjectList->DrawAll();

	/* カメラの設定 */
	SetCamera();
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

// マップデータのロード
void SceneGame::LoadMapData()
{
	/* 読み込むマップデータの番号を取得 */
	{
		/* マップデータのロード処理 */
	}

	/* マップデータの読み込み */
	{
		/* 読み込みたいマップデータのパス設定 */
		std::string path		= "resource/MapData/";
		std::string jsonFile	= "Island.json";
		std::ifstream file(path + jsonFile);

		/* データの入っている場所の名称設定 */
		std::string jsonObjName	= "Island";

		/* Jsonファイル読み込み */
		nlohmann::json json;
		file >> json;
	}
}

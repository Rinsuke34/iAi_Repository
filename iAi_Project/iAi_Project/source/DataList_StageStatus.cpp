/* 2025.01.22 駒沢風助 ファイル作成 */

#include "DataList_StageStatus.h"

/* ステージ状態管理クラスの定義 */

// コンストラクタ
DataList_StageStatus::DataList_StageStatus() : DataListBase("DataList_StageStatus")
{
	/* 初期化 */
	{
		this->iGameStatus	= GAMESTATUS_PLAY_GAME;		// ゲーム状態
		this->iNowStageNo	= 0;						// 開始ステージ番号
		this->iEndStageNo	= 0;						// 最終ステージ番号
		this->bGameSlowFlg	= false;					// スローモーションフラグ		/*2025.02.05 菊池雅道 変数追加 */
		this->iSlowCount	= 0;						// スローモーションのカウント
		this->bAddUiFlg		= false;					// UI追加フラグ
		this->iStartTime	= 0;						// 開始時の時間
		this->iClearTime	= 0;						// クリア時の時間
		this->iJumpStageNo	= 0;						// ジャンプ後のステージ番号(デバッグ用)

		/* カメラ関連 */
		this->iCameraMode						= CAMERA_MODE_NORMAL;						// カメラモード
		this->iCameraMode_Old					= CAMERA_MODE_NORMAL;						// カメラモード(変更前)
		this->vecCameraUp						= VGet(0, 1, 0);							// カメラの上方向(Y+方向で固定)
		this->vecCameraPosition					= VGet(0, 0, 0);							// カメラの座標(現在地点)
		this->vecCameraPosition_Start			= VGet(0, 0, 0);							// カメラの座標(変更前地点)
		this->vecCameraPosition_Target			= VGet(0, 0, 0);							// カメラの座標(変更後地点)
		this->iCameraPositionLeapCount			= 0;										// カメラ座標の線形保管用カウント
		this->vecCameraTarget					= VGet(0, 0, 0);							// カメラの注視点(現在地点)
		this->vecCameraTarget_Start				= VGet(0, 0, 0);							// カメラの注視点(移動前地点)
		this->vecCameraTarget_Target			= VGet(0, 0, 0);							// カメラの注視点(移動後地点)
		this->iCameraTargetLeapCount			= 0;										// カメラ注視点の線形補間用カウント
		this->fCameraRadius						= INIT_CAMERA_RADIUS;						// カメラの中心点からの距離
		this->fCameraAngleX						= 0;										// カメラのX軸回転量
		this->fCameraAngleY						= 0;										// カメラのY軸回転量
		this->fCameraRotationalSpeed_Controller	= INIT_CAMERA_ROTATIONAL_SPEED_CONTROLLER;	// カメラの回転速度(コントローラー)
		this->fCameraRotationalSpeed_Mouse		= INIT_CAMERA_ROTATIONAL_SPEED_MOUSE;		// カメラの回転速度(マウス)
		this->fCameraAngleLimitUp				= INIT_CAMERA_ANGLE_LIMIT_UP;				// カメラの回転角度制限(上)
		this->fCameraAngleLimitDown				= INIT_CAMERA_ANGLE_LIMIT_DOWN;				// カメラの回転角度制限(下)
		this->iCloseUpCount						= 0;										// クローズアップカウント
	}
}

// デストラクタ
DataList_StageStatus::~DataList_StageStatus()
{
	/* 画面エフェクトリストのクリア */
	for (auto& pScreenEffect : this->pScreenEffectList)
	{
		delete pScreenEffect;
	}
	this->pScreenEffectList.clear();
}


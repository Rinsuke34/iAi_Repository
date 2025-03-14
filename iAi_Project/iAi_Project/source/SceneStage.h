/* 2025.01.16 ファイル作成 駒沢風助 */
/* 2025.03.06 菊池雅道	カメラ制御処理修正 */

#pragma once
#include "AppFrame.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* データリスト */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Model.h"
#include "DataList_StageStatus.h"
#include "DataList_Option.h"

/* シーン */
#include "SceneGameOver.h"
#include "SceneStageClear.h"
#include "SceneResult.h"
#include "SceneEdit.h"
#include "ScenePause.h"
#include "SceneUi_Crosshairs.h"
#include "SceneUi_Combo.h"
#include "SceneUi_Hp.h"
#include "SceneUi_Kunai.h"
#include "SceneUi_Debug.h"
#include "SceneUi_Blood.h"
#include "SceneUi_Edit.h"

/* 画面エフェクト */
#include "ScreenEffect_Damage.h"

/* ステージクラスの宣言 */

// ステージベース
class SceneStage : public SceneBase
{
	public:
		SceneStage();							// コンストラクタ
		virtual ~SceneStage();					// デストラクタ

		void	Initialization()	override;	// 初期化
		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

		virtual void	LoadMapData();			// マップデータのロード

		/* 固定カメラ番号の設定 */
		void SetNowCameraFixedPositionNo(int iNowCameraFixedPositionNo)	{ this->iNowCameraFixedPositionNo = iNowCameraFixedPositionNo; }	// 現在のカメラ固定番号の設定

		/* 固定カメラ番号の取得 */
		int	iGetNowCameraFixedPositionNo()	{ return this->iNowCameraFixedPositionNo; };		// 現在のカメラ固定座標番号
		int	iGetMaxCameraFixedPositionNo()	{ return this->iMaxCameraFixedPositionNo; };		// カメラ固定座標番号総数

	private:
		/* 使用するデータリスト */
		DataList_Object*		ObjectList;			// オブジェクト管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態管理
		DataList_Model*			ModelList;			// 3Dモデル管理
		DataList_StageStatus*	StageStatusList;	// ステージ状態管理
		DataList_Option*		OptionList;			// オプション設定管理

		/* 関数 */
		void	Process_Main();			// 計算(メインの処理)
		void	Process_StageClear();	// 計算(ステージクリア時の処理)
		void	SetupShadowMap();		// シャドウマップの設定
		void	SetupLightMap();		// ライトマップの設定
		void	SetupMainScreen();		// メインの描写処理
		void	SetupEffectScreen();	// エフェクトの描写処理
		void	SetupScreenEffects();	// 画面エフェクト
		void	SetCamera_Setup();		// カメラ設定準備
		void	SetCmaera();			// カメラ設定

		/* カメラモード関連 */
		void	CameraRotateUpdata(int iCameraType);	// 入力によるカメラ回転量取得
		void	SetCamera_Free();						// カメラ設定(フリー)
		void	SetCamera_Aim_Melee();					// カメラ設定(構え(近接攻撃構え))
		void	SetCamera_Aim_Kunai();					// カメラ設定(構え(クナイ構え))
		void	SetCamera_Title();						// カメラ設定(タイトル)
		void	SetCamera_StageClear();					// カメラ設定(ステージクリア)
		void	CameraSmoothing(int iCameraPositionLeapCountMax);	// カメラ補正						/* 2025.03.06 菊池雅道	カメラ制御処理修正 */

		/* デバッグ関連 */
		void	DrawDebug();						// デバッグ描写

		/* 変数 */
		/* 描写画面関連 */
		// ライトマップ用画像ハンドル
		int	iLightMapScreenHandle;					// ライトマップのハンドル
		int iLightMapScreenHandle_DownScale;		// ライトマップ(1/8縮小)のハンドル
		int iLightMapScreenHandle_Gauss;			// ライトマップ(ぼかし)のハンドル
		int iMainScreenHandle;						// メイン画面のハンドル
		// シャドウマップハンドル
		int	iShadowMapScreenHandle;					// シャドウマップのハンドル

		/* カメラ関連 */
		CAMERA_FIXED_POSITION_INFO	vecCameraPositionInfo[CAMERA_FIXED_POSITION_MAX];	// カメラ固定座標情報
		int							iNowCameraFixedPositionNo;							// 現在のカメラ固定座標番号
		int							iMaxCameraFixedPositionNo;							// カメラ固定座標番号総数

		/* 使用する画像のハンドル */
		int*						piGrHandle_ResultFrame;								// リザルト画面のフレーム

		/* その他 */
		int							iStageClear_Count;									// ステージクリア時の処理で使用するカウント
		int							iBlendAlpha_StageClear_Fadein;						// ステージクリア時のフェードインのアルファ値(0～255)
};


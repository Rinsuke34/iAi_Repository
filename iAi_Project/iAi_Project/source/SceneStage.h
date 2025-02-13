/* 2025.01.16 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* データリスト */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Model.h"
#include "DataList_GameStatus.h"
#include "DataList_Image.h"

/* シーン */
#include "SceneEdit.h"
#include "SceneUi_Crosshairs.h"
#include "SceneUi_Combo.h"
#include "SceneUi_Hp.h"
#include "SceneUi_Kunai.h"
#include "SceneUi_Debug.h"
#include "SceneUi_Blood.h"
#include "SceneUi_Edit.h"

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

	private:
		/* 使用するデータリスト */
		DataList_Object*		ObjectList;			// オブジェクト管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態管理
		DataList_Model*			ModelList;			// 3Dモデル管理
		DataList_GameStatus*	GameStatusList;		// ゲーム状態管理

		/* 関数 */
		void	SetupShadowMap();				// シャドウマップの設定
		void	SetupLightMap();				// ライトマップの設定
		void	SetupMainScreen();				// メインの描写処理
		void	SetupEffectScreen();			// エフェクトの描写処理
		void	SetupScreenEffects();			// 画面エフェクト
		void	SetCamera();					// カメラ設定

		/* カメラモード関連 */
		void	CameraRotateUpdata(float fRate);	// 入力によるカメラ回転量取得
		void	SetCamera_Free();					// カメラ設定(フリー)
		void	SetCamera_Lock();					// カメラ設定(固定)
		void	SetCamera_Aim();					// カメラ設定(構え(ズーム))
		void	CameraSmoothing();					// カメラ補正

		/* デバッグ関連 */
		void	DrawDebug();						// デバッグ描写

		/* 描写画面関連 */
		// 画像ハンドル
		int	iLightMapScreenHandle;					// ライトマップのハンドル
		int iLightMapScreenHandle_DownScale;		// ライトマップ(1/8縮小)のハンドル
		int iLightMapScreenHandle_Gauss;			// ライトマップ(ぼかし)のハンドル
		int iMainScreenHandle;						// メイン画面のハンドル
		int iMainScreenEffectHandle;				// メイン画面(画面エフェクト用)のハンドル
		// シャドウマップハンドル
		int	iShadowMapScreenHandle;					// シャドウマップのハンドル
		// マスクハンドル
		int iMotionBlurMaskHandle;					// モーションブラー用のマスクハンドル
		// シェーダーハンドル
		int iSpeedLineShaderHandle;					// 集中線用のシェーダーハンドル
};


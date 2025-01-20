/* 2025.01.16 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* データリスト */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Model.h"

/* シーン */
#include "SceneEdit.h"

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

		virtual void	LoadMapData(int iStageNo);		// マップデータのロード

	private:
	protected:
		/* 使用するデータリスト */
		// 毎回データリストサーバーから取得するのは非効率なため、ここで保存しておく
		DataList_Object*		ObjectList;			// オブジェクト管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態管理
		DataList_Model*			ModelList;			// 3Dモデル管理

		/* 関数 */
		virtual void	SetupShadowMap();				// シャドウマップの設定
		virtual void	SetupLightMap();				// ライトマップの設定
		virtual void	SetCamera();					// カメラ設定

		/* カメラ関連 */
		void	SetCamera_Free();					// カメラ設定(フリーモード)

		/* デバッグ関連 */
		void	DrawDebug();						// デバッグ描写

		/* 描写画面関連 */
		int	iShadowMapScreenHandle;					// シャドウマップのハンドル
		int	iLightMapScreenHandle;					// ライトマップのハンドル
		int iLightMapScreenHandle_DownScale;		// ライトマップ(1/8縮小)のハンドル
		int iLightMapScreenHandle_Gauss;			// ライトマップ(ぼかし)のハンドル

		/* マップ情報(仮) */
		// ※データリスト作成予定
		bool bEditDrawFlg;							// エディット描写フラグ
		bool bGoalFlg;								// ゴールフラグ
};


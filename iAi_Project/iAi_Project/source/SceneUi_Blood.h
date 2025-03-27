/* 2025.02.11 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"

/* データリスト */
#include "DataList_GameResource.h"
#include "DataList_StageStatus.h"
#include "DataList_PlayerStatus.h"

/* UI(ブラッド(ゲーム内通貨))クラスの宣言 */

// UI(ブラッド(ゲーム内通貨))クラス
class SceneUi_Blood : public SceneBase
{
	public:
		SceneUi_Blood();					// コンストラクタ
		virtual ~SceneUi_Blood() {};		// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_GameResource*	GameResourceList;	// ゲーム内リソース管理
		DataList_StageStatus*	StageStatusList;	// ステージ状態管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態管理

		/* 使用する画像のハンドル */
		int* piGrHandle_Blood_Icon;					// ブラッドアイコン
		int* piGrHandle_Text_Frame;					// テキストフレーム
		int* piGrHandle_Text_Frame_Magnification;	// テキストフレーム(倍率用)
};

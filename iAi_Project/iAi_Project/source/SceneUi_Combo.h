/* 2025.01.28 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"

/* データリスト */
#include "DataList_PlayerStatus.h"
#include "DataList_GameStatus.h"
#include "DataList_Score.h"

/* UI(コンボ)クラスの宣言 */

// UI(コンボ)クラス
class SceneUi_Combo : public SceneBase
{
	public:
		SceneUi_Combo();					// コンストラクタ
		virtual ~SceneUi_Combo();			// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態管理
		DataList_GameStatus*	GameStatusList;		// ゲーム状態管理
		DataList_Score*			ScoreList;			// スコア関連管理

		/* 使用する画像のハンドル */
		int iCgHandle_Combo_Frame;			// コンボフレーム
		int iCgHandle_Combo_Timer;			// コンボタイマー
		int iCgHandle_Combo_Alphabet[5];	// コンボアルファベット
};
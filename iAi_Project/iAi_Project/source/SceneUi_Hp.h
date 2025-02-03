/* 2025.01.28 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"

/* データリスト */
#include "DataList_PlayerStatus.h"
#include "DataList_GameStatus.h"

/* UI(HP)クラスの宣言 */

// UI(HP)クラス
class SceneUi_Hp : public SceneBase
{
	public:
		SceneUi_Hp();					// コンストラクタ
		virtual ~SceneUi_Hp();			// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_PlayerStatus* PlayerStatusList;	// プレイヤー状態管理
		DataList_GameStatus* GameStatusList;		// ゲーム状態管理

		/* 使用する画像のハンドル */
		int iCgHandle_Hp_Frame;		// HPフレーム
		int iCgHandle_Hp_Gauge;		// HPゲージ
};


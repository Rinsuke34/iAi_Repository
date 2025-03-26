/* 2025.01.28 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"

/* データリスト */
#include "DataList_PlayerStatus.h"
#include "DataList_StageStatus.h"
#include "DataList_Image.h"

/* UI(HP)クラスの宣言 */

// UI(HP)クラス
class SceneUi_Hp : public SceneBase
{
	public:
		SceneUi_Hp();					// コンストラクタ
		virtual ~SceneUi_Hp() {};		// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態管理
		DataList_StageStatus*	StageStatusList;	// ステージ状態管理

		/* 使用する画像のハンドル */
		int* piGrHandle_Hp_Frame;		// HPフレーム
		int* piGrHandle_Hp_Gauge;		// HPゲージ
};


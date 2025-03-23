/* 2025.01.28 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"

/* データリスト */
#include "DataList_PlayerStatus.h"
#include "DataList_StageStatus.h"
#include "DataList_Image.h"

/* UI(クナイ)クラスの宣言 */

// UI(クナイ)クラス
class SceneUi_Kunai : public SceneBase
{
	public:
		SceneUi_Kunai();					// コンストラクタ
		virtual ~SceneUi_Kunai();			// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_PlayerStatus*	PlayerStatusList;		// プレイヤー状態管理
		DataList_StageStatus*	StageStatusList;		// ゲーム状態管理

		/* 使用する画像のハンドル */
		int* piGrHandle_Kunai_Frame;					// クナイフレーム
};

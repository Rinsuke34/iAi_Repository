/* 2025.02.11 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"

/* データリスト */
#include "DataList_StageStatus.h"
#include "DataList_GameResource.h"

/* UI(エディット)クラスの宣言 */

// UI(エディット)クラス
class SceneUi_Edit : public SceneBase
{
	public:
		SceneUi_Edit();					// コンストラクタ
		virtual ~SceneUi_Edit();		// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_StageStatus*	StageStatusList;		// ゲーム状態管理
		DataList_GameResource*	GameResourceList;	// ゲーム内リソース管理

		/* 現在のエディットデータ */
		EDIT_INFORMATION NowEditData[EDIT_MAX];		// 現在のエディットデータ

		/* 使用する画像のハンドル */
		int* piGrHandle_Edit_Frame[EDIT_RANK_MAX];			// エディットフレーム
		int* piGrHandle_Edit_Effect[EDIT_EFFECT_MAX];		// エディット効果
};

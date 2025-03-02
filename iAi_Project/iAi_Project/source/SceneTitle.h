/* 2024.12.XX YYYY ZZZZ */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* シーン */
#include "SceneStage.h"
#include "SceneAddStageSetup.h"

/* データリスト */
#include "DataList_StageStatus.h"

/* 循環参照対策 */
class SceneStage;

/* シーン「タイトル」の宣言 */

// シーン "タイトル画面"
class SceneTitle : public SceneBase
{
	public:
		SceneTitle();							// コンストラクタ
		virtual ~SceneTitle();					// デストラクタ

		void	Initialization()	override;	// 初期化
		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_StageStatus* StageStatusList;	// ゲーム状態管理

		/* シーン"ステージ"のポインタ */
		SceneStage* pSceneStage;

		/* 使用する画像のハンドル */
		int* piGrHandle_TitleLogo;		// タイトルロゴ
};

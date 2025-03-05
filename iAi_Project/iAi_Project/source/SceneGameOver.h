/* 2025.02.20 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_StageStatus.h"
#include "DataList_Image.h"

/* シーン */
#include "SceneAddTitleSetup.h"

/* シーン"ゲームオーバー"クラスの宣言 */

// シーン"ゲームオーバー"
class SceneGameOver : public SceneBase
{
	public:
		SceneGameOver();						// コンストラクタ
		virtual ~SceneGameOver();				// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_StageStatus* StageStatusList;	// ゲーム状態管理

		/* 使用する画像のハンドル */
		int* piGrHandle_GameOver;				// ゲームオーバー

		/* 関数 */
		void	Process_Main();					// メイン処理

		/* 変数 */
		int		iBlendAlpha;					// 描写する画像のアルファ値(0～255)
};

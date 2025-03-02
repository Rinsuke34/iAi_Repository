/* 2025.03.02 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_StageStatus.h"
#include "DataList_Image.h"

/* シーン"ゲームクリア"クラスの宣言 */

// シーン"ゲームクリア"
class SceneGameClear : public SceneBase
{
	public:
		SceneGameClear();						// コンストラクタ
		virtual ~SceneGameClear();				// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_StageStatus* StageStatusList;		// ゲーム状態管理

		/* 関数 */
		void	Process_Main();		// メイン処理

		/* 使用する画像のハンドル */
		int* piGrHandle_GameClear;					// ゲームクリア
};

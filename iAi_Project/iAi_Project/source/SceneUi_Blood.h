/* 2025.02.11 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"

/* データリスト */
#include "DataList_GameResource.h"

/* UI(ブラッド(ゲーム内通貨))クラスの宣言 */

// UI(ブラッド(ゲーム内通貨))クラス
class SceneUi_Blood : public SceneBase
{
	public:
		SceneUi_Blood();					// コンストラクタ
		virtual ~SceneUi_Blood();			// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_GameResource* GameResourceList;	// ゲーム内リソース管理

		/* 使用する画像のハンドル */

};

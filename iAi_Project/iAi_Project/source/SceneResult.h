/* 2025.02.16 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_GameStatus.h"
#include "DataList_GameResource.h"

/* シーン"リザルト"クラスの宣言 */

// シーン"リザルト"
class SceneResult : public SceneBase
{
	public:
		SceneResult();							// コンストラクタ
		virtual ~SceneResult();					// デストラクタ

		void	Initialization()	override;	// 初期化
		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_GameStatus* GameStatusList;		// ゲーム状態管理
		DataList_GameResource* GameResourceList;	// ゲーム内リソース管理
};

/* 2025.01.19 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_GameStatus.h"

/* シーン"エディット"クラスの宣言 */

// シーン"エディット"
class SceneEdit : public SceneBase
{
	public:
		SceneEdit();							// コンストラクタ
		virtual ~SceneEdit();					// デストラクタ

		void	Initialization()	override;	// 初期化
		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_GameStatus*	GameStatusList;		// ゲーム状態管理
};

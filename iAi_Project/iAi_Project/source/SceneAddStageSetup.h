/* 2025.02.27 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* シーン */
#include "SceneGame.h"

/* シーン「ステージ追加セットアップ」の宣言 */

// シーン "ステージ追加セットアップ"
// ※タイトル → ゲームと遷移してしまうと一部データリストが削除→取得となってしまうため、対策用に追加
class SceneAddStageSetup : public SceneBase
{
	public:
		SceneAddStageSetup();				// コンストラクタ
		virtual ~SceneAddStageSetup()	{};	// デストラクタ

		void	Process()			override;	// 計算

	private:
	protected:
};

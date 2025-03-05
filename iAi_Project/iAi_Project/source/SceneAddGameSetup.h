/* 2025.02.27 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* シーン */
#include "SceneGame.h"

/* シーン"ゲーム"追加セットアップの宣言 */

// シーン "ゲーム"追加セットアップ
// ※タイトル → ゲームと遷移してしまうと一部データリストが削除→取得となってしまうため、対策用に追加
class SceneAddSceneGameSetup : public SceneBase
{
	public:
		SceneAddSceneGameSetup();				// コンストラクタ
		virtual ~SceneAddSceneGameSetup()	{};	// デストラクタ

		void	Process()			override;	// 計算
};

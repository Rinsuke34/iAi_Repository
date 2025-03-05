/* 2025.03.05 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* シーン */
#include "SceneTitle.h"

/* シーン"タイトル"追加セットアップの宣言 */

// シーン "タイトル"追加セットアップ
// ※ゲーム → タイトルと遷移してしまうと一部データリストが削除→取得となってしまうため、対策用に追加
class SceneAddTitleSetup : public SceneBase
{
	public:
		SceneAddTitleSetup();				// コンストラクタ
		virtual ~SceneAddTitleSetup() {};	// デストラクタ

		void	Process()			override;	// 計算
};

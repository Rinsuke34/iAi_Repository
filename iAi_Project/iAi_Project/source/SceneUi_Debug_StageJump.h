/* 2025.03.11 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_StageStatus.h"

/* UI(デバッグメニュー/ステージジャンプ)クラスの宣言 */

// UI(デバッグメニュー/ステージジャンプ)クラス
class SceneUi_Debug_StageJump : public SceneBase
{
	public:
		SceneUi_Debug_StageJump();					// コンストラクタ
		virtual ~SceneUi_Debug_StageJump() {};		// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_StageStatus* StageStatusList;	// ステージ状態管理

		/* 変数 */
		int iJumpStageNo;	// ステージ番号
};

/* 2025.02.06 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_StageStatus.h"

/* 基本スカイスフィアクラスの宣言 */

// 基本スカイスフィアクラス
class SkySqhereBasic : public SkySqhereBase
{
	public:
		SkySqhereBasic();				// コンストラクタ
		virtual ~SkySqhereBasic();		// デストラクタ

		void Update() override;			// 更新

	private:
		/* 使用するデータリスト */
		DataList_StageStatus* StageStatusList;	// ステージ状態管理

	protected:

};

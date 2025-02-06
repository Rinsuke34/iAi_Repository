/* 2025.02.06 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Object.h"

/* 基本スカイスフィアクラスの宣言 */

// 基本スカイスフィアクラス
class SkySqhereBasic : public SkySqhereBase
{
	public:
		SkySqhereBasic();				// コンストラクタ
		virtual ~SkySqhereBasic();		// デストラクタ

		void Update() override;					// 更新

	private:
		/* 使用するデータリスト */
		DataList_Object* ObjectList;			// オブジェクト管理

	protected:

};

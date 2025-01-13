/* 2024.01.13 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* 発光するプラットフォームクラス(テスト)の宣言 */

// 発光するプラットフォームクラス(テスト)
class PlatformLight_Test : public PlatformBase
{
	public:
		PlatformLight_Test();				// コンストラクタ
		virtual ~PlatformLight_Test();		// デストラクタ

		virtual void	Initialization();	// 初期化
		virtual void	Update() {};		// 更新
		virtual void	Draw();				// 描写

	private:
	protected:

};

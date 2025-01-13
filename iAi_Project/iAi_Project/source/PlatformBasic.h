/* 2024.01.07 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* 基本プラットフォームクラスの宣言 */

// 基本プラットフォームクラス
class PlatformBasic : public PlatformBase
{
	public:
		PlatformBasic();				// コンストラクタ
		virtual ~PlatformBasic();		// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override {};	// 更新
		virtual void	Draw()				override;		// 描写
		virtual void	BloomDraw()			override;		// 発光描写

	private:
	protected:

};

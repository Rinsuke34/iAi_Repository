/* 2025.01.15 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* テスト用エフェクトクラス */

// エフェクトクラス
class TestEffect : public EffectBase
{
	public:
		TestEffect();				// コンストラクタ
		virtual ~TestEffect();		// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新

	private:
	protected:
		/* 関数 */

		/* 変数 */

		int iDeleteCount;
};

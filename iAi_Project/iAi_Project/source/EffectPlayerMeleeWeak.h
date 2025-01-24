/* 2025.01.24 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* 近接攻撃(弱)エフェクトクラスの宣言 */

// 近接攻撃(弱)エフェクトクラス
class EffectPlayerMeleeWeak : public EffectBase
{
	public:
		EffectPlayerMeleeWeak();				// コンストラクタ
		virtual ~EffectPlayerMeleeWeak();		// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新

	private:
	protected:
		/* 関数 */

		/* 変数 */
		int iDeleteCount;		// クラス削除までのカウント
};


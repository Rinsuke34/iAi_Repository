/* 2025.02.11 駒沢風助 ファイル作成 */

#pragma once
#include "ActorBase.h"

/* すべての実体のないアイテムのベースとなるクラスの宣言 */

// 実体なしアイテムクラス
class EffectItemBase : public ActorBase
{
	public:
		EffectItemBase();				// コンストラクタ
		virtual ~EffectItemBase() {};	// デストラクタ

	private:
	protected:

};

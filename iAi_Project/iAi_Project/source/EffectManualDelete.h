/* 2025.01.26 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* 手動で削除タイミングを設定するエフェクトクラスの宣言 */
// ※オブジェクト依存で表示を行うエフェクトで使用

// エフェクトクラス(手動削除)
class EffectManualDelete : public EffectBase
{
	public:
		EffectManualDelete();				// コンストラクタ
		virtual ~EffectManualDelete() {};	// デストラクタ

	private:
	protected:
};

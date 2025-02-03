/* 2025.01.24 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Object.h"
#include "DataList_Effect.h"

/* オブジェクト */
#include "EffectManualDelete.h"

/* 近接攻撃(弱)クラスの宣言 */

// 近接攻撃(弱)
class BulletPlayerMeleeWeak : public BulletBase
{
	public:
		BulletPlayerMeleeWeak();				// コンストラクタ
		virtual ~BulletPlayerMeleeWeak();		// デストラクタ

		virtual void	Initialization()	override;	// 初期化
		virtual void	Update()			override;	// 更新

	private:
		/* オブジェクト(エフェクト)のハンドル */
		EffectManualDelete* pEffect;

		int iDeleteCount;	// 仮追加の削除カウント

	protected:
};

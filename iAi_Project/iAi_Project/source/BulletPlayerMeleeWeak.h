/* 2025.01.24 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* 近接攻撃(弱)クラスの宣言 */

// 近接攻撃(弱)
class BulletPlayerMeleeWeak : public BulletBase
{
	public:
		BulletPlayerMeleeWeak();				// コンストラクタ
		virtual ~BulletPlayerMeleeWeak();		// デストラクタ

		virtual void	Initialization()	override;	// 初期化
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描写
		virtual void	BloomDraw()			override;	// 発光描写

	private:
	protected:
	
};

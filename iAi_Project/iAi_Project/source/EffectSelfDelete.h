/* 2025.01.26 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* 時間経過で削除されるエフェクトクラスの宣言 */
// ※オブジェクトに依存しないエフェクトで使用

// エフェクトクラス(自動削除)
class EffectSelfDelete : public EffectBase
{
	public:
		EffectSelfDelete();					// コンストラクタ
		virtual ~EffectSelfDelete() {};		// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新

		int 	iGetDeleteCount()	{ return this->iDeleteCount; };							// 削除までのカウントを取得

		void	SetDeleteCount(int iDeleteCount)	{ this->iDeleteCount = iDeleteCount; };	// 削除までのカウントを設定

	protected:
	private:
		/* 変数 */
		int iDeleteCount;		// クラス削除までのカウント
};

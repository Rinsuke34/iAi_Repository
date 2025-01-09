/* 2025.01.08 駒沢風助 ファイル作成 */

#pragma once
#include "ActorBase.h"
#include "EffekseerForDXLib.h"

/* すべてのエフェクトのベースとなるクラスの宣言 */

// エフェクトベースクラス
class EffectBase : public ActorBase
{
	public:
		EffectBase();			// コンストラクタ
		virtual ~EffectBase();	// デストラクタ

		virtual void	Update() {};		// 更新
		virtual void	Draw() {};			// 描写

		int	iGetEffectHandle()	{ return this->iEffectHandle; };	// エフェクトハンドルを取得
		int	iGetCount()			{ return this->iCount; };			// エフェクトのカウントを取得

		void SetEffectHandle(int iEffectHandle)	{ this->iEffectHandle	= iEffectHandle; };		// エフェクトハンドルを設定
		void SetCount(int iCount)				{ this->iCount			= iCount; };			// エフェクトのカウントを設定

	private:
	protected:
		/* 関数 */

		/* 変数 */
		int iEffectHandle;	// エフェクトハンドル
		int iCount;			// エフェクトのカウント
};

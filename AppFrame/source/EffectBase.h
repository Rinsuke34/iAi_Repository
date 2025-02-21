/* 2025.01.08 駒沢風助 ファイル作成 */

#pragma once
#include "ObjectBase.h"
#include <EffekseerForDXLib.h>

/* すべてのエフェクトのベースとなるクラスの宣言 */

// エフェクトベースクラス
class EffectBase : public ObjectBase
{
	public:
		EffectBase();			// コンストラクタ
		virtual ~EffectBase();	// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update();							// 更新
		virtual void	Draw();								// 描写

		int		iGetEffectHandle()					{ return this->iEffectHandle; }				// エフェクトハンドル取得

		void	SetEffectHandle(int iEffectHandle)	{ this->iEffectHandle = iEffectHandle; }	// エフェクトハンドル設定

		void Effect_PosUpdate();						// エフェクト位置更新
		void Effect_RotationUpdate();					// エフェクト回転量更新
		void Effect_ScaleUpdate();						// エフェクト拡大率更新

	private:
		/* 関数 */

		/* 変数 */
		int iEffectHandle;		// エフェクトハンドル
};

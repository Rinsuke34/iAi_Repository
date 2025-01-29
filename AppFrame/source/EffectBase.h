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

		void Effect_PosUpdate();						// エフェクト位置更新(現在座標に移動)
		void Effect_RotationUpdate();					// エフェクト回転量更新(現在回転に設定)

	private:
	protected:
		/* 関数 */

		/* 変数 */
		int iEffectHandle;		// エフェクトハンドル
};

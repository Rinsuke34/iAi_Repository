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

		virtual void	Initialization()	override {};	// 初期化
		virtual void	Update()			override {};	// 更新

		virtual void Effect_Load(std::string effectName);		// エフェクト読み込み
		virtual void Effect_PosUpdate();						// エフェクト位置更新(vecPosに)

	private:
	protected:
		/* 関数 */

		/* 変数 */
		int iEffectHandle_Resource;	// エフェクトハンドル(リソース)
		int iEffectHandle_Play;		// エフェクトハンドル(実行)
};

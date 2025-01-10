/* 2025.01.08 駒沢風助 ファイル作成 */

#include "EffectBase.h"

/* すべてのエフェクトのベースとなるクラスの定義 */

// コンストラクタ
EffectBase::EffectBase() : ActorBase()
{
	/* 初期化 */
	this->iEffectHandle	= -1;	// エフェクトハンドル
	this->iCount		= 0;	// エフェクトのカウント
}

// デストラクタ
EffectBase::~EffectBase()
{
	/* エフェクトのリソースを削除 */
	DeleteEffekseerEffect(this->iEffectHandle);
}

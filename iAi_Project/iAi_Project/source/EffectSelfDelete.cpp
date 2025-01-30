/* 2025.01.26 駒沢風助 ファイル作成 */

#include "EffectSelfDelete.h"

/* 手動で削除タイミングを設定するエフェクトクラスの定義 */
// コンストラクタ
EffectSelfDelete::EffectSelfDelete() : EffectBase()
{
	/* 初期化 */
	this->iDeleteCount = 0;
}

// 初期化
void EffectSelfDelete::Initialization()
{
	/* エフェクト座標更新 */
	this->Effect_PosUpdate();

	/* エフェクト回転量更新 */
	Effect_RotationUpdate();

	/* エフェクト再生開始 */
	this->iEffectHandle_Play = PlayEffekseer3DEffect(this->iEffectHandle_Resource);
}

// 更新
void EffectSelfDelete::Update()
{
	/* 削除カウントを確認 */
	if (this->iDeleteCount > 0)
	{
		/* カウントを減算 */
		this->iDeleteCount--;
	}
	else
	{
		/* 削除フラグを有効化 */
		this->bDeleteFlg = true;
	}

	/* エフェクト座標更新 */
	this->Effect_PosUpdate();

	/* エフェクト回転量更新 */
	Effect_RotationUpdate();
}

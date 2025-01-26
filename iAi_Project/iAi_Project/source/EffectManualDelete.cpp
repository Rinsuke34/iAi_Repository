/* 2025.01.26 駒沢風助 ファイル作成 */

#include "EffectManualDelete.h"

/* 手動で削除タイミングを設定するエフェクトクラスの定義 */
// コンストラクタ
EffectManualDelete::EffectManualDelete() : EffectBase()
{

}

// 初期化
void EffectManualDelete::Initialization()
{
	/* エフェクト座標更新 */
	Effect_PosUpdate();

	/* エフェクト回転量更新 */
	Effect_RotationUpdate();

	/* エフェクト再生開始 */
	this->iEffectHandle_Play = PlayEffekseer3DEffect(this->iEffectHandle_Resource);	
}

// 更新
void EffectManualDelete::Update()
{
	/* エフェクト座標更新 */
	Effect_PosUpdate();

	/* エフェクト回転量更新 */
	Effect_RotationUpdate();
}

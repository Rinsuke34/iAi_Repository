
#include "EffectTest.h"

// コンストラクタ
TestEffect::TestEffect() : EffectBase()
{
	iDeleteCount = 0;
}

// デストラクタ
TestEffect::~TestEffect()
{

}

// 初期化
void TestEffect::Initialization()
{
	/* 描写時間設定(とりあえず) */
	iDeleteCount = 60 * 2;

	/* エフェクト再生開始 */
	this->iEffectHandle_Play = PlayEffekseer3DEffect(this->iEffectHandle_Resource);

	/* 座標更新 */
	this->Effect_PosUpdate();
}

// 更新
void TestEffect::Update()
{
	/* 座標更新 */
	this->Effect_PosUpdate();

	if (iDeleteCount <= 0)
	{
		this->bDeleteFlg = true;
	}

	iDeleteCount--;
}

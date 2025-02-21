/* 2025.01.08 駒沢風助 ファイル作成 */

#include "EffectBase.h"

/* すべてのエフェクトのベースとなるクラスの定義 */

// コンストラクタ
EffectBase::EffectBase() : ObjectBase()
{
	/* 初期化 */
	this->iEffectHandle		= -1;	// エフェクトハンドル
}

// デストラクタ
EffectBase::~EffectBase()
{
	/* エフェクトのリソースを削除 */
	StopEffekseer3DEffect(this->iEffectHandle);
}

// 初期化
void EffectBase::Initialization()
{
	/* エフェクト拡大率更新 */
	Effect_ScaleUpdate();
}

// 更新
void EffectBase::Update()
{
	/* エフェクト座標更新 */
	Effect_PosUpdate();

	/* エフェクト回転量更新 */
	Effect_RotationUpdate();
}


// 描写
void EffectBase::Draw()
{
	/* エフェクトを描写 */
	DrawEffekseer3D_Draw(this->iEffectHandle);
}

// エフェクト位置更新
void EffectBase::Effect_PosUpdate()
{
	/* エフェクトの描写座標を現在のvecPositionに設定 */
	SetPosPlayingEffekseer3DEffect(this->iEffectHandle, this->vecPosition.x, this->vecPosition.y, this->vecPosition.z);
}

// エフェクト回転量更新
void EffectBase::Effect_RotationUpdate()
{
	/* エフェクトの回転量を現在のvecRotationに設定 */
	SetRotationPlayingEffekseer3DEffect(this->iEffectHandle, this->vecRotation.x, this->vecRotation.y, this->vecRotation.z);
}

// エフェクト拡大率更新
void EffectBase::Effect_ScaleUpdate()
{
	/* エフェクトの拡大率を現在のvecScaleに設定 */
	SetScalePlayingEffekseer3DEffect(this->iEffectHandle, this->vecScale.x, this->vecScale.y, this->vecScale.z);
}

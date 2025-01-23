/* 2025.01.24 駒沢風助 ファイル作成 */

#include "EffectPlayerMeleeWeak.h"

/* 近接攻撃(弱)エフェクトクラスの定義 */

// コンストラクタ
EffectPlayerMeleeWeak::EffectPlayerMeleeWeak()
{

}

// デストラクタ
EffectPlayerMeleeWeak::~EffectPlayerMeleeWeak()
{

}

// 初期化
void EffectPlayerMeleeWeak::Initialization()
{
	/* エフェクト再生開始 */
	this->iEffectHandle_Play = PlayEffekseer3DEffect(this->iEffectHandle_Resource);

	/* 座標をプレイヤー位置+100の位置に設定 */
	this->vecPosition = VAdd(this->vecPosition, VGet(0.f, 100.f, 0.f));

	/* クラス削除までのカウント設定 */
	// ※とりあえず60フレームで削除
	this->iDeleteCount	= 60;

	/* 座標更新 */
	this->Effect_PosUpdate();
}

// 更新
void EffectPlayerMeleeWeak::Update()
{
	/* クラス削除までのカウントが0以下になったら削除フラグを立てる */
	if (this->iDeleteCount <= 0)
	{
		this->bDeleteFlg = true;
	}
	/* クラス削除までのカウントを減算 */
	this->iDeleteCount--;
}

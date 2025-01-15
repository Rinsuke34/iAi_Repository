/* 2025.01.08 駒沢風助 ファイル作成 */

#include "EffectBase.h"

/* すべてのエフェクトのベースとなるクラスの定義 */

// コンストラクタ
EffectBase::EffectBase() : ObjectBase()
{
	/* 初期化 */
	this->iEffectHandle_Resource	= -1;	// エフェクトハンドル(リソース)
	this->iEffectHandle_Play		= -1;		// エフェクトハンドル(実行)
}

// デストラクタ
EffectBase::~EffectBase()
{
	/* エフェクトのリソースを削除 */
	DeleteEffekseerEffect(this->iEffectHandle_Resource);
	StopEffekseer3DEffect(this->iEffectHandle_Play);
}

// エフェクト読み込み
void EffectBase::Effect_Load(std::string effectName)
{
	// 引数
	// effectName	: エフェクト名

	/* エフェクトのファイルパスを取得 */
	std::string FileName = "resource/EffectData/" + effectName + ".efkefc";

	/* エフェクトを読み込み */
	this->iEffectHandle_Resource = LoadEffekseerEffect(FileName.c_str());
}

// エフェクト位置更新(vecPosに)
void EffectBase::Effect_PosUpdate()
{
	/* エフェクトの描写座標を現在のPosに設定 */
	SetPosPlayingEffekseer3DEffect(this->iEffectHandle_Play, this->vecPosition.x, this->vecPosition.y, this->vecPosition.z);
}

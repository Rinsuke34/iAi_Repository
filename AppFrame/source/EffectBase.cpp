/* 2025.01.08 駒沢風助 ファイル作成 */

#include "EffectBase.h"

/* すべてのエフェクトのベースとなるクラスの定義 */

// コンストラクタ
EffectBase::EffectBase() : ObjectBase()
{
	/* 初期化 */
	this->iEffectHandle_Resource	= -1;	// エフェクトハンドル(リソース)
	this->iEffectHandle_Play		= -1;	// エフェクトハンドル(実行)
}

// デストラクタ
EffectBase::~EffectBase()
{
	/* エフェクトのリソースを削除 */
	// ※エフェクトはリソースを複製して活用することが出来ないので都度リソースを読み込む
	StopEffekseer3DEffect(this->iEffectHandle_Play);
	DeleteEffekseerEffect(this->iEffectHandle_Resource);
}

// エフェクト読み込み
void EffectBase::Effect_Load(std::string effectName)
{
	// 引数
	// effectName	: エフェクト名

	// ■ エフェクトのリソース保管場所は下記の通り
	// 形式		: efkfcファイル
	// 保存場所	: resource/EffectData/エフェクトファイル
	// ■ リソースを読み込んだ時点で対象のエフェクトは必ず描写されてしまうため、3Dモデルのようにリソースを複製して使い回すことは仕様上不可。
	//    そのため、エフェクト毎にリソース読み込み→削除を行う。

	/* エフェクトのファイルパスを取得 */
	std::string FileName = "resource/EffectData/" + effectName + ".efkefc";

	/* エフェクトを読み込み */
	this->iEffectHandle_Resource = LoadEffekseerEffect(FileName.c_str());
}

// エフェクト位置更新(vecPosに)
void EffectBase::Effect_PosUpdate()
{
	/* エフェクトの描写座標を現在のvecPositionに設定 */
	SetPosPlayingEffekseer3DEffect(this->iEffectHandle_Play, this->vecPosition.x, this->vecPosition.y, this->vecPosition.z);
}

/* 2025.01.29 駒沢風助 ファイル作成 */

#include "DataList_Effect.h"

/* エフェクトリソース管理クラスの定義 */

// コンストラクタ
DataList_Effect::DataList_Effect() : DataListBase("DataList_Effect")
{
	/* mapをクリアする */
	pEffectList.clear();
}

// デストラクタ
DataList_Effect::~DataList_Effect()
{
	/* リスト内のエフェクトハンドルを削除 */
	for (const auto& pair : pEffectList)
	{
		/* エフェクトを削除 */
		DeleteEffekseerEffect(pair.second);
	}

	/* mapをクリアする */
	pEffectList.clear();
}

// エフェクトロード(事前読み込み用)
void DataList_Effect::LoadEffect(std::string effectName)
{
	// 引数
	// effectName	: エフェクト名

	/* エフェクトを読み込む */
	// ※複製は行わない

	/* 対象のエフェクトが存在するか確認 */
	if (bCheckEffect(effectName) == false)
	{
		// 存在しない場合
		/* エフェクトのファイルパスを取得 */
		std::string FileName = "resource/EffectData/" + effectName + ".efkefc";

		/* エフェクトを読み込み */
		int iReturn = LoadEffekseerEffect(FileName.c_str());

		/* エフェクトをリストに追加 */
		this->pEffectList[effectName] = iReturn;
	}

	return;
}

// エフェクト取得
int DataList_Effect::iGetEffect(std::string effectName)
{
	// 引数
	// effectName	: エフェクト名
	// 戻り値
	// int			: エフェクトハンドル(複製したものを渡す)

	int iReturn = 0;

	/* エフェクトを取得する */
	// ※すでにあるなら複製、ないなら読み込み

	/* 対象のエフェクトが存在するか確認 */
	if (bCheckEffect(effectName) == false)
	{
		// 存在しない場合
		/* エフェクトを読み込む */

		/* エフェクトのファイルパスを取得 */
		std::string FileName = "resource/EffectData/" + effectName + ".efkefc";

		/* エフェクトを読み込み */
		iReturn = LoadEffekseerEffect(FileName.c_str());

		/* エフェクトをリストに追加 */
		this->pEffectList[effectName] = iReturn;

		/* 読み込んだエフェクトを複製 */
		iReturn = PlayEffekseer3DEffect(iReturn);
	}
	else
	{
		// 存在している場合
		/* 対処のエフェクトを複製 */
		iReturn = PlayEffekseer3DEffect(this->pEffectList[effectName]);
	}

	return iReturn;
}

// エフェクトリソース存在確認
bool DataList_Effect::bCheckEffect(std::string effectName)
{
	// 引数
	// effectName	: エフェクト名
	// 戻り値
	// bool			: エフェクトが登録されているか(true:登録されている / false:登録されていない)

	/* 対象のエフェクトがリストに登録されているか確認 */

	bool bReturn = false;

	/* 対象のエフェクトが登録されているか */
	if (this->pEffectList.count(effectName) != 0)
	{
		// 登録されている場合
		bReturn = true;
	}

	return bReturn;
}

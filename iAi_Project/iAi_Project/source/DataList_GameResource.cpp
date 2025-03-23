/* 2025.02.11 駒沢風助 ファイル作成 */

#include "DataList_GameResource.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* ゲーム内リソース管理クラスの定義 */
// コンストラクタ
DataList_GameResource::DataList_GameResource() : DataListBase("DataList_GameResource")
{
	/* 初期化 */
	{
		/* 画像ハンドル取得 */
		{
			/* データリスト"画像リソース管理"取得 */
			DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

			/* エディットフレーム */
			for (int i = 0; i < EDIT_RANK_MAX; i++)
			{
				/* エディットフレームの画像ハンドル取得 */
				this->pGrHandle_EditFrameList[i] = ImageList->piGetImage(EDIT_RANK_NAME[i].strGrName);
			}

			/* エディット効果 */
			for (int i = 0; i < EDIT_EFFECT_MAX; i++)
			{
				/* エディット効果の画像ハンドル取得 */
				this->pGrHandle_EditEffectList[i] = ImageList->piGetImage(EDIT_EFFECT_NAME[i].strGrName);
			}
		}

		/* 初期値設定 */

		/* ブラッド(ゲーム内通貨)関連 */
		this->iHaveBlood	= 0;
		this->iStartBlood	= 0;

		/* エディット関連 */
		for (int i = 0; i < EDIT_MAX; i++)
		{
			/* 現在のエディット情報初期化 */
			this->NowEditData[i].iEditEffect	= EDIT_EFFECT_NONE;
			this->NowEditData[i].iEditRank		= EDIT_RANK_NONE;
			this->NowEditData[i].iEditCost		= 0;
		}

		// キープ中エディット情報初期化
		this->KeepEditData.iEditEffect	= EDIT_EFFECT_NONE;
		this->KeepEditData.iEditRank	= EDIT_RANK_NONE;
		this->KeepEditData.iEditCost	= 0;
	
		/* スコア関連 */
		this->iClearTotalEvaluation = 0;
	}

	JsonLoadEditEffectValue();
}

/* データ設定 */
// 現在のエディット情報設定
void DataList_GameResource::SetNowEditData(int iEditNum, EDIT_DATA EditData)
{
	// 引数
	// iEditNum		<-	番号(最大数未満)
	// EditData		<-	エディットの情報

	this->NowEditData[iEditNum] = EditData;
}

// エディット効果量読み込み
void DataList_GameResource::JsonLoadEditEffectValue()
{
	// ファイルが存在する場合
	/* パスとファイル名の設定 */
	std::string FilePath = "resource/SetupData/";	// 保存場所
	std::string jsonFileName = "EditDataBase.json";		// ファイル名

	/* ファイル展開 */
	std::ifstream inputFile(FilePath + jsonFileName);

	/* ファイルの展開が成功したか確認 */
	if (inputFile.is_open())
	{
		// ファイルが存在する場合
		/* 現在のステージの各評価の基準値を取得する */
		nlohmann::json	json;
		inputFile >> json;

		/* すべての要素を読み込む */
		for (auto& data : json)
		{
			/* エディット情報を取得 */
			EDIT_EFFECT_VALUE stEditEffectValue;
			data.at("Rank").get_to(stEditEffectValue.iEditRank);
			data.at("Effect").get_to(stEditEffectValue.iEditEffect);
			data.at("Value").get_to(stEditEffectValue.iValue);

			/* エディットの効果量登録 */
			EditEffectValueList.push_back(stEditEffectValue);
		}
	}
}

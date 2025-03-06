/* 2025.03.05 駒沢風助 ファイル作成 */

#include "DataList_Option.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* オプション設定管理クラスの定義 */
// コンストラクタ
DataList_Option::DataList_Option() : DataListBase("DataList_Option")
{
	/* オプションデータの読み込み */
	LoadOptionData();
}

// オプションデータ読み込み
void DataList_Option::LoadOptionData()
{
	/* Jsonファイル展開 */
	std::ifstream inputFile(FILE_PATH_OPTION);

	/* ファイルの展開が成功したか確認 */
	if (inputFile.is_open() == true)
	{
		// ファイルが存在する場合
		/* 現在のステージの各評価の基準値を取得する */
		nlohmann::json	json;
		inputFile >> json;

		for (auto& option : this->astOptionNameList)
		{
			if (json.contains(option.Name_Json) && json[option.Name_Json].contains("value"))
			{
				if (option.Type == DATA_TYPE_BOOL)
				{
					*static_cast<bool*>(option.pValue) = json[option.Name_Json]["value"].get<bool>();
				}
				else if (option.Type == DATA_TYPE_INT)
				{
					*static_cast<int*>(option.pValue) = json[option.Name_Json]["value"].get<int>();
				}
				else if (option.Type == DATA_TYPE_FLOAT)
				{
					*static_cast<float*>(option.pValue) = json[option.Name_Json]["value"].get<float>();
				}
			}
		}
	}
}

// オプションデータ保存
void DataList_Option::SaveOptionData()
{
	/* Jsonファイル読み込み */
	nlohmann::json json;

	/* 変数リストをループして JSON に書き込み */
	for (auto& option : this->astOptionNameList)
	{
		if (option.Type == DATA_TYPE_BOOL)
		{
			json[option.Name_Json]["value"] = *static_cast<bool*>(option.pValue);
		}
		else if (option.Type == DATA_TYPE_INT)
		{
			json[option.Name_Json]["value"] = *static_cast<int*>(option.pValue);
		}
		else if (option.Type == DATA_TYPE_FLOAT)
		{
			json[option.Name_Json]["value"] = *static_cast<float*>(option.pValue);
		}
	}

	/* Jsonファイル展開 */
	std::ofstream outputFile(FILE_PATH_OPTION);

	/* Jsonファイル書き込み */
	outputFile << json.dump(4);
}
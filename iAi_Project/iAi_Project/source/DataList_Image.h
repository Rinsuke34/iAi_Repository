/* 2025.02.12 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include <map>

/* 画像リソース管理クラスの宣言 */

// 画像リソース管理クラス
class DataList_Image : public DataListBase
{
	public:
		DataList_Image();				// コンストラクタ
		virtual ~DataList_Image();		// デストラクタ

		/* 画像リソース取得 */
		int*	piGetImage(std::string imageName);		// 画像取得(ポインタで返す)

	private:
		/* 管理するデータ */
		// リスト
		std::map<std::string, int>	pImageList;			// 画像リソースリスト

		/* 関数 */
		bool	bCheckImage(std::string imageName);		// 画像リソース存在確認
};

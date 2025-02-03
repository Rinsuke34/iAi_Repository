/* 2025.01.29 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include <map>

/* エフェクトリソース管理クラスの宣言 */

// エフェクトリソース管理クラス
class DataList_Effect : public DataListBase
{
	public:
		DataList_Effect();				// コンストラクタ
		virtual ~DataList_Effect();		// デストラクタ

		/* エフェクトリソース取得 */
		int		iGetEffect(std::string effectName);			// エフェクト取得

	private:
		/* 管理するデータ */
		// リスト
		std::map<std::string, int>	pEffectList;	// エフェクトリソースリスト

		/* 関数 */
		bool	bCheckEffect(std::string effectName);			// エフェクトリソース存在確認

	protected:
};

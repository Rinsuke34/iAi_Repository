/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include <map>

/* 3Dモデル管理クラスの宣言 */

// 3Dモデル管理クラス
class DataList_Model : public DataListBase
{
	public:
		DataList_Model();				// コンストラクタ
		virtual ~DataList_Model();		// デストラクタ

		/* 3Dモデル取得 */
		void	LoadModel(std::string modelName);			// 3Dモデルロード(事前読み込み用)
		int		iGetModel(std::string modelName);			// 3Dモデル取得

	private:
		/* 管理するデータ */
		// リスト
		std::map<std::string, int>	pModelHandleList;	// 3Dモデルリスト

		/* 関数 */
		bool	bCheckModel(std::string modelName);			// 3Dモデル存在確認

	protected:
};

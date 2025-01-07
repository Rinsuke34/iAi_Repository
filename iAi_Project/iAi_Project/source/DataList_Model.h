/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include <vector>
#include <map>

/* データリスト */
#include "DataList_Object.h"

/* 3Dモデル管理クラスの宣言 */

// 3Dモデル管理クラス
class DataList_Model : public DataListBase
{
	public:
		DataList_Model();				// コンストラクタ
		virtual ~DataList_Model();		// デストラクタ

		void	JsonDataLoad();			// Jsonからデータをロード"※仮作成"

		/* 3Dモデル取得 */
		int		iGetModel(std::string modelName, ObjectBase* pSetObject);	// 3Dモデル取得

	private:
		/* 管理するデータ */
		// リスト
		std::map<std::string, ObjectBase*>		pModelHandleList;	// 3Dモデルリスト(アクタとプラットフォームを対象)

		/* 関数 */
		bool	bCheckModel(std::string modelName);			// 3Dモデル存在確認

	protected:
};

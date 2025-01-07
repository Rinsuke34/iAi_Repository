/* 2024.01.07 駒沢風助 ファイル作成 */

#include "DataList_Model.h"

/* 3Dモデル管理クラスの定義 */

// コンストラクタ
DataList_Model::DataList_Model() : DataListBase("DataList_Model")
{
	/* 初期化(仮) */
}

// デストラクタ
DataList_Model::~DataList_Model()
{

}

// Jsonからデータをロード"※仮作成"
void DataList_Model::JsonDataLoad()
{

}

// 3Dモデル取得
int	DataList_Model::iGetModel(std::string modelName, ObjectBase* pSetObject)
{
	// 引数
	// modelName	: 3Dモデル名
	// pSetObject	: 3Dモデルを設定するオブジェクト(this)
	// 戻り値
	// int			: 3Dモデルハンドル(複製したものを渡す)

	int iReturn = 0;

	/* 対象の3Dモデルを取得する */
	// ※すでにあるなら複製、ないなら読み込み

	/* 対象の3Dモデルが存在するか確認 */
	if (bCheckModel(modelName) == false)
	{
		// 存在しない場合
		/* 3Dモデルを読み込む */

		/* 3Dモデルのファイルパスを取得 */
		std::string FileName = "resource/ModelData/" + modelName + ".mv1";

		/* 3Dモデルを読み込み */
		iReturn = MV1LoadModel(FileName.c_str());

		/* 読み込んだモデルを設定するオブジェクトのパスを取得 */
		this->pModelHandleList[modelName] = pSetObject;
	}
	else
	{
		// 存在している場合
		/* 対象のモデルを所持するオブジェクトを取得 */
		ObjectBase* pModel = this->pModelHandleList[modelName];

		/* そのモデルがアクタであるか確認 */
		ActorBase* pActor = dynamic_cast<ActorBase*>(pModel);

		/* キャストが成功したか確認 */
		if (pActor != nullptr)
		{
			// 成功した(アクタであった)場合
			/* モデルハンドルを複製して取得 */
			iReturn = MV1DuplicateModel(pActor->iGetModelHandle());
		}
		
		/* そのモデルがプラットフォームであるか確認 */
		PlatformBase* pPlatform = dynamic_cast<PlatformBase*>(pModel);

		/* キャストが成功したか確認 */
		if (pPlatform != nullptr)
		{
			// 成功した(プラットフォームであった)場合
			/* モデルハンドルを取得 */
			iReturn = MV1DuplicateModel(pPlatform->iGetModelHandle());
		}
	}

	return iReturn;
}

// 3Dモデル存在確認
bool DataList_Model::bCheckModel(std::string modelName)
{
	// 引数
	// modelName	: 3Dモデル名
	// 戻り値
	// bool			: 3Dモデルが登録されているか(true:登録されている / false:登録されていない)

	/* 対象の3Dモデルがリストに登録されているか確認 */

	bool bReturn = false;

	/* 対象の3Dモデルが登録されているか */
	if (this->pModelHandleList.count(modelName) != 0)
	{
		// 登録されている場合
		bReturn = true;
	}
	else
	{
		// 登録されていない場合
		bReturn = false;
	}

	return bReturn;
}

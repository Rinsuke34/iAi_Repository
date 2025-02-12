/* 2025.02.12 駒沢風助 ファイル作成 */

#include "DataList_Image.h"

/* 画像リソース管理クラスの定義 */
// コンストラクタ
DataList_Image::DataList_Image() : DataListBase("DataList_Image")
{

}

// デストラクタ
DataList_Image::~DataList_Image()
{
	/* リスト内の画像ハンドルを削除 */
	for (const auto& pair : pImageList)
	{
		/* 画像ハンドルを削除 */
		DeleteGraph(pair.second);
	}

	/* mapをクリアする */
	pImageList.clear();
}

// 画像取得(ポインタで返す)
int* DataList_Image::piGetImage(std::string imageName)
{
	// 引数
	// imageName	: 画像名
	// 戻り値
	// int*			: 画像ハンドル(ポインタ)

	int* piReturn = nullptr;

	/* 対象の画像を取得する */
	// ※すでにあるならポインタを返し、ないなら読み込み
	/* 対象の画像が存在するか確認 */
	if (bCheckImage(imageName) == false)
	{
		// 存在しない場合
		/* 画像のファイルパスを取得 */
		std::string FileName = "resource/ImageData/" + imageName + ".png";

		/* 画像を読み込み */
		int iHandle = LoadGraph(FileName.c_str());

		/* 画像をリストに追加 */
		this->pImageList[imageName] = iHandle;

		/* 読み込んだ画像をポインタで返す */
		piReturn = &this->pImageList[imageName];
	}
	else
	{
		// 存在している場合
		/* 対処の画像をポインタで返す */
		piReturn = &this->pImageList[imageName];
	}

	/* 画像ハンドルを返す */
	return piReturn;
}

// 画像リソース存在確認
bool DataList_Image::bCheckImage(std::string imageName)
{
	// 引数
	// imageName	: 画像名
	// 戻り値
	// bool		: 画像が存在するか(true:存在する / false:存在しない)

	/* 対象の画像がリストに登録されているか確認 */

	bool bReturn = false;

	/* 画像リソースが登録されているか */
	if (this->pImageList.count(imageName) != 0)
	{
		// 登録されている場合
		bReturn = true;
	}

	return bReturn;
}

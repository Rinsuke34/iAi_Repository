/* 2025.02.11 駒沢風助 ファイル作成 */

#include "DataList_GameResource.h"

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
		this->iHaveBlood = 0;

		/* エディット関連 */
		for (int i = 0; i < EDIT_MAX; i++)
		{
			/* 現在のエディット情報初期化 */
			this->NowEditData[i].iEditEffect	= EDIT_EFFECT_NONE;
			this->NowEditData[i].iEditRank		= EDIT_RANK_NONE;
		}

		// 現在のエディット情報初期化
		for (int i = 0; i < EDIT_MAX; i++)
		{
			/* 初期状態ではすべて"効果なし"に設定 */
			this->NowEditData[i].iEditEffect	= EDIT_EFFECT_NONE;

			/* ランクは"なし"に設定 */
			this->NowEditData[i].iEditRank		= EDIT_RANK_NONE;
		}

		// キープ中エディット情報初期化
		this->KeepEditData.iEditEffect	= EDIT_EFFECT_NONE;
		this->KeepEditData.iEditRank	= EDIT_RANK_NONE;
	

		/* スコア関連 */
		this->iClearTotalEvaluation = 0;
	}
}

// デストラクタ
DataList_GameResource::~DataList_GameResource()
{

}

/* データ設定 */
// 現在のエディット情報設定
void DataList_GameResource::SetNowEditData(int iEditNum, int iEditEffect, int iEditRank)
{
	// 引数
	// iEditNum		<-	番号(最大数未満)
	// iEditEffect	<-	エディット効果ID
	// iEditRank	<-	エディットランクID

	this->NowEditData[iEditNum].iEditEffect	= iEditEffect;
	this->NowEditData[iEditNum].iEditRank	= iEditRank;
}

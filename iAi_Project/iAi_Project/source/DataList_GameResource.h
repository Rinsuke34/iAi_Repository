/* 2025.02.11 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include "EditDefine.h"
#include <map>
#include <vector>

/* データリスト */
#include "DataList_Image.h"

/* ゲーム内リソース管理クラスの宣言 */
// ※通貨やエディット情報、スコアなどのリソースを管理するクラス

// ゲーム内リソース管理クラス
class DataList_GameResource : public DataListBase
{
	public:
		DataList_GameResource();			// コンストラクタ
		virtual ~DataList_GameResource();	// デストラクタ

		/* データ取得 */
		// ブラッド(ゲーム内通過)関連
		int		iGetHaveBlood() { return this->iHaveBlood; }		// 所持ブラッド取得

		// エディット関連
		int*		piGetGrHandle_EditEffect(int iEditEffect)	{ return this->pGrHandle_EditEffectList[iEditEffect]; }		// エディット効果画像ハンドル取得
		int*		piGetGrHandle_EditFrame(int iEditRank)		{ return this->pGrHandle_EditFrameList[iEditRank]; }		// エディットフレーム画像ハンドル取得
		EDIT_DATA	pGetNowEditData(int iIndex)					{ return this->NowEditData[iIndex]; }						// 現在のエディット情報取得

		/* データ設定 */
		// ブラッド(ゲーム内通過)関連
		void	SetHaveBlood(int iBlood)					{ this->iHaveBlood			= iBlood; }	// 所持ブラッド設定
		void	SetClearEvaluation(int iClearEvaluation)	{ this->iClearEvaluation	= iClearEvaluation; }

		// エディット関連
		void	SetNowEditData(int iEditNum, int iEditEffect, int iEditRank);	// 現在のエディット情報設定

	private:
		/* 変数(管理用) */
		std::map<int, int*>	pGrHandle_EditEffectList;	// 画像ハンドル
		std::map<int, int*>	pGrHandle_EditFrameList;	// エディット情報リスト

		/* 変数 */
		/* ブラッド(ゲーム内通貨)関連 */
        int iHaveBlood;									// 所持ブラッド

		/* エディット関連 */
		EDIT_DATA	NowEditData[EDIT_MAX];				// 現在のエディット情報

		/* スコア関連 */
		int		iClearEvaluation;						// ステージクリア時の評価
};

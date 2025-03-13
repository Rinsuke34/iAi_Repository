/* 2025.02.11 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include "EditDefine.h"
#include "PublicInclude.h"
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
		DataList_GameResource();				// コンストラクタ
		virtual ~DataList_GameResource() {};	// デストラクタ

		/* データ取得 */
		// ブラッド(ゲーム内通過)関連
		int		iGetHaveBlood() { return this->iHaveBlood; }		// 所持ブラッド取得

		// エディット関連
		int* piGetGrHandle_EditEffect(int iEditEffect)			{ return this->pGrHandle_EditEffectList[iEditEffect]; }		// エディット効果画像ハンドル取得
		int* piGetGrHandle_EditFrame(int iEditRank)				{ return this->pGrHandle_EditFrameList[iEditRank]; }		// エディットフレーム画像ハンドル取得
		EDIT_DATA			stGetNowEditData(int iIndex)		{ return this->NowEditData[iIndex]; }						// 現在のエディット情報取得
		EDIT_DATA			stGetKeepEditData()					{ return this->KeepEditData; }								// キープ中のエディット情報取得
		EDIT_DATA*			pstGetNowEditData(int iIndex)		{ return &this->NowEditData[iIndex]; }						// 現在のエディット情報のポインタ取得
		EDIT_DATA*			pstGetKeepEditData()				{ return &this->KeepEditData; }								// キープ中のエディット情報のポインタ取得
		std::vector<EDIT_EFFECT_VALUE>	GetEffectValueList()	{ return this->EditEffectValueList; }						// エディット効果量取得

		// スコア関連
		int		iGetClearEvaluation()	{ return this->iClearTotalEvaluation; }		// ステージクリア時の合計評価(D～Sの5段階*3種類)取得

		/* データ設定 */
		// ブラッド(ゲーム内通過)関連
		void	SetHaveBlood(int iBlood)	{ this->iHaveBlood	= iBlood; }			// 所持ブラッド設定

		// エディット関連
		void	SetNowEditData(int iEditNum, int iEditEffect, int iEditRank);								// 現在のエディット情報設定
		void	SetKeepEditData(EDIT_DATA KeepEditData)			{ this->KeepEditData = KeepEditData; };		// キープ中のエディット情報取得

		// スコア関連
		void	SetClearEvaluation(int iClearTotalEvaluation)	{ this->iClearTotalEvaluation = iClearTotalEvaluation; }	// ステージクリア時の合計評価(D～Sの5段階*3種類)設定

	private:
		/* 変数(管理用) */
		std::map<int, int*>	pGrHandle_EditEffectList;	// 画像ハンドル
		std::map<int, int*>	pGrHandle_EditFrameList;	// エディット情報リスト

		/* 関数 */
		void	JsonLoadEditEffectValue();			// エディット効果量読み込み

		/* 変数 */
		/* ブラッド(ゲーム内通貨)関連 */
        int iHaveBlood;									// 所持ブラッド

		/* エディット関連 */
		EDIT_DATA						NowEditData[EDIT_MAX];	// 現在のエディット情報
		EDIT_DATA						KeepEditData;			// キープ中のエディット情報
		std::vector<EDIT_EFFECT_VALUE>	EditEffectValueList;	// エディットの効果量

		/* スコア関連 */
		int		iClearTotalEvaluation;					// ステージクリア時の合計評価(D～Sの5段階*3種類)
};

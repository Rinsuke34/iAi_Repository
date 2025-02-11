/* 2025.02.11 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include "EditDefine.h"

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
		int		iGetHaveBlood()				{ return this->iHaveBlood; }		// 所持ブラッド取得

		/* データ設定 */
		// ブラッド(ゲーム内通過)関連
		void	SetHaveBlood(int iBlood)	{ this->iHaveBlood	=	iBlood; }	// 所持ブラッド設定

	private:
		/* ブラッド(ゲーム内通貨)関連 */
		int iHaveBlood;		// 所持ブラッド

		/* エディット関連 */

		/* スコア関連 */
};

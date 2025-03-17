/* 2025.02.24 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"
#include "PublicInclude.h"

/* すべての画面エフェクトのベースとなるクラスの宣言 */

// 画面エフェクトベースクラス
class ScreenEffect_Base
{
	public:
		ScreenEffect_Base();				// コンストラクタ
		virtual ~ScreenEffect_Base()	{};	// デストラクタ

		virtual void	Update(int iGrHandle_Screen);	// 更新

		bool	bGetDeleteFlg() { return this->bDeleteFlg; };	// 削除フラグを取得

		void	SetDeleteFlg(bool bDeleteFlg)	{ this->bDeleteFlg	= bDeleteFlg; };	// 削除フラグを設定
		void	SetDeleteTime(int iDeleteTime)	{ this->iDeleteTime	= iDeleteTime; };	// 削除時間を設定

	protected:
		/* 関数 */
		virtual void	ScreenEffectDraw(int iGrHandle_Screen) {};	// 画面エフェクト描写(引数は対象の画像のハンドル)

		/* 変数 */
		bool bDeleteFlg;	// 削除フラグ(有効なら画面エフェクトクラスを削除)
		int iDeleteTime;	// 削除時間(フレーム数)
};

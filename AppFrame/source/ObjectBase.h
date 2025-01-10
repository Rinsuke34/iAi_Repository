/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include <DxLib.h>
#include "AppStructDefine.h"

/* すべてのオブジェクトのベースとなるクラスの宣言 */

// オブジェクトベースクラス
class ObjectBase
{
	public:
		ObjectBase();					// コンストラクタ
		virtual ~ObjectBase() {};		// デストラクタ

		virtual void	Update() {};	// 更新

		bool	bGetDeleteFlg()		{ return this->bDeleteFlg; };		// 削除フラグを取得
		VECTOR	vecGetPosition()	{ return this->vecPosition; };		// 座標を取得

		void	SetDeleteFlg(bool bDeleteFlg)	{ this->bDeleteFlg	= bDeleteFlg; };	// 削除フラグを設定
		void	SetPosition(VECTOR vecPostion)	{ this->vecPosition	= vecPostion; };	// オブジェクトの座標を設定

	private:
	protected:
		/* 関数 */

		/* 変数 */
		bool	bDeleteFlg;				// 削除フラグ(有効ならオブジェクトを削除)
		VECTOR	vecPosition;			// オブジェクトの座標
};
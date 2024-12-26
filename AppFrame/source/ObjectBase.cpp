/* 2024.12.15 駒沢風助 ファイル作成 */

#include "ObjectBase.h"

/* すべてのオブジェクトのベースとなるクラスの定義 */

// コンストラクタ
ObjectBase::ObjectBase()
{
	/* 初期化 */
	this->bDeleteFlg	= false;	// 削除フラグ
	this->vecPosition	= {};		// オブジェクト座標
}

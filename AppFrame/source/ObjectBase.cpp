/* 2024.12.15 駒沢風助 ファイル作成 */

#include "ObjectBase.h"

/* すべてのオブジェクトのベースとなるクラスの定義 */

// コンストラクタ
ObjectBase::ObjectBase()
{
	/* 初期化 */
	this->bDeleteFlg	= false;				// 削除フラグ
	this->vecPosition	= {};					// オブジェクト座標
	this->vecRotation	= {};					// オブジェクトの回転量
	this->vecScale		= VGet(1.f, 1.f, 1.f);	// オブジェクトの拡大率
}

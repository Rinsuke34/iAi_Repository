/* 2024.12.15 駒沢風助 ファイル作成 */

#include "ObjectBase.h"

/* すべてのオブジェクトのベースとなるクラスの定義 */

// コンストラクタ
ObjectBase::ObjectBase()
{
	/* 初期化 */
	this->bDeleteFlg			= false;				// 削除フラグ
	this->vecPosition			= VGet(0.f, 0.f, 0.f);	// オブジェクト座標
	this->vecRotation			= VGet(0.f, 0.f, 0.f);	// オブジェクトの回転量
	this->vecScale				= VGet(1.f, 1.f, 1.f);	// オブジェクトの拡大率
	this->vecPosition_Initial	= VGet(0.f, 0.f, 0.f);	// 初期状態でのオブジェクトの座標
	this->vecRotation_Initial	= VGet(0.f, 0.f, 0.f);	// 初期状態でのオブジェクトの回転量
	this->vecScale_Initial		= VGet(1.f, 1.f, 1.f);	// 初期状態でのオブジェクトの拡大率(x,y,z方向それぞれの拡大倍率)
}

// 初期位置設定
void ObjectBase::SetupInitialPosition()
{
	/* 初期位置を設定 */
	this->vecPosition_Initial	= this->vecPosition;
	this->vecRotation_Initial	= this->vecRotation;
	this->vecScale_Initial		= this->vecScale;
}
/* 2024.12.21 駒沢風助 ファイル作成 */

#pragma once
#include "EnemyBase.h"

/* すべてのエネミーのベースとなるクラスの定義 */

// コンストラクタ
EnemyBase::EnemyBase() : CharacterBase()
{
	/* 初期化 */
	this->iMaxHp			= 0;					// 最大HP
	this->iNowHp			= 0;					// 現在HP
	this->iObjectType		= OBJECT_TYPE_ENEMY;	// オブジェクトの種類
}

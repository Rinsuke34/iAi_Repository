/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "ActorBase.h"

/* すべてのアクタのベースとなるクラスの定義 */

// コンストラクタ
ActorBase::ActorBase() : ObjectBase()
{
	/* 初期化 */
	this->vecMovement	= {};	// 移動量
	this->iModelHandle	= -1;	// モデルハンドル
}

// デストラクタ
ActorBase::~ActorBase()
{
	/* モデルハンドル削除 */
	MV1DeleteModel(this->iModelHandle);
}

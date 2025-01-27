/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "ActorBase.h"

/* すべてのアクタのベースとなるクラスの定義 */

// コンストラクタ
ActorBase::ActorBase() : ObjectBase()
{
	/* 初期化 */
	this->iModelHandle	= -1;	// モデルハンドル
	this->iLightFrameNo	= -2;	// 発光部分の設定されたモデルのフレーム番号
	this->iObjectType	= -1;	// オブジェクトの種類
}

// デストラクタ
ActorBase::~ActorBase()
{
	/* モデルハンドル削除 */
	MV1DeleteModel(this->iModelHandle);
}

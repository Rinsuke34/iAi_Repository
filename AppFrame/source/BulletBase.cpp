/* 2024.12.18 駒沢風助 ファイル作成 */

#include "BulletBase.h"

/* すべての弾丸のベースとなるクラスの定義 */

// コンストラクタ
BulletBase::BulletBase() : ActorBase()
{
	/* 初期化 */
	this->stCollisionSqhere = {};	// コリジョン(球体)
	this->vecMoveDirection	= {};	// 移動方向
}

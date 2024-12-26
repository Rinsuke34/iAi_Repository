/* 2024.12.18 駒沢風助 ファイル作成 */

#pragma once
#include "ActorBase.h"
#include "AppStructDefine.h"

/* すべての弾丸のベースとなるクラスの宣言 */

// 弾丸ベースクラス
class BulletBase : public ActorBase
{
	public:
		BulletBase();				// コンストラクタ
		virtual ~BulletBase() {};	// デストラクタ

		virtual void	Update() {};		// 更新
		virtual void	Draw() {};			// 描写

		Struct_Collision::COLLISION_SQHERE	stGetCollision_Sqhere() { return this->stCollisionSqhere; };		// コリジョン(球体)を取得
		VECTOR								GetMoveDirection()		{ return this->vecMoveDirection; };			// 移動方向を取得

		void	SetCollision_Capsule(Struct_Collision::COLLISION_SQHERE stCollisionSqhere) { this->stCollisionSqhere = stCollisionSqhere; };	// コリジョン(カプセル)を設定
		void	SetMoveDirection(VECTOR vecMoveDirection) { this->vecMoveDirection = vecMoveDirection; };										// 移動方向を設定

	private:
	protected:
		/* 関数 */

		/* 変数 */
		Struct_Collision::COLLISION_SQHERE		stCollisionSqhere;		// コリジョン(球体)
		VECTOR vecMoveDirection;										// 移動方向
};

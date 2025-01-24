/* 2024.12.18 駒沢風助 ファイル作成 */

#pragma once
#include "ActorBase.h"
#include "AppStructDefine.h"

/* 名前空間省略 */
using namespace Struct_Collision;

/* すべての弾丸のベースとなるクラスの宣言 */

// 弾丸ベースクラス
class BulletBase : public ActorBase
{
	public:
		BulletBase();				// コンストラクタ
		virtual ~BulletBase() {};	// デストラクタ

		virtual void	Initialization()	override	{};	// 初期化
		virtual void	Update()			override	{};	// 更新
		virtual void	Draw()				override	{};	// 描写
		virtual void	BloomDraw()			override	{};	// 発光描写
		virtual void	CollisionDraw();					// 当たり判定描写

		/* 接触判定 */
		// 簡易的な結果(接触しているかどうか)
		bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// 球体 - カプセル
		bool	HitCheck(COLLISION_SQHERE	stSqhere);			// 球体 - 球体
		bool	HitCheck(int iModelHandle, int iFrameIndex);	// 球体 - モデル

		COLLISION_SQHERE	stGetCollision_Sqhere() { return this->stCollisionSqhere; };		// コリジョン(球体)を取得
		VECTOR				vecGetMoveDirection()	{ return this->vecDirection; };				// 向きを取得
		float				fGetMoveSpeed()			{ return this->fMoveSpeed; };				// 移動速度を取得

		void	SetCollision_Capsule(COLLISION_SQHERE stCollisionSqhere)	{ this->stCollisionSqhere	= stCollisionSqhere; };		// コリジョン(球体)を設定
		void	SetDirection(VECTOR vecDirection)							{ this->vecDirection		= vecDirection; };			// 向きを設定
		void	SetMoveSpeed(float fMoveSpeed)								{ this->fMoveSpeed			= fMoveSpeed; };			// 移動速度を設定

	private:
	protected:
		/* 関数 */

		/* 変数 */
		COLLISION_SQHERE			stCollisionSqhere;		// コリジョン(球体)
		VECTOR						vecDirection;			// 向き
		float						fMoveSpeed;				// 移動速度
};

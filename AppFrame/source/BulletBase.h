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

		virtual void	CollisionDraw();					// 当たり判定描写

		/* 接触判定 */
		// 簡易的な結果(接触しているかどうか)
		virtual bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// 球体 - カプセル
		virtual bool	HitCheck(COLLISION_SQHERE	stSqhere);			// 球体 - 球体
		virtual bool	HitCheck(int iModelHandle, int iFrameIndex);	// 球体 - モデル

		COLLISION_SQHERE	stGetCollision_Sqhere() { return this->stCollisionSqhere; };		// コリジョン(球体)を取得
		VECTOR				vecGetMoveDirection()	{ return this->vecDirection; };				// 向きを取得
		float				fGetMoveSpeed()			{ return this->fMoveSpeed; };				// 移動速度を取得
		int					iGetTargetType()		{ return this->iTargetObjectType; };		// 接触する対象のタイプを取得
		bool				bGetParryFlg()			{ return this->bParryFlg; };				// パリィフラグ(反射できるか)を取得

		void	SetCollision_Sqhere(COLLISION_SQHERE stCollisionSqhere)		{ this->stCollisionSqhere	= stCollisionSqhere; };		// コリジョン(球体)を設定
		void	SetDirection(VECTOR vecDirection)							{ this->vecDirection		= vecDirection; };			// 向きを設定
		void	SetMoveSpeed(float fMoveSpeed)								{ this->fMoveSpeed			= fMoveSpeed; };			// 移動速度を設定
		void	SetTargetType(int iTargetType)								{ this->iTargetObjectType	= iTargetType; };			// 接触する対象のタイプを設定
		void	SetParryFlg(bool bParryFlg)									{ this->bParryFlg			= bParryFlg; };				// パリィフラグ(反射できるか)を設定

	protected:
		/* 変数 */
		COLLISION_SQHERE			stCollisionSqhere;		// コリジョン(球体)
		VECTOR						vecDirection;			// 向き
		float						fMoveSpeed;				// 移動速度
		int							iTargetObjectType;		// 接触する対象のタイプ
		bool						bParryFlg;				// パリィフラグ(反射できるか)
		int							iBulletType;			// 弾丸の種類(反射可能であるか)
};

/* 2025.01.27 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* 近接攻撃(強)クラスの宣言 */

// 近接攻撃(強)
class BulletPlayerMeleeStrong : public BulletBase
{
	public:
		BulletPlayerMeleeStrong();				// コンストラクタ
		virtual ~BulletPlayerMeleeStrong() {};	// デストラクタ

		virtual void	Update()			override;	// 更新
		virtual void	CollisionDraw()		override;	// 当たり判定描写

		/* 接触判定 */
		// 簡易的な結果(接触しているかどうか)
		bool	HitCheck(COLLISION_CAPSULE	stCapsule)		override;	// 球体 - カプセル
		bool	HitCheck(COLLISION_SQHERE	stSqhere)		override;	// 球体 - 球体
		bool	HitCheck(int iModelHandle, int iFrameIndex)	override;	// 球体 - モデル

		COLLISION_CAPSULE	stGetCollision_Capsule()	{ return this->stCollisionCapsule; };	// コリジョン(カプセル)を取得

		void	SetCollision_Capsule(COLLISION_CAPSULE stCollisionCapsule)	{ this->stCollisionCapsule = stCollisionCapsule; };		// コリジョン(カプセル)を設定

	private:
		/* 変数 */
		COLLISION_CAPSULE	stCollisionCapsule;		// コリジョン(カプセル)

		int iDeleteCount;	// 仮追加の削除カウント
	protected:
};

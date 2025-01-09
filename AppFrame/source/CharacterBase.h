/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "ActorBase.h"

/* 名前空間省略 */
using namespace Struct_Collision;

/* すべてのキャラクターのベースとなるクラスの宣言 */

// キャラクターベースクラス
class CharacterBase : public ActorBase
{
	public:
		CharacterBase();	// コンストラクタ
		virtual ~CharacterBase() {};		// デストラクタ

		virtual void	Update() {};		// 更新
		virtual void	Draw() {};			// 描写

		/* 接触判定 */
		// 簡易的な結果(接触しているかどうか)
		bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// カプセル - カプセル
		bool	HitCheck(COLLISION_SQHERE	stSqhere);			// カプセル - 球体
		bool	HitCheck(int iModelHandle, int iFrameIndex);	// カプセル - モデル

		COLLISION_CAPSULE	stGetCollision_Capsule()	{ return this->stCollisionCapsule; };		// コリジョン(カプセル)を取得
		VECTOR				GetDirection()				{ return this->vecDirection; };				// 向きを取得

		void	SetCollision_Capsule(COLLISION_CAPSULE stCollisionCapsule)	{ this->stCollisionCapsule	= stCollisionCapsule; };	// コリジョン(カプセル)を設定
		void	SetDirection(VECTOR vecDirection)							{ this->vecDirection		= vecDirection; };			// 向きを設定

	private:
	protected:
		/* 関数 */

		/* 変数 */
		COLLISION_CAPSULE		stCollisionCapsule;		// コリジョン(カプセル)
		VECTOR vecDirection;							// 向き
};

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

		virtual void	Initialization()	override;		// 初期化
		virtual void	BloomDraw()			override;		// 発光描写
		virtual void	CollisionDraw()		override;		// 当たり判定描写
		virtual void	Draw()				override;		// 描写

		/* 接触判定 */
		// 簡易的な結果(接触しているかどうか)
		bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// カプセル - カプセル
		bool	HitCheck(COLLISION_SQHERE	stSqhere);			// カプセル - 球体
		bool	HitCheck(int iModelHandle, int iFrameIndex);	// カプセル - モデル

		COLLISION_CAPSULE	stGetCollision_Capsule()	{ return this->stCollisionCapsule; };		// コリジョン(カプセル)を取得
		int					iGetInvincibilityTime()		{ return this->iInvincibilityTime; };		// 無敵時間を取得

		void	SetCollision_Capsule(COLLISION_CAPSULE stCollisionCapsule)	{ this->stCollisionCapsule	= stCollisionCapsule; };	// コリジョン(カプセル)を設定
		void	SetInvincibilityTime(int iInvincibilityTime)				{ this->iInvincibilityTime	= iInvincibilityTime; };	// 無敵時間を設定

	private:
	protected:
		/* 関数 */
		void	UpdataLightFrame();						// 発光の設定されたフレームを取得

		/* 変数 */
		COLLISION_CAPSULE		stCollisionCapsule;		// コリジョン(カプセル)
		int						iInvincibilityTime;		// 無敵時間
		std::vector<int>		aiLightFrameNo;			// 発光フレーム番号
};

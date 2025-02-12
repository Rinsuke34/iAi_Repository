/* 2025.02.11 駒沢風助 ファイル作成 */

#pragma once
#include "CharacterBase.h"

/* すべての実体のないアイテムのベースとなるクラスの宣言 */

// 実体なしアイテムクラス
class EffectItemBase : public CharacterBase
{
	public:
		EffectItemBase();				// コンストラクタ
		virtual ~EffectItemBase() {};	// デストラクタ

		virtual void	Initialization()	override {};	// 初期化
		virtual void	BloomDraw()			override {};	// 発光描写
		virtual void	CollisionDraw()		override {};	// 当たり判定描写
		virtual void	Draw()				override {};	// 描写

		/* 接触判定 */
		// ※使用しないのですべてfalseを返す
		bool	HitCheck(COLLISION_CAPSULE	stCapsule)		{ return false; };	// カプセル - カプセル
		bool	HitCheck(COLLISION_SQHERE	stSqhere)		{ return false; };	// カプセル - 球体
		bool	HitCheck(int iModelHandle, int iFrameIndex)	{ return false; };	// カプセル - モデル

	private:
	protected:

};

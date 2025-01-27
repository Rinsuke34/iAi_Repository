/* 2025.01.22 駒沢風助 ファイル作成 */

#pragma once
#include "PlatformBase.h"

/* 名前空間省略 */
using namespace Struct_Collision;

/* プラットフォームコリジョンのベースとなるクラスの宣言 */
// ※デザイナーの負担対策にコリジョン用と描写用でモデルを分ける

// プラットフォームコリジョンクラス
class CollisionBase : public PlatformBase
{
	public:
		CollisionBase();				// コンストラクタ
		virtual ~CollisionBase() {};	// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	CollisionDraw();					// 当たり判定描写

		/* 接触判定 */
		// 簡易的な結果(接触しているかどうか)
		bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// モデル - カプセル
		bool	HitCheck(COLLISION_SQHERE	stSqhere);			// モデル - 球体
		bool	HitCheck(COLLISION_LINE		stLine);			// モデル - 線分
		// 詳細な結果(接触ポリゴン数、接触位置など)
		MV1_COLL_RESULT_POLY		HitCheck_Line(COLLISION_LINE		stLine);	// モデル - 線分
		MV1_COLL_RESULT_POLY_DIM	HitCheck_Capsule(COLLISION_CAPSULE	stCapsule);	// モデル - カプセル

	private:
	protected:
		/* 関数 */
		void	UpdateCollisionFrame();					// コリジョンの設定されたフレームの設定

		/* 変数 */
		int						iCollisionFrameNo;		// コリジョンフレーム番号(※モデルにつき1つだけ)
};

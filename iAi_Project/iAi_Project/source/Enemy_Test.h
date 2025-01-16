/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* テスト用敵クラス */

// エネミーベースクラス
class TestEnemy : public EnemyBase
{
	public:
		TestEnemy();				// コンストラクタ
		virtual ~TestEnemy();		// デストラクタ

		virtual void	Update();		// 更新
		virtual void	Draw();			// 描写

		COLLISION_CAPSULE stCollisionCapsule;// コリジョン(カプセル)
	private:
	protected:
		/* 関数 */
		void	CollisionUpdate();		// コリジョン更新
};

		/* 変数 */


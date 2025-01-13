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

		virtual void	Initialization();	// 初期化
		virtual void	Update();			// 更新
		virtual void	Draw();				// 描写

	private:
	protected:
		/* 関数 */

		/* 変数 */
};

/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* テスト用敵クラス */

// エネミーベースクラス
class TestEnemy : public EnemyBase
{
	public:
		TestEnemy();				// コンストラクタ
		virtual ~TestEnemy();		// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新

	private:
	protected:
		/* 使用するデータリスト */
		DataList_Object* ObjectList;			// オブジェクト管理

		/* 関数 */

		/* 変数 */
};

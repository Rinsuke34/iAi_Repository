/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* オブジェクト */
#include "EnemyBasic.h"
#include "EffectManualDelete.h"

/* テスト用敵クラス */

// エネミーベースクラス
class TestEnemy : public EnemyBasic
{
	public:
		TestEnemy();				// コンストラクタ
		virtual ~TestEnemy();		// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新

	private:
		EffectManualDelete* eEffect;
	protected:
		/* 使用するデータリスト */
		DataList_Object* ObjectList;			// オブジェクト管理
		void MoveEnemy(); // 敵を移動させるメソッドを追加

		int actioncount;
};

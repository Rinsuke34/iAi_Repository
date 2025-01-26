/* 2025.01.21 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* ゴールオブジェクトクラスの宣言 */
// ※エネミーとして作成する(仮)

// ゴールクラス
class EnemyGoalObject : public EnemyBase
{
	public:
		EnemyGoalObject();				// コンストラクタ
		virtual ~EnemyGoalObject();		// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新

	private:
	protected:
		/* 使用するデータリスト */
		DataList_Object* ObjectList;			// オブジェクト管理

		/* 関数 */

		/* 変数 */
};

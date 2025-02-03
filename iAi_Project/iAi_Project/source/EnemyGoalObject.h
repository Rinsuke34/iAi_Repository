/* 2025.01.21 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_GameStatus.h"

/* オブジェクト */
#include "EnemyBasic.h"

/* ゴールオブジェクトクラスの宣言 */
// ※エネミーとして作成する(仮)

// ゴールクラス
class EnemyGoalObject : public EnemyBasic
{
	public:
		EnemyGoalObject();				// コンストラクタ
		virtual ~EnemyGoalObject();		// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新

		bool	bGetStageChangeFlg()	{ return this->bStageChangeFlg; };		// 次のステージに遷移するかのフラグを取得

		void	SetStageChangeFlg(bool bStageChangeFlg)	{ this->bStageChangeFlg = bStageChangeFlg; }	// 次のステージに遷移するかのフラグを設定

	private:
	protected:
		/* 使用するデータリスト */
		DataList_Object*		ObjectList;			// オブジェクト管理
		DataList_GameStatus*	GameStatusList;		// ゲーム状態管理

		/* 変数 */
		bool	bStageChangeFlg;	/* 次のステージに遷移するかのフラグ */
};

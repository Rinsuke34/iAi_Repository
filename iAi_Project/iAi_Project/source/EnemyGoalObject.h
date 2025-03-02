/* 2025.01.21 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_StageStatus.h"

/* オブジェクト */
#include "EnemyBasic.h"
#include "EffectManualDelete.h"

/* ゴールオブジェクトクラスの宣言 */

// ゴールクラス
class EnemyGoalObject : public EnemyBasic
{
	public:
		EnemyGoalObject();				// コンストラクタ
		virtual ~EnemyGoalObject();		// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新
		virtual void	BloomDraw()			override;		// 発光描写

		/* データ取得 */
		bool	bGetStageChangeFlg()	{ return this->bStageChangeFlg; };		// 次のステージに遷移するかのフラグを取得

		/* データ設定 */
		void	SetStageChangeFlg(bool bStageChangeFlg)	{ this->bStageChangeFlg = bStageChangeFlg; }	// 次のステージに遷移するかのフラグを設定

	private:
		/* 使用するデータリスト */
		DataList_Object*		ObjectList;			// オブジェクト管理
		DataList_StageStatus*	StageStatusList;	// ゲーム状態管理

		/* 変数 */
		bool	bStageChangeFlg;	/* 次のステージに遷移するかのフラグ */

		/* エフェクト */
		EffectManualDelete* pEffect_Glory;		// 発光エフェクト
		EffectManualDelete* pEffect_Clear;		// 撃破時エフェクト
};

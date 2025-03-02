/* 2025.02.16 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_StageStatus.h"
#include "DataList_GameResource.h"
#include "DataList_PlayerStatus.h"

/* シーン"リザルト"クラスの宣言 */

// シーン"リザルト"
class SceneResult : public SceneBase
{
	public:
		SceneResult();							// コンストラクタ
		virtual ~SceneResult();					// デストラクタ

		void	Initialization()	override;	// 初期化
		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_StageStatus*	StageStatusList;	// ゲーム状態管理
		DataList_GameResource*	GameResourceList;	// ゲーム内リソース管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態管理

		/* 関数 */
		void	Process_Main();					// メイン処理
		void	ResultCalculation_JsonLoad();	// 評価基準取得
		void	ClearEvaluation();				// 評価算出

		/* 変数 */
		int		iClearEvaluation_Combo;						// 評価(最大コンボ)
		int		iClearEvaluation_Time;						// 評価(クリアタイム)
		int		iClearEvaluation_Damage;					// 評価(被ダメージ)
		int		iClearEvaluation_Total;						// 評価(総合)
		int		Calculation_Combo[RESULT_EVALUATION_MAX];	// 評価基準(コンボ数)
		int		Calculation_Time[RESULT_EVALUATION_MAX];	// 評価基準(クリアタイム)
		int		Calculation_Damage[RESULT_EVALUATION_MAX];	// 評価基準(被ダメージ数)
};

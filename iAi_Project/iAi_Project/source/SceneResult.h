/* 2025.02.16 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"
#include "SceneResultDefine.h"

/* データリスト */
#include "DataList_StageStatus.h"
#include "DataList_GameResource.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Image.h"

/* シーン */
#include "SceneConversation.h"

/* シーン"リザルト"クラスの宣言 */

// シーン"リザルト"
class SceneResult : public SceneBase
{
	public:
		SceneResult();							// コンストラクタ
		virtual ~SceneResult() {};				// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_StageStatus*	StageStatusList;	// ゲーム状態管理
		DataList_GameResource*	GameResourceList;	// ゲーム内リソース管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態管理

		/* 使用する画像のハンドル */
		int*	piGrHandle_ResultBackGround;					// リザルト画面の背景
		int*	piGrHandle_String_Result;						// リザルト画面の文字(リザルト)
		int*	piGrHandle_String_Rank;							// リザルト画面の文字(ランク)
		int*	piGrHandle_ResultFrame;							// リザルトフレーム
		int*	apiGrHandle_Alphabet[RESULT_EVALUATION_MAX];	// アルファベット(コンボ用の物を流用)

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
		int		iAddTextNo;									// 追加するテキスト番号
};

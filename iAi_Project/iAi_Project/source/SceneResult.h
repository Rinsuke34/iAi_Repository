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
		int*	piGrHandle_ResultBackGround;							// リザルト画面の背景
		int*	apiGrHandle_Alphabet_Section[RESULT_EVALUATION_MAX];	// 各評価のアルファベット
		int*	apiGrHandle_Alphabet[RESULT_EVALUATION_MAX];			// 総合評価アルファベット(コンボ用の物を流用)

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
		int		iDrawFaze;									// 描写フェーズ
		int		iDrawTimeMinute;							// クリアタイム(分)(描写用)
		int		iDrawTimeSecond;							// クリアタイム(秒)(描写用)
		int		iDrawTimeFractionalSecond;					// クリアタイム(少数秒)(描写用)
		int		iDrawMaxCombo;								// 最大コンボ(描写用)
		int		iDrawTakeDamage;							// 被ダメージ(描写用)
		int		iDrawTotalGetBlood;							// 獲得ブラッド(描写用)
		int		iDrawDelayTime;								// 描写遅延時間
		bool	bPlaySoundCount;							// SE"リザルトカウント"が再生中であるかのフラグ
};

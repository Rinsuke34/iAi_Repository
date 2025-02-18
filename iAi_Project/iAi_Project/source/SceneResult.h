/* 2025.02.16 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_GameStatus.h"
#include "DataList_GameResource.h"

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
		DataList_GameStatus* GameStatusList;		// ゲーム状態管理
		DataList_GameResource* GameResourceList;	// ゲーム内リソース管理

		/* 関数 */
		void	Process_Main();		// メイン処理
		void	Process_Decid();	// 決定入力時の処理

		/* 変数 */
		int		iClearEvaluation_Combo;		// 評価(最大コンボ)
		int		iClearEvaluation_Time;		// 評価(クリアタイム)
		int		iClearEvaluation_Damage;	// 評価(被ダメージ)
		int		iClearEvaluation_Total;		// 評価(総合)
};

/* 2025.02.20 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_StageStatus.h"
#include "DataList_Image.h"

/* シーン */
#include "SceneAddTitleSetup.h"

/* シーン"ゲームオーバー"クラスの宣言 */

// シーン"ゲームオーバー"
class SceneGameOver : public SceneBase
{
	public:
		SceneGameOver();						// コンストラクタ
		virtual ~SceneGameOver() {};			// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_StageStatus* StageStatusList;	// ゲーム状態管理

		/* 使用する画像のハンドル */
		int* piGrHandle_GameOver;				// ゲームオーバー
		int* piGrHandle_Window_GameOver;		// ウィンドウ(リトライ)
		int* piGrHandle_Window_GameOverCheck;	// ウィンドウ(リトライ警告)
		int* apiGrHandle_SkipWindow_Yes[2];		// スキップ確認YES(0:選択中/1:非選択中)
		int* apiGrHandle_SkipWindow_No[2];		// スキップ確認NO(0:選択中/1:非選択中)

		/* 変数 */
		int		iBlendAlpha;					// 描写する画像のアルファ値(0～255)
		int		iDrawPhase;						// 描写フェイズ(0:ゲームオーバー, 1:リトライ確認, 2:リトライ最終確認)
		bool	bSelectYes;						// YESを選択中であるか(スキップ画面)
};

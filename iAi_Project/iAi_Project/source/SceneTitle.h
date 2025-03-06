/* 2024.12.XX YYYY ZZZZ */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* シーン */
#include "SceneStage.h"
#include "SceneAddGameSetup.h"
#include "Screen.h"
#include "LargeScreen.h"


/* データリスト */
#include "DataList_StageStatus.h"
#include "DataList_Input.h"
#include "DataList_Model.h"
#include "DataList_Object.h"

/* 循環参照対策 */
class SceneStage;

/* シーン「タイトル」の宣言 */

// シーン "タイトル画面"
class SceneTitle : public SceneBase
{
	public:
		SceneTitle();							// コンストラクタ
		virtual ~SceneTitle();					// デストラクタ

		void	Initialization()	override;	// 初期化
		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_StageStatus* StageStatusList;	// ゲーム状態管理
		DataList_Input* InputList;			// 入力管理/* 使用するデータリスト */
		DataList_Object* ObjectList;			// オブジェクト管理
		DataList_Model* ModelList;			// 3Dモデル管理

		/* シーン"ステージ"のポインタ */
		SceneStage* pSceneStage;

		/* 使用する画像のハンドル */
		int* piGrHandle_TitleLogo;		// タイトルロゴ
		//変数
		int iUICount;	//UIのカウント
		//UIの画像Handle
		int iImageNewgameHandle;		// ニューゲーム
		int iImageNewgameChoiceHandle;	// ニューゲーム選択
		int iImageContinueHandle;		// コンティニュー
		int iImageContinueChoiceHandle;	// コンティニュー選択
		int iImageDateHandle;			// データ
		int iImageDateChoiceHandle;		// データ選択
		int iImageConfigHandle;			// コンフィグ
		int iImageConfigChoiceHandle;	// コンフィグ選択

		bool bGameStartFlg;					//スタートフラグ

};

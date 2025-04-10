/* 2024.12.20 ファイル追加 駒沢風助 */

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

/* グローバル変数 */
extern bool g_bActiveFlg;

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
		DataList_Input* InputList;				// 入力管理/* 使用するデータリスト */
		DataList_Object* ObjectList;			// オブジェクト管理
		DataList_Model* ModelList;				// 3Dモデル管理

		/* シーン"ステージ"のポインタ */
		SceneStage* pSceneStage;



		//変数
		int iUICount;							// UIのカウント
		int iTimer;								// タイマーを追加
		int iAlphaCount;						// アルファカウントを追加
		bool bTransition;						// シーン遷移フラグを追加
		bool bHideFinalCheck;					// 最終確認画面を隠すフラグを追加
		bool bAlphaFlg;							// アルファフラグを追加
		bool bConfigFlg;						// コンフィグフラグを追加
		bool bSettingFlg;						// 設定フラグを追加

		VECTOR	vecMovePos;

		//UIの画像Handle
		int iImageNewgameHandle;				// ニューゲーム
		int iImageNewgameChoiceHandle;			// ニューゲーム選択
		int iImageContinueHandle;				// コンティニュー
		int iImageContinueChoiceHandle;			// コンティニュー選択
		int iImageDateHandle;					// データ
		int iImageDateChoiceHandle;				// データ選択
		int iImageConfigHandle;					// コンフィグ
		int iImageConfigChoiceHandle;			// コンフィグ選択
		bool bGameStartFlg;						// スタートフラグ
		bool bHomeFlg;							// ホームフラグ
		bool bPlayTitleBgmFlg;					// BGM再生フラグ

		/* 使用する画像のハンドル */
		int* piGrHandle_TitleLogo;				// タイトルロゴ
		int iImageFinalCheckHandle;				// 最終確認背景
		int iImageYesHandle;					// yes
		int iImageYesChoiceHandle;				// yes選択
		int iImageNoHandle;						// no
		int iImageNoChoiceHandle;				// no選択
		int iImageAButtonStartHandle;			// aボタンスタート

};

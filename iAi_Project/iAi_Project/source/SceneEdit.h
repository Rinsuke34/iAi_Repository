/* 2025.01.19 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"
#include "SceneEditDefine.h"

/* データリスト */
#include "DataList_StageStatus.h"
#include "DataList_GameResource.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Image.h"

/* シーン"エディット"クラスの宣言 */

// シーン"エディット"
class SceneEdit : public SceneBase
{
	public:
		SceneEdit();							// コンストラクタ
		virtual ~SceneEdit();					// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_StageStatus* StageStatusList;		// ゲーム状態管理
		DataList_GameResource* GameResourceList;	// ゲーム内リソース管理
		DataList_PlayerStatus* PlayerStatusList;	// プレイヤー状態管理

		/* 使用する画像のハンドル */
		int* piGrHandle_SelectFrame[2];						// 選択フレーム(0:ホールド無し、 1:ホールドあり)
		int* apiGrHandle_SelectStatus[SELECT_STATUS_MAX];	// 選択項目の状態フレーム
		int* piGrHandle_SelectNext;							// 次ステージ遷移ボタン
		int* piGrHandle_ResultFrame;						// リザルトフレーム
		int* piGrHandle_ResultBackGround;					// リザルト画面背景(流用)
		int* piGrHandle_NowEdit_Under;						// 現在のエディット情報
		int* piGrHandle_UnderExplain_Under;					// 現在のエディット情報の説明欄
		int* piGrHandle_NewEdit_Under;						// 新規エディット情報の説明欄
		int* piGrHandle_KeepEdit_Under;						// キープエディット情報の説明欄
		int* piGrHandle_KeepIcon;							// キープアイコン
		int* piGrHandle_Keep;								// キープ(文字)
		int* piGrHandle_Delete;								// 削除
		int* piGrHandle_New;								// NEW(文字)
		int* piGrHandle_Custom;								// カスタム(文字)
		int* piGrHandle_Blood;								// ブラッド
		int* apiGrHandle_EditLock[2];						// エディットロック文字(0:Bランク, 1:Aランク)

		/* 関数 */
		void	Process_Main();				// メイン処理
		void	Process_Decid();			// 決定入力時の処理
		void	Process_Select();			// 方向入力時の処理
		void	Process_NowEditUpdate();	// 現在のエディット情報の更新

		/* 変数 */
		EDIT_SELECT_ITEM	astSelectItemList[SELECT_ITEM_MAX];		// 選択項目一覧
		int					iSelectItem;							// 選択中の項目の番号
		int					iHoldSelectItemNo;						// ホールド中の選択項目の番号
		int					iHoldSelectItemType;					// ホールド中の選択項目の種類
		EDIT_DATA			HoldEditData;							// ホールド中のエディット情報
		EDIT_DATA			NewEditData[EDIT_UPGRADE_MAX];			// 新規のエディット情報
		EDIT_DATA			DeleteEditData;							// 削除予定のエディット情報
		int					iNewEditNumber;							// 新規エディット数
};

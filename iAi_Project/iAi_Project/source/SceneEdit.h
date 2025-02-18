/* 2025.01.19 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"
#include "SceneEditDefine.h"

/* データリスト */
#include "DataList_GameStatus.h"
#include "DataList_GameResource.h"
#include "DataList_Image.h"

/* シーン"エディット"クラスの宣言 */

// シーン"エディット"
class SceneEdit : public SceneBase
{
	public:
		SceneEdit();							// コンストラクタ
		virtual ~SceneEdit();					// デストラクタ

		void	Initialization()	override;	// 初期化
		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_GameStatus* GameStatusList;		// ゲーム状態管理
		DataList_GameResource* GameResourceList;	// ゲーム内リソース管理

		/* 使用する画像のハンドル */
		int* piGrHandle_SelectFrame;						// 選択フレーム
		int* piGrHandle_SelectNext;							// 次ステージ遷移ボタン
		int* apiGrHandle_SelectStatus[SELECT_STATUS_MAX];	// 選択項目の状態フレーム

		/* 関数 */
		void	Process_Main();				// メイン処理
		void	Process_Decid();			// 決定入力時の処理
		void	Process_Select();			// 方向入力時の処理
		void	Process_NowEditUpdate();	// 現在のエディット情報の更新

		/* 変数 */
		EDIT_SELECT_ITEM	astSelectItemList[SELECT_ITEM_MAX];		// 選択項目一覧
		int					iUpgradeRate;							// アップグレードのレート(0～10)
		int					iSelectItem;							// 選択中の項目の番号
		int					iHoldSelectItemNo;						// ホールド中の選択項目の番号
		int					iHoldSelectItemType;					// ホールド中の選択項目の種類
		EDIT_DATA			HoldEditData;							// ホールド中のエディット情報
		EDIT_DATA			NewEditData[EDIT_UPGRADE_MAX];			// 新規のエディット情報
		EDIT_DATA			DeleteEditData;							// 削除予定のエディット情報
};

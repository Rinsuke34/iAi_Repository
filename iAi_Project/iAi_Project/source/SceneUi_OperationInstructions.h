/* 2025.03.24 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"

/* データリスト */
#include "DataList_Image.h"
#include "DataList_Option.h"
#include "DataList_PlayerStatus.h"
#include "DataList_StageStatus.h"

/* UI(操作説明)クラスの宣言 */

// UI(操作説明)クラス
class SceneUi_OperationInstructions : public SceneBase
{
	public:
		SceneUi_OperationInstructions();				// コンストラクタ
		virtual ~SceneUi_OperationInstructions() {};	// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_Option*		OptionList;			// オプション設定管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態管理
		DataList_StageStatus*	StatusStatusList;	// ステージ状態管理

		/* 使用する画像のハンドル */
		int* piGrHandle_Base[2];		// 操作説明画像ベース(0:コントローラー、1:キーボード)
		int* piGrHandle_Attack[2];		// 通常時操作説明画像(0:コントローラー、1:キーボード)
		int* piGrHandle_Kunai[2];		// クナイ構え時操作説明画像(0:コントローラー、1:キーボード)

		/* 変数 */
		int iDrawTypeNo;				// 描画タイプ番号(0:コントローラー、1:キーボード)
};

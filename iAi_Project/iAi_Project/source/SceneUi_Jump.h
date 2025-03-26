/* 2025.03.26 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_PlayerStatus.h"
#include "DataList_StageStatus.h"
#include "DataList_Image.h"
#include "DataList_Object.h"

/* UI(ジャンプ回数)クラスの宣言 */

// UI(ジャンプ回数)クラス
class SceneUi_Jump : public SceneBase
{
	public:
		SceneUi_Jump();					// コンストラクタ
		virtual ~SceneUi_Jump() {};		// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態管理
		DataList_StageStatus*	StageStatusList;	// ゲーム状態管理
		DataList_Object*		ObjectList;			// オブジェクト管理

		/* 使用する画像のハンドル */
		int* piGrHandle_Jump_Icon_Valid;	// ジャンプアイコン(有効)
		int* piGrHandle_Jump_Icon_Invalid;	// ジャンプアイコン(無効)
};

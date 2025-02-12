/* 2025.01.27 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"
#include "DataList_GameStatus.h"
#include "DataList_Image.h"

/* UI(クロスヘア)クラスの宣言 */

// UI(クロスヘア)クラス
class SceneUi_Crosshairs : public SceneBase
{
	public:
		SceneUi_Crosshairs();					// コンストラクタ
		virtual ~SceneUi_Crosshairs()	{};		// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_Object*		ObjectList;			// オブジェクト管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態管理
		DataList_GameStatus*	GameStatusList;		// ゲーム状態管理

		/* 関数 */
		void	Draw_RockOn();		// 描写(ロックオンエネミー)
		void	Draw_Move();		// 描写(溜め攻撃の移動後座標)

		/* 変数 */
		int*	ipCgHandle_Flont;			// 中心クロスヘア
		int*	ipCgHandle_Target_Main;		// ロックオン対象(メイン)クロスヘア
		int*	ipCgHandle_Target_Sub;		// ロックオン対象(サブ)クロスヘア
};


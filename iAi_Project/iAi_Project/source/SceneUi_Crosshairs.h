/* 2025.01.27 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"
#include "DataList_StageStatus.h"
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
		DataList_StageStatus*	StageStatusList;		// ステージ状態管理

		/* 関数 */
		void	Draw_RockOn_Melee();	// 描写(近接攻撃の溜め時のロックオンエネミー)
		void	Draw_RockOn_Kunai();	// 描写(遠距離攻撃の溜め時のロックオンエネミー)
		void	Draw_Move();			// 描写(溜め攻撃の移動後座標)

		/* 使用する画像のハンドル */
		int*	piGrHandle_Flont;			// 中心クロスヘア
		int*	piGrHandle_Target_Main;		// ロックオン対象(メイン)クロスヘア
		int*	piGrHandle_Target_Sub;		// ロックオン対象(サブ)クロスヘア
		int*	piGrHandle_Kunai_Zero;		// クナイ残段無し表示
};


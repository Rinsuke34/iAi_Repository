/* 2025.03.16 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_PlayerStatus.h"

/* UI(デバッグメニュー/ステータス調整)クラスの宣言 */

// UI(デバッグメニュー/ステータス調整)クラス
class SceneUi_Debug_StatusSetup : public SceneBase
{
	public:
		SceneUi_Debug_StatusSetup();				// コンストラクタ
		virtual ~SceneUi_Debug_StatusSetup();		// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_PlayerStatus*	PlayerStatusList;	// ステージ状態管理

		/* 変数 */
		int						iSelectItem;		// 選択中の項目の番号
		bool					bSelectFlg;			// 選択状態であるかのフラグ
};

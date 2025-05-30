/* 2025.01.27 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* シーン */
#include "SceneUi_Debug_StageJump.h"
#include "SceneUi_Debug_StatusSetup.h"

/* UI(デバッグメニュー)クラスの宣言 */

// UI(デバッグメニュー)クラス
class SceneUi_Debug : public SceneBase
{
	public:
		SceneUi_Debug();					// コンストラクタ
		virtual ~SceneUi_Debug() {};		// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 関数 */
		bool	bToggleFlg(bool bFlg);		// trueとfalseの切り替え

		/* 変数 */
		int					iSelectMode;	// 選択中のモード
		std::vector<bool*>	pDebugManu;		// デバッグ用広域変数の項目一覧
		int					iSelectNo;		// 選択中の項目の番号
};

/* 2025.01.27 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

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
		int		iSelectNo;
};

/* 2024.12.21 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* シーン「入力設定」の宣言 */

// シーン "オプション - 入力設定画面"
class SceneInputConfig : public SceneBase
{
	public:
		SceneInputConfig();						// コンストラクタ
		virtual ~SceneInputConfig();			// デストラクタ

		void	Initialization()	override;	// 初期化
		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:

	protected:
};

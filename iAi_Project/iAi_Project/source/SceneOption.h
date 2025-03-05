/* 2025.03.05 ファイル追加 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* シーン「オプション」の宣言 */

// シーン "オプション画面"
class SceneOption : public SceneBase
{
	public:
		SceneOption();							// コンストラクタ
		virtual ~SceneOption();					// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:

	protected:
};

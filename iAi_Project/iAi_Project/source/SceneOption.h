/* 2024.12.XX YYYY ZZZZ */

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

		void	Process()	override;			// 計算
		void	Draw()		override;			// 描画

	private:

	protected:
};

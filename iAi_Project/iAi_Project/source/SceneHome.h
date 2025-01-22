/* 2024.12.XX YYYY ZZZZ */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* シーン「ホーム」の宣言 */

// シーン "ホーム画面"
class SceneHome : public SceneBase
{
	public:
		SceneHome();							// コンストラクタ
		virtual ~SceneHome();					// デストラクタ

		void	Initialization()	override;	// 初期化
		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:

	protected:
};

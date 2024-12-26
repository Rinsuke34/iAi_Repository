#pragma once
#include "AppFrame.h"

// シーン "シーンロード画面"
class SceneLoad : public SceneBase
{
	public:
		SceneLoad();							// コンストラクタ
		virtual ~SceneLoad();				// デストラクタ

		void	Process()	override;			// 計算
		void	Draw()		override;			// 描画

	private:

	protected:
};

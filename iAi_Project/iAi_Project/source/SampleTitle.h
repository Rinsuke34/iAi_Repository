#pragma once
#include "AppFrame.h"

// シーン "タイトル画面"
class SceneTitle : public SceneBase
{
	public:
		SceneTitle();							// コンストラクタ
		virtual ~SceneTitle();					// デストラクタ

		void	Process()	override;			// 計算
		void	Draw()		override;			// 描画

	private:

	protected:
};

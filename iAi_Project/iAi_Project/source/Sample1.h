#pragma once
#include "AppFrame.h"

// シーン "シーンサンプル"
class SceneSample : public SceneBase
{
	public:
		SceneSample();							// コンストラクタ
		virtual ~SceneSample();					// デストラクタ

		void	Process()	override;			// 計算
		void	Draw()		override;			// 描画

	private:

	protected:
};

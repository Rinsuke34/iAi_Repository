/* 2024.12.20 ファイル追加 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* シーン「ロード」の宣言 */

// シーン "ロード画面"
class SceneLoad : public SceneBase
{
	public:
		SceneLoad();			// コンストラクタ
		virtual ~SceneLoad();	// デストラクタ

		void	Initialization()	override;	// 初期化
		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* テスト用 */
		int iTestCount;

	protected:
};

/* 2024.12.XX YYYY ZZZZ */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* シーン「タイトル」の宣言 */

// シーン "タイトル画面"
class SceneTitle : public SceneBase
{
	public:
		SceneTitle();							// コンストラクタ
		virtual ~SceneTitle();					// デストラクタ

		void	Initialization()	override;	// 初期化
		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:

	//変数

	int iTitleLogoHandle;					// タイトルロゴハンドル

	int iTitleBackGroundHandle;				// タイトル背景ハンドル
	protected:
};

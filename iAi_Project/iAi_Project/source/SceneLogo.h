/* 2025.03.28 ファイル追加 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_Image.h"

/* シーン「ロゴ」の宣言 */

// シーン "ロゴ"
class SceneLogo : public SceneBase
{
	public:
		SceneLogo();				// コンストラクタ
		virtual ~SceneLogo() {};	// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 画像ハンドル */
		int* piGrHandle_Logo_School;	// ロゴ画像(学校)
		int* piGrHandle_Logo_Team;		// ロゴ画像(チーム)

		/* 変数 */
		int		iDrawFaze;		// 描写フェイズ(0:学校ロゴ, 1:チームロゴ)
		int		iAlpha;			// 描写のアルファ値
		bool	bFadeInFlg;		// フェードインから開始するかのフラグ
};

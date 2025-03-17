/* 2025.03.17 駒沢風助 ファイル作成 */

#ifndef SCREEN_EFFECT_CONCENTRATIONLINE_H
#define SCREEN_EFFECT_CONCENTRATIONLINE_H

#include "ScreenEffect_Base.h"

/* データリスト */
#include "DataList_Image.h"

/* 画面エフェクト(集中線)クラスの宣言 */

// 画面エフェクト(集中線)クラス
class ScreenEffect_ConcentrationLine : public ScreenEffect_Base
{
	public:
		ScreenEffect_ConcentrationLine();				// コンストラクタ
		virtual ~ScreenEffect_ConcentrationLine() {};	// デストラクタ

		void	ScreenEffectDraw(int iGrHandle_Screen)	override;	// 画面エフェクト描写

	private:
		/* 使用する画像ハンドル */
		int*	apiGrHandle_ConcentrationLine[3];	// 集中線画像ハンドル(3種類)

		/* 変数 */
		int		iEffectTypeChangeCount;				// エフェクト種類変更カウント
		int		iEffectType;						// エフェクト種類(3種類)
};

#endif
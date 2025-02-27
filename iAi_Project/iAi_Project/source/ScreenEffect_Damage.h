/* 2025.02.24 駒沢風助 ファイル作成 */

#ifndef SCREEN_EFFECT_DAMAGE_H
#define SCREEN_EFFECT_DAMAGE_H

#include "ScreenEffect_Base.h"

/* すべての画面エフェクトのベースとなるクラスの宣言 */

// 画面エフェクトベースクラス
class ScreenEffect_Damage : public ScreenEffect_Base
{
	public:
		ScreenEffect_Damage();				// コンストラクタ
		virtual ~ScreenEffect_Damage() {};	// デストラクタ

		void	ScreenEffectDraw(int iGrHandle_Screen)	override;	// 画面エフェクト描写

	private:
		/* 変数 */
		int				iEffectShiftChangeCount;	// エフェクトのシフト量変更カウント
		st2DPosition	stEffectShift;				// エフェクトのシフト量
};

#endif
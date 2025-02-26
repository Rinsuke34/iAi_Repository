/* 2025.02.24 駒沢風助 ファイル作成 */

#include "ScreenEffect_Damage.h"

/* すべての画面エフェクトのベースとなるクラスの宣言 */

// コンストラクタ
ScreenEffect_Damage::ScreenEffect_Damage() : ScreenEffect_Base()
{
	/* 初期化 */
	this->iDeleteTime				= DAMAGE_EFFECT_TIME;
	this->iEffectShiftChangeCount	= 0;
}

// 画面エフェクト描写
void ScreenEffect_Damage::ScreenEffectDraw(int iGrHandle_Screen)
{
	// 引数
	// iGrHandle_Screen : 描写する画像のハンドル

	/* エフェクトのシフト量変更カウントを更新 */
	this->iEffectShiftChangeCount--;

	/* シフト量変更カウントが0いかになったか確認 */
	if (this->iEffectShiftChangeCount <= 0)
	{
		// シフト量変更カウントが0いかになった場合
		/* シフト量変更カウントをリセット */
		this->iEffectShiftChangeCount = DAMAGE_EFFECT_SHIFT_CHANGE;

		/* シフト量を更新 */
		this->stEffectShift.ix = GetRand(DAMAGE_EFFECT_SHIFT) - DAMAGE_EFFECT_SHIFT / 2;
		this->stEffectShift.iy = GetRand(DAMAGE_EFFECT_SHIFT) - DAMAGE_EFFECT_SHIFT / 2;
	}

	//int iEffectShift = static_cast<int>(DAMAGE_EFFECT_SHIFT * ((1.0 - static_cast<float>(this->iDeleteTime)) / DAMAGE_EFFECT_TIME));
	//iEffectShift = DAMAGE_EFFECT_SHIFT;

	/* 描写ブレンドモードを"アルファブレンド"に設定 */
	SetDrawBlendMode(DX_BLENDMODE_ADD, DAMAGE_EFFECT_ALPHA);
	
	/* 赤色部分のみ描写 */
	SetDrawBright(255, 0, 0);

	/* 画像を描写 */
	DrawExtendGraph(0 + this->stEffectShift.ix, 0 + this->stEffectShift.iy, SCREEN_SIZE_WIDE + this->stEffectShift.ix, SCREEN_SIZE_HEIGHT + this->stEffectShift.iy, iGrHandle_Screen, TRUE);

	/* 青色部分のみ描写 */
	SetDrawBright(0, 0, 255);

	/* 画像を描写 */
	DrawExtendGraph(0 - this->stEffectShift.iy, 0 - this->stEffectShift.iy, SCREEN_SIZE_WIDE - this->stEffectShift.ix, SCREEN_SIZE_HEIGHT + this->stEffectShift.iy, iGrHandle_Screen, TRUE);

	/* 描写色をリセット */
	SetDrawBright(255, 255, 255);

	/* 描写ブレンドモードを"ノーブレンド"に設定 */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/* 2025.02.24 駒沢風助 ファイル作成 */

#include "ScreenEffect_Damage.h"

/* すべての画面エフェクトのベースとなるクラスの宣言 */

// コンストラクタ
ScreenEffect_Damage::ScreenEffect_Damage() : ScreenEffect_Base()
{
	/* 初期化 */
	this->iDeleteTime = DAMAGE_EFFECT_TIME;
}

// 画面エフェクト描写
void ScreenEffect_Damage::ScreenEffectDraw(int iGrHandle_Screen)
{
	// 引数
	// iGrHandle_Screen : 描写する画像のハンドル

	/* エフェクトのシフト量を更新 */
	//int iEffectShift = DAMAGE_EFFECT_SHIFT * (this->iDeleteTime / DAMAGE_EFFECT_TIME);
	//int iEffectShift = (DAMAGE_EFFECT_TIME - this->iDeleteTime) * DAMAGE_EFFECT_SHIFT;
	int iEffectShift = DAMAGE_EFFECT_SHIFT;

	/* 描写ブレンドモードを"アルファブレンド"に設定 */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, DAMAGE_EFFECT_ALPHA);

	/* 赤色部分のみ描写 */
	SetDrawBright(255, 0, 0);

	DrawExtendGraph(0 + iEffectShift, 0, SCREEN_SIZE_WIDE + iEffectShift, SCREEN_SIZE_HEIGHT, iGrHandle_Screen, TRUE);

	/* 青色部分のみ描写 */
	SetDrawBright(0, 0, 255);

	DrawExtendGraph(0 - iEffectShift, 0, SCREEN_SIZE_WIDE - iEffectShift, SCREEN_SIZE_HEIGHT, iGrHandle_Screen, TRUE);

	SetDrawBright(255, 255, 255);

	/* 描写ブレンドモードを"ノーブレンド"に設定 */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

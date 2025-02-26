/* 2025.02.24 駒沢風助 ファイル作成 */

#include "ScreenEffect_Base.h"

/* すべての画面エフェクトのベースとなるクラスの定義 */

// コンストラクタ
ScreenEffect_Base::ScreenEffect_Base()
{
	/* 初期化 */
	this->bDeleteFlg	= false;
	this->iDeleteTime	= 0;
}

// 更新
void ScreenEffect_Base::Update(int iGrHandle_Screen)
{
	// 引数
	// iGrHandle_Screen : 描写する画像のハンドル

	/* 画面エフェクト描写 */
	ScreenEffectDraw(iGrHandle_Screen);

	/* エフェクトの残り時間を更新 */
	this->iDeleteTime--;

	/* エフェクトの残り時間が0以下になったか確認 */
	if (this->iDeleteTime <= 0)
	{
		// 0以下になった場合
		/* 削除フラグを有効化 */
		this->bDeleteFlg = true;
	}
}
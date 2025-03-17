/* 2025.03.17 ファイル追加 駒沢風助 */

#include "ScreenEffect_ConcentrationLine.h"

/* 画面エフェクト(集中線)クラスの定義 */
// コンストラクタ
ScreenEffect_ConcentrationLine::ScreenEffect_ConcentrationLine() : ScreenEffect_Base()
{
	/* 画像取得 */
	{
		/* "画像管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 集中線画像(3種類)を取得 */
		this->apiGrHandle_ConcentrationLine[0] = ImageList->piGetImage("ScreenEffect/ConcentrationLine_1");
		this->apiGrHandle_ConcentrationLine[1] = ImageList->piGetImage("ScreenEffect/ConcentrationLine_2");
		this->apiGrHandle_ConcentrationLine[2] = ImageList->piGetImage("ScreenEffect/ConcentrationLine_3");
	}

	/* 初期化 */
	this->iEffectTypeChangeCount	= CONCENTRATIONLINE_EFFECT_CHANGE;
	this->iEffectType				= 0;
}

// 画面エフェクト描写
void ScreenEffect_ConcentrationLine::ScreenEffectDraw(int iGrHandle_Screen)
{
	// 引数
	// iGrHandle_Screen : 描写する画像のハンドル

	/* エフェクトの種類変更カウントを更新 */
	this->iEffectTypeChangeCount--;

	/* エフェクトの種類変更カウントが0以下になったか確認 */
	if (this->iEffectTypeChangeCount <= 0)
	{
		// エフェクトの種類変更カウントが0以下になった場合
		/* エフェクトの種類変更カウントをリセット */
		this->iEffectTypeChangeCount = CONCENTRATIONLINE_EFFECT_CHANGE;

		/* エフェクトの種類を更新 */
		this->iEffectType++;

		/* エフェクトの種類が最大値を超えているか確認 */
		if (this->iEffectType >= CONCENTRATIONLINE_EFFECT_TYPE)
		{
			// エフェクトの種類が最大値を超えている場合
			/* エフェクトの種類をリセット */
			this->iEffectType = 0;
		}
	}

	/* 描写ブレンドモードを"アルファブレンド"に設定 */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, CONCENTRATIONLINE_EFFECT_ALPHA);

	/* 画像を描写 */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->apiGrHandle_ConcentrationLine[this->iEffectType], TRUE);

	/* 描写ブレンドモードを"ノーブレンド"に設定 */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/* 2025.03.12 駒沢風助 ファイル作成 */

#include "ScreenEffect_SlowMotion.h"

/* 画面エフェクト(スローモーション)クラスの定義 */
// コンストラクタ
ScreenEffect_SlowMotion::ScreenEffect_SlowMotion() : ScreenEffect_Base()
{
	/* 使用するデータリスト */
	this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
}

// 更新
void ScreenEffect_SlowMotion::Update(int iGrHandle_Screen)
{
	// 引数
	// iGrHandle_Screen : 描写する画像のハンドル

	/* 画面エフェクト描写 */
	ScreenEffectDraw(iGrHandle_Screen);

	/* スローモーションフラグが無効であるか確認 */
	if(StageStatusList->bGetGameSlowFlg() == false)
	{
		// 無効である場合
		/* 削除フラグを有効化 */
		this->bDeleteFlg = true;
	}
}

// 画面エフェクト描写
void ScreenEffect_SlowMotion::ScreenEffectDraw(int iGrHandle_Screen)
{
	// 引数
	// iGrHandle_Screen : 描写する画像のハンドル

	/* 描写ブレンドモードを"アルファブレンド"に設定 */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);

	/* 画面全体を青色で描写 */
	DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(0, 0, 255), TRUE);

	/* 描写ブレンドモードを"ノーブレンド"に設定 */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

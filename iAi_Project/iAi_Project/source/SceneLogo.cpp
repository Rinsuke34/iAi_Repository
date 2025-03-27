/* 2025.03.28 ファイル追加 駒沢風助 */

#include "SceneLogo.h"

/* シーン「ロゴ」の定義 */
// コンストラクタ
SceneLogo::SceneLogo() : SceneBase("Logo", 20, true)
{
	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* ロゴ画像(学校) */
		this->piGrHandle_Logo_School	= ImageList->piGetImage("Logo/amgLOGO");

		/* ロゴ画像(チーム) */
		this->piGrHandle_Logo_Team		= ImageList->piGetImage("Logo/LOGO1");
	}

	/* 初期化 */
	this->iDrawFaze		= 0;	// 描写フェイズ(0:学校ロゴ, 1:チームロゴ)
	this->iAlpha		= 0;	// 描写のアルファ値
	this->bFadeInFlg	= true;	// フェードインから開始するかのフラグ
}

// 計算
void SceneLogo::Process()
{
	/* フェードインから開始するかの確認 */
	if (this->bFadeInFlg == true)
	{
		// フェードインから開始する場合
		/* フェードイン（アルファ値を増加）*/
		this->iAlpha += 2;
		if (this->iAlpha >= 255)
		{
			this->iAlpha		= 255;
			this->bFadeInFlg	= false;
		}
	}
	else
	{
		// フェードアウトから開始する場合
		/* フェードアウト（アルファ値を減少）*/
		this->iAlpha -= 2;
		if (this->iAlpha <= 0)
		{
			this->iAlpha = 0;
			this->iDrawFaze++;

			/* 全てのフェイズが完了したか確認 */
			if (this->iDrawFaze >= 2)
			{
				// 完了した場合
				/* 削除フラグを有効にする */
				this->bDeleteFlg = true;
				return;
			}

			this->bFadeInFlg = true;
		}
	}
}

// 描画
void SceneLogo::Draw()
{
	/* 背景を黒色で描写 */
	DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);

	/* ブレンドモード設定 */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->iAlpha);

	/* 現在のフェイズに応じて描画 */
	if (this->iDrawFaze == 0)
	{
		/* 学校ロゴ */
		DrawGraph(0, 0, *this->piGrHandle_Logo_School, TRUE);
	}
	else if (this->iDrawFaze == 1)
	{
		/* チームロゴ */
		DrawGraph(0, 0, *this->piGrHandle_Logo_Team, TRUE);
	}

	/* ブレンドモードを元に戻す */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

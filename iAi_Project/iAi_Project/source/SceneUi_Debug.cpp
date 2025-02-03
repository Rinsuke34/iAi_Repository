/* 2025.01.31 ファイル作成 駒沢風助 */

#include "SceneUi_Debug.h"

/* UI(デバッグメニュー)クラスの定義 */

// コンストラクタ
SceneUi_Debug::SceneUi_Debug() : SceneBase("UI_Debug", 200, true)
{
	this->iSelectNo	= 0;
}

// 計算
void SceneUi_Debug::Process()
{
	/* 入力取得 */
	// 上
	{
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
		{
			this->iSelectNo -= 1;
			if (this->iSelectNo < 0)
			{
				this->iSelectNo = 0;
			}
		}
	}
	
	// 下
	{
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
		{
			this->iSelectNo += 1;
			if (this->iSelectNo > 8)
			{
				this->iSelectNo = 8;
			}
		}
	}

	// 決定
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		switch (this->iSelectNo)
		{
			case 0:
				if (gbDrawSceneListFlg == true)
				{
					gbDrawSceneListFlg = false;
				}
				else
				{
					gbDrawSceneListFlg = true;
				}
				break;

			case 1:
				if (gbDrawDatalistFlg == true)
				{
					gbDrawDatalistFlg = false;
				}
				else
				{
					gbDrawDatalistFlg = true;
				}
				break;

			case 2:
				if (gbDrawShadowMapFlg == true)
				{
					gbDrawShadowMapFlg = false;
				}
				else
				{
					gbDrawShadowMapFlg = true;
				}
				break;

			case 3:
				if (gbDrawLightMapFlg == true)
				{
					gbDrawLightMapFlg = false;
				}
				else
				{
					gbDrawLightMapFlg = true;
				}
				break;

			case 4:
				if (gbDrawLightMapDownScaleFlg == true)
				{
					gbDrawLightMapDownScaleFlg = false;
				}
				else
				{
					gbDrawLightMapDownScaleFlg = true;
				}
				break;

			case 5:
				if (gbDrawLightMapGaussFlg == true)
				{
					gbDrawLightMapGaussFlg = false;
				}
				else
				{
					gbDrawLightMapGaussFlg = true;
				}
				break;

			case 6:
				if (gbDrawCollisionFlg == true)
				{
					gbDrawCollisionFlg = false;
				}
				else
				{
					gbDrawCollisionFlg = true;
				}
				break;

			case 7:
				if (gbDrawDeleteBackGroundFlg == true)
				{
					gbDrawDeleteBackGroundFlg = false;
				}
				else
				{
					gbDrawDeleteBackGroundFlg = true;
				}
				break;

			case 8:
				if (gbUseMouseFlg == true)
				{
					gbUseMouseFlg = false;
				}
				else
				{
					gbUseMouseFlg = true;
				}
		}
	}

	// 戻る
	{
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
		{
			this->bDeleteFlg = true;
		}
	}
}

// 描画
void SceneUi_Debug::Draw()
{
	DrawBox(700, 300, 1200, 300 + 16 * 9, GetColor(0, 0, 0), TRUE);
	DrawFormatString(800, 300 + 16 * 0, GetColor(255, 255, 255), "シーンリストの描写");
	DrawFormatString(800, 300 + 16 * 1, GetColor(255, 255, 255), "データリストの描写");
	DrawFormatString(800, 300 + 16 * 2, GetColor(255, 255, 255), "シャドウマップの描写");
	DrawFormatString(800, 300 + 16 * 3, GetColor(255, 255, 255), "ライトマップの描写");
	DrawFormatString(800, 300 + 16 * 4, GetColor(255, 255, 255), "ライトマップ(縮小)の描写");
	DrawFormatString(800, 300 + 16 * 5, GetColor(255, 255, 255), "ライトマップ(ぼかし)のハンドル");
	DrawFormatString(800, 300 + 16 * 6, GetColor(255, 255, 255), "全オブジェクトのコリジョン描写");
	DrawFormatString(800, 300 + 16 * 7, GetColor(255, 255, 255), "バックグランドオブジェクトの非表示");
	DrawFormatString(800, 300 + 16 * 8, GetColor(255, 255, 255), "マウス使用フラグ");

	DrawFormatString(700, 300 + 16 * this->iSelectNo, GetColor(255, 255, 255), "→");
}

/* 2025.01.31 ファイル作成 駒沢風助 */

#include "SceneUi_Debug.h"

/* UI(デバッグメニュー)クラスの定義 */

// コンストラクタ
SceneUi_Debug::SceneUi_Debug() : SceneBase("UI_Debug", 200, true)
{
	/* 初期化 */
	this->iSelectMode	= DEBUG_MODE_OPTION;
	this->iSelectNo		= 0;

	/* グローバル変数をデバッグ項目に登録 */
	pDebugManu.push_back(&gbDrawSceneListFlg);			// シーンリストの描写
	pDebugManu.push_back(&gbDrawDatalistFlg);			// データリストの描写
	pDebugManu.push_back(&gbDrawShadowMapFlg);			// シャドウマップの描写
	pDebugManu.push_back(&gbDrawLightMapFlg);			// ライトマップの描写
	pDebugManu.push_back(&gbDrawLightMapDownScaleFlg);	// ライトマップ(縮小)の描写
	pDebugManu.push_back(&gbDrawLightMapGaussFlg);		// ライトマップ(ぼかし)のハンドル
	pDebugManu.push_back(&gbDrawCollisionFlg);			// 全オブジェクトのコリジョン描写
	pDebugManu.push_back(&gbDrawDeleteBackGroundFlg);	// バックグランドオブジェクトの非表示
	pDebugManu.push_back(&gbUseMouseFlg);				// マウス使用フラグの有効・無効の切り替え
	pDebugManu.push_back(&gbDrawFpsFlg);				// フレームレートの描写
}

// 計算
void SceneUi_Debug::Process()
{
	/* モードに応じて処理を変更する */
	switch (this->iSelectMode)
	{
		/* デバッグオプション */
		case DEBUG_MODE_OPTION:
			/* プレイヤーの入力取得 */
			// ※プレイヤーの入力に応じて選択中の項目番号を変更する
			// 上入力
			if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
			{
				this->iSelectNo -= 1;
				if (this->iSelectNo < 0)
				{
					this->iSelectNo = 0;
				}
			}

			// 下入力
			if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
			{
				this->iSelectNo += 1;
				if (this->iSelectNo > pDebugManu.size())
				{
					this->iSelectNo = (int)pDebugManu.size();
				}
			}

			// 決定
			if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
			{
				*pDebugManu[this->iSelectNo] = bToggleFlg(*pDebugManu[this->iSelectNo]);
			}
			break;

		/* デバッグ操作 */
		case DEBUG_MODE_OPERATION:
			/* プレイヤーの入力取得 */
			// ※プレイヤーの入力に応じて選択中の項目番号を変更する
			// 上入力
			if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
			{
				this->iSelectNo -= 1;
				if (this->iSelectNo < 0)
				{
					this->iSelectNo = 0;
				}
			}

			// 下入力
			if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
			{
				this->iSelectNo += 1;
				if (this->iSelectNo > DEBUG_OPERATION_MAX)
				{
					this->iSelectNo = DEBUG_OPERATION_MAX;
				}
			}

			// 決定
			if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
			{
				switch (this->iSelectNo)
				{
					/* ステージジャンプ */
					case DEBUG_OPERATION_STAGEJUMP:
						{
							/* シーン"ステージジャンプ"を作成 */
							SceneBase* pAddScene = new SceneUi_Debug_StageJump();

							/* シーン"ステージジャンプ"をシーンサーバーに追加 */
							gpSceneServer->AddSceneReservation(pAddScene);
						}
						break;

					/* ステータス調整 */
					case DEBUG_OPERATION_STATUSSETUP:
						{
							/* シーン"ステータス調整"を作成 */
							SceneBase* pAddScene = new SceneUi_Debug_StatusSetup();
						
							/* シーン"ステータス調整"をシーンサーバーに追加 */
							gpSceneServer->AddSceneReservation(pAddScene);
						}
						break;
				}
			}
			break;
	}

	// 左入力
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT))
	{
		this->iSelectNo = 0;

		this->iSelectMode += 1;
		if (this->iSelectMode >= DEBUG_MODE_MAX)
		{
			this->iSelectMode = DEBUG_MODE_MAX - 1;
		}
	}

	// 右入力
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT))
	{
		this->iSelectNo = 0;

		this->iSelectMode -= 1;
		if (this->iSelectMode <= 0)
		{
			this->iSelectMode = 0;
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
	/* モードに応じて処理を変更する */
	switch (this->iSelectMode)
	{
		/* デバッグオプション */
		case DEBUG_MODE_OPTION:
			DrawBox(780, 300, 1200, 300 - 16, GetColor(255, 0, 0), TRUE);
			DrawFormatString(800, 300 - 16, GetColor(255, 255, 255), "デバッグオプション");
			DrawBox(780, 300, 1200, 300 + 16 * 10, GetColor(0, 0, 0), TRUE);
			DrawFormatString(800, 300 + 16 * 0, GetColor(255, 255, 255), "シーンリストの描写");
			DrawFormatString(800, 300 + 16 * 1, GetColor(255, 255, 255), "データリストの描写");
			DrawFormatString(800, 300 + 16 * 2, GetColor(255, 255, 255), "シャドウマップの描写");
			DrawFormatString(800, 300 + 16 * 3, GetColor(255, 255, 255), "ライトマップの描写");
			DrawFormatString(800, 300 + 16 * 4, GetColor(255, 255, 255), "ライトマップ(縮小)の描写");
			DrawFormatString(800, 300 + 16 * 5, GetColor(255, 255, 255), "ライトマップ(ぼかし)のハンドル");
			DrawFormatString(800, 300 + 16 * 6, GetColor(255, 255, 255), "全オブジェクトのコリジョン描写");
			DrawFormatString(800, 300 + 16 * 7, GetColor(255, 255, 255), "バックグランドオブジェクトの非表示");
			DrawFormatString(800, 300 + 16 * 8, GetColor(255, 255, 255), "マウス使用フラグ");
			DrawFormatString(800, 300 + 16 * 9, GetColor(255, 255, 255), "フレームレートの描写");
			break;

		/* デバッグ操作 */
		case DEBUG_MODE_OPERATION:
			DrawBox(780, 300, 1200, 300 - 16, GetColor(255, 0, 0), TRUE);
			DrawFormatString(800, 300 - 16, GetColor(255, 255, 255), "デバッグ操作");
			DrawBox(780, 300, 1200, 300 + 16 * 2, GetColor(0, 0, 0), TRUE);
			DrawFormatString(800, 300 + 16 * 0, GetColor(255, 255, 255), "ステージジャンプ");
			DrawFormatString(800, 300 + 16 * 1, GetColor(255, 255, 255), "ステータス調整");
			break;

	}

	/* 矢印を描写 */
	DrawFormatString(780, 300 + 16 * this->iSelectNo, GetColor(255, 255, 255), "→");
}

// trueとfalseの切り替え
bool SceneUi_Debug::bToggleFlg(bool bFlg)
{
	// 引数
	// bFlg	: 切り替えるフラグ

	return !bFlg;
}

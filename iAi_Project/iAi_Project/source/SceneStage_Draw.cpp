/* 2025.02.04 ファイル作成 駒沢風助 */

#include "SceneStage.h"

/* ステージクラスの定義(描写) */

// 描画
void SceneStage::Draw()
{
	/* ローディング中であるか確認 */
	if (gbNowLoadingFlg == true)
	{
		// ローディング中である場合
		/* 描写を行わない */
		return;
	}

	/* 透明度に関係なく描写するよう設定　*/
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_ALWAYS);

	/* シャドウマップ作成 */
	SetupShadowMap();

	/* ライトマップ作成 */
	SetupLightMap();

	/* メインの描写処理 */
	SetupMainScreen();

	/* メイン画面を描写 */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, this->iMainScreenHandle, FALSE);

	/* 画面エフェクトを描写 */
	SetupScreenEffects();

	/* カメラ設定 */
	SetCamera();

	/* ゲーム状態が"ステージクリア"である場合 */
	// ※ステージクリア処理用のカウントが1以上であるなら"ステージクリア"判定
	if (this->iStageClear_Count > 0)
	{
		// ステージクリアである場合
		/* フェードイン処理 */
		{
			/* 描写ブレンドモードを"アルファブレンド"に設定 */
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->iBlendAlpha_StageClear_Fadein);

			/* 画面全体を白色で描写 */
			DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(255, 255, 255), TRUE);

			/* 描写ブレンドモードを"ノーブレンド"に設定 */
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			/* シーン"リザルト"を作成したか確認 */
			if (this->iStageClear_Count >= STAGECLEAR_COUNT_START_RESULT)
			{
				// 作成している場合
				/* リザルト用のフレームを描写 */
				DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->piGrHandle_ResultFrame, FALSE);
			}
		}
	}	
}

// シャドウマップの設定
void SceneStage::SetupShadowMap()
{
	/* ライト方向設定 */
	SetShadowMapLightDirection(this->iShadowMapScreenHandle, VNorm(VGet(0.f, -1.f, 0.f)));

	/* シャドウマップの描写範囲設定 */
	{
		/* カメラのターゲット座標を取得 */
		VECTOR vecTargetPos = this->StageStatusList->vecGetCameraTarget();

		/* シャドウマップ範囲設定 */
		// ※カメラのターゲット座標を中心に描写
		SetShadowMapDrawArea(this->iShadowMapScreenHandle, VAdd(vecTargetPos, VGet(-SHADOWMAP_RANGE, -SHADOWMAP_RANGE, -SHADOWMAP_RANGE)), VAdd(vecTargetPos, VGet(SHADOWMAP_RANGE, SHADOWMAP_RANGE, SHADOWMAP_RANGE)));
	}

	/* シャドウマップへの描写を開始 */
	ShadowMap_DrawSetup(this->iShadowMapScreenHandle);

	/* すべてのオブジェクトの描写 */
	ObjectList->DrawAll();

	/* シャドウマップへの描写を終了 */
	ShadowMap_DrawEnd();
}

// ライトマップの設定
void SceneStage::SetupLightMap()
{
	/* ライトマップ描写 */
	{
		/* ライトマップへの描写を開始 */
		SetDrawScreen(this->iLightMapScreenHandle);

		/* ライティングを無効化 */
		SetUseLighting(FALSE);

		/* 画面クリア */
		ClearDrawScreen();

		/* カメラの設定 */
		SetCamera();

		/* すべてのオブジェクトの発光部分の描写 */
		ObjectList->DrawAll_Bloom();

		/* ライトマップへの描写を終了 */
		SetDrawScreen(DX_SCREEN_BACK);

		/* ライティングを有効化 */
		SetUseLighting(TRUE);
	}

	/* ライトマップの縮小版を取得 */
	GraphFilterBlt(this->iLightMapScreenHandle, this->iLightMapScreenHandle_DownScale, DX_GRAPH_FILTER_DOWN_SCALE, LIGHTMAP_DOWNSCALE);

	/* ライトマップのぼやかした版を取得 */
	GraphFilterBlt(this->iLightMapScreenHandle_DownScale, this->iLightMapScreenHandle_Gauss, DX_GRAPH_FILTER_GAUSS, LIGHTMAP_GAUSS_WIDTH, LIGHTMAP_GAUSS_RATIO);
}

// メインの描写処理
void SceneStage::SetupMainScreen()
{
	/* メイン画面への描写を開始 */
	SetDrawScreen(this->iMainScreenHandle);

	/* 画面クリア */
	ClearDrawScreen();

	/* カメラの設定 */
	SetCamera();

	/* 描写に使用するシャドウマップの設定 */
	SetUseShadowMap(0, this->iShadowMapScreenHandle);

	/* 半透明部分を描写しないよう設定 */
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_NOT_SEMITRANS_ONLY);

	/* 半透明部分のないすべてのオブジェクトを描写 */
	ObjectList->DrawAll();

	/* 描写に使用するシャドウマップの設定を解除 */
	SetUseShadowMap(this->iShadowMapScreenHandle, -1);

	/* 半透明部分のみ描写するように設定 */
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_SEMITRANS_ONLY);

	/* 半透明部分のすべてのオブジェクトを描写 */
	ObjectList->DrawAll();

	/* コリジョン描写フラグが有効であるか確認 */
	if (gbDrawCollisionFlg == true)
	{
		/* コリジョン描写 */
		/* 半透明かどうか関係なく描画するように設定 */
		MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_ALWAYS);

		/* すべてのオブジェクトのコリジョンを描写 */
		ObjectList->DrawAll_Collision();
	}

	/* エフェクトの描写処理 */
	SetupEffectScreen();

	/* ライトマップ描写 */
	{
		/* 描画モードをバイリニアフィルタリングに変更　*/
		// ※拡大時にドットをぼやけさせる
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		/* 描画ブレンドモードを加算にする */
		// ※ライトマップの黒色部分を描写されないようにする
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

		/* ライトマップを描写 */
		DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, this->iLightMapScreenHandle, FALSE);

		/* ライトマップ(ぼかし)を描写 */
		DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, this->iLightMapScreenHandle_Gauss, FALSE);

		/* 描画ブレンドモードをブレンド無しに戻す */
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		/* 描画モードを二アレストに戻す */
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}

	/* デバッグ描写 */
	DrawDebug();

	/* メイン画面への描写を終了 */
	SetDrawScreen(DX_SCREEN_BACK);
}

/* エフェクトの描写処理 */
void SceneStage::SetupEffectScreen()
{
	/* エフェクト更新 */
	UpdateEffekseer3D();

	/* エフェクト用カメラ位置同期 */
	Effekseer_Sync3DSetting();

	/* エフェクト描写 */
	//ObjectList->DrawEffect();
	DrawEffekseer3D();
}

// 画面エフェクト
void SceneStage::SetupScreenEffects()
{
	/* 画面エフェクト描写 */
	for (auto& pScreenEffectDraw : this->StageStatusList->GetScreenEffectList())
	{
		/* 画面エフェクト更新処理 */
		pScreenEffectDraw->Update(this->iMainScreenHandle);
	}

	/* 削除フラグが有効な画面エフェクトを削除 */
	this->StageStatusList->GetScreenEffectList().erase(std::remove_if(this->StageStatusList->GetScreenEffectList().begin(), this->StageStatusList->GetScreenEffectList().end(), [](ScreenEffect_Base* pScreenEffect)
		{
			/* 削除フラグが有効であるか確認　*/
			if (pScreenEffect->bGetDeleteFlg() == true)
			{
				// 有効である場合
				delete pScreenEffect;
				return true;
			}
			else
			{
				// 無効である場合
				return false;
			}
		}), this->StageStatusList->GetScreenEffectList().end());
}


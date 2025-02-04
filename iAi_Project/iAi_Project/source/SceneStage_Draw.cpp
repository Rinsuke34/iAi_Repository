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

	/* 画面エフェクトの描写処理 */
	// ※ノイズやぼかし等画面に直接関与するエフェクト
	SetupScreenEffects();

	/////* 描画ブレンドモードを加算にする (黒色部分が透明になる) */
	////SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	///* 画像をメイン画面に重ねて描写 */
	//DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, this->iMainScreenEffectHandle, TRUE);

	/////* 描画ブレンドモードをブレンド無しに戻す */
	////SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// シャドウマップの設定
void SceneStage::SetupShadowMap()
{
	/* ライト方向設定 */
	SetShadowMapLightDirection(this->iShadowMapScreenHandle, VNorm(VGet(1.f, -1.f, 0.f)));

	SetShadowMapAdjustDepth(this->iShadowMapScreenHandle, 0.002f);

	/* シャドウマップの描写範囲設定 */
	{
		/* カメラのターゲット座標を取得 */
		VECTOR vecTargetPos = this->PlayerStatusList->vecGetCameraTarget();

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
	//DrawEffekseer3D();
}

// 画面エフェクト
void SceneStage::SetupScreenEffects()
{
	///* メイン画面(画面エフェクト用)への描写を開始 */
	//SetDrawScreen(this->iMainScreenEffectHandle);

	///* 画面クリア */
	//ClearDrawScreen();

	///* 画面エフェクト(モーションブラー) */
	//{
	//	/* マスク画面を作成 */
	//	CreateMaskScreen();

	//	/* 中央部分のみ白、周囲は黒のマスクを描写 */
	//	// ここでは白色部分が中央を示し、黒色部分がぼかしを適用するエリアです
	//	//DrawFillMask(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, this->iMotionBlurMaskHandle);
	//
	//	DrawMask(0, 0, this->iMotionBlurMaskHandle, DX_MASKTRANS_BLACK);

	//	/* メイン画面を描写 */
	//	DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(255, 0, 0), TRUE);
	//	//DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, this->iMainScreenHandle, TRUE);

	//	/* ガウスフィルタ(ぼかし)を適用 */
	//	//GraphFilterBlt(this->iMainScreenEffectHandle, this->iMainScreenEffectHandle, DX_GRAPH_FILTER_GAUSS, LIGHTMAP_GAUSS_WIDTH, LIGHTMAP_GAUSS_RATIO);

	//	/* マスク画面を削除 */
	//	DeleteMaskScreen();
	//}

	///* メイン画面(画面エフェクト用)への描写を終了 */
	//SetDrawScreen(DX_SCREEN_BACK);
}


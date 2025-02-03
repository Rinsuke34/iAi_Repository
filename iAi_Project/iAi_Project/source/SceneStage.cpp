/* 2025.01.16 ファイル作成 駒沢風助 */

#include "SceneStage.h"

/* ステージクラスの定義 */

// コンストラクタ
SceneStage::SceneStage(): SceneBase("Stage", 1, true)
{
	/* データリスト作成 */
	{
		/* データリストサーバーに"プレイヤー状態"を追加 */
		gpDataListServer->AddDataList(new DataList_PlayerStatus());

		/* データリストサーバーに"オブジェクト管理"を追加 */
		gpDataListServer->AddDataList(new DataList_Object());
	}

	/* データリスト取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList		= dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "3Dモデル管理"を取得 */
		this->ModelList			= dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* "ゲーム状態管理"を取得 */
		this->GameStatusList	= dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
	}

	/* UI追加 */
	{
		/* クロスヘア */
		gpSceneServer->AddSceneReservation(new SceneUi_Crosshairs());

		/* HP */
		gpSceneServer->AddSceneReservation(new SceneUi_Hp());

		/* クナイ */
		gpSceneServer->AddSceneReservation(new SceneUi_Kunai());

		/* コンボ */
		gpSceneServer->AddSceneReservation(new SceneUi_Combo());
	}

	/* マップハンドル作成 */
	this->iShadowMapScreenHandle			= MakeShadowMap(SHADOWMAP_SIZE, SHADOWMAP_SIZE);
	this->iLightMapScreenHandle				= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	this->iLightMapScreenHandle_DownScale	= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
	this->iLightMapScreenHandle_Gauss		= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);

	/* 初期化 */
	Initialization();
}

// デストラクタ
SceneStage::~SceneStage()
{
	/* データリスト削除 */
	gpDataListServer->DeleteDataList("DataList_PlayerStatus");	// プレイヤー状態
	gpDataListServer->DeleteDataList("DataList_Object");		// オブジェクト管理

	/* マップハンドル削除 */
	DeleteShadowMap(iShadowMapScreenHandle);	// シャドウマップ
	DeleteGraph(iLightMapScreenHandle);			// ライトマップ
}

// 初期化
void SceneStage::Initialization()
{
	/* ゲーム状態を"ゲーム実行"に変更 */
	this->GameStatusList->SetGameStatus(GAMESTATUS_PLAY_GAME);
}

// 計算
void SceneStage::Process()
{
	/* ゲーム状態を確認 */
	int iGameStatus = this->GameStatusList->iGetGameStatus();

	/* ゲーム状態に応じて処理を変更 */
	switch (iGameStatus)
	{
		/* "ゲーム実行"状態 */
		case GAMESTATUS_PLAY_GAME:
			/* すべてのオブジェクトの更新 */
			ObjectList->UpdateAll();

			/* 削除フラグが有効なオブジェクトの削除 */
			ObjectList->DeleteAll();
			break;

		/* "エディット"状態 */
		case GAMESTATUS_EDIT:
			/* エディット画面作成処理 */
			{
				/* カメラモードを"固定"に変更 */
				this->PlayerStatusList->SetCameraMode(CAMERA_MODE_LOCK);

				/* シーン"エディット画面"を作成 */
				SceneBase* pAddScene = new SceneEdit();

				/* シーン"エディット画面"をシーンサーバーに追加 */
				gpSceneServer->AddSceneReservation(pAddScene);
			}
			break;

		/* "次のステージへ遷移"状態 */
		case GAMESTATUS_NEXTSTAGE:
			/* シーンの削除フラグを有効にする */
			this->bDeleteFlg = true;

			/* ゲーム状態を"ゲーム実行"に変更する */
			this->GameStatusList->SetGameStatus(GAMESTATUS_PLAY_GAME);
			break;
	}

	// デバッグメニューを出す(エンターキー)
	if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
	{
		gpSceneServer->AddSceneReservation(new SceneUi_Debug());
	}
}

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

	/* オブジェクト描写 */
	{
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
	}

	/* エフェクト描写 */
	{
		/* エフェクト更新 */
		UpdateEffekseer3D();

		/* エフェクト用カメラ位置同期 */
		Effekseer_Sync3DSetting();

		/* エフェクト描写 */
		//ObjectList->DrawEffect();
		//DrawEffekseer3D();
	}

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

// デバッグ描写
void SceneStage::DrawDebug()
{
	int iDrawCount = 0;

	/* シャドウマップ描写 */
	if (gbDrawShadowMapFlg == true)
	{
		TestDrawShadowMap(iShadowMapScreenHandle, SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1));
		iDrawCount++;
	}

	/* ライトマップ描写 */
	if (gbDrawLightMapFlg == true)
	{
		DrawExtendGraph(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1), this->iLightMapScreenHandle, FALSE);
		iDrawCount++;
	}

	/* ライトマップ(縮小)描写 */
	if (gbDrawLightMapDownScaleFlg == true)
	{
		DrawExtendGraph(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1), this->iLightMapScreenHandle_DownScale, FALSE);
		iDrawCount++;
	}

	/* ライトマップ(ぼかし)描写 */
	if (gbDrawLightMapGaussFlg == true)
	{
		DrawExtendGraph(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1), this->iLightMapScreenHandle_Gauss, FALSE);
		iDrawCount++;
	}

	DrawFormatString(800, 360 + 16 * 2, GetColor(255, 255, 255), "線形補完カウント : %d", this->PlayerStatusList->iGetCameraPositionLeapCount());
}

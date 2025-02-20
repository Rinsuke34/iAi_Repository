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

		/* ブラッド */
		gpSceneServer->AddSceneReservation(new SceneUi_Blood());

		/* エディット */
		gpSceneServer->AddSceneReservation(new SceneUi_Edit());
	}

	/* マップハンドル作成 */
	// 画像ハンドル
	this->iLightMapScreenHandle				= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	this->iLightMapScreenHandle_DownScale	= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
	this->iLightMapScreenHandle_Gauss		= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
	this->iMainScreenHandle					= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	this->iMainScreenEffectHandle			= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	// シャドウマップハンドル
	this->iShadowMapScreenHandle_Platform			= MakeShadowMap(1028 * 2, 1028 * 2);

	//int	iShadowMapScreenHandle_Platform;			// シャドウマップ(固定の足場)のハンドル
	//int	iShadowMapScreenHandle_Actor_Nearby_Player;	// シャドウマップ(プレイヤー付近のアクタ)のハンドル
	//int	iShadowMapScreenHandle_Actor_Wide;			// シャドウマップ(広範囲のアクタ)

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
	// 画像ハンドル
	DeleteGraph(this->iLightMapScreenHandle);
	DeleteGraph(this->iLightMapScreenHandle_DownScale);
	DeleteGraph(this->iLightMapScreenHandle_Gauss);
	DeleteGraph(this->iMainScreenHandle);
	DeleteGraph(this->iMainScreenEffectHandle);
	// シャドウマップ
	DeleteShadowMap(this->iShadowMapScreenHandle_Platform);
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

		/* "リザルト"状態 */
		case GAMESTATUS_RESULT:
			/* エディット画面作成処理 */
			{
				/* カメラモードを"固定"に変更 */
				this->PlayerStatusList->SetCameraMode(CAMERA_MODE_LOCK);

				/* シーン"リザルト画面"を作成 */
				SceneBase* pAddScene = new SceneResult();

				/* シーン"リザルト画面"をシーンサーバーに追加 */
				gpSceneServer->AddSceneReservation(pAddScene);
			}
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

// デバッグ描写
void SceneStage::DrawDebug()
{
	int iDrawCount = 0;

	/* シャドウマップ描写 */
	if (gbDrawShadowMapFlg == true)
	{
		TestDrawShadowMap(iShadowMapScreenHandle_Platform, SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1));
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
}

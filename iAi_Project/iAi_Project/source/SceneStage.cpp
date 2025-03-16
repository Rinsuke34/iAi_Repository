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

		/* "ステージ状態管理"を取得 */
		this->StageStatusList	= dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "オプション設定管理"を取得 */
		this->OptionList		= dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));
	}

	/* マップハンドル作成 */
	// 画像ハンドル
	this->iMainScreenHandle					= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	this->iLightMapScreenHandle				= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	this->iLightMapScreenHandle_DownScale	= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
	this->iLightMapScreenHandle_Gauss		= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
	// シャドウマップハンドル
	this->iShadowMapScreenHandle			= MakeShadowMap(1028 * 2, 1028 * 2);

	/* 初期化 */
	/* カメラ固定座標の初期化 */
	for (int i = 0; i < CAMERA_FIXED_POSITION_MAX; ++i)
	{
		vecCameraPositionInfo[i].iNo			= i;
		vecCameraPositionInfo[i].bUseFlg		= false;
		vecCameraPositionInfo[i].vecPosition	= VGet(0, 0, 0);
		vecCameraPositionInfo[i].vecTarget		= VGet(0, 0, 0);
	}
	this->iNowCameraFixedPositionNo		= CAMERA_FIXED_POSITION_START;	// 現在のカメラ固定座標番号
	this->iOldCameraFixedPositionNo		= CAMERA_FIXED_POSITION_START;	// 変更前のカメラ固定座標番号
	this->iMaxCameraFixedPositionNo		= CAMERA_FIXED_POSITION_START;	// カメラ固定座標番号総数
	this->iBlendAlpha_StageClear_Fadein	= 0;							// ステージクリア時のフェードインのアルファ値
	this->iStageClear_Count				= 0;							// ステージクリア時の処理で使用するカウント
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
	// シャドウマップ
	DeleteShadowMap(this->iShadowMapScreenHandle);
}

// 初期化
void SceneStage::Initialization()
{
	/* ゲーム状態を"ゲーム実行"に変更 */
	this->StageStatusList->SetGameStatus(GAMESTATUS_PLAY_GAME);

	/* UIを追加するか確認*/
	if (this->StageStatusList->bGetAddUiFlg() == true)
	{
		// 追加する場合
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
	}

	/* 最初にエディット画面を追加するか確認 */
	if (this->StageStatusList->bGetFastEditFlg() == true)
	{
		// 追加する場合
		/* ゲーム状態を"エディット"状態に変更 */
		this->StageStatusList->SetGameStatus(GAMESTATUS_EDIT);
	}

	/* ステージ開始時の時間を設定 */
	this->StageStatusList->SetStartTime(GetNowCount());

	/* カメラモードを"フリーモード"に設定 */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_NORMAL);
}

// 計算
void SceneStage::Process()
{
	/* ゲーム状態を確認 */
	int iGameStatus = this->StageStatusList->iGetGameStatus();

	/* ゲーム状態に応じて処理を変更 */
	switch (iGameStatus)
	{
		/* "ゲーム実行"状態 */
		case GAMESTATUS_PLAY_GAME:
			Process_Main();
			break;

		/* "ステージクリア準備"状態 */
		case GAMESTATUS_STAGE_CLEAR_SETUP:
			Process_StageClear();
			break;

		/* "ステージクリア"状態 */
		case GAMESTATUS_STAGE_CLEAR:
			{
				/* シーン"ステージクリア画面"を作成 */
				SceneBase* pAddScene = new SceneGameClear();

				/* シーン"ステージクリア画面"をシーンサーバーに追加 */
				gpSceneServer->AddSceneReservation(pAddScene);
			}
			break;

		/* "リザルト"状態 */
		case GAMESTATUS_RESULT:
			{
				/* シーン"リザルト画面"を作成 */
				SceneBase* pAddScene = new SceneResult();

				/* シーン"リザルト画面"をシーンサーバーに追加 */
				gpSceneServer->AddSceneReservation(pAddScene);
			}
			break;

		/* "エディット"状態 */
		case GAMESTATUS_EDIT:
			/* シーン"エディット画面"を作成 */
			{
				SceneBase* pAddScene = new SceneEdit();

				/* シーン"エディット画面"をシーンサーバーに追加 */
				gpSceneServer->AddSceneReservation(pAddScene);
			}
			break;

		/* "次のステージへ遷移"状態 */
		case GAMESTATUS_NEXTSTAGE:
			/* シーンの削除フラグを有効にする */
			this->bDeleteFlg = true;
			break;

		/* "ゲームオーバー"状態 */
		case GAMESTATUS_GAMEOVER:
			{
				/* シーン"ゲームオーバー"を作成 */
				SceneBase* pAddScene = new SceneGameOver();

				/* シーン"ゲームオーバー"をシーンサーバーに登録 */
				gpSceneServer->AddSceneReservation(pAddScene);
			}
			break;

		/* "リセット"状態 */
		case GAMESTATUS_RESET:
			/* すべてのオブジェクトのリセット処理を実行する */
			ObjectList->ResetAll();

			/* ステージ状態を初期化する */
			Initialization();

			/* ゲーム状態を"ゲーム実行"に変更 */
			StageStatusList->SetGameStatus(GAMESTATUS_PLAY_GAME);
			break;

		/* "ゲーム開始"状態 */
		case GAMESTATUS_START:
			Process_StageStart();
			break;

		/* ステージジャンプ */
		case GAMESTATUS_STAGE_JUMP:
			/* シーンの削除フラグを有効にする */
			this->bDeleteFlg = true;
			break;
	}

	/* カメラ設定準備 */
	SetCamera_Setup();

	/* エフェクト更新 */
	UpdateEffekseer3D();
}

// 計算(メインの処理)
void SceneStage::Process_Main()
{
	/* 2025.03.12 コメントアウト 菊池雅道 */
	/* スローモーションフラグが有効であるか確認 */
	//if (StageStatusList->bGetGameSlowFlg() == true)
	//{
	//	// 有効である場合
	//	/* スローモーションカウントを取得 */
	//	int iSlowCount = StageStatusList->iGetSlowCount();

	//	/* スローモーションのカウントが0であるか確認 */
	//	if (iSlowCount <= 0)
	//	{
	//		// 0である場合
	//		/* カウントを初期化する */
	//		StageStatusList->SetSlowCount(SLOW_SPEED);
	//	}
	//	else
	//	{
	//		// 0でない場合
	//		/* カウントを-1する */
	//		StageStatusList->SetSlowCount(iSlowCount - 1);

	//		/* 計算処理を終了する */
	//		return;
	//	}
	//}

	/* すべてのオブジェクトの更新 */
	ObjectList->UpdateAll();

	/* 削除フラグが有効なオブジェクトの削除 */
	ObjectList->DeleteAll();

	/* プレイヤーが存在していて、死亡フラグが有効であるか確認 */
	if ((this->ObjectList->GetCharacterPlayer() != nullptr) && (this->PlayerStatusList->bGetPlayerDeadFlg() == true))
	{
		// プレイヤーが存在かつ死亡フラグが有効ならば
		/* ゲーム状態を"ゲームオーバー"に変更する */
		this->StageStatusList->SetGameStatus(GAMESTATUS_GAMEOVER);
	}

	/* UI追加フラグが有効である(ゲーム中である)か確認 */
	if (this->StageStatusList->bGetAddUiFlg() == true)
	{
		// 有効である場合
		/* オプションボタンが押されているか */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_PAUSE) == true)
		{
			// 押されている場合
			/* シーン"一時停止"を追加 */
			gpSceneServer->AddSceneReservation(new ScenePause());
		}

		/* エンターキーを入力されたか確認 */
		if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
		{
			/* シーン"一時停止"を追加 */
			gpSceneServer->AddSceneReservation(new SceneUi_Debug());
		}
	}
}

// 計算(ステージクリア時の処理)
void SceneStage::Process_StageClear()
{
	/* カメラモードを"ステージクリア"に設定 */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_STAGECLEAR);

	/* クリア時カウントが開始時の状態であるか */
	if (this->iStageClear_Count == STAGECLEAR_COUNT_START)
	{
		// 開始時の状態である場合
		/* ステージクリア時の時間を設定する */
		this->StageStatusList->SetClearTime(GetNowCount());
	}

	/* クリア時カウントがフェードイン開始に達しているか確認 */
	if (this->iStageClear_Count >= STAGECLEAR_COUNT_START_FADEIN)
	{
		// 達している場合
		/* フェードインのアルファブレンド値を加算 */
		this->iBlendAlpha_StageClear_Fadein += FADE_ALPHA_CHANGE_SPEED;
	}

	/* クリア時カウントがリザルト開始に達しているか確認 */
	if (this->iStageClear_Count >= STAGECLEAR_COUNT_START_RESULT)
	{
		// 達している場合
		/* ゲーム状態を"ステージクリア"に変更 */
		StageStatusList->SetGameStatus(GAMESTATUS_STAGE_CLEAR);
	}

	/* ステージクリアのカウントを加算 */
	this->iStageClear_Count += 1;
}

// 計算(ステージ開始時の処理)
void SceneStage::Process_StageStart()
{
	/* カメラモードを"ステージ開始"に設定 */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_STAGESTART);

	/* カメラ固定座標の値が最大値を超えているか確認 */
	if (this->iNowCameraFixedPositionNo >= this->iMaxCameraFixedPositionNo - 1)
	{
		// 超えている場合
		/* ステージ状態を初期化する */
		Initialization();

		return;
	}

	/* プレイヤー、エネミー以外のオブジェクトの更新 */
	//ObjectList->UpdatePlayer();
	ObjectList->UpdateSkySqhere();
	ObjectList->UpdateEffect();
	ObjectList->UpdateBullet();
	ObjectList->UpdatePlatform();
	ObjectList->UpdateEffectItem();
	ObjectList->UpdatePickUpItem();
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
}

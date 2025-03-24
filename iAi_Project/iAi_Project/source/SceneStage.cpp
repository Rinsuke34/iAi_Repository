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

		/* "ゲーム内リソース管理"を取得 */
		this->GameResourceList	= dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}

	/* マップハンドル作成 */
	// 画像ハンドル
	this->iMainScreenHandle					= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	this->iLightMapScreenHandle				= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	this->iLightMapScreenHandle_DownScale	= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
	this->iLightMapScreenHandle_Gauss		= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
	// シャドウマップハンドル
	this->iShadowMapScreenHandle_Actor		= MakeShadowMap(SHADOWMAP_SIZE_ACTOR, SHADOWMAP_SIZE_ACTOR);
	this->iShadowMapScreenHandle_Platform	= MakeShadowMap(SHADOWMAP_SIZE_PLATFORM, SHADOWMAP_SIZE_PLATFORM);

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
	this->iPlayerSlowTime				= 1;							// プレイヤーのスローモーション速度
	this->bPlayBgmFlg					= false;						// BGMを再生済みかのフラグ
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
	DeleteShadowMap(this->iShadowMapScreenHandle_Actor);
	DeleteShadowMap(this->iShadowMapScreenHandle_Platform);
}

// 初期化
void SceneStage::Initialization()
{
	/* ゲーム状態を"ゲーム開始"に変更 */
	this->StageStatusList->SetGameStatus(GAMESTATUS_START);

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

			/* 経過時間 */
			gpSceneServer->AddSceneReservation(new SceneUi_Time());

			/* 操作説明 */
			gpSceneServer->AddSceneReservation(new SceneUi_OperationInstructions());
		}
	}

	/* 最初にエディット画面を追加するか確認 */
	if (this->StageStatusList->bGetFastEditFlg() == true)
	{
		// 追加する場合
		/* ゲーム状態を"エディット"状態に変更 */
		this->StageStatusList->SetGameStatus(GAMESTATUS_EDIT);

		return;
	}

	/* ステージ開始時の時間を設定 */
	this->StageStatusList->SetStartTime(GetNowCount());

	/* ストップ時の合計時間を初期化 */
	this->StageStatusList->SetStopTotalTime(0);

	/* ステージ開始時の所持ブラッド数を設定 */
	this->GameResourceList->SetStartBlood(this->GameResourceList->iGetHaveBlood());

	/* プレイヤーのステータスを更新 */
	this->PlayerStatusList->StatusBuffUpdate();

	/* BGMを再生していない状態であるか確認 */
	if (this->bPlayBgmFlg == false)
	{
		// 再生していない場合
		/* 再生するBGM番号を取得 */
		int iBgmNo = BGM_STAGE_0;

		/* ステージ番号に応じて再生するBGMを変更する */
		switch (this->StageStatusList->iGetNowStageNo())
		{
			case STAGE_NO_1_1:
			case STAGE_NO_1_2:
			case STAGE_NO_1_3:
				iBgmNo = BGM_STAGE_0;
				break;

			case STAGE_NO_2_1:
			case STAGE_NO_2_2:
			case STAGE_NO_2_3:
				iBgmNo = BGM_STAGE_1;
				break;

			case STAGE_NO_3_1:
			case STAGE_NO_3_2:
				iBgmNo = BGM_STAGE_2;
				break;
				
			case STAGE_NO_3_3:
				iBgmNo = BGM_STAGE_3;
				break;
		}

		/* BGMを再生 */
		gpDataList_Sound->BGM_SetHandle(iBgmNo);

		/* BGMを再生済みに設定 */
		this->bPlayBgmFlg = true;
	}	
}

// 計算
void SceneStage::Process()
{
	/* エフェクト共通処理更新フラグ */
	// ※有効なら共通処理でエフェクト更新を行う
	bool bGrobalEffectUpdateFlg	= true;

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

			/* エフェクト更新フラグを無効にする */
			bGrobalEffectUpdateFlg = false;
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
			/* 現在のステージ番号が最終ステージでないか確認 */
			if (this->StageStatusList->iGetNowStageNo() < this->StageStatusList->iGetEndStageNo())
			{
				// 最終ステージでない場合
				/* シーン"エディット画面"をシーンサーバーに追加 */
				gpSceneServer->AddSceneReservation(new SceneEdit());
			}
			else
			{
				// 最終ステージである場合
				/* ステージ状態を"次のステージへ遷移"に設定 */
				this->StageStatusList->SetGameStatus(GAMESTATUS_NEXTSTAGE);
			}
			break;

		/* "次のステージへ遷移"状態 */
		case GAMESTATUS_NEXTSTAGE:
			/* シーンの削除フラグを有効にする */
			this->bDeleteFlg = true;
			break;

		/* "ゲームオーバー"状態 */
		case GAMESTATUS_GAMEOVER:
			/* シーン"ゲームオーバー"をシーンサーバーに追加 */
			gpSceneServer->AddSceneReservation(new SceneGameOver());
			break;

		/* "リセット"状態 */
		case GAMESTATUS_RESET:
			/* すべてのオブジェクトのリセット処理を実行する */
			ObjectList->ResetAll();

			/* 所持ブラッドをステージ開始時の設定に戻す */
			this->GameResourceList->SetHaveBlood(this->GameResourceList->iGetStartBlood());

			/* 所持クナイ数をステージ開始時の設定に戻す */
			this->PlayerStatusList->SetNowHaveKunai(this->PlayerStatusList->iGetStartHaveKunai());

			/* プレイヤーHPをステージ開始時の設定に戻す */
			this->PlayerStatusList->SetPlayerNowHp(this->PlayerStatusList->iGetPlayerMaxHp());

			/* ステージ状態を初期化する */
			Initialization();
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

	/* エフェクト共通処理更新フラグが有効であるか確認 */
	if (bGrobalEffectUpdateFlg == true)
	{
		// 有効である場合
		/* エフェクト更新 */
		UpdateEffekseer3D();
	}
}

// 計算(メインの処理)
void SceneStage::Process_Main()
{
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

			/* "ポーズメニュー開閉"のSEを再生 */
			gpDataList_Sound->SE_PlaySound(SE_SYSTEM_POSEMENU);
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

	/* アイテムの更新処理 */
	ObjectList->UpdateEffectItem();
	ObjectList->DeleteEffectItem();

	/* プレイヤーの更新処理(少しづつプレイヤーのスローモーション速度を上げる) */
	if (((this->iStageClear_Count % this->iPlayerSlowTime) == 0) && (this->iPlayerSlowTime < 120))
	{
		// スローモーション速度のカウントが一定値に達している場合
		/* プレイヤーの更新処理 */
		ObjectList->UpdatePlayer();

		/* エフェクト更新 */
		UpdateEffekseer3D();

		/* スローモーション速度を加算 */
		this->iPlayerSlowTime = static_cast<int>(this->iPlayerSlowTime * 1.2f) + 1;
	}
}

// 計算(ステージ開始時の処理)
void SceneStage::Process_StageStart()
{
	/* "決定"がトリガ入力されたか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID) == true)
	{
		// 入力された場合
		/* カメラ固定座標の値を最大値に設定 */
		this->iNowCameraFixedPositionNo = this->iMaxCameraFixedPositionNo - 1;
	}

	/* カメラ固定座標の値が最大値を超えているか確認 */
	if (this->iNowCameraFixedPositionNo >= this->iMaxCameraFixedPositionNo - 1)
	{
		// 超えている場合
		/* カメラモードを"ステージ開始(プレイヤークローズアップ)"に設定 */
		this->StageStatusList->SetCameraMode(CAMERA_MODE_STAGESTART_CLOSE_UP);

		/* プレイヤーの"開始時モーション開始フラグ"を有効化 */
		this->PlayerStatusList->SetStartFastMotion(true);
		
		/* クローズアップカウントを取得 */
		int iCloseUpCount = this->StageStatusList->iGetCloseUpCount();

		/* クローズアップカウントが最大値を超えているか確認 */
		if (iCloseUpCount >= CAMERA_CLOSEUP_COUNT_MAX)
		{
			// 超えている場合
			/* ステージ状態を初期化する */
			Initialization();

			/* ゲーム状態を"ゲーム実行"に変更 */
			this->StageStatusList->SetGameStatus(GAMESTATUS_PLAY_GAME);
		}
		else
		{
			// 超えていない場合
			/* クローズアップカウントを加算 */
			this->StageStatusList->SetCameraCloseUpCount(iCloseUpCount + 1);
		}
	}
	else
	{
		// 超えていない場合
		/* カメラモードを"ステージ開始"に設定 */
		this->StageStatusList->SetCameraMode(CAMERA_MODE_STAGESTART);

		/* クローズアップカウントを初期化 */
		this->StageStatusList->SetCameraCloseUpCount(0);
	}

	/* エネミー以外のオブジェクトの更新 */
	ObjectList->UpdatePlayer();
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
		TestDrawShadowMap(iShadowMapScreenHandle_Actor, SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1));
		iDrawCount++;
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

	/* 入力描写テスト */
	if (gbDrawInputTest == true)
	{
		/* ジャンプ */
		if (gpDataList_Input->bGetGameInputAction(INPUT_HOLD, GAME_JUMP))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "ジャンプ入力", GetColor(255, 255, 255));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_TRG, GAME_JUMP))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "ジャンプトリガ入力", GetColor(255 ,0 ,0));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_REL, GAME_JUMP))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "ジャンプリリース入力", GetColor(255, 255, 255));
			iDrawCount++;
		}
		
		/* 攻撃 */
		if (gpDataList_Input->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "攻撃入力", GetColor(255, 255, 255));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_TRG, GAME_ATTACK))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "攻撃トリガ入力", GetColor(255, 0, 0));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_REL, GAME_ATTACK))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "攻撃ホールド入力", GetColor(255, 255, 255));
			iDrawCount++;
		}

		/* エイム(構え) */
		if (gpDataList_Input->bGetGameInputAction(INPUT_HOLD, GAME_AIM))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount,"エイム(構え)入力", GetColor(255, 255, 255));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_TRG, GAME_AIM))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "エイム(構え)トリガ入力", GetColor(255, 0, 0));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_REL, GAME_AIM))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "エイム(構え)リリース入力", GetColor(255, 255, 255));
			iDrawCount++;
		}

		/* カメラリセット */
		if (gpDataList_Input->bGetGameInputAction(INPUT_HOLD, GAME_RESET))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "カメラリセット入力", GetColor(255, 255, 255));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_TRG, GAME_RESET))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "カメラリセットトリガ入力", GetColor(255, 0, 0));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_REL, GAME_RESET))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "カメラリセットリリース入力", GetColor(255, 255, 255));
			iDrawCount++;
		}

		/* 回避 */
		if (gpDataList_Input->bGetGameInputAction(INPUT_HOLD, GAME_DODGE))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "回避入力", GetColor(255, 255, 255));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_TRG, GAME_DODGE))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "回避トリガ入力", GetColor(255, 255, 255));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_REL, GAME_DODGE))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "回避リリース入力", GetColor(255, 255, 255));
			iDrawCount++;
		}
	}
}

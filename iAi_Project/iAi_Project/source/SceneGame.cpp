/* 2024.12.XX YYYY ZZZZ */

#include "SceneGame.h"

/* シーン「ゲーム」の定義 */

// コンストラクタ
SceneGame::SceneGame() : SceneBase("Game", 0, false)
{
	/* データリスト作成 */
	{
		/* データリストサーバーに"ゲームリソース管理"を追加 */
		gpDataListServer->AddDataList(new DataList_GameResource());
	}

	/* データリスト取得 */
	{
		/* "ステージ状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* BGMを設定 */
	gpDataList_Sound->BGM_SetHandle(BGM_STAGE);

	/* 初期化 */
	/* 最初のステージ番号を設定 */
	this->StageStatusList->SetNowStageNo(STAGE_START);

	/* 最終ステージ番号を設定 */
	this->StageStatusList->SetEndStageNo(STAGE_END);

	/* カメラモードを"フリー"に設定 */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_NORMAL);

	/* UI追加フラグを有効化 */
	this->StageStatusList->SetAddUiFlg(true);

	/* 最初にエディット画面を追加する状態にする */
	this->StageStatusList->SetFastEditFlg(true);

	/* "最初のステージ番号"のステージを読み込む */
	/* シーン"ステージ"を作成 */
	SceneBase* pAddScene = new SceneStage();

	/* シーン"ステージ"をシーンサーバーに追加 */
	gpSceneServer->AddSceneReservation(pAddScene);

	/* ステージの読み込みを開始 */
	dynamic_cast<SceneStage*>(pAddScene)->LoadMapData();

	/* 初期化処理 */
	pAddScene->Initialization();
}

// デストラクタ
SceneGame::~SceneGame()
{
	/* データリスト削除 */
	{
		/* ゲームリソース管理 */
		gpDataListServer->DeleteDataList("DataList_StageResource");
	}
}

// 計算
void SceneGame::Process()
{
	/* ゲーム状態に応じて処理を変更 */
	switch (this->StageStatusList->iGetGameStatus())
	{
		/* "次のステージへ遷移"状態 */
		case GAMESTATUS_NEXTSTAGE:
			{
				/* 現在のステージ番号を取得 */
				int iNowStageNo = this->StageStatusList->iGetNowStageNo();

				/* ステージ番号を+1する */
				iNowStageNo++;

				/* ステージ番号が最終ステージ番号を超えていないか確認 */
				if (iNowStageNo <= this->StageStatusList->iGetEndStageNo())
				{
					// 超えていない(次のステージがある)場合
					/* ステージ番号を設定 */
					this->StageStatusList->SetNowStageNo(iNowStageNo);

					/* ロードシーン追加フラグを有効化 */
					gpSceneServer->SetAddLoadSceneFlg(true);

					/* シーン"ステージ"を作成 */
					SceneBase* pAddScene = new SceneStage();

					/* 初期化処理を実施 */
					pAddScene->Initialization();

					/* シーン"ステージ"をシーンサーバーに追加 */
					gpSceneServer->AddSceneReservation(pAddScene);

					/* ステージの読み込みを開始 */
					dynamic_cast<SceneStage*>(pAddScene)->LoadMapData();
				}
				else
				{
					// 超えている(次のステージがない)場合
					/* シーン削除フラグを有効にする */
					this->bDeleteFlg = true;

					/* ロード画面追加フラグを有効化 */
					gpSceneServer->SetAddLoadSceneFlg(true);

					/* 現行シーン削除フラグを有効化 */
					gpSceneServer->SetDeleteCurrentSceneFlg(true);

					/* シーン"タイトル画面"を追加 */
					gpSceneServer->AddSceneReservation(new SceneAddTitleSetup());
				}
			}

			/* ゲーム状態を"ゲーム実行"に変更する */
			this->StageStatusList->SetGameStatus(GAMESTATUS_PLAY_GAME);
			break;

		/* "ステージジャンプ"状態 */
		case GAMESTATUS_STAGE_JUMP:
			{
				/* ジャンプ後のステージ番号を取得 */
				int iJumpStageNo = this->StageStatusList->iGetJumpStageNo();

				/* ステージ番号を設定 */
				this->StageStatusList->SetNowStageNo(iJumpStageNo);

				/* ロードシーン追加フラグを有効化 */
				gpSceneServer->SetAddLoadSceneFlg(true);

				/* シーン"ステージ"を作成 */
				SceneBase* pAddScene = new SceneStage();

				/* 初期化処理を実施 */
				pAddScene->Initialization();

				/* シーン"ステージ"をシーンサーバーに追加 */
				gpSceneServer->AddSceneReservation(pAddScene);

				/* ステージの読み込みを開始 */
				dynamic_cast<SceneStage*>(pAddScene)->LoadMapData();
			}
			break;
	}
}

// 描画
void SceneGame::Draw()
{
	/* 現在のステージ番号を取得 */
	int iNowStageNo = this->StageStatusList->iGetNowStageNo();

	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "現在のステージ番号 ： %d", iNowStageNo);
}


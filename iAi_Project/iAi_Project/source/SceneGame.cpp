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

		/* "ゲーム内リソース管理"を取得 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}

	/* 初期化 */
	/* 最終ステージ番号を設定 */
	this->StageStatusList->SetEndStageNo(STAGE_END);	
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

// 初期化
void SceneGame::Initialization()
{
	/* 最初のステージ番号を設定 */
	int iStartStageNo = STAGE_START;

	/* 中断データが残っているか確認 */
	{
		/* セーブデータ(中断時)のパス設定 */
		std::string SaveDataFileName = "resource/SaveData/SuspensionSaveData.json";

		/* ファイルの存在確認 */
		std::ifstream inputFile(SaveDataFileName);

		/* ファイルが存在するか確認 */
		if (inputFile.is_open())
		{
			// 存在する場合
			/* セーブデータ内の情報を取得する */
			nlohmann::json	json;
			inputFile >> json;

			/* 所持ブラッドを読み込み */
			int iBlood = 0;
			json.at("Blood").get_to(iBlood);
			this->GameResourceList->SetHaveBlood(iBlood);

			/* ステージ番号を読み込み */
			json.at("StageNo").get_to(iStartStageNo);

			/* 現在のエディット情報を読み込み */
			int iIndex = 0;
			for (const auto& edit : json["EditData"])
			{
				/* エディット情報を取得 */
				EDIT_DATA stEditData;
				stEditData.iEditEffect	= edit["Effect"];
				stEditData.iEditCost	= edit["Cost"];
				stEditData.iEditRank	= edit["Rank"];
				stEditData.aText		= edit["Text"];

				/* 読み込んだ文字列をUTF-8～Shift-JISに変換 */
				stEditData.aText = PUBLIC_PROCESS::aUtf8ToShiftJIS(stEditData.aText);

				/* エディット情報を設定 */
				this->GameResourceList->SetNowEditData(iIndex, stEditData);

				/* インデックスを+1する */
				iIndex++;
			}

			/* キープ中のエディット情報を読み込み */
			EDIT_DATA stKeepEditData;
			stKeepEditData.iEditCost	= json["KeepEditData"]["Cost"];
			stKeepEditData.iEditEffect	= json["KeepEditData"]["Effect"];
			stKeepEditData.iEditRank	= json["KeepEditData"]["Rank"];
			stKeepEditData.aText		= json["KeepEditData"]["Text"];

			/* 読み込んだ文字列をUTF-8～Shift-JISに変換 */
			stKeepEditData.aText = PUBLIC_PROCESS::aUtf8ToShiftJIS(stKeepEditData.aText);

			/* キープ中のエディット情報を設定 */
			this->GameResourceList->SetKeepEditData(stKeepEditData);
		}
		else
		{
			// 存在しない場合
			/* 会話パート(オープニング)を生成 */
			SceneConversation* pAddConversation = new SceneConversation();
			gpSceneServer->AddSceneReservation(pAddConversation);
			pAddConversation->SetTextFileNo(0);
			pAddConversation->Initialization();
		}
	}

	/* ステージ番号を設定 */
	this->StageStatusList->SetNowStageNo(iStartStageNo);

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

	/* 初期化処理を実行する */
	pAddScene->Initialization();
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

					/* 初期化処理を実行する */
					pAddScene->Initialization();
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

					/* シーン"エンドクレジット"をシーンサーバーに追加 */
					gpSceneServer->AddSceneReservation(new SceneEndcredit());
				}
			}
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


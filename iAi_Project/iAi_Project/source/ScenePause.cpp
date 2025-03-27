/* 2025.03.05 ファイル作成 駒沢風助 */

#include "ScenePause.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* 一時停止クラスの定義 */
// コンストラクタ
ScenePause::ScenePause() : SceneBase("Pause", 450, true)
{
	/* データリスト取得 */
	{
		/* "ステージ状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "ゲーム内リソース管理"を取得 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}

	/* 初期化 */
	this->iSelectItem	= PAUSE_MANU_CONTINUE;

	/* 停止開始時の時間を取得 */
	this->iStopStartTime	= GetNowCount();

	/* マウスを使用可能に設定 */
	gbUseMouseFlg = true;
}

// デストラクタ
ScenePause::~ScenePause()
{
	/* 現在の時間と開始時の時間の差異を取得 */
	int iStopTime = GetNowCount() - this->iStopStartTime;

	/* ステージ上の停止総合時間を取得 */
	int iStopTotalTime = this->StageStatusList->iGetStopTotalTime();

	/* ステージ上の停止総合時間に加算し登録 */
	this->StageStatusList->SetStopTotalTime(iStopTotalTime + iStopTime);

	/* "ポーズメニュー開閉"のSEを再生 */
	gpDataList_Sound->SE_PlaySound(SE_SYSTEM_POSEMENU);

	/* マウスを使用不可に設定 */
	gbUseMouseFlg = false;
}

// 計算
void ScenePause::Process()
{
	/* "決定"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		// 入力されている場合
		/* "決定"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

		/* 選択中の項目によって処理を分岐 */
		switch (this->iSelectItem)
		{
			/* 続ける */
			case PAUSE_MANU_CONTINUE:
				/* このシーンの削除フラグを有効にする */
				this->bDeleteFlg = true;
				break;

			/* 最初から */
			case PAUSE_MANU_RESTART:
				/* ゲーム状態を"リセット"に変更する */
				this->StageStatusList->SetGameStatus(GAMESTATUS_RESET);

				/* このシーンの削除フラグを有効にする */
				this->bDeleteFlg = true;
				break;

			/* オプション */
			case PAUSE_MANU_OPTION:
				/* シーン"オプション"を追加 */
				gpSceneServer->AddSceneReservation(new SceneOption());
				break;

			/* タイトルへ */
			case PAUSE_MANU_TITLE:
				/* セーブデータを作成する */
				SaveDataCreate();

				/* ロード画面追加フラグを有効化 */
				gpSceneServer->SetAddLoadSceneFlg(true);

				/* 現行シーン削除フラグを有効化 */
				gpSceneServer->SetDeleteCurrentSceneFlg(true);

				/* シーン"タイトル"を追加 */
				gpSceneServer->AddSceneReservation(new SceneAddTitleSetup());
				break;
		}

		return;
	}

	/* "キャンセル"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
	{
		// 入力されている場合
		/* "キャンセル"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_CANCEL);

		/* このシーンの削除フラグを有効にする */
		this->bDeleteFlg = true;

		return;
	}

	/* "上"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
	{
		// 入力されている場合
		/* "カーソル移動"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* 選択項目を上に進める */
		this->iSelectItem -= 1;
	}

	/* "下"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
	{
		// 入力されている場合
		/* "カーソル移動"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* 選択項目を下に進める */
		this->iSelectItem += 1;
	}

	/* 選択中の項目の番号を範囲内に収める*/
	if (this->iSelectItem < 0)
	{
		this->iSelectItem = 0;
	}
	else if (this->iSelectItem >= PAUSE_MANU_MAX)
	{
		this->iSelectItem = PAUSE_MANU_MAX - 1;
	}
}

// 描画
void ScenePause::Draw()
{
	/* 画面全体を暗くする */
	{
		/* 描写ブレンドモードを"アルファブレンド"に設定 */
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, PAUSE_BLACK_ALPHA);

		/* 画面全体を黒色で描写 */
		DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);

		/* 描写ブレンドモードを"ノーブレンド"に設定 */
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	/* 選択肢描写 */
	{
		/* 描写文字列 */
		std::vector<std::string> options = { "続ける", "最初から", "オプション", "タイトルへ" };

		/* 座標データ */
		// 最も上の項目の描写座標
		const int iX		= SCREEN_SIZE_WIDE / 2 - 100;
		const int iY		= SCREEN_SIZE_HEIGHT / 2 - 100;
		// 選択肢の間隔
		const int iOffsetY	= 50;

		/* 各項目を描写 */
		for (size_t i = 0; i < options.size(); ++i)
		{
			/* 描写色(白) */
			int iColor = GetColor(255, 255, 255);

			/* 現在の選択項目であるか確認 */
			if (i == this->iSelectItem)
			{
				// 現在の選択項目である場合
				/* 描写色を黄色に設定 */
				iColor = GetColor(255, 255, 0);
			}

			/* 文字列描写 */
			DrawFormatStringToHandle(iX, iY + static_cast<int>(i) * iOffsetY, iColor, giFontHandle_Small, options[i].c_str());
		}
	}
}

// セーブデータ作成
void ScenePause::SaveDataCreate()
{
	/* セーブデータ(中断時)のパス設定 */
	std::string SaveDataFileName = "resource/SaveData/SuspensionSaveData.json";

	/* 対象のファイルを削除 */
	std::remove(SaveDataFileName.c_str());

	/* Jsonデータの作成 */
	nlohmann::json json;

	/* ステージ開始時の所持ブラッドを保存 */
	json["Blood"] = this->GameResourceList->iGetStartBlood();

	/* ステージ番号を保存 */
	json["StageNo"] = this->StageStatusList->iGetNowStageNo();

	/* 現在エディット情報を保存 */
	{
		for (int i = 0; i < EDIT_MAX; i++)
		{
			/* 現在のエディット情報を取得 */
			EDIT_DATA stEditData = this->GameResourceList->stGetNowEditData(i);

			/* エディット情報を保存 */
			json["EditData"][i]["Effect"]	= stEditData.iEditEffect;
			json["EditData"][i]["Rank"]		= stEditData.iEditRank;
			json["EditData"][i]["Cost"]		= stEditData.iEditCost;
			json["EditData"][i]["Text"]		= PUBLIC_PROCESS::aShiftJisToUtf8(stEditData.aText);
		}
	}

	/* キープエディット情報を保存 */
	{
		/* キープエディット情報を取得 */
		EDIT_DATA stEditData = this->GameResourceList->stGetKeepEditData();

		/* エディット情報を保存 */
		json["KeepEditData"]["Effect"]	= stEditData.iEditEffect;
		json["KeepEditData"]["Rank"]	= stEditData.iEditRank;
		json["KeepEditData"]["Cost"]	= stEditData.iEditCost;
		json["KeepEditData"]["Text"]	= PUBLIC_PROCESS::aShiftJisToUtf8(stEditData.aText);
	}

	/* Jsonファイル展開 */
	std::ofstream outputFile(SaveDataFileName);

	/* Jsonファイル書き込み */
	outputFile << json.dump(4);
}

/* 2025.03.27 ファイル作成 駒沢風助 */

#include "SceneUi_Tutorial.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* UI(チュートリアル)クラスの定義 */
// コンストラクタ
SceneUi_Tutorial::SceneUi_Tutorial() : SceneBase("Tutorial", 400, true)
{
	/* データリスト取得 */
	{
		/* "ステージ状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* チュートリアルウィンドウ */
		this->piGrHandle_Tutorial_Window = ImageList->piGetImage("UI_Tutorial/Tutorial_Window");
	}

	/* 停止開始時の時間を取得 */
	this->iTutorialNo		= 0;				// 描写するチュートリアルの番号
	this->iStopStartTime	= GetNowCount();	// 停止開始時の時間
	this->iMaxItemNo		= 0;				// 現在のチュートリアルの最大項目数
	this->iNowItemNo		= 0;				// 現在のチュートリアルの描写中の項目数
}

// デストラクタ
SceneUi_Tutorial::~SceneUi_Tutorial()
{
	/* 現在の時間と開始時の時間の差異を取得 */
	int iStopTime = GetNowCount() - this->iStopStartTime;

	/* ステージ上の停止総合時間を取得 */
	int iStopTotalTime = this->StageStatusList->iGetStopTotalTime();

	/* ステージ上の停止総合時間に加算し登録 */
	this->StageStatusList->SetStopTotalTime(iStopTotalTime + iStopTime);

	/* "ポーズメニュー開閉"のSEを再生 */
	gpDataList_Sound->SE_PlaySound(SE_SYSTEM_POSEMENU);
}

// 初期化
void SceneUi_Tutorial::Initialization()
{
	/* 現在のチュートリアル番号の描写内容を取得 */
	{
		/* 取得した画像名を保存する配列の宣言 */
		std::vector<std::string> aImageName;

		/* パスとファイル名の設定 */
		std::string FilePath		= "resource/SetupData/";	// 保存場所
		std::string jsonFileName	= "TutorialData.json";		// ファイル名

		/* ファイル展開 */
		std::ifstream inputFile(FilePath + jsonFileName);

		/* ファイルの展開が成功したか確認 */
		if (inputFile.is_open())
		{
			// ファイルが存在する場合
			/* JSON データを取得 */
			nlohmann::json json;
			inputFile >> json;

			/* 対象のキーのデータを取得 */
			auto& value = json.at(std::to_string(this->iTutorialNo));

			/* 描写画像 */
			if (value.contains("DrawCg"))
			{
				// DrawCgが配列なので、std::vector<std::string> で取得する
				std::vector<std::string> drawCg = value.at("DrawCg").get<std::vector<std::string>>();

				// 配列内の各要素をaImageNameに追加
				aImageName.insert(aImageName.end(), drawCg.begin(), drawCg.end());
			}

			/* 描写テキスト */
			if (value.contains("Text"))
			{
				// Textも配列なので、std::vector<std::string> で取得する
				std::vector<std::string> text = value.at("Text").get<std::vector<std::string>>();

				// this->aTextに追加
				this->aText.insert(this->aText.end(), text.begin(), text.end());
			}

			/* テキストをUTF-8からShift-Jisに変換 */
			for (auto& name : this->aText)
			{
				/* 変換 */
				name = PUBLIC_PROCESS::aUtf8ToShiftJIS(name);
			}

			/* ファイルを閉じる */
			inputFile.close();
		}

		/* 画像読み込み */
		{
			/* データリスト"画像ハンドル管理"を取得 */
			DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

			/* チュートリアル描写画像 */
			for (auto& name : aImageName)
			{
				/* 画像を取得 */
				std::string str = "UI_Tutorial/Image/" + name;
				int* iImageData = ImageList->piGetImage(str);

				/* 取得した画像を保存 */
				this->apiGrHandle_Tutorial_Cg.push_back(iImageData);

				/* 項目数設定 */
				this->iMaxItemNo++;
			}
		}
	}
}

// 計算
void SceneUi_Tutorial::Process()
{
	/* "決定"が入力されたか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// 入力された場合
		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
	}

	/* "左"が入力されたか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT))
	{
		// 入力された場合
		/* 描写項目を一つ戻す*/
		this->iNowItemNo -= 1;

		/* 描写項目が最初の項目であるか*/
		if (this->iNowItemNo <= 0)
		{
			// 最初の項目である場合
			/* 描写項目を最初の項目に設定 */
			this->iNowItemNo = 0;
		}
	}

	/* "右"が入力されたか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT))
	{
		// 入力された場合
		/* 描写項目を一つ進める*/
		this->iNowItemNo += 1;

		/* 描写項目が最後の項目であるか*/
		if (this->iNowItemNo >= this->iMaxItemNo)
		{
			// 最後の項目である場合
			/* 描写項目を最後の項目に設定 */
			this->iNowItemNo = this->iMaxItemNo - 1;
		}
	}
}

// 描画
void SceneUi_Tutorial::Draw()
{
	/* 画面全体を暗くする */
	{
		/* 描写ブレンドモードを"アルファブレンド"に設定 */
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

		/* 画面全体を黒色で描写 */
		DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);

		/* 描写ブレンドモードを"ノーブレンド"に設定 */
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	/* チュートリアルウィンドウを描写 */
	//DrawGraph(522, 28, *this->piGrHandle_Tutorial_Window, TRUE);

	/* チュートリアル描写画像を描写 */
	DrawGraph(522, 28, *this->apiGrHandle_Tutorial_Cg[this->iNowItemNo], TRUE);

	/* テキストを描写 */
	std::string formattedText = PUBLIC_PROCESS::aInsertNewLine(this->aText[this->iNowItemNo], 26);
	DrawFormatStringToHandle(522 + 50, 28 + 512, GetColor(255, 255, 255), giFontHandle_Small, "%s", formattedText.c_str());
}


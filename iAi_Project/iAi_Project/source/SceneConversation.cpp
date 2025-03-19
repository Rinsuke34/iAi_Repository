/* 2025.03.19 ファイル追加 駒沢風助 */

#include "SceneConversation.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <algorithm>

/* シーン"会話パート"の定義 */
// コンストラクタ
SceneConversation::SceneConversation() : SceneBase("Conversation", 400, true)
{
	/* データリスト取得 */
	{
		/* "オプション設定管理"を取得 */
		this->OptionList = dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));
	}

	/* 画像ハンドル取得 */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 画像ハンドル */
		//this->piGrHandle = ImageList->piGetImage("");
	}

	/* 初期化 */
	this->iTextFileNo	=	0;	// テキストファイル番号
	this->iDrawText		=	0;	// テキストの描写量
	this->iNowTextNo	=	0;	// 現在のテキスト番号
	this->iHoldTimer	=	0;	// 長押し時間
}

// デストラクタ
SceneConversation::~SceneConversation()
{

}

// 初期化
void SceneConversation::Initialization()
{
	/* 現在のテキストファイル番号のテキストを読み込む */
	LoadTextData();
}

// 計算
void SceneConversation::Process()
{
	/* 現在のテキスト番号のテキスト情報を取得 */
	TEXT_DATA stTextData = this->astTextDataList[this->iNowTextNo];

	/* テキスト描写量を加算 */
	this->iDrawText += stTextData.iSpeed;

	/* テキスト描写量が総量を超えたか確認 */
	if (this->iDrawText >= static_cast<int>(stTextData.aText.size()))
	{
		// 一定量を超えた場合
		/* テキスト描写量をテキスト総量に設定 */
		this->iDrawText = static_cast<int>(stTextData.aText.size());

		/* "決定"がトリガ入力されているか */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
		{
			// 入力されている場合
			/* テキスト番号を加算 */
			this->iNowTextNo += 1;

			/* テキスト描写量をリセット */
			this->iDrawText = 0;

			/* テキスト番号が総量を超えたか確認 */
			if (this->iNowTextNo >= static_cast<int>(this->astTextDataList.size()))
			{
				// 総量を超えた場合
				/* シーンの削除フラグを有効にする */
				this->bDeleteFlg = true;
			}
		}
	}

	/* "決定"がホールド入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_HOLD, UI_DECID))
	{
		// 入力されている場合
		/* 長押し時間を加算 */
		this->iHoldTimer += 1;

		/* 長押し時間が一定時間を超えたか確認 */
		if (this->iHoldTimer >= 60)
		{
			// 一定時間を超えた場合
			/* スキップ確認画面を描写 */
		}
	}
	else
	{
		// 入力されていない場合
		/* 長押し時間をリセット */
		this->iHoldTimer = 0;
	}
}

// 描画
void SceneConversation::Draw()
{
	/* 現在のテキスト情報から描写テキスト内容を作成 */
	std::string	aDrawText = PUBLIC_PROCESS::aCutShitfJisString(this->astTextDataList[this->iNowTextNo].aText, this->iDrawText);
	
	/* 現在のテキスト情報に応じた発言者の名称を描写 */

	/* 立ち絵を手前に持ってくるキャラクターに応じてネームプレートの名称を変更 */
	switch (this->astTextDataList[this->iNowTextNo].iFocusCharacter)
	{
		/* 左のキャラクター */
		case 1:
			/* 名称"シロ" */
			DrawFormatStringToHandle(100, 500, GetColor(255, 255, 255), giFontHandle_NotoSerifJP_SemiBold, "シロ");
			break;

		/* 右のキャラクター */
		case 2:
			/* 名称"サエジマ" */
			DrawFormatStringToHandle(100, 500, GetColor(255, 255, 255), giFontHandle_NotoSerifJP_SemiBold, "サエジマ");
			break;

		/* 無し */
		/* 両方 */
		default:
			/* ネームプレートに名前を描写しない */
			break;
	}

	/* テキスト描写 */
	DrawFormatStringToHandle(100, 600, GetColor(255, 255, 255), giFontHandle_NotoSerifJP_Medium, aDrawText.c_str());
}

// テキストデータ読み込み
void SceneConversation::LoadTextData()
{
	/* パスとファイル名の設定 */
	std::string strTextData = "resource/TextData/TextData_" + std::to_string(this->iTextFileNo) + ".json";

	/* ファイル展開 */
	std::ifstream inputFile(strTextData);

	/* ファイルの展開が成功したか確認 */
	if (inputFile.is_open())
	{
		// ファイルが存在する場合
		/* 会話パート用のテキストデータリストを取得 */
		nlohmann::json	json;
		inputFile >> json;
		/* すべての要素を読み込む */
		for (auto& data : json)
		{
			/* テキストデータを取得 */
			TEXT_DATA stTextData;
			data.at("Text").get_to(stTextData.aText);
			data.at("FocusChara").get_to(stTextData.iFocusCharacter);
			data.at("LeftCharaCg").get_to(stTextData.iLeftCharactorCg);
			data.at("RightCharaCg").get_to(stTextData.iRightCharactorCg);
			data.at("Speed").get_to(stTextData.iSpeed);
			data.at("VoiceNo").get_to(stTextData.iVoiceNo);

			/* 読み込んだ文字列をUTF-8～Shift-JISに変換 */
			stTextData.aText = PUBLIC_PROCESS::aUtf8ToShiftJIS(stTextData.aText);

			/* 配列に追加 */
			this->astTextDataList.push_back(stTextData);
		}

		/* ファイルを閉じる */
		inputFile.close();
	}
}

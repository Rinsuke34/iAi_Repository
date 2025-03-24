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

		/* スキップ確認ウィンドウ */
		this->piGrHandle_SkipWindow				= ImageList->piGetImage("Conversation/SkipWindow/UI_Window_Skip");

		/* スキップ確認ウィンドウ_ボタン */
		this->apiGrHandle_SkipWindow_Yes[0]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_Yes_Selected");
		this->apiGrHandle_SkipWindow_Yes[1]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_Yes_NotSelected");
		this->apiGrHandle_SkipWindow_No[0]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_No_Selected");
		this->apiGrHandle_SkipWindow_No[1]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_No_NotSelected");

		/* 決定アイコン(0:コントローラー/1:キーボード) */
		this->piGrHandle_Icon_Button_Select[0]	= ImageList->piGetImage("Input_Icon/XBOX/xbox_button_a");
		this->piGrHandle_Icon_Button_Select[1]	= ImageList->piGetImage("Input_Icon/Keyboard/keyboard_z");

		/* ホールドアイコン */
		this->piGrHandle_Icon_Hold				= ImageList->piGetImage("Conversation/HoldTimer");

		/* 背景 */
		this->piGrhandle_BackGround				= ImageList->piGetImage("Conversation/Bg_Dialogue_Stage");

		/* テキスト背景 */
		this->piGrHandle_TextBackGround			= ImageList->piGetImage("Conversation/UI_Dialogue_Frame");

		/* プレイヤー立ち絵 */
		this->apiGrHandle_Standing_Player[0]	= ImageList->piGetImage("Conversation/Standing/Player/stand_player_01");
		this->apiGrHandle_Standing_Player[1]	= ImageList->piGetImage("Conversation/Standing/Player/stand_player_02");
		this->apiGrHandle_Standing_Player[2]	= ImageList->piGetImage("Conversation/Standing/Player/stand_player_03");

		/* 博士(サエジマ)立ち絵 */
		this->apiGrHandle_Standing_Doctor[0]	= ImageList->piGetImage("Conversation/Standing/Doctor/stand_doctor_01");
		this->apiGrHandle_Standing_Doctor[1]	= ImageList->piGetImage("Conversation/Standing/Doctor/stand_doctor_02");
		this->apiGrHandle_Standing_Doctor[2]	= ImageList->piGetImage("Conversation/Standing/Doctor/stand_doctor_03");
	}

	/* 初期化 */
	this->iTextFileNo		=	-1;		// テキストファイル番号
	this->iTextDrawDelay	=	0;		// テキスト更新待機時間
	this->iDrawText			=	0;		// テキストの描写量
	this->iNowTextNo		=	0;		// 現在のテキスト番号
	this->iHoldTimer		=	0;		// 長押し時間
	this->bAddSkipCheckFlg	=	false;	// スキップ確認画面を描写中であるか
	this->bSelectYes		=	false;	// YESを選択中であるか(スキップ画面)
}

// 初期化
void SceneConversation::Initialization()
{
	/* テキストファイル番号が0(オープニング会話)であるか確認 */
	if (this->iTextFileNo == 0)
	{
		// オープニング会話である場合
		/* 背景を別の物に変更する */
		/* 画像ハンドル取得 */
		{
			/* データリスト"画像ハンドル管理"を取得 */
			DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

			/* 背景 */
			this->piGrhandle_BackGround = ImageList->piGetImage("Conversation/Bg_Dialogue_Op");
		}
	}

	/* 現在のテキストファイル番号のテキストを読み込む */
	LoadTextData();
}

// 計算
void SceneConversation::Process()
{
	/* テキストファイル番号が無効(-1)であるか確認 */
	if (this->iTextFileNo == -1)
	{
		// 無効である場合
		/* このシーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
		return;
	}

	/* スキップ確認画面を描写中であるか確認 */
	if (this->bAddSkipCheckFlg == true)
	{
		// 描写中である場合
		/* スキップ確認画面の描写処理 */
		Process_SkipCheck();
	}
	else
	{
		// 描写中でない場合
		/* 会話パートの描写処理 */
		Process_Conversation();
	}
}

// 描画
void SceneConversation::Draw()
{
	/* 背景描写 */
	DrawGraph(0, 0, *this->piGrhandle_BackGround, TRUE);

	/* 立ち絵描写 */
	DrawGraph(0,	0, *this->apiGrHandle_Standing_Player[this->astTextDataList[this->iNowTextNo].iLeftCharactorCg], TRUE);
	DrawGraph(840,	0, *this->apiGrHandle_Standing_Doctor[this->astTextDataList[this->iNowTextNo].iRightCharactorCg], TRUE);

	/* 会話ウィンドウ背景描写 */
	DrawGraph(0, 715, *this->piGrHandle_TextBackGround, TRUE);

	/* 現在のテキスト情報から描写テキスト内容を作成 */
	std::string	aDrawText = PUBLIC_PROCESS::aCutShitfJisString(this->astTextDataList[this->iNowTextNo].aText, this->iDrawText);
	
	/* 立ち絵を手前に持ってくるキャラクターに応じてネームプレートの名称を変更 */
	switch (this->astTextDataList[this->iNowTextNo].iFocusCharacter)
	{
		/* 左のキャラクター */
		case 1:
			/* 名称"シロ" */
			DrawFormatStringToHandle(200, 850, GetColor(0, 0, 255), giFontHandle_NotoSerifJP_SemiBold, "シロ");
			break;

		/* 右のキャラクター */
		case 2:
			/* 名称"サエジマ" */
			DrawFormatStringToHandle(200, 850, GetColor(0, 0, 255), giFontHandle_NotoSerifJP_SemiBold, "サエジマ");
			break;

		/* 無し */
		/* 両方 */
		default:
			/* ネームプレートに名前を描写しない */
			break;
	}

	/* テキスト描写 */
	DrawFormatStringToHandle(250, 900, GetColor(255, 255, 255), giFontHandle_NotoSerifJP_Medium, aDrawText.c_str());

	/* スキップ確認画面を描写中であるか確認 */
	if (this->bAddSkipCheckFlg == true)
	{
		// 描写中である場合
		/* スキップ確認画面を描写 */
		DrawGraph(570, 270, *this->piGrHandle_SkipWindow, TRUE);

		/* YESが選択中であるか確認 */
		if (this->bSelectYes == true)
		{
			// YESが選択中の場合
			/* YESを選択中として描写 */
			DrawGraph(690, 560, *this->apiGrHandle_SkipWindow_Yes[0], TRUE);

			/* NOを非選択中として描写 */
			DrawGraph(1020, 560, *this->apiGrHandle_SkipWindow_No[1], TRUE);
		}
		else
		{
			// YESが選択中でない場合
			/* YESを非選択中として描写 */
			DrawGraph(690, 560, *this->apiGrHandle_SkipWindow_Yes[1], TRUE);

			/* NOを選択中として描写 */
			DrawGraph(1020, 560, *this->apiGrHandle_SkipWindow_No[0], TRUE);
		}
	}

	/* キーボード描写であるか確認 */
	int iDrawTypeNo = 0;
	if (OptionList->bGetOperation_Keyboard() == true)
	{
		// キーボード描写である場合
		/* 描写タイプ番号をキーボード描写に設定 */
		iDrawTypeNo = 1;
	}
	else
	{
		// キーボード描写でない場合
		/* 描写タイプ番号をコントローラー描写に設定 */
		iDrawTypeNo = 0;
	}

	/* Aボタン描写 */
	DrawGraph(1820, 980, *this->piGrHandle_Icon_Button_Select[iDrawTypeNo], TRUE);
	double dComboTimerPercent = (static_cast<double>(this->iHoldTimer / 60.f) * 100.0);
	DrawCircleGauge(1820 + 32, 980 + 32, dComboTimerPercent, *this->piGrHandle_Icon_Hold);
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
			data.at("BgmNo").get_to(stTextData.iBgmNo);

			/* 読み込んだ文字列をUTF-8～Shift-JISに変換 */
			stTextData.aText = PUBLIC_PROCESS::aUtf8ToShiftJIS(stTextData.aText);

			/* 配列に追加 */
			this->astTextDataList.push_back(stTextData);
		}

		/* ファイルを閉じる */
		inputFile.close();
	}
	else
	{
		// ファイルが存在しない場合
		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
	}
}

// 計算(スキップ画面描写中)
void SceneConversation::Process_SkipCheck()
{
	/* "決定"がトリガ入力されているか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// 入力されている場合
		/* "決定"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

		/* YESが選択中であるか確認 */
		if (this->bSelectYes == true)
		{
			// 選択中である場合
			/* 削除フラグを有効にする */
			this->bDeleteFlg = true;
		}
		else
		{
			// 選択中でない場合
			/* スキップ確認画面を非描写中にする */
			this->bAddSkipCheckFlg = false;
		}
	}

	/* "キャンセル"がトリガ入力されているか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
	{
		// 入力されている場合
		/* スキップ確認画面を非描写中にする */
		this->bAddSkipCheckFlg = false;
	}

	/* "左"がトリガ入力されているか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT))
	{
		// 入力されている場合
		/* "カーソル移動"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* YESを選択中とする */
		this->bSelectYes = true;
	}

	/* "右"がトリガ入力されているか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT))
	{
		// 入力されている場合
		/* "カーソル移動"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* Noを選択中とする */
		this->bSelectYes = false;
	}
}

// 計算(会話パート描写中)
void SceneConversation::Process_Conversation()
{
	/* 現在のテキスト番号のテキスト情報を取得 */
	TEXT_DATA stTextData = this->astTextDataList[this->iNowTextNo];

	/* テキストが描写された直後であるか */
	if ((this->iDrawText == 0) && (this->iTextDrawDelay == 0))
	{
		// 描写された直後である場合
		/* ボイス番号が有効であるか確認 */
		if (stTextData.iVoiceNo != -1)
		{
			// 有効である場合
			/* ボイス再生 */
			gpDataList_Sound->VOICE_PlaySound(stTextData.iVoiceNo);
		}

		/* BGM番号が有効であるか確認 */
		if (stTextData.iBgmNo != -1)
		{
			// 有効である場合
			/* BGM再生 */
			gpDataList_Sound->BGM_SetHandle(stTextData.iBgmNo);
		}
	}

	/* テキスト更新待機時間を加算 */
	this->iTextDrawDelay += 1;

	/* テキスト更新待機時間が設定された時間を超えたか確認 */
	if (this->iTextDrawDelay > stTextData.iSpeed)
	{
		// 超えた場合
		/* テキスト更新待機時間をリセット */
		this->iTextDrawDelay = 0;

		/* テキスト描写量を加算 */
		this->iDrawText += 1;
	}

	/* テキスト描写量が総量を超えたか確認 */
	if (this->iDrawText >= static_cast<int>(stTextData.aText.size()))
	{
		// 一定量を超えた場合
		/* テキスト描写量をテキスト総量に設定 */
		this->iDrawText = static_cast<int>(stTextData.aText.size());

		/* "決定"がトリガ入力されているか確認 */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
		{
			// 入力されている場合
			/* "決定"のSEを再生 */
			gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

			/* テキスト番号を加算 */
			this->iNowTextNo += 1;

			/* テキスト更新待機時間をリセット */
			this->iTextDrawDelay = 0;

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
	else
	{
		// 総量を超えていない場合
		/* "決定"がトリガ入力されているか確認 */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
		{
			// 入力されている場合
			/* "決定"のSEを再生 */
			gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

			/* テキスト描写量をテキスト総量に設定 */
			this->iDrawText = static_cast<int>(stTextData.aText.size());
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
			/* 長押し時間をリセット */
			this->iHoldTimer = 0;

			/* スキップ確認画面を描写中にする */
			this->bAddSkipCheckFlg = true;
		}
	}
	else
	{
		// 入力されていない場合
		/* 長押し時間をリセット */
		this->iHoldTimer = 0;
	}
}

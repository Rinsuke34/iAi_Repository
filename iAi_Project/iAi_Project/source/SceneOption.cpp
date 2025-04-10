/* 2025.03.05 ファイル追加 駒沢風助 */

#include "SceneOption.h"

/* シーン「オプション」の定義 */

// コンストラクタ
SceneOption::SceneOption() : SceneBase("Option", 500, true)
{
	/* データリスト取得 */
	{
		/* "オプション設定管理"を取得 */
		this->OptionList = dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));
	}

	/* 画像リソース取得 */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* リザルト用フレーム */
		this->piGrHandle_ResultFrame	= ImageList->piGetImage("Result/UI_Result_Frame");
	}

	/* オプション名リストのポインタを取得 */
	this->astOptionNameList = this->OptionList->stGetOptionNameList();

	/* 初期化 */
	this->iSelectItem		= 0;			// 選択中の項目の番号
}

// デストラクタ
SceneOption::~SceneOption()
{
	/* 更新したオプション設定をjsonファイルに書き込む */
	this->OptionList->SaveOptionData();
}

// 計算
void SceneOption::Process()
{
	/* 現在のSE音量とボイス音量を取得 */
	int iSeSoundVolume_Old		= this->OptionList->iGetSeVolume();
	int iVoiceSoundVolume_Old	= this->OptionList->iGetVoiceVolume();

	/* "キャンセル"がトリガ入力されているか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL) == true)
	{
		// 入力されている場合
		/* 削除フラグを有効にする */
		this->bDeleteFlg = true;
	}

	/* "上"がトリガ入力されているか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP) == true)
	{
		// 入力されている場合
		/* "カーソル移動"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* 選択項目を上に進める */
		this->iSelectItem -= 1;
	}

	/* "下"がトリガ入力されているか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN) == true)
	{
		// 入力されている場合
		/* "カーソル移動"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* 選択項目を下に進める */
		this->iSelectItem += 1;
	}

	/* "右"がトリガ入力されているか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT) == true)
	{
		/* データ型に応じて処理を変更 */
		std::string OptionType = this->astOptionNameList->at(this->iSelectItem).Type.c_str();

		/* データ型に応じて処理を変更 */
		if (OptionType == DATA_TYPE_BOOL)
		{
			// ブール型の場合
			/* ブール値を反転する */
			bool* pBoolValue = static_cast<bool*>(this->astOptionNameList->at(this->iSelectItem).pValue);
			*pBoolValue = !(*pBoolValue);
		}
		else if (OptionType == DATA_TYPE_INT)
		{
			// 整数型の場合
			/* 現在の値をfloat型で取得 */
			float fValue = static_cast<float>(*static_cast<int*>(this->astOptionNameList->at(this->iSelectItem).pValue));

			/* 値を変更 */
			fValue += static_cast<float>(this->astOptionNameList->at(this->iSelectItem).fStepValue);

			/* 最大値を上回っていないか確認 */
			if (fValue > this->astOptionNameList->at(this->iSelectItem).fMax)
			{
				// 上回っている場合
				/* 最大値に設定 */
				fValue = this->astOptionNameList->at(this->iSelectItem).fMax;
			}

			/* 整数型に変換して設定 */
			*static_cast<int*>(this->astOptionNameList->at(this->iSelectItem).pValue) = static_cast<int>(fValue);
		}
		else if (OptionType == DATA_TYPE_FLOAT)
		{
			// 浮動小数点型の場合
			/* 現在の値を取得 */
			float* pFloatValue = static_cast<float*>(this->astOptionNameList->at(this->iSelectItem).pValue);

			/* 値を変更 */
			*pFloatValue += this->astOptionNameList->at(this->iSelectItem).fStepValue;

			/* 最大値を上回っていないか確認 */
			if (*pFloatValue > this->astOptionNameList->at(this->iSelectItem).fMax)
			{
				// 上回っている場合
				/* 最大値に設定 */
				*pFloatValue = this->astOptionNameList->at(this->iSelectItem).fMax;
			}
		}
	}

	/* "左"がトリガ入力されているか確認 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT) == true)
	{
		/* データ型に応じて処理を変更 */
		std::string OptionType = this->astOptionNameList->at(this->iSelectItem).Type.c_str();

		/* データ型に応じて処理を変更 */
		if (OptionType == DATA_TYPE_BOOL)
		{
			// ブール型の場合
			/* ブール値を反転する */
			bool* pBoolValue = static_cast<bool*>(this->astOptionNameList->at(this->iSelectItem).pValue);
			*pBoolValue = !(*pBoolValue);
		}
		else if (OptionType == DATA_TYPE_INT)
		{
			// 整数型の場合
			/* 現在の値をfloat型で取得 */
			float fValue = static_cast<float>(*static_cast<int*>(this->astOptionNameList->at(this->iSelectItem).pValue));

			/* 値を変更 */
			fValue -= static_cast<float>(this->astOptionNameList->at(this->iSelectItem).fStepValue);

			/* 最小値を下回っていないか確認 */
			if (fValue < this->astOptionNameList->at(this->iSelectItem).fMin)
			{
				// 下回っている場合
				/* 最小値に設定 */
				fValue = this->astOptionNameList->at(this->iSelectItem).fMin;
			}

			/* 整数型に変換して設定 */
			*static_cast<int*>(this->astOptionNameList->at(this->iSelectItem).pValue) = static_cast<int>(fValue);
		}
		else if (OptionType == DATA_TYPE_FLOAT)
		{
			// 浮動小数点型の場合
			/* 現在の値を取得 */
			float* pFloatValue = static_cast<float*>(this->astOptionNameList->at(this->iSelectItem).pValue);

			/* 値を変更 */
			*pFloatValue -= this->astOptionNameList->at(this->iSelectItem).fStepValue;

			/* 最小値を下回っていないか確認 */
			if (*pFloatValue < this->astOptionNameList->at(this->iSelectItem).fMin)
			{
				// 下回っている場合
				/* 最小値に設定 */
				*pFloatValue = this->astOptionNameList->at(this->iSelectItem).fMin;
			}
		}
	}

	/* 選択中の項目の番号を範囲内に収める*/
	if (this->iSelectItem < 0)
	{
		this->iSelectItem = 0;
	}
	else if (this->iSelectItem >= static_cast<int>(this->astOptionNameList->size()))
	{
		this->iSelectItem = static_cast<int>(this->astOptionNameList->size()) - 1;
	}

	/* BGMの音量を変更 */
	// ※音量調整をリアルタイムで反映するため、毎フレーム音量を更新する
	gpDataList_Sound->BGM_VolumeChange();

	/* 現在のSE音量とボイス音量を取得 */
	int iSeSoundVolume		= this->OptionList->iGetSeVolume();
	int iVoiceSoundVolume	= this->OptionList->iGetVoiceVolume();

	/* SE音量が変更されているか確認 */
	if (iSeSoundVolume != iSeSoundVolume_Old)
	{
		// 変更されている場合
		/* "会話シーン決定"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_CONV_DICISION);
	}

	/* ボイス音量が変更されているか確認 */
	if (iVoiceSoundVolume != iVoiceSoundVolume_Old)
	{
		// 変更されている場合
		/* "タイトルコール(共通)"ボイスを再生 */
		gpDataList_Sound->VOICE_PlaySound(VOICE_TITLE_CALL);
	}
}

// 描画
void SceneOption::Draw()
{
	/* リザルト用のフレームを描写する */
	// ※リザルト用のフレームを流用する
	DrawExtendGraph(0 + FRAME_SIZE_REDUCTION_AMOUNT, 0 + FRAME_SIZE_REDUCTION_AMOUNT, SCREEN_SIZE_WIDE - FRAME_SIZE_REDUCTION_AMOUNT, SCREEN_SIZE_HEIGHT - FRAME_SIZE_REDUCTION_AMOUNT, *this->piGrHandle_ResultFrame, TRUE);

	/* オプションの最大数を取得 */
	int iOptionMax = this->astOptionNameList->size();

	/* オプション描写 */
	for (int i = 0; i < iOptionMax; i++)
	{
		/* 項目の色を設定 */
		int iColor = GetColor(255, 255, 255);

		/* 描写位置を設定 */
		int iDrawPosX = OPTION_DRAWPOS_X;
		int iDrawPosY = OPTION_DRAWPOS_Y + i * 50;

		/* 選択中の項目か確認 */
		if (i == this->iSelectItem)
		{
			// 選択中の場合
			/* 選択中の項目の色を変更 */
			iColor = GetColor(255, 255, 0);

			/* 選択項目の左右に矢印を描写 */
			DrawTriangle(iDrawPosX + OPTION_STATUS_DRAWPOS_X - 32, iDrawPosY, iDrawPosX + OPTION_STATUS_DRAWPOS_X - 32, iDrawPosY + 32, iDrawPosX + OPTION_STATUS_DRAWPOS_X - 56, iDrawPosY + 16, iColor, TRUE);
			DrawTriangle(iDrawPosX + OPTION_STATUS_DRAWPOS_X + 160, iDrawPosY, iDrawPosX + OPTION_STATUS_DRAWPOS_X + 160, iDrawPosY + 32, iDrawPosX + OPTION_STATUS_DRAWPOS_X + 184, iDrawPosY + 16, iColor, TRUE);
		}

		/* オプション名を描写 */
		DrawStringToHandle(iDrawPosX + 50, iDrawPosY, this->astOptionNameList->at(i).Name.c_str(), iColor, giFontHandle_Small);

		/* オプションの設定値を描写 */
		{
			/* データ型に応じて処理を変更 */
			std::string OptionType = this->astOptionNameList->at(i).Type.c_str();

			/* データ型に応じて処理を変更 */
			if (OptionType == DATA_TYPE_BOOL)
			{
				// ブール型の場合
				/* 有効であるか描写を行う */
				if (*static_cast<bool*>(this->astOptionNameList->at(i).pValue) == true)
				{
					// 有効である場合
					DrawStringToHandle(iDrawPosX + OPTION_STATUS_DRAWPOS_X, iDrawPosY, "有効", iColor, giFontHandle_Small);
				}
				else
				{
					// 無効である場合
					DrawStringToHandle(iDrawPosX + OPTION_STATUS_DRAWPOS_X, iDrawPosY, "無効", iColor, giFontHandle_Small);
				}
			}
			else if (OptionType == DATA_TYPE_INT)
			{
				// 整数型の場合
				/* 現在の値を描写する */
				DrawFormatStringToHandle(iDrawPosX + OPTION_STATUS_DRAWPOS_X, iDrawPosY, iColor, giFontHandle_Small, "%d", *static_cast<int*>(this->astOptionNameList->at(i).pValue));
			}
			else if (OptionType == DATA_TYPE_FLOAT)
			{
				// 浮動小数点型の場合
				/* 現在の値を描写する */
				DrawFormatStringToHandle(iDrawPosX + OPTION_STATUS_DRAWPOS_X, iDrawPosY, iColor, giFontHandle_Small, "%.2f", *static_cast<float*>(this->astOptionNameList->at(i).pValue));
			}
		}
	}
}

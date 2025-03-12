/* 2025.01.30 駒沢風助 ファイル作成 */

#include "DataList_Sound.h"

/* データリスト */
#include "DataList_Option.h"

/* サウンド管理データリストの定義 */

// コンストラクタ
DataList_Sound::DataList_Sound() : DataListBase("DataList_Sound")
{
	/* データリスト取得 */
	{
		/* "オプション設定管理"を取得 */
		this->OptionList = dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));
	}

	/* 初期化 */
	this->apiSpeakerInfo[VOICE_TYPE_PLAYER]	=	nullptr;
	this->apiSpeakerInfo[VOICE_TYPE_DOCTOR]	=	nullptr;

	/* 全てのSEを取得 */
	SE_AllSetHandle();

	/* 全てのボイスを取得 */
	VOICE_AllSetHandle();
}

// デストラクタ
DataList_Sound::~DataList_Sound()
{
	/* 全てのサウンドデータを削除 */
	InitSoundMem();
}

/* BGM系 */
// BGMを設定
void DataList_Sound::BGM_SetHandle(int iBgmNo)
{
	// 引数
	// iBgmNo		<- 読み込むBGMの番号

	/* 現在流れているBGMを停止 */
	BGM_StopSound();

	/* 現在のサウンドハンドルを削除 */
	BGM_DeleteHandle();

	/* BGMの番号に応じたBGMを読み込む */
	{
		/* BGM番号に応じて読み込むBGM名を変更 */
		std::string BgmName		= BGM_NAME[iBgmNo];

		std::string FileName	= "resource/SoundData/BGM/" + BgmName + ".ogg";

		/* BGMを読み込み */
		this->iBgmHandle = LoadSoundMem(FileName.c_str());
	}

	/* BGMの音量を変更 */
	BGM_VolumeChange();

	/* BGMを再生 */
	BGM_PlaySound();
}

// BGMを削除
void DataList_Sound::BGM_DeleteHandle()
{
	/* BGMが設定されているか確認 */
	if (this->iBgmHandle != 0)
	{
		// 設定されているなら
		/* BGMを削除する */
		DeleteSoundMem(this->iBgmHandle);
	}
}

// BGMを再生
void DataList_Sound::BGM_PlaySound()
{
	/* BGMが設定されているか確認 */
	if (this->iBgmHandle != 0)
	{
		// 設定されているなら
		/* BGMを再生する */
		PlaySoundMem(this->iBgmHandle, DX_PLAYTYPE_LOOP);
	}
}

// BGM音量を変更
void DataList_Sound::BGM_VolumeChange()
{
	/* BGMが設定されているか確認 */
	if (this->iBgmHandle != 0)
	{
		// 設定されているなら
		/* BGMの音量を変更する */
		ChangeVolumeSoundMem(this->OptionList->iGetBgmVolume(), this->iBgmHandle);
	}
}

// BGMを停止
void DataList_Sound::BGM_StopSound()
{
	/* BGMが設定されているか確認 */
	if (this->iBgmHandle != 0)
	{
		// 設定されているなら
		/* BGMを停止させる */
		StopSoundMem(this->iBgmHandle);
	}
}

/* SE系 */
// 全てのサウンドハンドルを取得
void DataList_Sound::SE_AllSetHandle()
{
	/* リソースファイルから全てのSEを取得 */
	for (int i = 0; i < SE_MAX; i++)
	{
		/* ファイル名を取得 */
		std::string	FileName	= SE_NAME[i];
		
		/* 対象のSEファイルのパスを取得 */
		std::string FilePath	= "resource/SoundData/SE/" + FileName + ".wav";
		
		/* SEを読み込み */
		int iAddSoundHandle		= LoadSoundMem(FilePath.c_str());

		/* SEをリストに追加 */
		this->pSeHandleList[FileName] = iAddSoundHandle;
	}
}

// SEを再生
void DataList_Sound::SE_PlaySound(int iSeNo)
{
	// 引数
	// iSeNo		<- 読み込むSEの番号

	/* SEの音量を設定 */
	ChangeVolumeSoundMem(this->OptionList->iGetSeVolume(), this->pSeHandleList[SE_NAME[iSeNo]]);

	/* SEを再生する */
	PlaySoundMem(this->pSeHandleList[SE_NAME[iSeNo]], DX_PLAYTYPE_BACK);
}

// 全てのボイスハンドルを取得
void DataList_Sound::VOICE_AllSetHandle()
{
	/* リソースファイルから全てのボイスを取得 */
	for (int i = 0; i < VOICE_MAX; i++)
	{
		/* ファイル名を取得 */
		std::string	FileName			= stVoice_Info[i].aVoiceName;

		/* ボイスタイプに応じたフォルダ名を取得 */
		std::string FileName_VoiceType	= VOICE_TYPE_NAME[stVoice_Info[i].iVoiceType];

		/* 対象のボイスファイルのパスを取得 */
		std::string FilePath = "resource/SoundData/VOICE/" + FileName_VoiceType+ "/" + FileName + ".opus";

		/* ボイスをリストに追加 */
		VOICE_HANDLE_INFO addVoice;
		addVoice.iVoiceHandle	= LoadSoundMem(FilePath.c_str());
		addVoice.iVoiceType		= stVoice_Info[i].iVoiceType;
		addVoice.iVoiceNo		= stVoice_Info[i].iVoiceNo;

		this->VoiceHandleList.push_back(addVoice);
	}
}

// ボイスを再生
void DataList_Sound::VOICE_PlaySound(int iVoiceNo)
{
	// 引数
	// iVoiceNo		<- 読み込むボイスの番号

	/* ボイス情報を保存する用の構造体を定義 */
	std::vector<int>	SelectVoice;
	int					iVoiceType = 0;

	/* 対象のボイス番号のすべてのボイスを取得 */
	for (int i = 0; i < VOICE_MAX; i++)
	{
		/* ボイス番号を取得 */
		if (this->VoiceHandleList[i].iVoiceNo == iVoiceNo)
		{
			/* ボイスのハンドルを取得 */
			SelectVoice.push_back(this->VoiceHandleList[i].iVoiceHandle);

			/* ボイスの種類(発言者情報)を取得 */
			iVoiceType = this->VoiceHandleList[i].iVoiceType;
		}
	}

	/* ボイスの個数が複数あるならランダムに1つピックする */
	int iVoiceHandle = SelectVoice[GetRand(static_cast<int>(SelectVoice.size()) - 1)];

	/* 設定されたボイスが登録されているか確認 */
	if (this->apiSpeakerInfo[iVoiceType] != nullptr)
	{
		// 登録されている場合
		/* 設定された発言者のボイスが再生状態であるか確認 */
		if (CheckSoundMem(*this->apiSpeakerInfo[iVoiceType]) == 1)
		{
			// ボイスが再生状態である場合
			/* ボイスを停止 */
			StopSoundMem(*this->apiSpeakerInfo[iVoiceType]);
		}
	}

	/* ボイスの音量を設定 */
	ChangeVolumeSoundMem(this->OptionList->iGetVoiceVolume(), iVoiceHandle);

	/* ボイスを再生する */
	PlaySoundMem(iVoiceHandle, DX_PLAYTYPE_BACK);

	/* 発言者情報を更新 */
	this->apiSpeakerInfo[iVoiceType] = &iVoiceHandle;
}

/* 2025.01.30 駒沢風助 ファイル作成 */

#include "DataList_Sound.h"

/* サウンド管理データリストの定義 */

// コンストラクタ
DataList_Sound::DataList_Sound() : DataListBase("DataList_Sound")
{
	/* データリスト取得 */
	{
		/* "オプション設定管理"を取得 */
//		this->OptionList = dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));
	}

	/* 全てのSEを取得 */
	SE_AllSetHandle();
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
//		ChangeVolumeSoundMem(this->OptionList->iGetBgmVolume(), this->iBgmHandle);
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
	/* リソースファイルから全てのサウンドを取得 */
	for (int i = 0; i < SE_MAX; i++)
	{
		/* ファイル名を取得 */
		std::string	FileName	= SE_NAME[i];
		
		/* 対象のSEファイルのパスを取得 */
		std::string FilePath	= "resource/SoundData/SE/" + FileName + ".wav";
		
		/* サウンドを読み込み */
		int iAddSoundHandle		= LoadSoundMem(FilePath.c_str());

		/* サウンドをリストに追加 */
		this->pSeHandleList[FileName] = iAddSoundHandle;
	}
}

// サウンドを再生
void DataList_Sound::SE_PlaySound(int iSeNo)
{
	// 引数
	// iSeNo		<- 読み込むSEの番号

	/* SEの音量を設定 */
//	ChangeVolumeSoundMem(this->OptionList->iGetSeVolume(), this->pSeHandleList[SE_NAME[iSeNo]]);

	/* SEを再生する */
	PlaySoundMem(this->pSeHandleList[SE_NAME[iSeNo]], DX_PLAYTYPE_BACK);
}


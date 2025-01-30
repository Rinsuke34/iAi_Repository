/* 2025.01.30 駒沢風助 ファイル作成 */

#include "DataList_Sound.h"

/* サウンド管理データリストの定義 */

// コンストラクタ
DataList_Sound::DataList_Sound() : DataListBase("DataList_Sound")
{
	/* 初期化 */
	this->iBgmVolume	= 128;		// BGMの音量(0 ～ 255)
	this->iBgmHandle	= 0;		// BGMのハンドル
	this->iSeVolum		= 128;		// SEの音量(0 ～ 255)
}

// デストラクタ
DataList_Sound::~DataList_Sound()
{
	/* 全てのサウンドデータを削除 */
	InitSoundMem();
}

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
		ChangeVolumeSoundMem(this->iBgmVolume, this->iBgmHandle);
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

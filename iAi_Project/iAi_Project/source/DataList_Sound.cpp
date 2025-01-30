/* 2025.01.30 ��򕗏� �t�@�C���쐬 */

#include "DataList_Sound.h"

/* �T�E���h�Ǘ��f�[�^���X�g�̒�` */

// �R���X�g���N�^
DataList_Sound::DataList_Sound() : DataListBase("DataList_Sound")
{
	/* ������ */
	this->iBgmVolume	= 128;		// BGM�̉���(0 �` 255)
	this->iBgmHandle	= 0;		// BGM�̃n���h��
	this->iSeVolum		= 128;		// SE�̉���(0 �` 255)
}

// �f�X�g���N�^
DataList_Sound::~DataList_Sound()
{
	/* �S�ẴT�E���h�f�[�^���폜 */
	InitSoundMem();
}

// BGM��ݒ�
void DataList_Sound::BGM_SetHandle(int iBgmNo)
{
	// ����
	// iBgmNo		<- �ǂݍ���BGM�̔ԍ�

	/* ���ݗ���Ă���BGM���~ */
	BGM_StopSound();

	/* ���݂̃T�E���h�n���h�����폜 */
	BGM_DeleteHandle();

	/* BGM�̔ԍ��ɉ�����BGM��ǂݍ��� */
	{
		/* BGM�ԍ��ɉ����ēǂݍ���BGM����ύX */
		std::string BgmName		= BGM_NAME[iBgmNo];

		std::string FileName	= "resource/SoundData/BGM/" + BgmName + ".ogg";

		/* BGM��ǂݍ��� */
		this->iBgmHandle = LoadSoundMem(FileName.c_str());
	}

	/* BGM�̉��ʂ�ύX */
	BGM_VolumeChange();

	/* BGM���Đ� */
	BGM_PlaySound();
}

// BGM���폜
void DataList_Sound::BGM_DeleteHandle()
{
	/* BGM���ݒ肳��Ă��邩�m�F */
	if (this->iBgmHandle != 0)
	{
		// �ݒ肳��Ă���Ȃ�
		/* BGM���폜���� */
		DeleteSoundMem(this->iBgmHandle);
	}
}

// BGM���Đ�
void DataList_Sound::BGM_PlaySound()
{
	/* BGM���ݒ肳��Ă��邩�m�F */
	if (this->iBgmHandle != 0)
	{
		// �ݒ肳��Ă���Ȃ�
		/* BGM���Đ����� */
		PlaySoundMem(this->iBgmHandle, DX_PLAYTYPE_LOOP);
	}
}

// BGM���ʂ�ύX
void DataList_Sound::BGM_VolumeChange()
{
	/* BGM���ݒ肳��Ă��邩�m�F */
	if (this->iBgmHandle != 0)
	{
		// �ݒ肳��Ă���Ȃ�
		/* BGM�̉��ʂ�ύX���� */
		ChangeVolumeSoundMem(this->iBgmVolume, this->iBgmHandle);
	}
}

// BGM���~
void DataList_Sound::BGM_StopSound()
{
	/* BGM���ݒ肳��Ă��邩�m�F */
	if (this->iBgmHandle != 0)
	{
		// �ݒ肳��Ă���Ȃ�
		/* BGM���~������ */
		StopSoundMem(this->iBgmHandle);
	}
}

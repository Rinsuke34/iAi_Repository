/* 2025.01.30 ��򕗏� �t�@�C���쐬 */

#include "DataList_Sound.h"

/* �T�E���h�Ǘ��f�[�^���X�g�̒�` */

// �R���X�g���N�^
DataList_Sound::DataList_Sound() : DataListBase("DataList_Sound")
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�I�v�V�����ݒ�Ǘ�"���擾 */
//		this->OptionList = dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));
	}

	/* �S�Ă�SE���擾 */
	SE_AllSetHandle();
}

// �f�X�g���N�^
DataList_Sound::~DataList_Sound()
{
	/* �S�ẴT�E���h�f�[�^���폜 */
	InitSoundMem();
}

/* BGM�n */
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
//		ChangeVolumeSoundMem(this->OptionList->iGetBgmVolume(), this->iBgmHandle);
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

/* SE�n */
// �S�ẴT�E���h�n���h�����擾
void DataList_Sound::SE_AllSetHandle()
{
	/* ���\�[�X�t�@�C������S�ẴT�E���h���擾 */
	for (int i = 0; i < SE_MAX; i++)
	{
		/* �t�@�C�������擾 */
		std::string	FileName	= SE_NAME[i];
		
		/* �Ώۂ�SE�t�@�C���̃p�X���擾 */
		std::string FilePath	= "resource/SoundData/SE/" + FileName + ".wav";
		
		/* �T�E���h��ǂݍ��� */
		int iAddSoundHandle		= LoadSoundMem(FilePath.c_str());

		/* �T�E���h�����X�g�ɒǉ� */
		this->pSeHandleList[FileName] = iAddSoundHandle;
	}
}

// �T�E���h���Đ�
void DataList_Sound::SE_PlaySound(int iSeNo)
{
	// ����
	// iSeNo		<- �ǂݍ���SE�̔ԍ�

	/* SE�̉��ʂ�ݒ� */
//	ChangeVolumeSoundMem(this->OptionList->iGetSeVolume(), this->pSeHandleList[SE_NAME[iSeNo]]);

	/* SE���Đ����� */
	PlaySoundMem(this->pSeHandleList[SE_NAME[iSeNo]], DX_PLAYTYPE_BACK);
}


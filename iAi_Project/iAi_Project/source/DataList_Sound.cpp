/* 2025.01.30 ��򕗏� �t�@�C���쐬 */

#include "DataList_Sound.h"

/* �f�[�^���X�g */
#include "DataList_Option.h"

/* �T�E���h�Ǘ��f�[�^���X�g�̒�` */

// �R���X�g���N�^
DataList_Sound::DataList_Sound() : DataListBase("DataList_Sound")
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�I�v�V�����ݒ�Ǘ�"���擾 */
		this->OptionList = dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));
	}

	/* ������ */
	this->apiSpeakerInfo[VOICE_TYPE_PLAYER]	=	nullptr;
	this->apiSpeakerInfo[VOICE_TYPE_DOCTOR]	=	nullptr;

	/* �S�Ă�SE���擾 */
	SE_AllSetHandle();

	/* �S�Ẵ{�C�X���擾 */
	VOICE_AllSetHandle();
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
		ChangeVolumeSoundMem(this->OptionList->iGetBgmVolume(), this->iBgmHandle);
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
	/* ���\�[�X�t�@�C������S�Ă�SE���擾 */
	for (int i = 0; i < SE_MAX; i++)
	{
		/* �t�@�C�������擾 */
		std::string	FileName	= SE_NAME[i];
		
		/* �Ώۂ�SE�t�@�C���̃p�X���擾 */
		std::string FilePath	= "resource/SoundData/SE/" + FileName + ".wav";
		
		/* SE��ǂݍ��� */
		int iAddSoundHandle		= LoadSoundMem(FilePath.c_str());

		/* SE�����X�g�ɒǉ� */
		this->pSeHandleList[FileName] = iAddSoundHandle;
	}
}

// SE���Đ�
void DataList_Sound::SE_PlaySound(int iSeNo)
{
	// ����
	// iSeNo		<- �ǂݍ���SE�̔ԍ�

	/* SE�̉��ʂ�ݒ� */
	ChangeVolumeSoundMem(this->OptionList->iGetSeVolume(), this->pSeHandleList[SE_NAME[iSeNo]]);

	/* SE���Đ����� */
	PlaySoundMem(this->pSeHandleList[SE_NAME[iSeNo]], DX_PLAYTYPE_BACK);
}

// �S�Ẵ{�C�X�n���h�����擾
void DataList_Sound::VOICE_AllSetHandle()
{
	/* ���\�[�X�t�@�C������S�Ẵ{�C�X���擾 */
	for (int i = 0; i < VOICE_MAX; i++)
	{
		/* �t�@�C�������擾 */
		std::string	FileName			= stVoice_Info[i].aVoiceName;

		/* �{�C�X�^�C�v�ɉ������t�H���_�����擾 */
		std::string FileName_VoiceType	= VOICE_TYPE_NAME[stVoice_Info[i].iVoiceType];

		/* �Ώۂ̃{�C�X�t�@�C���̃p�X���擾 */
		std::string FilePath = "resource/SoundData/VOICE/" + FileName_VoiceType+ "/" + FileName + ".opus";

		/* �{�C�X�����X�g�ɒǉ� */
		VOICE_HANDLE_INFO addVoice;
		addVoice.iVoiceHandle	= LoadSoundMem(FilePath.c_str());
		addVoice.iVoiceType		= stVoice_Info[i].iVoiceType;
		addVoice.iVoiceNo		= stVoice_Info[i].iVoiceNo;

		this->VoiceHandleList.push_back(addVoice);
	}
}

// �{�C�X���Đ�
void DataList_Sound::VOICE_PlaySound(int iVoiceNo)
{
	// ����
	// iVoiceNo		<- �ǂݍ��ރ{�C�X�̔ԍ�

	/* �{�C�X����ۑ�����p�̍\���̂��` */
	std::vector<int>	SelectVoice;
	int					iVoiceType = 0;

	/* �Ώۂ̃{�C�X�ԍ��̂��ׂẴ{�C�X���擾 */
	for (int i = 0; i < VOICE_MAX; i++)
	{
		/* �{�C�X�ԍ����擾 */
		if (this->VoiceHandleList[i].iVoiceNo == iVoiceNo)
		{
			/* �{�C�X�̃n���h�����擾 */
			SelectVoice.push_back(this->VoiceHandleList[i].iVoiceHandle);

			/* �{�C�X�̎��(�����ҏ��)���擾 */
			iVoiceType = this->VoiceHandleList[i].iVoiceType;
		}
	}

	/* �{�C�X�̌�����������Ȃ烉���_����1�s�b�N���� */
	int iVoiceHandle = SelectVoice[GetRand(static_cast<int>(SelectVoice.size()) - 1)];

	/* �ݒ肳�ꂽ�{�C�X���o�^����Ă��邩�m�F */
	if (this->apiSpeakerInfo[iVoiceType] != nullptr)
	{
		// �o�^����Ă���ꍇ
		/* �ݒ肳�ꂽ�����҂̃{�C�X���Đ���Ԃł��邩�m�F */
		if (CheckSoundMem(*this->apiSpeakerInfo[iVoiceType]) == 1)
		{
			// �{�C�X���Đ���Ԃł���ꍇ
			/* �{�C�X���~ */
			StopSoundMem(*this->apiSpeakerInfo[iVoiceType]);
		}
	}

	/* �{�C�X�̉��ʂ�ݒ� */
	ChangeVolumeSoundMem(this->OptionList->iGetVoiceVolume(), iVoiceHandle);

	/* �{�C�X���Đ����� */
	PlaySoundMem(iVoiceHandle, DX_PLAYTYPE_BACK);

	/* �����ҏ����X�V */
	this->apiSpeakerInfo[iVoiceType] = &iVoiceHandle;
}

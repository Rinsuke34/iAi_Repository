/* 2025.01.30 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <vector>
#include "AppFrame.h"
#include "SoundDefine.h"

/* �z�Q�Ƒ΍���s��` */
class DataList_Option;

/* �T�E���h�Ǘ��f�[�^���X�g�̐錾 */

// �T�E���h�Ǘ��f�[�^���X�g
class DataList_Sound : public DataListBase
{
	public:
		DataList_Sound();				// �R���X�g���N�^
		virtual ~DataList_Sound();		// �f�X�g���N�^

		/* BGM�֌W */
		void BGM_SetHandle(int iBgmNo);			// BGM��ݒ�
		void BGM_DeleteHandle();				// BGM���폜
		void BGM_PlaySound();					// BGM���Đ�
		void BGM_VolumeChange();				// BGM�����ʕύX
		void BGM_StopSound();					// BGM���~

		/* SE�֌W */
		void SE_AllSetHandle();					// �S�ẴT�E���h�n���h�����擾
		void SE_PlaySound(int iSeNo);			// �T�E���h���Đ�

		/* �{�C�X�֌W */
		//void VOICE_AllSetHandle();				// �S�Ẵ{�C�X�n���h�����擾
		//void VOICE_PlaySound(int iVoiceNo);		// �{�C�X���Đ�

	private:
		/* �f�[�^���X�g */
		DataList_Option* OptionList;				// �I�v�V�����ݒ�Ǘ�

		/* BGM�֌W */
		// ��BGM�͍Đ�����^�C�~���O�œǂݍ��݂��s��
		int iBgmHandle;								// BGM�̃n���h��

		/* SE�֌W */
		std::map<std::string, int>	pSeHandleList;	// �T�E���h�n���h�����X�g

		/* �{�C�X�֌W */
};

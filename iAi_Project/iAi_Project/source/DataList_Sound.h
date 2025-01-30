/* 2025.01.30 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <vector>
#include "AppFrame.h"
#include "SoundDefine.h"

/* �T�E���h�Ǘ��f�[�^���X�g�̐錾 */

// �T�E���h�Ǘ��f�[�^���X�g
class DataList_Sound : public DataListBase
{
	public:
		DataList_Sound();				// �R���X�g���N�^
		virtual ~DataList_Sound();		// �f�X�g���N�^

		/* BGM�n */
		void BGM_SetHandle(int iBgmNo);			// BGM��ݒ�
		void BGM_DeleteHandle();				// BGM���폜
		void BGM_PlaySound();					// BGM���Đ�
		void BGM_VolumeChange();				// BGM�����ʕύX
		void BGM_StopSound();					// BGM���~

		/* SE�n */
		//void SE_AllSetHandle();					// �S�ẴT�E���h�n���h�����擾

	private:
		/* BGM�֌W */
		// ��BGM�͍Đ�����^�C�~���O�œǂݍ��݂��s��
		int iBgmVolume;								// BGM�̉���(0 �` 255)
		int iBgmHandle;								// BGM�̃n���h��

		/* SE�֌W */
		int iSeVolum;								// SE�̉���(0 �` 255)
		std::map<std::string, int>	pSeHandleList;	// �T�E���h�n���h�����X�g
};

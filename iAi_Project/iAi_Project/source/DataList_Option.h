/* 2025.03.05 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "AppFrame.h"
#include <vector>
#include "PublicInclude.h"

/* �I�v�V�����ݒ�Ǘ��N���X�̐錾 */

// �I�v�V�����ݒ�Ǘ��N���X
class DataList_Option : public DataListBase
{
	public:
		DataList_Option();					// �R���X�g���N�^
		virtual ~DataList_Option() {};		// �f�X�g���N�^

		/* �f�[�^�擾 */
		bool	bGetCameraInversion(int iInputType, int iAxis)		{ return this->abCameraInversion[iInputType][iAxis]; }		// �J�������]�ݒ�擾
		float	fGetCameraSensitivity(int iInputType, int iAxis)	{ return this->afCameraSensitivity[iInputType][iAxis]; }	// �J�������x�ݒ�擾

		/* �f�[�^�ݒ� */
		void	SetCameraInversion(int iInputType, int iAxis, bool bCameraInversion)		{ this->abCameraInversion[iInputType][iAxis] = bCameraInversion; }		// �J�������]�ݒ�
		void	SetCameraSensitivity(int iInputType, int iAxis, float fCameraSensitivity)	{ this->afCameraSensitivity[iInputType][iAxis] = fCameraSensitivity; }	// �J�������x�ݒ�

	private:
		/* �Ǘ�����f�[�^ */
		// ���͐ݒ�
		bool	abCameraInversion[INPUT_TYPE_MAX][INPUT_CAMERA_MODE_MAX];		// �J�������]�ݒ�(���̓^�C�v/��)
		float	afCameraSensitivity[INPUT_TYPE_MAX][AXIS_MAX];					// �J�������x�ݒ�(�{��)(���̓^�C�v/��)

		// �T�E���h�ݒ�
		int		iBgmVolume;			// BGM�̉���(0 �` 255)
		int		iSeVolume;			// SE�̉���(0 �` 255)
		int		iVoiceVolume;		// �{�C�X�̉���(0 �` 255)

		// ���̑�
		bool	bTutorialMassage;	// �`���[�g���A�����b�Z�[�W�\��
};

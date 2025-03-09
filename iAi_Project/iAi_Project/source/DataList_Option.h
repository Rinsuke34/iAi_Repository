/* 2025.03.05 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "AppFrame.h"
#include <vector>
#include "PublicInclude.h"
#include "OptionDefine.h"

/* �I�v�V�����ݒ�Ǘ��N���X�̐錾 */

// �I�v�V�����ݒ�Ǘ��N���X
class DataList_Option : public DataListBase
{
	public:
		DataList_Option();					// �R���X�g���N�^
		virtual ~DataList_Option() {};		// �f�X�g���N�^

		/* json�t�@�C���֘A */
		void	LoadOptionData();			// �I�v�V�����f�[�^�ǂݍ���
		void	SaveOptionData();			// �I�v�V�����f�[�^�ۑ�

		/* �f�[�^�擾 */
		bool	bGetCameraInversion(int iInputType, int iAxis)		{ return this->abCameraInversion[iInputType][iAxis]; }		// �J�������]�ݒ�擾
		float	fGetCameraSensitivity(int iInputType, int iAxis)	{ return this->afCameraSensitivity[iInputType][iAxis]; }	// �J�������x�ݒ�擾
		float	fGetEnemyDrawDistance()								{ return this->fEnemyDrawDistance; }						// �G�l�~�[�`�ʋ����擾
		int		iGetBgmVolume()										{ return this->iBgmVolume; }								// BGM�̉��ʎ擾
		int		iGetSeVolume()										{ return this->iSeVolume; }									// SE�̉��ʎ擾
		int		iGetVoiceVolume()									{ return this->iVoiceVolume; }								// �{�C�X�̉��ʎ擾
		bool	bGetTutorialMassage()								{ return this->bTutorialMassage; }							// �`���[�g���A�����b�Z�[�W�\���擾

		/* �f�[�^�ݒ� */
		void	SetCameraInversion(int iInputType, int iAxis, bool bCameraInversion)		{ this->abCameraInversion[iInputType][iAxis]	= bCameraInversion; }		// �J�������]�ݒ�
		void	SetCameraSensitivity(int iInputType, int iAxis, float fCameraSensitivity)	{ this->afCameraSensitivity[iInputType][iAxis]	= fCameraSensitivity; }		// �J�������x�ݒ�
		void	SetEnemyDrawDistance(float fEnemyDrawDistance)								{ this->fEnemyDrawDistance						= fEnemyDrawDistance; }		// �G�l�~�[�`�ʋ����ݒ�
		void	SetBgmVolume(int iBgmVolume)												{ this->iBgmVolume								= iBgmVolume; }				// BGM�̉��ʐݒ�
		void	SetSeVolume(int iSeVolume)													{ this->iSeVolume								= iSeVolume; }				// SE�̉��ʐݒ�
		void	SetVoiceVolume(int iVoiceVolume)											{ this->iVoiceVolume							= iVoiceVolume; }			// �{�C�X�̉��ʐݒ�
		void	SetTutorialMassage(bool bTutorialMassage)									{ this->bTutorialMassage						= bTutorialMassage; }		// �`���[�g���A�����b�Z�[�W�\���ݒ�

		/* �I�v�V�������X�g�̃|�C���^�擾 */
		std::vector<OPTION_LIST>* stGetOptionNameList() { return &this->astOptionNameList; }						// �I�v�V���������X�g�擾

	private:
		/* �Ǘ�����f�[�^ */
		// ���͐ݒ�
		bool	abCameraInversion[INPUT_TYPE_MAX][INPUT_CAMERA_MODE_MAX];		// �J�������]�ݒ�(���̓^�C�v/�J�������)
		float	afCameraSensitivity[INPUT_TYPE_MAX][AXIS_MAX];					// �J�������x�ݒ�(�{��)(���̓^�C�v/��)
		float	fEnemyDrawDistance;
		// �T�E���h�ݒ�
		int		iBgmVolume;			// BGM�̉���(0 �` 255)
		int		iSeVolume;			// SE�̉���(0 �` 255)
		int		iVoiceVolume;		// �{�C�X�̉���(0 �` 255)
		// ���̑�
		bool	bTutorialMassage;	// �`���[�g���A�����b�Z�[�W�\��

		/* Json�t�@�C���ł̃I�v�V�������ƕϐ��̑Ή��\ */
		// �� �I�v�V�������ڂ�ǉ�����ꍇ�͂����ɒǉ�����
		std::vector<OPTION_LIST> astOptionNameList =
		{
			/* �I�v�V������(Json��),							�I�v�V������(���{��),									�Ή������ϐ�(�|�C���^),													�f�[�^�^,			�ŏ��l,							�ő�l,							�ύX�� */
			// �J�����n
			{ OPTION_NAME_CAMERAINVERSION_CONTROLLER_NORMAL,	OPTION_NAME_CAMERAINVERSION_CONTROLLER_NORMAL_JP,		&abCameraInversion[INPUT_TYPE_CONTROLLER][INPUT_CAMERA_MODE_NORMAL],	DATA_TYPE_BOOL,		0.f,							0.f,							0.f								},
			{ OPTION_NAME_CAMERAINVERSION_CONTROLLER_AIM,		OPTION_NAME_CAMERAINVERSION_CONTROLLER_AIM_JP,			&abCameraInversion[INPUT_TYPE_CONTROLLER][INPUT_CAMERA_MODE_AIM],		DATA_TYPE_BOOL,		0.f,							0.f,							0.f								},
			{ OPTION_NAME_CAMERAINVERSION_MOUSE_NORMAL,			OPTION_NAME_CAMERAINVERSION_MOUSE_NORMAL_JP,			&abCameraInversion[INPUT_TYPE_MOUSE][INPUT_CAMERA_MODE_NORMAL],			DATA_TYPE_BOOL,		0.f,							0.f,							0.f								},
			{ OPTION_NAME_CAMERAINVERSION_MOUSE_AIM,			OPTION_NAME_CAMERAINVERSION_MOUSE_AIM_JP,				&abCameraInversion[INPUT_TYPE_MOUSE][INPUT_CAMERA_MODE_AIM],			DATA_TYPE_BOOL,		0.f,							0.f,							0.f								},
			{ OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_X,		OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_X_JP,			&afCameraSensitivity[INPUT_TYPE_CONTROLLER][INPUT_CAMERA_MODE_NORMAL],	DATA_TYPE_FLOAT,	OPTION_CAMERA_SENSITIVITY_MIN,	OPTION_CAMERA_SENSITIVITY_MAX,	OPTION_CAMERA_SENSITIVITY_STEP	},
			{ OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_Y,		OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_Y_JP,			&afCameraSensitivity[INPUT_TYPE_CONTROLLER][INPUT_CAMERA_MODE_AIM],		DATA_TYPE_FLOAT,	OPTION_CAMERA_SENSITIVITY_MIN,	OPTION_CAMERA_SENSITIVITY_MAX,	OPTION_CAMERA_SENSITIVITY_STEP	},
			{ OPTION_NAME_CAMERASENSITIVITY_MOUSE_X,			OPTION_NAME_CAMERASENSITIVITY_MOUSE_X_JP,				&afCameraSensitivity[INPUT_TYPE_MOUSE][INPUT_CAMERA_MODE_NORMAL],		DATA_TYPE_FLOAT,	OPTION_CAMERA_SENSITIVITY_MIN,	OPTION_CAMERA_SENSITIVITY_MAX,	OPTION_CAMERA_SENSITIVITY_STEP	},
			{ OPTION_NAME_CAMERASENSITIVITY_MOUSE_Y,			OPTION_NAME_CAMERASENSITIVITY_MOUSE_Y_JP,				&afCameraSensitivity[INPUT_TYPE_MOUSE][INPUT_CAMERA_MODE_AIM],			DATA_TYPE_FLOAT,	OPTION_CAMERA_SENSITIVITY_MIN,	OPTION_CAMERA_SENSITIVITY_MAX,	OPTION_CAMERA_SENSITIVITY_STEP	},
			{ OPTION_NAME_ENEMY_DRAW_DISTANCE,					OPTION_NAME_ENEMY_DRAW_DISTANCE_JP,						&fEnemyDrawDistance,													DATA_TYPE_FLOAT,	OPTION_ENEMY_DRAW_DISTANCE_MIN,	OPTION_ENEMY_DRAW_DISTANCE_MAX,	OPTION_ENEMY_DRAW_DISTANCE_STEP	},
			// �T�E���h�n
			{ OPTION_NAME_BGMVOLUME,							OPTION_NAME_BGMVOLUME_JP,								&iBgmVolume,															DATA_TYPE_INT,		OPTION_SOUND_VOLUME_MIN,		OPTION_SOUND_VOLUME_MAX,		OPTION_SOUND_VOLUME_STEP		},
			{ OPTION_NAME_SEVOLUME,								OPTION_NAME_SEVOLUME_JP,								&iSeVolume,																DATA_TYPE_INT,		OPTION_SOUND_VOLUME_MIN,		OPTION_SOUND_VOLUME_MAX,		OPTION_SOUND_VOLUME_STEP		},
			{ OPTION_NAME_VOICEVOLUME,							OPTION_NAME_VOICEVOLUME_JP,								&iVoiceVolume,															DATA_TYPE_INT,		OPTION_SOUND_VOLUME_MIN,		OPTION_SOUND_VOLUME_MAX,		OPTION_SOUND_VOLUME_STEP		},
			// ���̑�
			{ OPTION_NAME_TUTORIALMESSAGE,						OPTION_NAME_TUTORIALMESSAGE_JP,							&bTutorialMassage,														DATA_TYPE_BOOL,		0.f,							0.f,							0.f								}
		};
};

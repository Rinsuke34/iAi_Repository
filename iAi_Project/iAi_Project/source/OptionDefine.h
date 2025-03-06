/* 2025.03.06 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <string>

/* �I�v�V�����֘A�̍\���̂�萔�̐錾���s�� */

/* �I�v�V�����֘A�̍ő�A�ŏ��l */
static const float	OPTION_CAMERA_SENSITIVITY_MIN	=	0.1f;	// �J�������x�̍ŏ��l
static const float	OPTION_CAMERA_SENSITIVITY_MAX	=	10.f;	// �J�������x�̍ő�l
static const float	OPTION_CAMERA_SENSITIVITY_STEP	=	0.1f;	// �J�������x�̕ύX��
static const float	OPTION_SOUND_VOLUME_MIN			=	0.f;	// �T�E���h�̉��ʂ̍ŏ��l
static const float	OPTION_SOUND_VOLUME_MAX			=	255.f;	// �T�E���h�̉��ʂ̍ő�l
static const float	OPTION_SOUND_VOLUME_STEP		=	1.f;	// �T�E���h�̉��ʂ̕ύX��

/* �I�v�V������(Json�t�@�C����) */
// �J�����n
const std::string OPTION_NAME_CAMERAINVERSION_CONTROLLER_NORMAL	= "CameraInversion_Controller_Normal";		// �J�������]�ݒ�(�R���g���[���[/�ʏ펞)
const std::string OPTION_NAME_CAMERAINVERSION_CONTROLLER_AIM	= "CameraInversion_Controller_Aim";			// �J�������]�ݒ�(�R���g���[���[/�G�C����)
const std::string OPTION_NAME_CAMERAINVERSION_MOUSE_NORMAL		= "CameraInversion_Mouse_Normal";			// �J�������]�ݒ�(�}�E�X/�ʏ펞)
const std::string OPTION_NAME_CAMERAINVERSION_MOUSE_AIM			= "CameraInversion_Mouse_Aim";				// �J�������]�ݒ�(�}�E�X/�G�C����)
const std::string OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_X	= "CameraSensitivity_Controller_X";			// �J�������x�{��(�R���g���[���[/X��)
const std::string OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_Y	= "CameraSensitivity_Controller_Y";			// �J�������x�{��(�R���g���[���[/Y��)
const std::string OPTION_NAME_CAMERASENSITIVITY_MOUSE_X			= "CameraSensitivity_Mouse_X";				// �J�������x�{��(�}�E�X/X��)
const std::string OPTION_NAME_CAMERASENSITIVITY_MOUSE_Y			= "CameraSensitivity_Mouse_Y";				// �J�������x�{��(�}�E�X/Y��)
// �T�E���h�n
const std::string OPTION_NAME_BGMVOLUME							= "Bgm_Volume";								// BGM�̉���( 0 �` 255 )
const std::string OPTION_NAME_SEVOLUME							= "Se_Volume";								// SE�̉���( 0 �` 255 )
const std::string OPTION_NAME_VOICEVOLUME						= "Voice_Volume";							// �{�C�X�̉���( 0 �` 255 )
// ���̑�
const std::string OPTION_NAME_TUTORIALMESSAGE					= "TutorialMassage";						// �`���[�g���A�����b�Z�[�W�\��

/* �I�v�V������(���{��) */
// �J�����n
const std::string OPTION_NAME_CAMERAINVERSION_CONTROLLER_NORMAL_JP	= "�J�������]�ݒ�(�R���g���[���[/�ʏ펞)";		// �J�������]�ݒ�(�R���g���[���[/�ʏ펞)
const std::string OPTION_NAME_CAMERAINVERSION_CONTROLLER_AIM_JP		= "�J�������]�ݒ�(�R���g���[���[/�G�C����)";	// �J�������]�ݒ�(�R���g���[���[/�G�C����)
const std::string OPTION_NAME_CAMERAINVERSION_MOUSE_NORMAL_JP		= "�J�������]�ݒ�(�}�E�X/�ʏ펞)";				// �J�������]�ݒ�(�}�E�X/�ʏ펞)
const std::string OPTION_NAME_CAMERAINVERSION_MOUSE_AIM_JP			= "�J�������]�ݒ�(�}�E�X/�G�C����)";			// �J�������]�ݒ�(�}�E�X/�G�C����)
const std::string OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_X_JP		= "�J�������x�{��(�R���g���[���[/X��)";			// �J�������x�{��(�R���g���[���[/X��)
const std::string OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_Y_JP		= "�J�������x�{��(�R���g���[���[/Y��)";			// �J�������x�{��(�R���g���[���[/Y��)
const std::string OPTION_NAME_CAMERASENSITIVITY_MOUSE_X_JP			= "�J�������x�{��(�}�E�X/X��)";					// �J�������x�{��(�}�E�X/X��)
const std::string OPTION_NAME_CAMERASENSITIVITY_MOUSE_Y_JP			= "�J�������x�{��(�}�E�X/Y��)";					// �J�������x�{��(�}�E�X/Y��)
// �T�E���h�n
const std::string OPTION_NAME_BGMVOLUME_JP							= "BGM�̉���";									// BGM�̉���( 0 �` 255 )
const std::string OPTION_NAME_SEVOLUME_JP							= "SE�̉���";									// SE�̉���( 0 �` 255 )
const std::string OPTION_NAME_VOICEVOLUME_JP						= "�{�C�X�̉���";								// �{�C�X�̉���( 0 �` 255 )
// ���̑�
const std::string OPTION_NAME_TUTORIALMESSAGE_JP					= "�`���[�g���A�����b�Z�[�W�\��";				// �`���[�g���A�����b�Z�[�W�\��

/* �t�@�C���p�X */
const std::string FILE_PATH_OPTION = "resource/SetupData/OptionData.json";

/* �I�v�V�������X�g */
struct OPTION_LIST
{
	std::string	Name_Json;			// ����(Json�t�@�C����)
	std::string	Name;				// ����(���{��)
	void*		pValue;				// �ϐ�(��std::variant���g�p�o���Ȃ��̂Ŋ댯�������̕��@�Ŋ֐����擾����)
	std::string	Type;				// �f�[�^�^
	float		fMin;				// �ŏ��l(�f�[�^�^�ɉ����ăL���X�g���Ďg�p���� / bool�^�͖��g�p)
	float		fMax;				// �ő�l(�f�[�^�^�ɉ����ăL���X�g���Ďg�p���� / bool�^�͖��g�p)
	float		fStepValue;			// �ύX��(�f�[�^�^�ɉ����ăL���X�g���Ďg�p���� / bool�^�͖��g�p)
};

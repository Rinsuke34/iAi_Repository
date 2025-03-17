/* 2025.01.22 ��򕗏� �t�@�C���쐬 */

#include "DataList_StageStatus.h"

/* �X�e�[�W��ԊǗ��N���X�̒�` */

// �R���X�g���N�^
DataList_StageStatus::DataList_StageStatus() : DataListBase("DataList_StageStatus")
{
	/* ������ */
	{
		this->iGameStatus	= GAMESTATUS_PLAY_GAME;		// �Q�[�����
		this->iNowStageNo	= 0;						// �J�n�X�e�[�W�ԍ�
		this->iEndStageNo	= 0;						// �ŏI�X�e�[�W�ԍ�
		this->bGameSlowFlg	= false;					// �X���[���[�V�����t���O		/*2025.02.05 �e�r�듹 �ϐ��ǉ� */
		this->iSlowCount	= 0;						// �X���[���[�V�����̃J�E���g
		this->bAddUiFlg		= false;					// UI�ǉ��t���O
		this->iStartTime	= 0;						// �J�n���̎���
		this->iClearTime	= 0;						// �N���A���̎���
		this->iJumpStageNo	= 0;						// �W�����v��̃X�e�[�W�ԍ�(�f�o�b�O�p)

		/* �J�����֘A */
		this->iCameraMode						= CAMERA_MODE_NORMAL;						// �J�������[�h
		this->iCameraMode_Old					= CAMERA_MODE_NORMAL;						// �J�������[�h(�ύX�O)
		this->vecCameraUp						= VGet(0, 1, 0);							// �J�����̏����(Y+�����ŌŒ�)
		this->vecCameraPosition					= VGet(0, 0, 0);							// �J�����̍��W(���ݒn�_)
		this->vecCameraPosition_Start			= VGet(0, 0, 0);							// �J�����̍��W(�ύX�O�n�_)
		this->vecCameraPosition_Target			= VGet(0, 0, 0);							// �J�����̍��W(�ύX��n�_)
		this->iCameraPositionLeapCount			= 0;										// �J�������W�̐��`�ۊǗp�J�E���g
		this->vecCameraTarget					= VGet(0, 0, 0);							// �J�����̒����_(���ݒn�_)
		this->vecCameraTarget_Start				= VGet(0, 0, 0);							// �J�����̒����_(�ړ��O�n�_)
		this->vecCameraTarget_Target			= VGet(0, 0, 0);							// �J�����̒����_(�ړ���n�_)
		this->iCameraTargetLeapCount			= 0;										// �J���������_�̐��`��ԗp�J�E���g
		this->fCameraRadius						= INIT_CAMERA_RADIUS;						// �J�����̒��S�_����̋���
		this->fCameraAngleX						= 0;										// �J������X����]��
		this->fCameraAngleY						= 0;										// �J������Y����]��
		this->fCameraRotationalSpeed_Controller	= INIT_CAMERA_ROTATIONAL_SPEED_CONTROLLER;	// �J�����̉�]���x(�R���g���[���[)
		this->fCameraRotationalSpeed_Mouse		= INIT_CAMERA_ROTATIONAL_SPEED_MOUSE;		// �J�����̉�]���x(�}�E�X)
		this->fCameraAngleLimitUp				= INIT_CAMERA_ANGLE_LIMIT_UP;				// �J�����̉�]�p�x����(��)
		this->fCameraAngleLimitDown				= INIT_CAMERA_ANGLE_LIMIT_DOWN;				// �J�����̉�]�p�x����(��)
		this->iCloseUpCount						= 0;										// �N���[�Y�A�b�v�J�E���g
	}
}

// �f�X�g���N�^
DataList_StageStatus::~DataList_StageStatus()
{
	/* ��ʃG�t�F�N�g���X�g�̃N���A */
	for (auto& pScreenEffect : this->pScreenEffectList)
	{
		delete pScreenEffect;
	}
	this->pScreenEffectList.clear();
}


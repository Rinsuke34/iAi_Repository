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

		/* �J�����֘A */
		this->iCameraMode						= CAMERA_MODE_FREE;							// �J�������[�h
		this->iCameraMode_Old					= CAMERA_MODE_FREE;							// �J�������[�h(�ύX�O)
		this->vecCameraUp						= VGet(0, 1, 0);							// �J�����̏����(Y+�����ŌŒ�)
		this->vecCameraPosition					= VGet(0, 0, 0);							// �J�����̍��W(���ݒn�_)
		this->vecCameraPosition_Start			= VGet(0, 0, 0);							// �J�����̍��W(�ύX�O�n�_)
		this->vecCameraPosition_Target			= VGet(0, 0, 0);							// �J�����̍��W(�ύX��n�_)
		this->iCameraPositionLeapCount			= CAMERA_POSITION_LEAP_COUNT_MAX;			// �J�������W�̐��`�ۊǗp�J�E���g
		this->vecCameraTarget					= VGet(0, 0, 0);							// �J�����̒����_
		this->fCameraRadius						= INIT_CAMERA_RADIUS;						// �J�����̒��S�_����̋���
		this->fCameraAngleX						= 0;										// �J������X����]��
		this->fCameraAngleY						= 0;										// �J������Y����]��
		this->fCameraRotationalSpeed_Controller	= INIT_CAMERA_ROTATIONAL_SPEED_CONTROLLER;	// �J�����̉�]���x(�R���g���[���[)
		this->fCameraRotationalSpeed_Mouse		= INIT_CAMERA_ROTATIONAL_SPEED_MOUSE;		// �J�����̉�]���x(�}�E�X)
		this->fCameraAngleLimitUp				= INIT_CAMERA_ANGLE_LIMIT_UP;				// �J�����̉�]�p�x����(��)
		this->fCameraAngleLimitDown				= INIT_CAMERA_ANGLE_LIMIT_DOWN;				// �J�����̉�]�p�x����(��)
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

// �������A�|�C���g������
void DataList_StageStatus::RecoveryPointList_Initialization()
{
	/* �������A�|�C���g���X�g�̃N���A */
	this->vecFallRecoveryPointList.clear();
}

/* 2024.12.26 ��򕗏� �t�@�C���쐬 */
/* 2025.01.10 �e�r�듹 �����������ǉ� */
#include "DataList_PlayerStatus.h"

/* �v���C���[�X�e�[�^�X�Ǘ��N���X�̒�` */

// �R���X�g���N�^
DataList_PlayerStatus::DataList_PlayerStatus() : DataListBase("DataList_PlayerStatus")
{
	/* ������(��) */
	/* �v���C���[��Ԋ֘A */
	this->fPlayerNowMoveSpeed		= 0;		// �v���C���[�̌��݂̈ړ����x
	this->fPlayerAngleX				= 0;		// �v���C���[��X����]��(���W�A��)
	this->fPlayerNowFallSpeed		= 0;		// �v���C���[�̌��݂̗������x

	/* 2025.01.10 �e�r�듹 �����������ǉ� �J�n */
	this->vecPlayerOldVector = { 0,0,0 };
	this->fPlayerOldRadian = 0;
	this->iPlayerNormalDashFlameCount = 0;
	this->bPlayerJumpingFlag = false;
	this->iPlayerJumpCount = 0;
	this->bPlayerDodgingFlag = false;
	this->fPlayerDodgeProgress = 0.0f;
	this->vecPlayerDodgeDirection = VGet(0, 0, 0);
	this->iPlayerDodgeWhileJumpingCount = 0;
	this->bPlayerAfterDodgeFlag = false;
	/* 2025.01.10 �e�r�듹 �����������ǉ� �I�� */

	/* �\�͒l�֘A */
	this->fPlayerMoveAcceleration	= INIT_ATTRIBUTES_MOVE_ACCELERATION;	// �v���C���[�̈ړ������x
	this->fPlayerMaxMoveSpeed		= INIT_ATTRIBUTES_MOVE_SPEED_MAX;		// �v���C���[�̍ő�ړ����x
	this->fPlayerFallAcceleration	= INIT_ATTRIBUTES_FALL_ACCELERATION;	// �v���C���[�̗��������x
	this->fPlayerMaxFallSpeed		= INIT_ATTRIBUTES_FALL_SPEED_MAX;		// �v���C���[�̍ő嗎�����x
	/* 2025.01.10 �e�r�듹 �����������ǉ� �J�n */
	this->fPlayerMoveSpeed = PLAYER_WALK_MOVE_SPEED;
	float fPlayerJumpSpeed = PLAYER_JUMP_SPEED; //�v���C���[�W�����v���x
	float fPlayerDodgeTime = PLAYER_DODGE_TIME; // �v���C���[�������
	float fPlayerDodgeSpeed = PLAYER_DODGE_SPEED; //�v���C���[��𑬓x
	/* 2025.01.10 �e�r�듹 �����������ǉ� �I�� */

	/* �J�����֘A */
	this->iCameraMode						= CAMERA_MODE_FREE;							// �J�������[�h
	this->vecCameraUp						= VGet(0, 1, 0);							// �J�����̏����(Y+�����ŌŒ�)
	this->vecCameraPosition					= VGet(0, 0, 0);							// �J�����̍��W
	this->vecCameraTarget					= VGet(0, 0, 0);							// �J�����̒����_
	this->fCameraRadius						= INIT_CAMERA_RADIUS;						// �J�����̒��S�_����̋���
	this->fCameraAngleX						= 0;										// �J������X����]��
	this->fCameraAngleY						= 0;										// �J������Y����]��
	this->fCameraRotationalSpeed_Controller	= INIT_CAMERA_ROTATIONAL_SPEED_CONTROLLER;	// �J�����̉�]���x(�R���g���[���[)
	this->fCameraRotationalSpeed_Mouse		= INIT_CAMERA_ROTATIONAL_SPEED_MOUSE;		// �J�����̉�]���x(�}�E�X)
	this->fCameraAngleLimitUp				= INIT_CAMERA_ANGLE_LIMIT_UP;				// �J�����̉�]�p�x����(��)
	this->fCameraAngleLimitDown				= INIT_CAMERA_ANGLE_LIMIT_DOWN;				// �J�����̉�]�p�x����(��)


	
}

// �f�X�g���N�^
DataList_PlayerStatus::~DataList_PlayerStatus()
{

}

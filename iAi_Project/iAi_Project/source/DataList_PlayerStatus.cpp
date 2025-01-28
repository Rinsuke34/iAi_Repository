/* 2024.12.26 ��򕗏� �t�@�C���쐬 */
/* 2025.01.10 �e�r�듹 �����������ǉ�  */
/* 2025.01.22 �e�r�듹 �����������ǉ�  */
#include "DataList_PlayerStatus.h"

/* �v���C���[�X�e�[�^�X�Ǘ��N���X�̒�` */

// �R���X�g���N�^
DataList_PlayerStatus::DataList_PlayerStatus() : DataListBase("DataList_PlayerStatus")
{
	/* ������(��) */
	/* �v���C���[��Ԋ֘A */
	this->iPlayerState						= PLAYER_STATUS_FREE;	// �v���C���[�̏��
	this->iPlayerMotion						= PLAYER_MOTION_IDLE;	// �v���C���[�̃��[�V����
	this->bPlayerLandingFlg					= false;				// �v���C���[�����n���Ă��邩
	this->fPlayerNowMoveSpeed				= 0;					// �v���C���[�̌��݂̈ړ����x
	this->fPlayerAngleX						= 0;					// �v���C���[��X����]��(���W�A��)
	this->fPlayerNowFallSpeed				= 0;					// �v���C���[�̌��݂̗������x
	this->iPlayerNowJumpCount				= 0;					// �v���C���[�̃W�����v��(���ݐ�)
	/* 2025.01.10 �e�r�듹 �����������ǉ� �J�n */
	this->iPlayerNormalDashFlameCount		= 0;			//�ʏ�_�b�V�����o�߃t���[�����i�����_�b�V���ւ̈ڍs�Ɏg�p�j
	this->bPlayerJumpingFlag				= false;		//�v���C���[���W�����v�����̃t���O
	this->iPlayerJumpCount					= 0;			//�v���C���[�̌��݂̃W�����v��
	this->fPlayerDodgeProgress				= 0.0f;			//�v���C���[������[�V�����i�s�x
	this->vecPlayerDodgeDirection			= { 0, 0, 0 };	//�v���C���[������
	this->iPlayerDodgeWhileJumpingCount		= 0;			//�v���C���[�W�����v���̉����
	this->fPlayerJumpSpeed					= 0;			//�v���C���[�W�����v���x
	this->iPlayerNowDodgeFlame				= 0;			// �v���C���[�̌��݂̉���t���[����
	this->fPlayerDodgeSpeed					= 0;			//�v���C���[��𑬓x
	this->bPlayerAfterDodgeFlag				= false;		//�v���C���[�̉����t���O
	/* 2025.01.10 �e�r�듹 �����������ǉ� �I�� */
	/* 2025.01.22 �e�r�듹 �����������ǉ� �J�n */
	this->iPlayerNowAttakChargeFlame		= 0;			//���݂̃v���C���[���ߍU���`���[�W�t���[����  2025.01.22 �e�r�듹 �����������ǉ�
	this->vecPlayerChargeAttakTargetMove	= { 0, 0, 0 };	//�v���C���[���ߍU���̖ړI�n
	/* 2025.01.22 �e�r�듹 �����������ǉ� �I�� */
	this->iPlayerChargeAttackCount			= 0;			// �ߐڍU��(��)�̃J�E���g
	this->pLockOnEnemy						= nullptr;		// ���b�N�I���Ώۂ̃G�l�~�[

	/* �\�͒l�֘A */
	this->fPlayerMoveAcceleration	= INIT_ATTRIBUTES_MOVE_ACCELERATION;	// �v���C���[�̈ړ������x
	this->fPlayerMaxMoveSpeed		= INIT_ATTRIBUTES_MOVE_SPEED_MAX;		// �v���C���[�̍ő�ړ����x
	this->fPlayerFallAcceleration	= INIT_ATTRIBUTES_FALL_ACCELERATION;	// �v���C���[�̗��������x
	this->fPlayerMaxFallSpeed		= INIT_ATTRIBUTES_FALL_SPEED_MAX;		// �v���C���[�̍ő嗎�����x
	this->iPlayerMaxJumpCount		= INIT_ATTRIBUTES_JUMP_COUNT_MAX;		// �v���C���[�̃W�����v��(�ő吔)
	this->fPlayerRockOnRadius		= INIT_ATTRIBUTES_ROCK_ON_RADIUS;		// ���b�N�I���͈͂̔��a

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

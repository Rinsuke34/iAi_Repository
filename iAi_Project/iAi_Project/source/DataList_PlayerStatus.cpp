/* 2024.12.26 ��򕗏� �t�@�C���쐬 */

#include "DataList_PlayerStatus.h"

/* �v���C���[�X�e�[�^�X�Ǘ��N���X�̒�` */

// �R���X�g���N�^
DataList_PlayerStatus::DataList_PlayerStatus() : DataListBase("DataList_PlayerStatus")
{
	/* ������ */
	this->vecCameraUp				= VGet(0, 1, 0);				// �J�����̏����(Y+�����ŌŒ�)
	this->vecCameraPosition			= VGet(0, 0, 0);				// �J�����̍��W
	this->vecCameraTarget			= VGet(0, 0, 0);				// �J�����̒����_
	this->fCameraRadius				= INIT_CAMERA_RADIUS;			// �J�����̒��S�_����̋���
	this->fCameraAngleX				= 0;							// �J������X����]��
	this->fCameraAngleY				= 0;							// �J������Y����]��
	this->fCameraRotationalSpeed	= INIT_CAMERA_ROTATIONAL_SPEED;	// �J�����̉�]���x
	this->fCameraAngleLimitUp		= INIT_CAMERA_ANGLE_LIMIT_UP;	// �J�����̉�]�p�x����(��)
	this->fCameraAngleLimitDown		= INIT_CAMERA_ANGLE_LIMIT_DOWN;	// �J�����̉�]�p�x����(��)
}

// �f�X�g���N�^
DataList_PlayerStatus::~DataList_PlayerStatus()
{

}

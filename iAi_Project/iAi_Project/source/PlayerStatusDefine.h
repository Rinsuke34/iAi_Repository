#pragma once
/* 2024.12.26 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <string>

/* �v���C���[��ԊǗ��̍\���̂�萔�̐錾���s�� */

/* �������p�̒萔(��) */
// ����Json����ǂݍ��߂�悤�ɂ���\��
/* �\�͒l�֘A */
static const float	INIT_ATTRIBUTES_MOVE_ACCELERATION	= 0.5f;			// �v���C���[�̈ړ������x
static const float	INIT_ATTRIBUTES_MOVE_SPEED_MAX		= 10.f;			// �v���C���[�̍ő�ړ����x
static const float	INIT_ATTRIBUTES_FALL_ACCELERATION	= 0.5f;			// �v���C���[�̗��������x
static const float	INIT_ATTRIBUTES_FALL_SPEED_MAX		= 10.f;			// �v���C���[�̍ő嗎�����x

/* �J�����֘A */
static const float	INIT_CAMERA_RADIUS						= 300;				// �J�����̒��S�_����̋���
static const float	INIT_CAMERA_ROTATIONAL_SPEED_CONTROLLER	= 0.02f;			// �J�����̉�]���x(�R���g���[���[)
static const float	INIT_CAMERA_ROTATIONAL_SPEED_MOUSE		= 0.005f;			// �J�����̉�]���x(�}�E�X)
static const float	INIT_CAMERA_ANGLE_LIMIT_UP				= DX_PI_F / +2.f;	// �J�����̉�]�p�x����(��)(���W�A��)
static const float	INIT_CAMERA_ANGLE_LIMIT_DOWN			= DX_PI_F / -2.f;	// �J�����̉�]�p�x����(��)(���W�A��)

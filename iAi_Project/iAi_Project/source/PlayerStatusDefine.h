#pragma once
/* 2024.12.26 ��򕗏� �t�@�C���쐬 */
/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ� */

#pragma once
#include <string>

/* �v���C���[��ԊǗ��̍\���̂�萔�̐錾���s�� */

/* �������p�̒萔(��) */
// ����Json����ǂݍ��߂�悤�ɂ���\��
/* �\�͒l�֘A */
static const float	INIT_ATTRIBUTES_MOVE_ACCELERATION	= 0.5f;			// �v���C���[�̈ړ������x

/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ��J�n */
//�ړ��֌W
static const float PLAYER_WALK_MOVE_SPEED = 1.0f; //�v���C���[�̕����̈ړ����x
static const float PLAER_DASH_NOMAL_SPEED = 5.0f; //�v���C���[�̑���i�ʏ�j�̈ړ����x
static const float PLAER_DASH_MAX_SPEED = 10.0f; //�v���C���[�̑���i�ő�j�̈ړ����x
static const int FLAME_COUNT_TO_MAX_SPEED = 180; //�v���C���[�̑���̒ʏ큨�ő�ɂȂ�t���[����
static const int STICK_TILT_PLAER_DASH = 700; //�v���C���[�������ԂɂȂ�X�e�B�b�N�̌X���@�i�͈́F�O�`�P�O�O�O�j

//�W�����v�֌W
static const float PLAYER_JUMP_SPEED = 50.0f; //�v���C���[�̃W�����v�̑��x
static const float GRAVITY_SREED = -9.8f; //�d�͂̑��x�@Y���̉������Ȃ̂Ń}�C�i�X�Ƃ���
static const float GRAVITY_BUFFER = 0.1f; //�L�����N�^�[�ɂ�����d�͒����@�P���傫���Əd���Ȃ�@�P��菬�����ƌy���Ȃ�
static const int PLAYER_JUMPING_IN_AIR_LIMIT = 1;//�v���C���[���󒆃W�����v�ł����
//����֌W
static const float PLAYER_DODGE_SPEED = 50.0f;//�v���C���[�̉�𑬓x
static const float PLAYER_DODGE_TIME = 0.3f; //�v���C���[�̉������

/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ��I�� */

static const float	INIT_ATTRIBUTES_MOVE_SPEED_MAX		= 10.0f;			// �v���C���[�̍ő�ړ����x
static const float	INIT_ATTRIBUTES_FALL_ACCELERATION	= 0.5f;			// �v���C���[�̗��������x
static const float	INIT_ATTRIBUTES_FALL_SPEED_MAX		= 10.0f;			// �v���C���[�̍ő嗎�����x

/* �J�����֘A */
static const float	INIT_CAMERA_RADIUS						= 300;				// �J�����̒��S�_����̋���
static const float	INIT_CAMERA_ROTATIONAL_SPEED_CONTROLLER	= 0.02f;			// �J�����̉�]���x(�R���g���[���[)
static const float	INIT_CAMERA_ROTATIONAL_SPEED_MOUSE		= 0.005f;			// �J�����̉�]���x(�}�E�X)
static const float	INIT_CAMERA_ANGLE_LIMIT_UP				= DX_PI_F / +2.f;	// �J�����̉�]�p�x����(��)(���W�A��)
static const float	INIT_CAMERA_ANGLE_LIMIT_DOWN			= DX_PI_F / -2.f;	// �J�����̉�]�p�x����(��)(���W�A��)


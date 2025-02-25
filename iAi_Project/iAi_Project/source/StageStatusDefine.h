/* 2024.12.26 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <string>

/* �Q�[���̏�ԊǗ��̍\���̂�萔�̐錾���s�� */

/* �Q�[����� */
static const int	GAMESTATUS_PLAY_GAME	= 0;	// �Q�[�����s
static const int	GAMESTATUS_RESULT		= 1;	// ���U���g���s
static const int	GAMESTATUS_EDIT			= 2;	// �G�f�B�b�g���s
static const int	GAMESTATUS_NEXTSTAGE	= 3;	// ���̃X�e�[�W�֑J��
static const int	GAMESTATUS_GAMEOVER		= 4;	// �Q�[���I�[�o�[

/* �J�����֘A */
// ��{���
static const float	INIT_CAMERA_RADIUS						= 400;				// �J�����̒��S�_����̋���
static const float	INIT_CAMERA_ROTATIONAL_SPEED_CONTROLLER	= 0.02f;			// �J�����̉�]���x(�R���g���[���[)
static const float	INIT_CAMERA_ROTATIONAL_SPEED_MOUSE		= 0.005f;			// �J�����̉�]���x(�}�E�X)
static const float	INIT_CAMERA_ANGLE_LIMIT_UP				= DX_PI_F / +2.f;	// �J�����̉�]�p�x����(��)(���W�A��)
static const float	INIT_CAMERA_ANGLE_LIMIT_DOWN			= DX_PI_F / -2.f;	// �J�����̉�]�p�x����(��)(���W�A��)
// �J�������
static const int	CAMERA_MODE_FREE						= 0;				// �t���[���[�h(�ʏ�̎O�l�̎��_)
static const int    CAMERA_MODE_LOCK						= 1;				// �Œ�
static const int	CAMERA_MODE_AIM_MELEE					= 2;				// �\��(�ߐڍU���\��)
static const int	CAMERA_MODE_AIM_KUNAI					= 3;				// �\��(�N�i�C�\��)
static const int	CAMERA_MODE_TITLE						= 4;				// �^�C�g��
// ���`���
static const int	CAMERA_POSITION_LEAP_COUNT_MAX			= 60 * 2;			// �J�������W�̐��`�ۊǗp�J�E���g�̍ő�l

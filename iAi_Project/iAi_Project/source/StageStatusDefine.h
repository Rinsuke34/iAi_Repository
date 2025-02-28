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
// �J�����Œ���W
static const int	CAMERA_FIXED_POSITION_START				= 0;				// �J�����Œ���W(�J�n�n�_)
static const int	CAMERA_FIXED_POSITION_A					= 1;				// �J�����Œ���W(A�n�_)
static const int	CAMERA_FIXED_POSITION_B					= 2;				// �J�����Œ���W(B�n�_)
static const int	CAMERA_FIXED_POSITION_C					= 3;				// �J�����Œ���W(C�n�_)
static const int	CAMERA_FIXED_POSITION_D					= 4;				// �J�����Œ���W(D�n�_)
static const int	CAMERA_FIXED_POSITION_E					= 5;				// �J�����Œ���W(E�n�_)
static const int	CAMERA_FIXED_POSITION_MAX				= 6;				// �J�����Œ���W�̍ő吔

/* �J�����Œ���W��� */
struct CAMERA_FIXED_POSITION_INFO
{
	int		iNo;			// �J�����Œ���W�ԍ�
	bool	bUseFlg;		// �g�p���邩
	VECTOR	vecPosition;	// �J�����Œ���W
	VECTOR	vecTarget;		// �J�����Œ蒍���_
};

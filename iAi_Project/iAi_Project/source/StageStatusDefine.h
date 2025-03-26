/* 2024.12.26 ��򕗏� �t�@�C���쐬 */
/* 2025.03.06 �e�r�듹 �萔�ǉ� */

#pragma once
#include <string>

/* �Q�[���̏�ԊǗ��̍\���̂�萔�̐錾���s�� */

/* �Q�[����� */
static const int	GAMESTATUS_PLAY_GAME			= 0;	// �Q�[�����s
static const int	GAMESTATUS_STAGE_CLEAR_SETUP	= 1;	// �X�e�[�W�N���A����
static const int	GAMESTATUS_STAGE_CLEAR			= 2;	// �X�e�[�W�N���A
static const int	GAMESTATUS_RESULT				= 3;	// ���U���g���s
static const int	GAMESTATUS_EDIT					= 4;	// �G�f�B�b�g���s
static const int	GAMESTATUS_NEXTSTAGE			= 5;	// ���̃X�e�[�W�֑J��
static const int	GAMESTATUS_GAMEOVER				= 6;	// �Q�[���I�[�o�[
static const int	GAMESTATUS_RESET				= 7;	// ���Z�b�g
static const int	GAMESTATUS_START				= 8;	// �Q�[���J�n
static const int	GAMESTATUS_STAGE_JUMP			= 9;	// �X�e�[�W�W�����v

/* �Q�[���N���A���̃J�E���g�ɉ��������� */
static const int	STAGECLEAR_COUNT_START				= 0;	// �X�e�[�W�N���A�����J�n
static const int	STAGECLEAR_COUNT_CAMERA_STOP		= 30;	// �J������~
static const int	STAGECLEAR_COUNT_CAMERA_TRUN_FAST	= 60;	// �J������]
static const int	STAGECLEAR_COUNT_CAMERA_TRUN_LAST	= 90;	// �J������]
static const int	STAGECLEAR_COUNT_START_FADEIN		= 120;	// �t�F�[�h�C���J�n
static const int	STAGECLEAR_COUNT_START_RESULT		= 240;	// ���U���g�J�n

/* �J�����֘A */
// ��{���
static const float	INIT_CAMERA_RADIUS						= 400;				// �J�����̒��S�_����̋���
static const float	INIT_CAMERA_ROTATIONAL_SPEED_CONTROLLER	= 0.02f;			// �J�����̉�]���x(�R���g���[���[)
static const float	INIT_CAMERA_ROTATIONAL_SPEED_MOUSE		= 0.005f;			// �J�����̉�]���x(�}�E�X)
static const float	INIT_CAMERA_ANGLE_LIMIT_UP				= DX_PI_F / +2.f;	// �J�����̉�]�p�x����(��)(���W�A��)
static const float	INIT_CAMERA_ANGLE_LIMIT_DOWN			= DX_PI_F / -2.f;	// �J�����̉�]�p�x����(��)(���W�A��)
static const float	INIT_CAMERA_NEAR						= 100.f;			// �J�����̑O���N���b�v����
static const float	INIT_CAMERA_FAR							= 30000.f;			// �J�����̌���N���b�v����
static const float	INIT_CAMERA_FOG_START					= 20000.f;			// �J�����̃t�H�O�J�n����
static const float	INIT_CAMERA_FOG_END						= 26000.f;			// �J�����̃t�H�O�I������
// �J�������
static const int	CAMERA_MODE_NORMAL						= 0;				// �t���[���[�h(�ʏ�̎O�l�̎��_)
static const int    CAMERA_MODE_LOCK						= 1;				// �Œ�
static const int	CAMERA_MODE_AIM_MELEE					= 2;				// �\��(�ߐڍU���\��)
static const int	CAMERA_MODE_AIM_KUNAI					= 3;				// �\��(�N�i�C�\��)
static const int	CAMERA_MODE_TITLE						= 4;				// �^�C�g��
static const int	CAMERA_MODE_STAGECLEAR					= 5;				// �X�e�[�W�N���A
static const int	CAMERA_MODE_STAGESTART					= 6;				// �X�e�[�W�J�n
static const int	CAMERA_MODE_STAGESTART_CLOSE_UP			= 7;				// �X�e�[�W�J�n(�v���C���[�N���[�Y�A�b�v)
static const int	CAMERA_MODE_FALL						= 8;				// ����
// ���`���
static const int	CAMERA_POSITION_LEAP_COUNT_MAX_NORMAL		= 30 * 1;		// �J�������W�̐��`�ۊǗp�J�E���g�̍ő�l(�t���[)				/* 2025.03.06 �e�r�듹 �萔�ǉ� */
static const int	CAMERA_POSITION_LEAP_CONT_MAX_TITLE			= 60 * 1;		// �J�������W�̐��`�ۊǗp�J�E���g�̍ő�l(�^�C�g��)				/* 2025.03.06 �e�r�듹 �萔�ǉ� */
static const int	CAMERA_POSITION_LEAP_COUNT_MAX_MELEE		= 40 * 1;		// �J�������W�̐��`�ۊǗp�J�E���g�̍ő�l(�ߋ����U��(��))		/* 2025.03.06 �e�r�듹 �萔�ǉ� */
static const int	CAMERA_POSITION_LEAP_COUNT_MAX_PROJECTILE	= 30 * 1;		// �J�������W�̐��`�ۊǗp�J�E���g�̍ő�l(�������U��)			/* 2025.03.06 �e�r�듹 �萔�ǉ� */
static const int	CAMERA_POSITION_LEAP_COUNT_MAX_STAGECLEAR	= 60 * 2;		// �J�������W�̐��`�ۊǗp�J�E���g�̍ő�l(�X�e�[�W�N���A)		/* 2025.03.06 �e�r�듹 �萔�ǉ� */
static const int	CAMERA_POSITION_LEAP_COUNT_MAX_STAGESTART	= 60 * 4;		// �J�������W�̐��`�ۊǗp�J�E���g�̍ő�l(�X�e�[�W�J�n/���)
// �J�����Œ���W
static const int	CAMERA_FIXED_POSITION_START				= 0;				// �J�����Œ���W(�J�n�n�_)
static const int	CAMERA_FIXED_POSITION_A					= 1;				// �J�����Œ���W(A�n�_)
static const int	CAMERA_FIXED_POSITION_B					= 2;				// �J�����Œ���W(B�n�_)
static const int	CAMERA_FIXED_POSITION_C					= 3;				// �J�����Œ���W(C�n�_)
static const int	CAMERA_FIXED_POSITION_D					= 4;				// �J�����Œ���W(D�n�_)
static const int	CAMERA_FIXED_POSITION_E					= 5;				// �J�����Œ���W(E�n�_)
static const int	CAMERA_FIXED_POSITION_MAX				= 6;				// �J�����Œ���W�̍ő吔
// �N���[�Y�A�b�v�֘A�萔
static const int	CAMERA_CLOSEUP_COUNT_MAX				= 180;				// �N���[�Y�A�b�v�J�E���g�̍ő�l
static const int	CAMERA_CLOSEUP_POSITION_HEIGHT			= 100;				// �N���[�Y�A�b�v���̃J�����̍���(�v���C���[�����)

/* �J�����Œ���W��� */
struct CAMERA_FIXED_POSITION_INFO
{
	int		iNo;			// �J�����Œ���W�ԍ�
	bool	bUseFlg;		// �g�p���邩
	VECTOR	vecPosition;	// �J�����Œ���W
	VECTOR	vecTarget;		// �J�����Œ蒍���_
};

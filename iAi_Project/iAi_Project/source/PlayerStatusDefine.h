/* 2024.12.26 ��򕗏� �t�@�C���쐬 */
/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
/* 2025.01.22 �e�r�듹 �U���֘A�̒萔�ǉ� */
/* 2025.02.03 �e�r�듹 �U���֘A�̒萔�ǉ� */

#pragma once
#include <string>

/* �v���C���[��ԊǗ��̍\���̂�萔�̐錾���s�� */

/* �������p�̒萔(��) */
// ����Json����ǂݍ��߂�悤�ɂ���\��
/* �\�͒l�֘A(�ő�l) */
//static const float	INIT_ATTRIBUTES_MOVE_ACCELERATION	= 0.5f;			// �v���C���[�̈ړ������x
static const float	INIT_ATTRIBUTES_MOVE_ACCELERATION = 1.f;			// �v���C���[�̈ړ������x
//static const float	INIT_ATTRIBUTES_MOVE_SPEED_MAX		= 10.f;			// �v���C���[�̍ő�ړ����x
static const float	INIT_ATTRIBUTES_MOVE_SPEED_MAX		= 30.f;			// �v���C���[�̍ő�ړ����x
static const float	INIT_ATTRIBUTES_FALL_ACCELERATION	= 0.5f;			// �v���C���[�̗��������x
static const float	INIT_ATTRIBUTES_FALL_SPEED_MAX		= 10.f;			// �v���C���[�̍ő嗎�����x
//static const int	INIT_ATTRIBUTES_JUMP_COUNT_MAX		= 2;			// �v���C���[�̃W�����v��(�ő吔)
static const int	INIT_ATTRIBUTES_JUMP_COUNT_MAX = 3;			// �v���C���[�̃W�����v��(�ő吔)
static const float	INIT_ATTRIBUTES_ROCK_ON_RADIUS		= 200.f;		// ���b�N�I���͈͂̔��a
static const int	INIT_ATTRIBUTES_HP_MAX				= 10;			// �v���C���[�̍ő�HP
static const int	INIT_ATTRIBUTES_INVINCIBLE_TIME_MAX	= 60;			// �v���C���[�̍ő喳�G����

/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ��J�n */
// �ړ��֌W
//static const float	PLAYER_WALK_MOVE_SPEED				= 1.0f;			// �v���C���[�̕����̈ړ����x
static const float	PLAYER_WALK_MOVE_SPEED = 2.0f;			// �v���C���[�̕����̈ړ����x
//static const float	PLAER_DASH_NOMAL_SPEED				= 5.0f;			// �v���C���[�̑���i�ʏ�j�̈ړ����x
static const float	PLAER_DASH_NOMAL_SPEED = 10.0f;			// �v���C���[�̑���i�ʏ�j�̈ړ����x
//static const float	PLAER_DASH_MAX_SPEED				= 10.0f;		// �v���C���[�̑���i�ő�j�̈ړ����x
static const float	PLAER_DASH_MAX_SPEED = 20.0f;		// �v���C���[�̑���i�ő�j�̈ړ����x
static const int	FLAME_COUNT_TO_MAX_SPEED			= 180;			// �v���C���[�̑���̒ʏ큨�ő�ɂȂ�t���[����
static const float	STICK_TILT_PLAER_DASH				= 0.8f;			// �v���C���[�������ԂɂȂ�X�e�B�b�N�̌X���i�͈́F�ő�1�j

// �W�����v�֌W
static const float	PLAYER_JUMP_SPEED					= 50.0f;		// �v���C���[�̃W�����v�̑��x
static const float	GRAVITY_SREED						= -9.8f;		// �d�͂̑��x�@Y���̉������Ȃ̂Ń}�C�i�X�Ƃ���
static const float	GRAVITY_BUFFER						= 0.1f;			// �L�����N�^�[�ɂ�����d�͒����@�P���傫���Əd���Ȃ�@�P��菬�����ƌy���Ȃ�
static const int	PLAYER_JUMPING_IN_AIR_LIMIT			= 1;			// �v���C���[���󒆃W�����v�ł����
// ����֌W
static const float	PLAYER_DODGE_SPEED					= 100.0f;		// �v���C���[�̉�𑬓x
static const int	PLAYER_DODGE_FLAME					= 10;			// �v���C���[�̉���t���[����
//static const int	PLAYER_DODGE_IN_AIR_LIMIT			= 1;			// �v���C���[���󒆂ŉ���ł����
static const int	PLAYER_DODGE_IN_AIR_LIMIT = 2;			// �v���C���[���󒆂ŉ���ł����
/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ��I�� */


// �U���֌W
static const int	PLAYER_CHARGE_FINISH_FLAME			= 180;			// �ߐڍU����(��)�̗��ߊ����t���[����		/* 2025.01.29 �e�r�듹 �U���֘A�̒萔�ǉ� */
static const int	PLAYER_SEARCH_RANGE_AFTER_MELEE		= 2000;			// �ߐڍU����(��)��̍��G�͈�			/* 2025.02.03 �e�r�듹 �U���֘A�̒萔�ǉ� */


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
static const int	CAMERA_MODE_AIM							= 2;				// �\��(�Y�[��)
// ���`���
static const int	CAMERA_POSITION_LEAP_COUNT_MAX			= 60 * 2;		// �J�������W�̐��`�ۊǗp�J�E���g�̍ő�l

/* �v���C���[��� */
// ����Ԃɉ����ĉ\�ȍs�����ς��
static const int	PLAYER_STATUS_EVENT					= 0;	// �C�x���g���(����s��)
static const int	PLAYER_STATUS_FREE					= 1;	// ���R���
static const int	PLAYER_STATUS_DODGING				= 2;	// �����Ԓ�
static const int	PLAYER_STATUS_MELEE_POSTURE			= 3;	// �ߐڍU���\����
static const int	PLAYER_STATUS_MELEE_WEEK			= 4;	// �ߐڍU����(��)
static const int	PLAYER_STATUS_MELEE_STRONG			= 5;	// �ߐڍU����(��)
static const int	PLAYER_STATUS_PROJECTILE_POSTURE	= 6;	// �������U���\����
static const int	PLAYER_STATUS_PROJECTILE			= 7;	// �������U����

/* �v���C���[���[�V���� */
static const int	PLAYER_MOTION_IDLE					= 0;	// �ҋ@
static const int	PLAYER_MOTION_WALK					= 1;	// ���s
static const int	PLAYER_MOTION_RUN_LOW				= 2;	// ���s(�ᑬ)
static const int	PLAYER_MOTION_RUN_HIGH				= 3;	// ���s(����)
static const int	PLAYER_MOTION_DRAW_SWORD_CHARGE		= 4;	// ����(����)
static const int	PLAYER_MOTION_DRAW_SWORD_WEAK		= 5;	// ����(��)
static const int	PLAYER_MOTION_DRAW_SWORD_STRONG		= 6;	// ����(��)
static const int	PLAYER_MOTION_DRAW_SWORD_END		= 7;	// ����(��)(�I��)
static const int	PLAYER_MOTION_THROW_KUNAI_AIM		= 8;	// �N�i�C(�\��)
static const int	PLAYER_MOTION_THROW_KUNAI_THROW		= 9;	// �N�i�C(����)
static const int	PLAYER_MOTION_DODGE					= 10;	// ���
static const int	PLAYER_MOTION_JUMP_UP				= 11;	// �W�����v(�㏸)
static const int	PLAYER_MOTION_JUMP_DOWN				= 12;	// �W�����v(���~)

/* �v���C���[�����p�萔 */
static const float	PLAYER_HEIGHT						= 160.f;	// ����(�����蔻��)
static const float	PLAYER_WIDE							= 15.f;		// ��(�����蔻��)
static const float	PLAYER_CLIMBED_HEIGHT				= 35.f;		// �����œo��鍂��
//static const int	PLAYER_CHARGE_TO_STRONG_TIME		= 5;		// �ߐڍU�������U���ɐ؂�ւ��܂ł̃t���[����
static const int	PLAYER_CHARGE_TO_STRONG_TIME = 30;		// �ߐڍU�������U���ɐ؂�ւ��܂ł̃t���[����
static const int	PLAYER_MOVE_COLLISION_UP			= 0;		// �v���C���[�̈ړ��p�R���W�����㑤
static const int	PLAYER_MOVE_COLLISION_DOWN			= 1;		// �v���C���[�̈ړ��p�R���W��������
static const int	PLAYER_MOVE_COLLISION_MAX			= 2;		// �v���C���[�̈ړ��p�R���W������
static const int	PLAYER_MELEE_STRONG_MOVESPEED		= 100;		// �ߐڍU��(��)�̈ړ����x
static const int	PLAYER_MELEE_CHARGE_MAX				= 180;		// �ߐڍU���̍ő嗭�ߎ���

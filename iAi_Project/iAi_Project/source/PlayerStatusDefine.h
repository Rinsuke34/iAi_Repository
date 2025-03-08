/* 2024.12.26 ��򕗏� �t�@�C���쐬 */
/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
/* 2025.01.22 �e�r�듹 �U���֘A�̒萔�ǉ� */
/* 2025.02.03 �e�r�듹 �U���֘A�̒萔�ǉ� */
/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̒萔�C�� */
/* 2025.02.10 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
/* 2025.02.22 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
/* 2025.02.26 �e�r�듹 �N�[���^�C���֘A�̒萔�ǉ� */
/* 2025.02.26 �e�r�듹 �U���֘A�̒萔�ǉ� */

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
static const int	INIT_ATTRIBUTES_COMBO_DURATION		= 60 * 3 * 2;		// �R���{�̎�������


// �ړ��֌W
static const float	PLAER_DASH_SPEED					= 20.0f;				// �v���C���[�̑���i�ʏ�j�̈ړ����x							/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
static const float	PLAYER_TURN_SPEED					= 0.2f;					// �v���C���[�̕����]���̑��x�i�͈́F0.0?1.0�j				/* 2025.02.10 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
static const float	PLAYER_TURN_LIMIT					= DX_PI_F * 2.0f;		// �v���C���[�̉�]�p�x����(���W�A��)							/* 2025.02.10 �e�r�듹 �ړ��֘A�̒萔�ǉ� */	/* 2025.02.13 �e�r�듹 �萔�C�� */
static const float	PLAYER_WALL_KICK_MOVE_FLAME			= 30.0f;				// �v���C���[�̕ǃL�b�N�̈ړ��t���[����							/* 2025.02.22 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
static const float	PLAYER_WALL_KICK_HORIZONTAL_SPEED	= 80.0f;				// �v���C���[�̕ǃL�b�N�̑��x(��������)							/* 2025.02.22 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
static const float	PLAYER_WALL_KICK_VERTICAL_SPEED		= -15.0f;				// �v���C���[�̕ǃL�b�N�̑��x(��������)							/* 2025.02.22 �e�r�듹 �ړ��֘A�̒萔�ǉ� */

// ����֌W
static const float	PLAYER_DODGE_SPEED					= 100.0f;				// �v���C���[�̉�𑬓x											/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
static const int	PLAYER_DODGE_IN_AIR_LIMIT			= 2;					// �v���C���[���󒆂ŉ���ł����								/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
static const int	PLAYER_DODGE_FLAME					= 30;					// �v���C���[�̉���̃t���[����									/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
static const int	PLAYER_DODGE_COOLTIME				= 30;					// �v���C���[�̉���̃N�[���^�C��								/* 2025.02.26 �e�r�듹 �N�[���^�C���֘A�̒萔�ǉ� */


// �U���֌W
static const int	PLAYER_CHARGE_FINISH_FLAME			= 180;			// �ߐڍU����(��)�̗��ߊ����t���[����		/* 2025.01.29 �e�r�듹 �U���֘A�̒萔�ǉ� */
static const int	PLAYER_SEARCH_RANGE_AFTER_MELEE		= 2000;			// �ߐڍU����(��)��̍��G�͈�			/* 2025.02.03 �e�r�듹 �U���֘A�̒萔�ǉ� */
static const int	PLAYER_STRONG_MELEE_AIR_MAX			= 1;			// �󒆂ł̋ߐڍU��(��)�̍ő��(���G���U�����Ă��Ȃ��ꍇ)			/* 2025.02.26 �e�r�듹 �U���֘A�̒萔�ǉ� */
static const int	PLAYER_MELEE_WEAK_COLLTIME			= 60;			// �ߐڍU��(��)�̃N�[���^�C��										/* 2025.02.26 �e�r�듹 �N�[���^�C���֘A�̒萔�ǉ� */
static const int	PLAYER_PROJECTILE_COLLTIME			= 60;			// �������U���̃N�[���^�C��											/* 2025.02.26 �e�r�듹 �N�[���^�C���֘A�̒萔�ǉ� */

/* �v���C���[�ړ���� */
// ����Ԃɉ����ĉ\�ȍs�����ς��
static const int	PLAYER_MOVESTATUS_EVENT					= 0;	// �C�x���g���(����s��)			/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̒萔�C�� */
static const int	PLAYER_MOVESTATUS_FREE					= 1;	// ���R���							/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̒萔�C�� */
static const int	PLAYER_MOVESTATUS_DODGING				= 2;	// �����Ԓ�						/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̒萔�C�� */
static const int	PLYAER_MOVESTATUS_DEAD					= 3;	// ���S���(����s��)

/* �v���C���[�U����� */
// ����Ԃɉ����ĉ\�ȍs�����ς��
static const int	PLAYER_ATTACKSTATUS_EVENT				= 0;	// �C�x���g���(����s��)			/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̒萔�C�� */
static const int	PLAYER_ATTACKSTATUS_FREE				= 1;	// ���R���							/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̒萔�C�� */
static const int	PLAYER_ATTACKSTATUS_MELEE_POSTURE		= 2;	// �ߐڍU���\����					/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̒萔�C�� */
static const int	PLAYER_ATTACKSTATUS_MELEE_WEEK			= 3;	// �ߐڍU����(��)					/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̒萔�C�� */
static const int	PLAYER_ATTACKSTATUS_MELEE_STRONG		= 4;	// �ߐڍU����(��)					/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̒萔�C�� */
static const int	PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE	= 5;	// �������U���\����					/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̒萔�C�� */
static const int	PLAYER_ATTACKSTATUS_PROJECTILE			= 6;	// �������U����						/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̒萔�C�� */
static const int	PLAYER_ATTACKSTATUS_DEAD				= 7;	// ���S���(����s��)

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

/* 2024.12.26 ��򕗏� �t�@�C���쐬 */
/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
/* 2025.01.22 �e�r�듹 �U���֘A�̒萔�ǉ� */
/* 2025.02.03 �e�r�듹 �U���֘A�̒萔�ǉ� */
/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̒萔�C�� */
/* 2025.02.10 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
/* 2025.02.22 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
/* 2025.02.26 �e�r�듹 �N�[���^�C���֘A�̒萔�ǉ� */
/* 2025.02.26 �e�r�듹 �U���֘A�̒萔�ǉ� */
/* 2025.03.11 �e�r�듹 ���[�V�����֘A�̒萔�ǉ� */
/* 2025.03.12 �e�r�듹 �X���[���[�V�����֘A�̒萔�ǉ� */

#pragma once
#include <string>

/* �v���C���[��ԊǗ��̍\���̂�萔�̐錾���s�� */

/* �\�͒l����(json) */
const std::string	BASE_STATUS_NAME_MOVE_ACCELERATION			= "MoveAcceleration";		// �v���C���[�̈ړ������x
const std::string	BASE_STATUS_NAME_MOVE_SPEED_MAX				= "MoveSpeed_Max";			// �v���C���[�̍ő�ړ����x
const std::string	BASE_STATUS_NAME_FALL_ACCELERATION			= "FallAcceleration";		// �v���C���[�̗��������x
const std::string	BASE_STATUS_NAME_FALL_SPEED_MAX				= "FallSpeed_Max";			// �v���C���[�̍ő嗎�����x
const std::string	BASE_STATUS_NAME_JUMP_COUNT_MAX				= "JumpCount_Max";			// �v���C���[�̃W�����v��(�ő吔)
const std::string	BASE_STATUS_NAME_ROCK_ON_RADIUS				= "RockOnRadius";			// ���b�N�I���͈͂̔��a
const std::string	BASE_STATUS_NAME_HP_MAX						= "Hp_Max";					// �v���C���[�̍ő�HP
const std::string	BASE_STATUS_NAME_INVINCIBLE_TIME_MAX		= "InvincibleTime_Max";		// �v���C���[�̍ő喳�G����
const std::string	BASE_STATUS_NAME_MELEE_STRONG_AIR_COUNT_MAX	= "MeleeStrongAirMaxCount";	// �v���C���[�̋󒆂ł̋ߋ����U��(��)��(���G���U�����Ă��Ȃ��ꍇ�̍ő吔)

/* �t�@�C���p�X */
const std::string FILE_PATH_STATUS = "resource/SetupData/PlayerStatusData.json";

// �ړ��֌W
static const float	PLAER_DASH_SPEED					= 20.0f;				// �v���C���[�̑���i�ʏ�j�̈ړ����x							/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
static const float	PLAYER_TURN_SPEED					= 0.2f;					// �v���C���[�̕����]���̑��x�i�͈́F0.0?1.0�j				/* 2025.02.10 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
static const float	PLAYER_TURN_LIMIT					= DX_PI_F * 2.0f;		// �v���C���[�̉�]�p�x����(���W�A��)							/* 2025.02.10 �e�r�듹 �ړ��֘A�̒萔�ǉ� */	/* 2025.02.13 �e�r�듹 �萔�C�� */
static const float	PLAYER_WALL_KICK_MOVE_FLAME			= 30.0f;				// �v���C���[�̕ǃL�b�N�̈ړ��t���[����							/* 2025.02.22 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
static const float	PLAYER_WALL_KICK_HORIZONTAL_SPEED	= 80.0f;				// �v���C���[�̕ǃL�b�N�̑��x(��������)							/* 2025.02.22 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
static const float	PLAYER_WALL_KICK_VERTICAL_SPEED		= -30.0f;				// �v���C���[�̕ǃL�b�N�̑��x(��������)							/* 2025.02.22 �e�r�듹 �ړ��֘A�̒萔�ǉ� */

// ����֌W
static const float	PLAYER_DODGE_SPEED					= 100.0f;				// �v���C���[�̉�𑬓x											/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
static const int	PLAYER_DODGE_IN_AIR_LIMIT			= 2;					// �v���C���[���󒆂ŉ���ł����								/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
static const int	PLAYER_DODGE_FLAME					= 30;					// �v���C���[�̉���̃t���[����									/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ� */
static const int	PLAYER_DODGE_COOLTIME				= 30;					// �v���C���[�̉���̃N�[���^�C��								/* 2025.02.26 �e�r�듹 �N�[���^�C���֘A�̒萔�ǉ� */

// �U���֌W
static const int	PLAYER_CHARGE_FINISH_FLAME			= 180;			// �ߐڍU����(��)�̗��ߊ����t���[����		/* 2025.01.29 �e�r�듹 �U���֘A�̒萔�ǉ� */
static const int	PLAYER_SEARCH_RANGE_AFTER_MELEE		= 2000;			// �ߐڍU����(��)��̍��G�͈�				/* 2025.02.03 �e�r�듹 �U���֘A�̒萔�ǉ� */
static const int	PLAYER_MELEE_WEAK_COLLTIME			= 60;			// �ߐڍU��(��)�̃N�[���^�C��										/* 2025.02.26 �e�r�듹 �N�[���^�C���֘A�̒萔�ǉ� */
static const int	PLAYER_PROJECTILE_COLLTIME			= 60;			// �������U���̃N�[���^�C��											/* 2025.02.26 �e�r�듹 �N�[���^�C���֘A�̒萔�ǉ� */
static const int	INIT_ATTRIBUTES_COMBO_DURATION		= 60 * 3 * 2;	// �R���{�̎�������

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
static const float	PLAYER_HEIGHT							= 160.f;	// ����(�����蔻��)
static const float	PLAYER_WIDE								= 15.f;		// ��(�����蔻��)
static const float	PLAYER_CLIMBED_HEIGHT					= 10.f;		// �����œo��鍂��
static const int	PLAYER_CHARGE_TO_STRONG_TIME			= 30;		// �ߐڍU�������U���ɐ؂�ւ��܂ł̃t���[����
static const int	PLAYER_MOVE_COLLISION_UP				= 0;		// �v���C���[�̈ړ��p�R���W�����㑤
static const int	PLAYER_MOVE_COLLISION_DOWN				= 1;		// �v���C���[�̈ړ��p�R���W��������
static const int	PLAYER_MOVE_COLLISION_MAX				= 2;		// �v���C���[�̈ړ��p�R���W������
static const int	PLAYER_MELEE_STRONG_MOVESPEED			= 100;		// �ߐڍU��(��)�̈ړ����x
static const int	PLAYER_MELEE_CHARGE_MAX					= 180;		// �ߐڍU���̍ő嗭�ߎ���
static const int	PLAYER_JUNP_DOWN_MOTION_SWITCH_FRAME	= 10;		// �������W�����v���~���[�V�����ɐ؂�ւ���ۂ̗P�\�t���[��(�Ӑ}���Ȃ����[�V�����؂�ւ���h�~���邽�߂Ɏg�p)		/* 2025.03.11 �e�r�듹 ���[�V�����֘A�̒萔�ǉ� */
static const int	PLAYER_SLOWMOTION_COUNT_MAX				= 120;		// �X���[���[�V�����̍ő�t���[����																					/* 2025.03.12 �e�r�듹 �X���[���[�V�����֘A�̒萔�ǉ� */

/* �v���C���[�\�͒l���X�g */
struct PLAYER_STATUS_LIST
{
	std::string	Name;		// �\�͒l����(Json�t�@�C��)
	void*		pValue;		// �ϐ�(��std::variant���g�p�o���Ȃ��̂Ŋ댯�������̕��@�Ŋ֐����擾����)
	std::string	Type;		// �f�[�^�^
};

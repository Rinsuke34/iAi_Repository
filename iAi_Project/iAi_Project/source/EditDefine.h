/* 2025.02.11 ��򕗏� �t�@�C���쐬 */

#pragma once

/* �G�f�B�b�g�֘A�̍\���̂�萔�̐錾���s�� */

/* �G�f�B�b�g�� */
static const int	EDIT_MAX			= 3;	// �����\�G�f�B�b�g��

/* �G�f�B�b�g�̎�� */
static const int	EDIT_TYPE_NORMAL	= 0;	// �ʏ�
static const int	EDIT_TYPE_SPECIAL	= 1;	// ����
static const int	EDIT_TYPE_CURSE		= 2;	// ��

/* �G�f�B�b�g�̃����N */
static const int	EDIT_RANK_CUPPER	= 0;	// ��
static const int	EDIT_RANK_SILVER	= 1;	// ��
static const int	EDIT_RANK_GOLD		= 2;	// ��

/* �G�f�B�b�g���� */
// �ʏ�
static const int	EDIT_EFFECT_NORMAL_MOVE_SPEED_UP				= 0;	// �ړ����x�A�b�v
static const int	EDIT_EFFECT_NORMAL_GET_BLOOD_UP					= 1;	// �u���b�h�擾�ʃA�b�v
static const int	EDIT_EFFECT_NORMAL_COMBO_DURATION_UP			= 2;	// �R���{�p�����ԃA�b�v
static const int	EDIT_EFFECT_NORMAL_MELEE_CHARGE_REDUCTION		= 3;	// �ߐڍU�����ߎ��Ԍ���
static const int	EDIT_EFFECT_NORMAL_JUMP_COUNT_UP				= 4;	// �W�����v�񐔃A�b�v
static const int	EDIT_EFFECT_NORMAL_AIR_MELEE_COUNT_UP			= 5;	// �󒆋����U���񐔃A�b�v
static const int	EDIT_EFFECT_NORMAL_GET_KUNAI_UP					= 6;	// �N�i�C�擾�ʃA�b�v
static const int	EDIT_EFFECT_NORMAL_BARIER_COUNT_UP				= 7;	// �o���A�񐔃A�b�v
// ����
static const int	EDIT_EFFECT_SPECIAL_GLIDING						= 8;	// ����A�N�V�����ǉ�
static const int	EDIT_EFFECT_SPECIAL_COUNTER						= 9;	// �J�E���^�[�A�N�V�����ǉ�
// ��
static const int	EDIT_EFFECT_CURCE_LIMIT_DASH_DODGE				= 10;	// �_�b�V���A��𐧌�
static const int	EDIT_EFFECT_CURCE_LIMIT_HP_ONE					= 11;	// HP1����
static const int	EDIT_EFFECT_CURCE_LIMIT_MELEE_CHARGE_CHANCEL	= 12;	// �����L�����Z������
// ���̑�
static const int	EDIT_EFFECT_MAX									= 13;	// �G�f�B�b�g���ʂ̍ő吔
static const int	EDIT_EFFECT_NONE								= -1;	// �Ȃ�

/* �A�b�v�O���[�h�t���O */
static const bool	EDIT_UPGRADE_FLAG_NONE	= false;	// �A�b�v�O���[�h�Ȃ�
static const bool	EDIT_UPGRADE_FLAG_TRUE	= true;		// �A�b�v�O���[�h����

/* �G�f�B�b�g�p�̍\���� */
struct EDIT_INFORMATION
{
	int			iEditType;		// �G�f�B�b�g�̎��
	int			iEditMinRank;	// �G�f�B�b�g�̍Œ჉���N
	int			iEditMaxRank;	// �G�f�B�b�g�̍ō������N
	int			iEditEffect;	// �G�f�B�b�g�̌���
	bool		bEditUpgrade;	// �A�b�v�O���[�h�t���O
	std::string	strEditName;	// �G�f�B�b�g��
};

/* �G�f�B�b�g�ꗗ */
static const std::array<EDIT_INFORMATION, EDIT_EFFECT_MAX> EDIT_LIST =
{ {
		// �G�f�B�b�g�̎��,	�G�f�B�b�g�̍Œ჉���N,		�G�f�B�b�g�̍ō������N,		�G�f�B�b�g�̌���,								�A�b�v�O���[�h�t���O,		�G�f�B�b�g��
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_MOVE_SPEED_UP,				EDIT_UPGRADE_FLAG_TRUE,		"�ړ����x�A�b�v"			},
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_GET_BLOOD_UP,				EDIT_UPGRADE_FLAG_TRUE,		"�u���b�h�擾�ʃA�b�v"		},
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_COMBO_DURATION_UP,			EDIT_UPGRADE_FLAG_TRUE,		"�R���{�p�����ԃA�b�v"		},
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_MELEE_CHARGE_REDUCTION,		EDIT_UPGRADE_FLAG_TRUE,		"�ߐڍU�����ߎ��Ԍ���"		},
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_JUMP_COUNT_UP,				EDIT_UPGRADE_FLAG_TRUE,		"�W�����v�񐔃A�b�v"		},
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_AIR_MELEE_COUNT_UP,			EDIT_UPGRADE_FLAG_TRUE,		"�󒆋����U���񐔃A�b�v"	},
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_GET_KUNAI_UP,				EDIT_UPGRADE_FLAG_TRUE,		"�N�i�C�擾�ʃA�b�v"		},
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_BARIER_COUNT_UP,				EDIT_UPGRADE_FLAG_TRUE,		"�o���A�񐔃A�b�v"			},
		{ EDIT_TYPE_SPECIAL,	EDIT_RANK_GOLD,				EDIT_RANK_GOLD,				EDIT_EFFECT_SPECIAL_GLIDING,					EDIT_UPGRADE_FLAG_NONE,		"����A�N�V�����ǉ�"		},
		{ EDIT_TYPE_SPECIAL,	EDIT_RANK_GOLD,				EDIT_RANK_GOLD,				EDIT_EFFECT_SPECIAL_COUNTER,					EDIT_UPGRADE_FLAG_NONE,		"�J�E���^�[�A�N�V�����ǉ�"	},
		{ EDIT_TYPE_CURSE,		EDIT_RANK_GOLD,				EDIT_RANK_GOLD,				EDIT_EFFECT_CURCE_LIMIT_DASH_DODGE,				EDIT_UPGRADE_FLAG_NONE,		"�_�b�V���A��𐧌�"		},
		{ EDIT_TYPE_CURSE,		EDIT_RANK_GOLD,				EDIT_RANK_GOLD,				EDIT_EFFECT_CURCE_LIMIT_HP_ONE,					EDIT_UPGRADE_FLAG_NONE,		"HP1����"					},
		{ EDIT_TYPE_CURSE,		EDIT_RANK_GOLD,				EDIT_RANK_GOLD,				EDIT_EFFECT_CURCE_LIMIT_MELEE_CHARGE_CHANCEL,	EDIT_UPGRADE_FLAG_NONE,		"�����L�����Z������"		}
} };


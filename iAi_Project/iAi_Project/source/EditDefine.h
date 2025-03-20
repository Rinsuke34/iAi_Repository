/* 2025.02.11 ��򕗏� �t�@�C���쐬 */

#pragma once

/* �G�f�B�b�g�֘A�̍\���̂�萔�̐錾���s�� */

/* �G�f�B�b�g�� */
static const int	EDIT_MAX			= 5;	// �����\�G�f�B�b�g��
static const int	EDIT_UPGRADE_MAX	= 5;	// �G�f�B�b�g�̋������ڐ�

/* �G�f�B�b�g�̎�� */
static const int	EDIT_TYPE_NORMAL	= 0;	// �ʏ�
static const int	EDIT_TYPE_SPECIAL	= 1;	// ����
static const int	EDIT_TYPE_CURSE		= 2;	// ��

/* �G�f�B�b�g�̃����N(�t���[��) */
static const int	EDIT_RANK_NONE		= 0;	// �����N�Ȃ�(�G�f�B�b�g����)
static const int	EDIT_RANK_CUPPER	= 1;	// ��
static const int	EDIT_RANK_SILVER	= 2;	// ��
static const int	EDIT_RANK_GOLD		= 3;	// ��
static const int	EDIT_RANK_MAX		= 4;	// �����N�̍ő吔

/* �G�f�B�b�g���� */
static const int	EDIT_EFFECT_NONE								= 0;	// �Ȃ�
// �ʏ�
static const int	EDIT_EFFECT_NORMAL_MOVE_SPEED_UP				= 1;	// �ړ����x�A�b�v
static const int	EDIT_EFFECT_NORMAL_GET_BLOOD_UP					= 2;	// �u���b�h�擾�ʃA�b�v
static const int	EDIT_EFFECT_NORMAL_COMBO_DURATION_UP			= 3;	// �R���{�p�����ԃA�b�v
static const int	EDIT_EFFECT_NORMAL_MELEE_CHARGE_REDUCTION		= 4;	// �ߐڍU�����ߎ��Ԍ���
static const int	EDIT_EFFECT_NORMAL_JUMP_COUNT_UP				= 5;	// �W�����v�񐔃A�b�v
static const int	EDIT_EFFECT_NORMAL_AIR_MELEE_COUNT_UP			= 6;	// �󒆋����U���񐔃A�b�v
static const int	EDIT_EFFECT_NORMAL_KUNAI_KEEP					= 7;	// �N�i�C����m������
static const int	EDIT_EFFECT_NORMAL_BARIER_COUNT_UP				= 8;	// �o���A�񐔃A�b�v
// ����
static const int	EDIT_EFFECT_SPECIAL_COUNTER						= 9;	// �J�E���^�[�A�N�V�����ǉ�
static const int	EDIT_EFFECT_KUNAI_EXPLOSION						= 11;	// �N�i�C����
// ��
static const int	EDIT_EFFECT_CURCE_LIMIT_HP_ONE					= 10;	// HP1����
// ���̑�
static const int	EDIT_EFFECT_MAX									= 12;	// �G�f�B�b�g���ʂ̍ő吔

/* �G�f�B�b�g���p�̍\���� */
struct EDIT_DATA
{
	int			iEditRank;				// �G�f�B�b�g�̃����N
	int			iEditEffect;			// �G�f�B�b�g�̌���
	int			iEditCost;				// �G�f�B�b�g�̉��i(�V�K�A�z�[���h���̃G�f�B�b�g�Ŏg�p)
	std::string	aText;					// ������
};

/* ���̊Ǘ��p�\���� */
struct EDIT_NAME
{
	std::string	strName;		// ����(���{��)
	std::string strEngName;		// ����(�p��)
	std::string	strGrName;		// �摜��
};

/* �G�f�B�b�g�����N(�t���[��)���� */
static const std::array<EDIT_NAME, EDIT_RANK_MAX> EDIT_RANK_NAME =
{ {
	// ����(���{��),	����(�p��),	�摜��
	{ "�Ȃ�",			"None",		"Edit/UI_NowEditFrame_None_256" },
	{ "��",				"Cupper",	"Edit/UI_NowEditFrame_Copper_256" },
	{ "��",				"Silver",	"Edit/UI_NowEditFrame_Silver_256" },
	{ "��",				"Gold",		"Edit/UI_NowEditFrame_Gold_256" }
} };

static const std::array<EDIT_NAME, EDIT_EFFECT_MAX> EDIT_EFFECT_NAME =
{ {
	// ����(���{��),				����(�p��),					�摜��
	{ "�Ȃ�",						"None",						"" },
	{ "�ړ����x�A�b�v",				"MoveSpeedUp",				"Edit/UI_Edit_SpeedUp" },
	{ "�u���b�h�擾�ʃA�b�v",		"GetBloodUp",				"Edit/UI_Edit_BloodPlus" },
	{ "�R���{�p�����ԃA�b�v",		"ComboDurationUp",			"Edit/UI_Edit_ComboTimerPlus" },
	{ "�ߐڍU�����ߎ��Ԍ���",		"MeleeChargeReduction",		"Edit/UI_Edit_ChargeShort" },
	{ "�W�����v�񐔃A�b�v",			"JumpCountUp",				"Edit/UI_Edit_JumpPlus" },
	{ "�󒆋����U���񐔃A�b�v",		"AirMeleeCountUp",			"Edit/UI_Edit_IaiAirPlus" },
	{ "�N�i�C����m������",			"KunaiKeep",				"Edit/UI_Edit_KunaiLucky"},
	{ "�o���A�񐔃A�b�v",			"BarierCountUp",			"Edit/UI_Edit_Barrier" },
	{ "�J�E���^�[�A�N�V�����ǉ�",	"Counter",					"Edit/UI_Edit_Parry" },
	{ "HP1����",					"LimitHpOne",				"Edit/UI_Edit_HpOne" },
	{ "�N�i�C����",					"KunaiExplosion",			"Edit/UI_Edit_KunaiBomb" }
} };

/* �G�f�B�b�g�Ǘ��p�̍\���� */
struct EDIT_INFORMATION
{
	int			iEditType;		// �G�f�B�b�g�̎��
	int			iEditEffect;	// �G�f�B�b�g�̌���
	int			iEditRank;		// �G�f�B�b�g�̃����N
	bool		bEditUpgrade;	// �A�b�v�O���[�h�t���O
};

/* �G�f�B�b�g�̌��ʗ� */
struct EDIT_EFFECT_VALUE
{
	int			iEditEffect;	// �G�f�B�b�g�̌���
	int			iEditRank;		// �G�f�B�b�g�̃����N
	int			iValue;			// �G�f�B�b�g�̌��ʗ�
};
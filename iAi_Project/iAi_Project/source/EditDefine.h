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
static const int	EDIT_EFFECT_NORMAL_GET_KUNAI_UP					= 7;	// �N�i�C�擾�ʃA�b�v
static const int	EDIT_EFFECT_NORMAL_BARIER_COUNT_UP				= 8;	// �o���A�񐔃A�b�v
// ����
static const int	EDIT_EFFECT_SPECIAL_GLIDING						= 9;	// ����A�N�V�����ǉ�
static const int	EDIT_EFFECT_SPECIAL_COUNTER						= 10;	// �J�E���^�[�A�N�V�����ǉ�
// ��
static const int	EDIT_EFFECT_CURCE_LIMIT_DASH_DODGE				= 11;	// �_�b�V���A��𐧌�
static const int	EDIT_EFFECT_CURCE_LIMIT_HP_ONE					= 12;	// HP1����
static const int	EDIT_EFFECT_CURCE_LIMIT_MELEE_CHARGE_CHANCEL	= 13;	// �����L�����Z������
// ���̑�
static const int	EDIT_EFFECT_MAX									= 14;	// �G�f�B�b�g���ʂ̍ő吔

/* �G�f�B�b�g���p�̍\���� */
struct EDIT_DATA
{
	int			iEditRank;				// �G�f�B�b�g�̃����N
	int			iEditEffect;			// �G�f�B�b�g�̌���
	int			iEditCost;				// �G�f�B�b�g�̉��i(�V�K�A�z�[���h���̃G�f�B�b�g�Ŏg�p)
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
	{ "�Ȃ�",			"None",		"Test_Edit/Frame/EditFrame_None" },
	{ "��",				"Cupper",	"Test_Edit/Frame/EditFrame_Cupper" },
	{ "��",				"Silver",	"Test_Edit/Frame/EditFrame_Silver" },
	{ "��",				"Gold",		"Test_Edit/Frame/EditFrame_Gold" }
} };

static const std::array<EDIT_NAME, EDIT_EFFECT_MAX> EDIT_EFFECT_NAME =
{ {
	// ����(���{��),				����(�p��),					�摜��
	{ "�Ȃ�",						"None",						"Test_Edit/Effect/NoImage" },
	{ "�ړ����x�A�b�v",				"MoveSpeedUp",				"Test_Edit/Effect/Edit_SpeedUp" },
	{ "�u���b�h�擾�ʃA�b�v",		"GetBloodUp",				"Test_Edit/Effect/Edit_BloodUp" },
	{ "�R���{�p�����ԃA�b�v",		"ComboDurationUp",			"Test_Edit/Effect/Edit_ComboUp" },
	{ "�ߐڍU�����ߎ��Ԍ���",		"MeleeChargeReduction",		"Test_Edit/Effect/Edit_ChargeSpeedUp" },
	{ "�W�����v�񐔃A�b�v",			"JumpCountUp",				"Test_Edit/Effect/Edit_JumpAdd" },
	{ "�󒆋����U���񐔃A�b�v",		"AirMeleeCountUp",			"Test_Edit/Effect/Edit_KunaiKeep" },
	{ "�N�i�C�擾�ʃA�b�v",			"GetKunaiUp",				"Test_Edit/Effect/Edit_KunaiAdd" },
	{ "�o���A�񐔃A�b�v",			"BarierCountUp",			"Test_Edit/Effect/Edit_BarrierAdd" },
	{ "����A�N�V�����ǉ�",			"Gliding",					"Test_Edit/Effect/NoImage" },
	{ "�J�E���^�[�A�N�V�����ǉ�",	"Counter",					"Test_Edit/Effect/NoImage" },
	{ "�_�b�V���A��𐧌�",			"LimitDashDodge",			"Test_Edit/Effect/NoImage" },
	{ "HP1����",					"LimitHpOne",				"Test_Edit/Effect/NoImage" },
	{ "�����L�����Z������",			"LimitMeleeChargeChancel",	"Test_Edit/Effect/NoImage" }
} };

/* �G�f�B�b�g�Ǘ��p�̍\���� */
struct EDIT_INFORMATION
{
	int			iEditType;		// �G�f�B�b�g�̎��
	int			iEditEffect;	// �G�f�B�b�g�̌���
	int			iEditRank;		// �G�f�B�b�g�̃����N
	bool		bEditUpgrade;	// �A�b�v�O���[�h�t���O
};

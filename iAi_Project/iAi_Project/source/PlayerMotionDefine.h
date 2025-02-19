/* 2025.02.07 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <string>
#include <array>
#include <utility>

/* �v���C���[���[�V�����֘A�̍\���̂�萔�̐錾���s�� */

/* �v���C���[���[�V����ID */
// �ړ��n
static const int	MOTION_ID_MOVE_WAIT				= 0;	// �ҋ@
static const int	MOTION_ID_MOVE_WALK				= 1;	// ���s
static const int	MOTION_ID_MOVE_JUMP_START		= 2;	// �W�����v(�J�n)
static const int	MOTION_ID_MOVE_JUMP_UP			= 3;	// �W�����v(�㏸)
static const int	MOTION_ID_MOVE_JUMP_DOWN		= 4;	// �W�����v(���~)
static const int	MOTION_ID_MOVE_LAND				= 5;	// ���n
static const int	MOTION_ID_MOVE_DODGE			= 6;	// ���
// �U���n
static const int	MOTION_ID_ATTACK_NONE			= 7;	// ����(���U���n�̓��͂��Ȃ��Ƃ��Ɏg�p)
static const int	MOTION_ID_ATTACK_WEAK			= 8;	// ��U��
static const int	MOTION_ID_ATTACK_CHARGE			= 9;	// ����
static const int	MOTION_ID_ATTACK_STRONG			= 10;	// ���U��(������)
static const int	MOTION_ID_ATTACK_STRONG_END		= 11;	// ���U��(�I��)
static const int	MOTION_ID_ATTACK_THROW_READY	= 12;	// ����(����)
static const int	MOTION_ID_ATTACK_THROW			= 13;	// ����
// ���v
static const int	MOTION_ID_MAX					= 14;	// ���[�V����ID�̍ő吔

/* �v���C���[���[�V������ */
// �ړ��n
static const std::string	MOTION_MOVE_WAIT		= "mot_attack_charge_loop";		// �ҋ@
static const std::string	MOTION_MOVE_WALK		= "mot_move_run";				// ���s
static const std::string	MOTION_MOVE_JUMP_START	= "mot_move_jump_f_start";		// �W�����v(�J�n)
static const std::string	MOTION_MOVE_JUMP_UP		= "mot_move_jump_f_uploop";		// �W�����v(�㏸)
static const std::string	MOTION_MOVE_JUMP_FALL	= "mot_move_jump_fall_loop";	// �W�����v(����)
static const std::string	MOTION_MOVE_lAND		= "mot_move_land";				// ���n
static const std::string	MOTION_MOVE_DODGE		= "mot_attack_charge_step";		// ���(���U��(�ړ���)�𗬗p)
// �U���n
static const std::string	MOTION_ATTACK			= "mot_attack_nomal";			// ��U��
static const std::string	MOTION_CHARGE_STEP		= "mot_attack_charge_step";		// ���U��(�ړ���)
static const std::string	MOTION_CHARGE_LOOP		= "mot_attack_charge_loop";		// ���ߒ�
static const std::string	MOTION_CHARGE_FINISH	= "mot_attack_charge_finish";	// ���U��(����)
static const std::string	MOTION_THROW_READY		= "mot_attack_throw_ready";		// ����(����)
static const std::string	MOTION_THROW			= "mot_attack_throw";			// ����

/* �v���C���[���[�V�����p�̍\���� */
struct PLAYER_MOTION
{
	/* �����o�ϐ� */
	int		iMotionID;			// ���[�V����ID
	std::string	strMotionName;	// ���[�V������
	float	fMotion_MaxTime;	// ���[�V�����̑��Đ�����
	int		iNextMotionID;		// ���̃��[�V����ID(���[�v���������ꍇ�A���̃��[�V�����Ɠ����l�����)
	float	fBlendRatio;		// �u�����h�̊���(�U�����̂ݑΏ�)
};

/* ���[�V����ID�ƃ��[�V�������𓝍������萔�z�� */
static const std::array<PLAYER_MOTION, MOTION_ID_MAX> MOTION_LIST =
{ {
	// ���[�V����ID,				���[�V������,			���[�V�����̑��Đ�����,		���̃��[�V����ID,				�u�����h�̊���(�U�����̂�)
	// �ړ��n
	{ MOTION_ID_MOVE_WAIT,			MOTION_MOVE_WAIT,		-1,							MOTION_ID_MOVE_WAIT,			0.f},
	{ MOTION_ID_MOVE_WALK,			MOTION_MOVE_WALK,		-1,							MOTION_ID_MOVE_WALK,			0.f},
	{ MOTION_ID_MOVE_JUMP_START,	MOTION_MOVE_JUMP_START,	-1,							MOTION_ID_MOVE_JUMP_UP,			0.f},
	{ MOTION_ID_MOVE_JUMP_UP,		MOTION_MOVE_JUMP_UP,	-1,							MOTION_ID_MOVE_JUMP_UP,			0.f},
	{ MOTION_ID_MOVE_JUMP_DOWN,		MOTION_MOVE_JUMP_FALL,	-1,							MOTION_ID_MOVE_JUMP_DOWN,		0.f},
	{ MOTION_ID_MOVE_LAND,			MOTION_MOVE_lAND,		-1,							MOTION_ID_MOVE_WAIT,			0.f},
	{ MOTION_ID_MOVE_DODGE,			MOTION_MOVE_DODGE,		-1,							MOTION_ID_MOVE_DODGE,			0.f},
	// �U���n
	{ MOTION_ID_ATTACK_NONE,		"",						-1,							MOTION_ID_ATTACK_NONE,			0.f},
	{ MOTION_ID_ATTACK_WEAK,		MOTION_ATTACK,			-1,							MOTION_ID_ATTACK_NONE,			0.7f},
	{ MOTION_ID_ATTACK_CHARGE,		MOTION_CHARGE_LOOP ,	-1,							MOTION_ID_ATTACK_CHARGE,		0.7f},
	{ MOTION_ID_ATTACK_STRONG,		MOTION_CHARGE_STEP ,	-1,							MOTION_ID_ATTACK_STRONG,		0.7f},
	{ MOTION_ID_ATTACK_STRONG_END,	MOTION_CHARGE_FINISH,	-1,							MOTION_ID_ATTACK_NONE,			0.9f},
	{ MOTION_ID_ATTACK_THROW_READY,	MOTION_THROW_READY,		-1,							MOTION_ID_ATTACK_THROW_READY,	0.7f},
	{ MOTION_ID_ATTACK_THROW,		MOTION_THROW,			-1,							MOTION_ID_ATTACK_NONE,			0.7f},
} };

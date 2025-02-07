/* 2025.02.07 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <string>

/* �v���C���[���[�V�����֘A�̍\���̂�萔�̐錾���s�� */

/* �v���C���[���[�V����ID */
// �ړ��n
static const int	MOTION_ID_MOVE_IDLE				= 0;	// �ҋ@
static const int	MOTION_ID_MOVE_WALK				= 1;	// ���s
static const int	MOTION_ID_MOVE_JUMP_START		= 2;	// �W�����v(�J�n)
static const int	MOTION_ID_MOVE_JUMP_UP			= 3;	// �W�����v(�㏸)
static const int	MOTION_ID_MOVE_JUMP_DOWN		= 4;	// �W�����v(���~)
static const int	MOTION_ID_MOVE_LAND				= 5;	// ���n
static const int	MOTION_ID_MOVE_DODGE			= 6;	// ���
// �U���n
static const int	MOTION_ID_ATTACK_NONE			= 0;	// ����(���U���n�̓��͂��Ȃ��Ƃ��Ɏg�p)
static const int	MOTION_ID_ATTACK_WEAK			= 1;	// ��U��
static const int	MOTION_ID_ATTACK_CHARGE			= 2;	// ����
static const int	MOTION_ID_ATTACK_STRONG			= 3;	// ���U��(������)
static const int	MOTION_ID_ATTACK_STRONG_END		= 4;	// ���U��(�I��)

/* �v���C���[���[�V������ */
// �ړ��n
static const std::string	MOTION_MOVE_RUN			=	"mot_move_run";				// �ړ�
static const std::string	MOTION_MOVE_JUMP_START	=	"mot_move_jump_f_start";	// �W�����v(�J�n)
static const std::string	MOTION_MOVE_JUMP_UP		=	"mot_move_jump_f_uploop";	// �W�����v(�㏸)
static const std::string	MOTION_MOVE_JUMP_FALL	=	"mot_move_jump_fall_loop";	// �W�����v(����)
static const std::string	MOTION_MOVE_lAND		=	"mot_move_land";			// ���n
static const std::string	MOTION_MOVE_WAIT		=	"mot_move_wait";			// �ҋ@
// �U���n
static const std::string	MOTION_CHARGE_STEP		=	"mot_attack_charge_stop";	// ���U��(�ړ���)
static const std::string	MOTION_CHARGE_LOOP		=	"mot_attack_charge_loop";	// ���ߒ�
static const std::string	MOTION_CHARGE_FINISH	=	"mot_attack_charge_finish";	// ���U��(����)


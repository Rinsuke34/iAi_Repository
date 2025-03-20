/* 2024.01.06 ��򕗏� �t�@�C���쐬 */
/* 2025.03.03 �e�r�듹 ���b�N�I���֘A�̒萔�ǉ� */
/* 2025.03.03 �e�r�듹 �v���C���[�֘A�̒萔�ǉ� */
#pragma once

#include <string>
#include "StructDefine.h"

/* �v���W�F�N�g�Ŏg�p����萔�̐錾 */

/* �v�Z�p�}�N�� */
#define	PI					(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )
#define	ACCELERATION(x)		( (x) / 60.0f * 60.0f )
#define GRAVITY				( -9.8f )

/* �X�e�[�W��� */
// �X�e�[�W��
static const int	STAGE_MAX       = 10;
// �X�e�[�W�ԍ�
static const int	STAGE_NO_1_1    = 0;
static const int	STAGE_NO_1_2    = 1;
static const int	STAGE_NO_1_3    = 2;
static const int	STAGE_NO_2_1    = 3;
static const int	STAGE_NO_2_2    = 4;
static const int	STAGE_NO_2_3    = 5;
static const int	STAGE_NO_3_1    = 6;
static const int	STAGE_NO_3_2    = 7;
static const int	STAGE_NO_3_3    = 8;
// �^�C�g���A�z�[��
static const int	STAGE_NO_TITLE  = 9;
// �J�n/�I���X�e�[�W�ԍ�
static const int    STAGE_START     = STAGE_NO_1_1;     // �J�n
static const int    STAGE_END       = STAGE_NO_3_3;     // �I��
// �X�e�[�W��
static const std::string STAGE_NAME[STAGE_MAX] =
{
    "Stage_1_1", "Stage_1_2", "Stage_1_3",
    "Stage_2_1", "Stage_2_2", "Stage_2_3",
    "Stage_3_1", "Stage_3_2", "Stage_3_3",
    "Stage_Title"
};

/* �`�ʊ֘A */
static const int    SHADOWMAP_SIZE_ACTOR        = 4096;     // �V���h�E�}�b�v(�A�N�^)�̃T�C�Y
static const int    SHADOWMAP_SIZE_PLATFORM     = 4096 * 2;		// �V���h�E�}�b�v(�v���b�g�t�H�[��)�̃T�C�Y

static const int    SHADOWMAP_RANGE_ACTOR_HEIGHT      = 2048;		// �V���h�E�}�b�v(�A�N�^)�̍���
static const int    SHADOWMAP_RANGE_ACTOR_WIDTH       = 2048;		// �V���h�E�}�b�v(�A�N�^)�̉���
static const int    SHADOWMAP_RANGE_PLATFORM_HEIGHT   = 2048 * 3;	// �V���h�E�}�b�v(�v���b�g�t�H�[��)�̍���
static const int    SHADOWMAP_RANGE_PLATFORM_WIDTH    = 2048 * 3;	// �V���h�E�}�b�v(�v���b�g�t�H�[��)�̉���

static const int	LIGHTMAP_DOWNSCALE		= 8;		// ���C�g�}�b�v�̏k���{��
static const int	LIGHTMAP_GAUSS_WIDTH	= 16;		// �ڂ����̋���(8, 16, 32�̂����ꂩ)
static const int	LIGHTMAP_GAUSS_RATIO	= 100;		// �ڂ����p�����[�^(100�ɂ���1�s�N�Z�����̕�)

static const int    ALPHA_MAX               = 255;		// �A���t�@�l�̍ő�l
static const int    FADE_ALPHA_CHANGE_SPEED = 3;		// �t�F�[�h�C��/�A�E�g�̑��x

/* �f�o�b�O�֘A */
static const int    DEBUG_MAP_HEIGHT	    = 256;	// �f�o�b�O�`�ʂ̍���
static const int    DEBUG_MAP_WIDTH         = 256;	// �f�o�b�O�`�ʂ̉���
// �f�o�b�O���[�h
static const int	DEBUG_MODE_OPTION       = 0;	// �f�o�b�O�I�v�V����
static const int	DEBUG_MODE_OPERATION    = 1;	// �f�o�b�O����
static const int	DEBUG_MODE_MAX          = 2;	// �f�o�b�O���[�h�̑���
// �f�o�b�O���얼
static const int    DEBUG_OPERATION_STAGEJUMP   = 0;	// �X�e�[�W�W�����v
static const int    DEBUG_OPERATION_STATUSSETUP = 1;	// �X�e�[�^�X����
static const int    DEBUG_OPERATION_MAX         = 2;    // �f�o�b�O����̑���

/* ���b�N�I���֌W */
// �G�l�~�[�̃v���C���[����̃��b�N�I�����
static const int PLAYER_LOCKON_NONE     = 0;    // ���b�N�I������Ă��Ȃ�
static const int PLAYER_LOCKON_RANGE    = 1;    // ���b�N�I���͈͓��ł���
static const int PLAYER_LOCKON_TARGET   = 2;    // ���b�N�I������Ă���
// ���b�N�I���֘A�̐ݒ�l
static const float PLAYER_LOCKON_RADIUS = 5000.0f;    // ���b�N�I���͈͂̔��a       /* 2025.03.03 �e�r�듹 ���b�N�I���֘A�̒萔�ǉ� */

/* �]�������N */
static const int	RESULT_EVALUATION_S     = 0;	// S(�ō������N)
static const int	RESULT_EVALUATION_A     = 1;	// A
static const int	RESULT_EVALUATION_B     = 2;	// B
static const int	RESULT_EVALUATION_C     = 3;	// C
static const int	RESULT_EVALUATION_D     = 4;	// D(�Œ჉���N)
static const int    RESULT_EVALUATION_MAX   = 5;    // �]�������N�̑���

/* ��ʃG�t�F�N�g�֘A */
// �_���[�W�G�t�F�N�g�֘A
static const int	DAMAGE_EFFECT_TIME              = 30;	// �_���[�W�G�t�F�N�g�̎�������(�t���[����)
static const int    DAMAGE_EFFECT_SHIFT_CHANGE      = 10;	// �_���[�W�G�t�F�N�g�̃V�t�g�ʕύX�J�E���g
static const int	DAMAGE_EFFECT_ALPHA             = 50;	// �_���[�W�G�t�F�N�g�̃A���t�@�l(0�`100)
static const int	DAMAGE_EFFECT_SHIFT             = 50;	// �_���[�W�G�t�F�N�g�̍ŏ��̃V�t�g��(�s�N�Z����)
// �W�����G�t�F�N�g�֘A
static const int    CONCENTRATIONLINE_EFFECT_CHANGE = 5;    // �W�����G�t�F�N�g�̕ύX�Ԋu(�t���[����)
static const int	CONCENTRATIONLINE_EFFECT_ALPHA  = 30;	// �_���[�W�G�t�F�N�g�̃A���t�@�l(0�`100)
static const int    CONCENTRATIONLINE_EFFECT_TYPE   = 2;    // �W�����G�t�F�N�g�̎�ނ̐�

/* �R���{�֘A */
// �R���{�����N
static const int    COMBO_RANK_S        = 0;    // S�����N
static const int    COMBO_RANK_A        = 1;    // A�����N
static const int    COMBO_RANK_B        = 2;    // B�����N
static const int    COMBO_RANK_C        = 3;    // C�����N
static const int    COMBO_RANK_D        = 4;    // D�����N
static const int    COMBO_RANK_MAX      = 5;	// �R���{�����N�̑���
static const int    COMBO_RANK_NONE     = -1;   // ����

/* �X���[�֘A */
static const int	SLOW_SPEED = 1;				// �X���[��Ԃł̑��x(���t���[���Ɉ�x���s����邩)

/* �v���C���[�֘A */
static const int	PLAYER_STRONG_MELEE_AFTER_COUNT_MAX = 120 * 1 / (SLOW_SPEED + 1);	// �ߐڍU��(��)��œG��|������̃J�E���g�̍ő�l(����ꍀ�ɃX���[���[�V�������l�����Ȃ��t���[����������)	/* 2025.03.03 �e�r�듹 �U���֘A�̒萔�ǉ� */

/* �v���C���[���̓^�C�v */
static const int    INPUT_TYPE_CONTROLLER   = 0;    // �R���g���[��
static const int    INPUT_TYPE_MOUSE        = 1;    // �}�E�X
static const int    INPUT_TYPE_MAX          = 2;    // ���̓^�C�v�̑���

/* �J�����֘A */
// �J�����ړ��^�C�v
static const int	INPUT_CAMERA_NORMAL     = 0;	// �ʏ�
static const int	INPUT_CAMERA_AIM        = 1;	// �G�C��(�\��/�N�i�C�\��)
static const int	INPUT_CAMERA_NONE       = 2;	// ����(���͎�t�Ȃ�)
static const int	INPUT_CAMERA_MAX        = 3;	// �J�����ړ��^�C�v�̑���

/* ���̓I�v�V�����֘A */
// ��
static const int    AXIS_X                  = 0;	// X��
static const int    AXIS_Y                  = 1;	// Y��
static const int    AXIS_MAX                = 2;	// ���̑���
// �J�������
static const int    INPUT_CAMERA_MODE_NORMAL      = 0;	// �ʏ���
static const int    INPUT_CAMERA_MODE_AIM         = 1;	// �G�C�����
static const int    INPUT_CAMERA_MODE_MAX         = 2;	// �J������Ԃ̑���

/* �f�[�^�^���� */
static const std::string DATA_TYPE_BOOL     = "bool";	// �u�[���^
static const std::string DATA_TYPE_INT      = "int";	// �����^
static const std::string DATA_TYPE_FLOAT    = "float";	// ���������_�^

/* �M�~�b�N�֘A */
static const int	GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_SHORT  = 0;		// �ړ����̈ړ������^�C�v(�Z)
static const int	GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_NORMAL = 1;		// �ړ����̈ړ������^�C�v(��)
static const int	GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_LONG   = 2;		// �ړ����̈ړ������^�C�v(��)

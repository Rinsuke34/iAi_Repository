/* 2024.01.06 ��򕗏� �t�@�C���쐬 */

#pragma once

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
static const int	SHADOWMAP_SIZE_PLATFORM     = 2048;		// �V���h�E�}�b�v�̃T�C�Y

static const float	SHADOWMAP_RANGE			= 1024;		// �V���h�E�}�b�v�̕`�ʔ͈�
static const int	LIGHTMAP_DOWNSCALE		= 8;		// ���C�g�}�b�v�̏k���{��
static const int	LIGHTMAP_GAUSS_WIDTH	= 16;		// �ڂ����̋���(8, 16, 32�̂����ꂩ)
static const int	LIGHTMAP_GAUSS_RATIO	= 100;		// �ڂ����p�����[�^(100�ɂ���1�s�N�Z�����̕�)

static const int    ALPHA_MAX               = 255;		// �A���t�@�l�̍ő�l
static const int    FADE_ALPHA_CHANGE_SPEED = 3;		// �t�F�[�h�C��/�A�E�g�̑��x

/* �f�o�b�O�֘A */
static const int DEBUG_MAP_HEIGHT	= 256;	// �f�o�b�O�`�ʂ̍���
static const int DEBUG_MAP_WIDTH	= 256;	// �f�o�b�O�`�ʂ̉���

/* ���b�N�I���֌W */
// �G�l�~�[�̃v���C���[����̃��b�N�I�����
static const int PLAYER_LOCKON_NONE     = 0;    // ���b�N�I������Ă��Ȃ�
static const int PLAYER_LOCKON_RANGE    = 1;    // ���b�N�I���͈͓��ł���
static const int PLAYER_LOCKON_TARGET   = 2;    // ���b�N�I������Ă���

/* �]�������N */
static const int	RESULT_EVALUATION_S     = 0;	// S(�ō������N)
static const int	RESULT_EVALUATION_A     = 1;	// A
static const int	RESULT_EVALUATION_B     = 2;	// B
static const int	RESULT_EVALUATION_C     = 3;	// C
static const int	RESULT_EVALUATION_D     = 4;	// D(�Œ჉���N)
static const int    RESULT_EVALUATION_MAX   = 5;    // �]�������N�̑���

/* ��ʃG�t�F�N�g�֘A */
// �_���[�W�G�t�F�N�g�֘A
static const int	DAMAGE_EFFECT_TIME          = 30;	// �_���[�W�G�t�F�N�g�̎�������(�t���[����)
static const int    DAMAGE_EFFECT_SHIFT_CHANGE  = 10;	// �_���[�W�G�t�F�N�g�̃V�t�g�ʕύX�J�E���g
static const int	DAMAGE_EFFECT_ALPHA         = 50;	// �_���[�W�G�t�F�N�g�̃A���t�@�l(0�`100)
static const int	DAMAGE_EFFECT_SHIFT         = 50;	// �_���[�W�G�t�F�N�g�̍ŏ��̃V�t�g��(�s�N�Z����)

/* �R���{�֘A */
// �R���{�����N
static const int    COMBO_RANK_S        = 0;    // S�����N
static const int    COMBO_RANK_A        = 1;    // A�����N
static const int    COMBO_RANK_B        = 2;    // B�����N
static const int    COMBO_RANK_C        = 3;    // C�����N
static const int    COMBO_RANK_D        = 4;    // D�����N
static const int    COMBO_RANK_NONE     = -1;   // ����
// �{�[�_�[���C��
// ���R���{�������̒l�𒴂��Ă���΂��̃R���{�����N
static const int    COMBO_RANK_BORDER_S = 21;   // S�����N
static const int    COMBO_RANK_BORDER_A = 11;   // A�����N
static const int    COMBO_RANK_BORDER_B = 5;    // B�����N
static const int    COMBO_RANK_BORDER_C = 2;    // C�����N

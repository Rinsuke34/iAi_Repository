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
static const int	STAGE_MAX   = 12;
// �X�e�[�W�ԍ�
static const int	STAGE_NO_0_1 = 0;
static const int	STAGE_NO_0_2 = 1;
static const int	STAGE_NO_0_3 = 2;
static const int	STAGE_NO_1_1 = 3;
static const int	STAGE_NO_1_2 = 4;
static const int	STAGE_NO_1_3 = 5;
static const int	STAGE_NO_2_1 = 6;
static const int	STAGE_NO_2_2 = 7;
static const int	STAGE_NO_2_3 = 8;
static const int	STAGE_NO_3_1 = 9;
static const int	STAGE_NO_3_2 = 10;
static const int	STAGE_NO_3_3 = 11;
// �J�n/�I���X�e�[�W�ԍ�
static const int    STAGE_NO_TUTORIAL_START    = STAGE_NO_0_1;     // �`���[�g���A���J�n
static const int    STAGE_NO_TUTORIAL_END      = STAGE_NO_0_3;     // �`���[�g���A���I��
static const int    STAGE_NO_PRACTICE_START    = STAGE_NO_1_1;     // ���H�J�n
static const int    STAGE_NO_PRACTICE_END      = STAGE_NO_3_3;     // ���H�I��
// �X�e�[�W��
static const std::string STAGE_NAME[STAGE_MAX] =
{
    "Stage_0_1", "Stage_0_2", "Stage_0_3",
    "Stage_1_1", "Stage_1_2", "Stage_1_3",
    "Stage_2_1", "Stage_2_2", "Stage_2_3",
    "Stage_3_1", "Stage_3_2", "Stage_3_3"
};

/* �`�ʊ֘A */
static const int	SHADOWMAP_SIZE			= 2048;		// �V���h�E�}�b�v�̃T�C�Y
static const float	SHADOWMAP_RANGE			= 1024;		// �V���h�E�}�b�v�̕`�ʔ͈�
static const int	LIGHTMAP_DOWNSCALE		= 8;		// ���C�g�}�b�v�̏k���{��
static const int	LIGHTMAP_GAUSS_WIDTH	= 16;		// �ڂ����̋���(8, 16, 32�̂����ꂩ)
static const int	LIGHTMAP_GAUSS_RATIO	= 100;		// �ڂ����p�����[�^(100�ɂ���1�s�N�Z�����̕�)

/* �f�o�b�O�֘A */
static const int DEBUG_MAP_HEIGHT	= 256;	// �f�o�b�O�`�ʂ̍���
static const int DEBUG_MAP_WIDTH	= 256;	// �f�o�b�O�`�ʂ̉���

// Effekseer�֘A
static const int EFFECT_MAX_PARTICLE	= 8000;		// �G�t�F�N�g�̍ő�p�[�e�B�N����

/* ���b�N�I���֌W */
// �G�l�~�[�̃v���C���[����̃��b�N�I�����
static const int PLAYER_LOCKON_NONE     = 0;    // ���b�N�I������Ă��Ȃ�
static const int PLAYER_LOCKON_RANGE    = 1;    // ���b�N�I���͈͓��ł���
static const int PLAYER_LOCKON_TARGET   = 2;    // ���b�N�I������Ă���

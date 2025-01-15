/* 2024.01.06 ��򕗏� �t�@�C���쐬 */

#pragma once

/* �v���W�F�N�g�Ŏg�p����萔�̐錾 */

/* �v�Z�p�}�N�� */
#define	PI					(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )
#define	ACCELERATION(x)		( (x) / 60.0f * 60.0f )
#define GRAVITY				( -9.8f )

/* �X�e�[�W�֘A */
static const int STAGE_0_1	= 0;	// �X�e�[�W0-1
static const int STAGE_0_2	= 1;	// �X�e�[�W0-2
static const int STAGE_0_3	= 2;	// �X�e�[�W0-3
static const int STAGE_1_1	= 3;	// �X�e�[�W1-1
static const int STAGE_1_2	= 4;	// �X�e�[�W1-2
static const int STAGE_1_3	= 5;	// �X�e�[�W1-3
static const int STAGE_2_1	= 6;	// �X�e�[�W2-1
static const int STAGE_2_2	= 7;	// �X�e�[�W2-2
static const int STAGE_2_3	= 8;	// �X�e�[�W2-3
static const int STAGE_3_1	= 9;	// �X�e�[�W0-1
static const int STAGE_3_2	= 10;	// �X�e�[�W0-2
static const int STAGE_3_3	= 11;	// �X�e�[�W0-3

/* �J�����֘A */
static const int CAMERA_MODE_FREE	= 0;	// �t���[���[�h(�ʏ�̎O�l�̎��_)

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

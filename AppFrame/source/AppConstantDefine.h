/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#pragma once

/* AppFrame�Ŏg�p����萔�̐錾 */

/* ��ʊ֘A */
static const int SCREEN_SIZE_WIDE	= 1920;		// ��ʃT�C�Y(��)
static const int SCREEN_SIZE_HEIGHT	= 1080;		// ��ʃT�C�Y(�c)

/* �t���[�����[�g�֘A */
static const int FPS_RATE			= 60;	// �t���[�����[�g�ݒ�l

/* ���͊֘A */
// ���̓^�C�v
static const int INPUT_HOLD	= 0;	// �z�[���h����
static const int INPUT_TRG	= 1;	// �g���K����
static const int INPUT_REL	= 2;	// �����[�X����
static const int INPUT_MAX	= 3;	// ���̓^�C�v�̍ő吔

// �X�e�B�b�N�A�g���K�[�p���E����
static const int INPUT_LEFT			= 0;	// ��(�X�e�B�b�N�A�g���K�[)
static const int INPUT_RIGHT		= 1;	// �E(�X�e�B�b�N�A�g���K�[)
static const int INPUT_DIRECTION	= 2;	// ���E�̑���(���}�W�b�N�i���o�[�΍�ō쐬)

// ����臒l
static const unsigned char	INIT_TRIGGER_THRESHOLD	= 10;	// �g���K�[���͂̏���臒l

/* 2024.12.21 ��򕗏� �t�@�C���쐬 */

#pragma once

/* �f�[�^���X�g */
#include "DataList_Input.h"
#include "DataList_Sound.h"

/* �v���W�F�N�g�Ŏg�p����L��ϐ��̐錾 */

/* ���s���N���X */
extern DataList_Input*	gpDataList_Input;	// �v���C���[���͊Ǘ��N���X
extern DataList_Sound*	gpDataList_Sound;	// �T�E���h�Ǘ��N���X

/* �f�o�b�O�p�`�ʊǗ��t���O */
extern bool gbDrawShadowMapFlg;				// �V���h�E�}�b�v�̕`��
extern bool gbDrawLightMapFlg;				// ���C�g�}�b�v�̕`��
extern bool gbDrawLightMapDownScaleFlg;		// ���C�g�}�b�v(�k��)�̕`��
extern bool gbDrawLightMapGaussFlg;			// ���C�g�}�b�v(�ڂ���)�̃n���h��
extern bool gbDrawCollisionFlg;				// �R���W�����`��
extern bool gbDrawDeleteBackGroundFlg;		// �o�b�N�O�����h��\��
extern bool gbDrawInputTest;				// ���̓e�X�g�̕`��
extern bool gbDrawStopBloomFlg;				// �^�������̖������t���O
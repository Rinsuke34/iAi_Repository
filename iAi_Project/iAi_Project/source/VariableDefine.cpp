/* 2024.12.22 ��򕗏� �t�@�C���쐬 */

#include "VariableDefine.h"

/* �L��ϐ��̏����� */

/* ���s���N���X */
DataList_Input*	gpDataList_Input	= nullptr;	// �v���C���[���͊Ǘ��N���X
DataList_Sound*	gpDataList_Sound	= nullptr;	// �T�E���h�Ǘ��N���X

/* �X�e�[�W�֘A */
bool gbTutorialFlg					= false;	// �`���[�g���A���t���O

/* �f�o�b�O�p�`�ʊǗ��t���O */
bool gbDrawShadowMapFlg				= false;		// �V���h�E�}�b�v�̕`��
bool gbDrawLightMapFlg				= false;		// ���C�g�}�b�v�̕`��
bool gbDrawLightMapDownScaleFlg		= false;		// ���C�g�}�b�v(�k��)�̕`��
bool gbDrawLightMapGaussFlg			= false;		// ���C�g�}�b�v(�ڂ���)�̃n���h��
bool gbDrawCollisionFlg				= false;		// �S�I�u�W�F�N�g�̃R���W�����`��
bool gbDrawDeleteBackGroundFlg		= false;		// �o�b�N�O�����h�I�u�W�F�N�g�̔�\��

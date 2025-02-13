/* 2025.01.16 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Model.h"
#include "DataList_GameStatus.h"
#include "DataList_Image.h"

/* �V�[�� */
#include "SceneEdit.h"
#include "SceneUi_Crosshairs.h"
#include "SceneUi_Combo.h"
#include "SceneUi_Hp.h"
#include "SceneUi_Kunai.h"
#include "SceneUi_Debug.h"
#include "SceneUi_Blood.h"
#include "SceneUi_Edit.h"

/* �X�e�[�W�N���X�̐錾 */

// �X�e�[�W�x�[�X
class SceneStage : public SceneBase
{
	public:
		SceneStage();							// �R���X�g���N�^
		virtual ~SceneStage();					// �f�X�g���N�^

		void	Initialization()	override;	// ������
		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

		virtual void	LoadMapData();			// �}�b�v�f�[�^�̃��[�h

	private:
		/* �g�p����f�[�^���X�g */
		DataList_Object*		ObjectList;			// �I�u�W�F�N�g�Ǘ�
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[��ԊǗ�
		DataList_Model*			ModelList;			// 3D���f���Ǘ�
		DataList_GameStatus*	GameStatusList;		// �Q�[����ԊǗ�

		/* �֐� */
		void	SetupShadowMap();				// �V���h�E�}�b�v�̐ݒ�
		void	SetupLightMap();				// ���C�g�}�b�v�̐ݒ�
		void	SetupMainScreen();				// ���C���̕`�ʏ���
		void	SetupEffectScreen();			// �G�t�F�N�g�̕`�ʏ���
		void	SetupScreenEffects();			// ��ʃG�t�F�N�g
		void	SetCamera();					// �J�����ݒ�

		/* �J�������[�h�֘A */
		void	CameraRotateUpdata(float fRate);	// ���͂ɂ��J������]�ʎ擾
		void	SetCamera_Free();					// �J�����ݒ�(�t���[)
		void	SetCamera_Lock();					// �J�����ݒ�(�Œ�)
		void	SetCamera_Aim();					// �J�����ݒ�(�\��(�Y�[��))
		void	CameraSmoothing();					// �J�����␳

		/* �f�o�b�O�֘A */
		void	DrawDebug();						// �f�o�b�O�`��

		/* �`�ʉ�ʊ֘A */
		// �摜�n���h��
		int	iLightMapScreenHandle;					// ���C�g�}�b�v�̃n���h��
		int iLightMapScreenHandle_DownScale;		// ���C�g�}�b�v(1/8�k��)�̃n���h��
		int iLightMapScreenHandle_Gauss;			// ���C�g�}�b�v(�ڂ���)�̃n���h��
		int iMainScreenHandle;						// ���C����ʂ̃n���h��
		int iMainScreenEffectHandle;				// ���C�����(��ʃG�t�F�N�g�p)�̃n���h��
		// �V���h�E�}�b�v�n���h��
		int	iShadowMapScreenHandle;					// �V���h�E�}�b�v�̃n���h��
		// �}�X�N�n���h��
		int iMotionBlurMaskHandle;					// ���[�V�����u���[�p�̃}�X�N�n���h��
		// �V�F�[�_�[�n���h��
		int iSpeedLineShaderHandle;					// �W�����p�̃V�F�[�_�[�n���h��
};


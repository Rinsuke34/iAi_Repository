/* 2025.01.16 �t�@�C���쐬 ��򕗏� */
/* 2025.03.06 �e�r�듹	�J�������䏈���C�� */

#pragma once
#include "AppFrame.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Model.h"
#include "DataList_StageStatus.h"
#include "DataList_Option.h"

/* �V�[�� */
#include "SceneGameOver.h"
#include "SceneStageClear.h"
#include "SceneResult.h"
#include "SceneEdit.h"
#include "ScenePause.h"
#include "SceneUi_Crosshairs.h"
#include "SceneUi_Combo.h"
#include "SceneUi_Hp.h"
#include "SceneUi_Kunai.h"
#include "SceneUi_Debug.h"
#include "SceneUi_Blood.h"
#include "SceneUi_Edit.h"

/* ��ʃG�t�F�N�g */
#include "ScreenEffect_Damage.h"

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

		/* �Œ�J�����ԍ��̐ݒ� */
		void SetNowCameraFixedPositionNo(int iNowCameraFixedPositionNo)	{ this->iNowCameraFixedPositionNo = iNowCameraFixedPositionNo; }	// ���݂̃J�����Œ�ԍ��̐ݒ�

		/* �Œ�J�����ԍ��̎擾 */
		int	iGetNowCameraFixedPositionNo()	{ return this->iNowCameraFixedPositionNo; };		// ���݂̃J�����Œ���W�ԍ�
		int	iGetMaxCameraFixedPositionNo()	{ return this->iMaxCameraFixedPositionNo; };		// �J�����Œ���W�ԍ�����

	private:
		/* �g�p����f�[�^���X�g */
		DataList_Object*		ObjectList;			// �I�u�W�F�N�g�Ǘ�
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[��ԊǗ�
		DataList_Model*			ModelList;			// 3D���f���Ǘ�
		DataList_StageStatus*	StageStatusList;	// �X�e�[�W��ԊǗ�
		DataList_Option*		OptionList;			// �I�v�V�����ݒ�Ǘ�

		/* �֐� */
		void	Process_Main();			// �v�Z(���C���̏���)
		void	Process_StageClear();	// �v�Z(�X�e�[�W�N���A���̏���)
		void	SetupShadowMap();		// �V���h�E�}�b�v�̐ݒ�
		void	SetupLightMap();		// ���C�g�}�b�v�̐ݒ�
		void	SetupMainScreen();		// ���C���̕`�ʏ���
		void	SetupEffectScreen();	// �G�t�F�N�g�̕`�ʏ���
		void	SetupScreenEffects();	// ��ʃG�t�F�N�g
		void	SetCamera_Setup();		// �J�����ݒ菀��
		void	SetCmaera();			// �J�����ݒ�

		/* �J�������[�h�֘A */
		void	CameraRotateUpdata(int iCameraType);	// ���͂ɂ��J������]�ʎ擾
		void	SetCamera_Free();						// �J�����ݒ�(�t���[)
		void	SetCamera_Aim_Melee();					// �J�����ݒ�(�\��(�ߐڍU���\��))
		void	SetCamera_Aim_Kunai();					// �J�����ݒ�(�\��(�N�i�C�\��))
		void	SetCamera_Title();						// �J�����ݒ�(�^�C�g��)
		void	SetCamera_StageClear();					// �J�����ݒ�(�X�e�[�W�N���A)
		void	CameraSmoothing(int iCameraPositionLeapCountMax);	// �J�����␳						/* 2025.03.06 �e�r�듹	�J�������䏈���C�� */

		/* �f�o�b�O�֘A */
		void	DrawDebug();						// �f�o�b�O�`��

		/* �ϐ� */
		/* �`�ʉ�ʊ֘A */
		// ���C�g�}�b�v�p�摜�n���h��
		int	iLightMapScreenHandle;					// ���C�g�}�b�v�̃n���h��
		int iLightMapScreenHandle_DownScale;		// ���C�g�}�b�v(1/8�k��)�̃n���h��
		int iLightMapScreenHandle_Gauss;			// ���C�g�}�b�v(�ڂ���)�̃n���h��
		int iMainScreenHandle;						// ���C����ʂ̃n���h��
		// �V���h�E�}�b�v�n���h��
		int	iShadowMapScreenHandle;					// �V���h�E�}�b�v�̃n���h��

		/* �J�����֘A */
		CAMERA_FIXED_POSITION_INFO	vecCameraPositionInfo[CAMERA_FIXED_POSITION_MAX];	// �J�����Œ���W���
		int							iNowCameraFixedPositionNo;							// ���݂̃J�����Œ���W�ԍ�
		int							iMaxCameraFixedPositionNo;							// �J�����Œ���W�ԍ�����

		/* �g�p����摜�̃n���h�� */
		int*						piGrHandle_ResultFrame;								// ���U���g��ʂ̃t���[��

		/* ���̑� */
		int							iStageClear_Count;									// �X�e�[�W�N���A���̏����Ŏg�p����J�E���g
		int							iBlendAlpha_StageClear_Fadein;						// �X�e�[�W�N���A���̃t�F�[�h�C���̃A���t�@�l(0�`255)
};


/* 2025.01.16 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Model.h"

/* �V�[�� */
#include "SceneEdit.h"

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

		virtual void	LoadMapData(int iStageNo);		// �}�b�v�f�[�^�̃��[�h

	private:
	protected:
		/* �g�p����f�[�^���X�g */
		// ����f�[�^���X�g�T�[�o�[����擾����͔̂�����Ȃ��߁A�����ŕۑ����Ă���
		DataList_Object*		ObjectList;			// �I�u�W�F�N�g�Ǘ�
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[��ԊǗ�
		DataList_Model*			ModelList;			// 3D���f���Ǘ�

		/* �֐� */
		virtual void	SetupShadowMap();				// �V���h�E�}�b�v�̐ݒ�
		virtual void	SetupLightMap();				// ���C�g�}�b�v�̐ݒ�
		virtual void	SetCamera();					// �J�����ݒ�

		/* �J�����֘A */
		void	SetCamera_Free();					// �J�����ݒ�(�t���[���[�h)

		/* �f�o�b�O�֘A */
		void	DrawDebug();						// �f�o�b�O�`��

		/* �`�ʉ�ʊ֘A */
		int	iShadowMapScreenHandle;					// �V���h�E�}�b�v�̃n���h��
		int	iLightMapScreenHandle;					// ���C�g�}�b�v�̃n���h��
		int iLightMapScreenHandle_DownScale;		// ���C�g�}�b�v(1/8�k��)�̃n���h��
		int iLightMapScreenHandle_Gauss;			// ���C�g�}�b�v(�ڂ���)�̃n���h��

		/* �}�b�v���(��) */
		// ���f�[�^���X�g�쐬�\��
		bool bEditDrawFlg;							// �G�f�B�b�g�`�ʃt���O
		bool bGoalFlg;								// �S�[���t���O
};


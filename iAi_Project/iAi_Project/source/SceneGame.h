/* 2024.12.XX YYYY ZZZZ */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Model.h"

/* �V�[���u�Q�[���v�̐錾 */

// �V�[�� "�Q�[�����"
class SceneGame : public SceneBase
{
	public:
		SceneGame();							// �R���X�g���N�^
		virtual ~SceneGame();					// �f�X�g���N�^

		void	Process()	override;			// �v�Z
		void	Draw()		override;			// �`��

	private:
		/* �g�p����f�[�^���X�g */
		// ����f�[�^���X�g�T�[�o�[����擾����͔̂�����Ȃ��߁A�����ŕۑ����Ă���
		DataList_Object*		ObjectList;				// �I�u�W�F�N�g�Ǘ�
		DataList_PlayerStatus*	PlayerStatusList;		// �v���C���[��ԊǗ�
		DataList_Model*			ModelList;				// 3D���f���Ǘ�

		/* �֐� */
		void	LoadMapData();						// �}�b�v�f�[�^�̃��[�h
		void	SetupShadowMap();					// �V���h�E�}�b�v�̐ݒ�
		void	SetupLightMap();					// ���C�g�}�b�v�̐ݒ�
		void	SetCamera();						// �J�����ݒ�

		/* �J�����֘A */
		void	SetCamera_Free();					// �J�����ݒ�(�t���[���[�h)

		/* �f�o�b�O�֘A */
		void	DrawDebug();						// �f�o�b�O�`��

		/* �`�ʉ�ʊ֘A */
		int	iShadowMapScreenHandle;					// �V���h�E�}�b�v�̃n���h��
		int	iLightMapScreenHandle;					// ���C�g�}�b�v�̃n���h��
		int iLightMapScreenHandle_DownScale;		// ���C�g�}�b�v(1/8�k��)�̃n���h��
		int iLightMapScreenHandle_Gauss;			// ���C�g�}�b�v(�ڂ���)�̃n���h��

	protected:
};

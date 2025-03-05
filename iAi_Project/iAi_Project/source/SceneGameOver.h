/* 2025.02.20 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_StageStatus.h"
#include "DataList_Image.h"

/* �V�[�� */
#include "SceneAddTitleSetup.h"

/* �V�[��"�Q�[���I�[�o�["�N���X�̐錾 */

// �V�[��"�Q�[���I�[�o�["
class SceneGameOver : public SceneBase
{
	public:
		SceneGameOver();						// �R���X�g���N�^
		virtual ~SceneGameOver();				// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_StageStatus* StageStatusList;	// �Q�[����ԊǗ�

		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_GameOver;				// �Q�[���I�[�o�[

		/* �֐� */
		void	Process_Main();					// ���C������

		/* �ϐ� */
		int		iBlendAlpha;					// �`�ʂ���摜�̃A���t�@�l(0�`255)
};

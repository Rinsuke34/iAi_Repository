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
		virtual ~SceneGameOver() {};			// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_StageStatus* StageStatusList;	// �Q�[����ԊǗ�

		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_GameOver;				// �Q�[���I�[�o�[
		int* piGrHandle_Window_GameOver;		// �E�B���h�E(���g���C)
		int* piGrHandle_Window_GameOverCheck;	// �E�B���h�E(���g���C�x��)
		int* apiGrHandle_SkipWindow_Yes[2];		// �X�L�b�v�m�FYES(0:�I��/1:��I��)
		int* apiGrHandle_SkipWindow_No[2];		// �X�L�b�v�m�FNO(0:�I��/1:��I��)

		/* �ϐ� */
		int		iBlendAlpha;					// �`�ʂ���摜�̃A���t�@�l(0�`255)
		int		iDrawPhase;						// �`�ʃt�F�C�Y(0:�Q�[���I�[�o�[, 1:���g���C�m�F, 2:���g���C�ŏI�m�F)
		bool	bSelectYes;						// YES��I�𒆂ł��邩(�X�L�b�v���)
};

/* 2025.03.24 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"

/* �f�[�^���X�g */
#include "DataList_Image.h"
#include "DataList_Option.h"
#include "DataList_PlayerStatus.h"
#include "DataList_StageStatus.h"

/* UI(�������)�N���X�̐錾 */

// UI(�������)�N���X
class SceneUi_OperationInstructions : public SceneBase
{
	public:
		SceneUi_OperationInstructions();				// �R���X�g���N�^
		virtual ~SceneUi_OperationInstructions() {};	// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_Option*		OptionList;			// �I�v�V�����ݒ�Ǘ�
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[��ԊǗ�
		DataList_StageStatus*	StatusStatusList;	// �X�e�[�W��ԊǗ�

		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_Base[2];		// ��������摜�x�[�X(0:�R���g���[���[�A1:�L�[�{�[�h)
		int* piGrHandle_Attack[2];		// �ʏ펞��������摜(0:�R���g���[���[�A1:�L�[�{�[�h)
		int* piGrHandle_Kunai[2];		// �N�i�C�\������������摜(0:�R���g���[���[�A1:�L�[�{�[�h)

		/* �ϐ� */
		int iDrawTypeNo;				// �`��^�C�v�ԍ�(0:�R���g���[���[�A1:�L�[�{�[�h)
};

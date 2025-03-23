/* 2025.01.28 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"

/* �f�[�^���X�g */
#include "DataList_PlayerStatus.h"
#include "DataList_StageStatus.h"
#include "DataList_Image.h"

/* UI(�N�i�C)�N���X�̐錾 */

// UI(�N�i�C)�N���X
class SceneUi_Kunai : public SceneBase
{
	public:
		SceneUi_Kunai();					// �R���X�g���N�^
		virtual ~SceneUi_Kunai();			// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_PlayerStatus*	PlayerStatusList;		// �v���C���[��ԊǗ�
		DataList_StageStatus*	StageStatusList;		// �Q�[����ԊǗ�

		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_Kunai_Frame;					// �N�i�C�t���[��
};

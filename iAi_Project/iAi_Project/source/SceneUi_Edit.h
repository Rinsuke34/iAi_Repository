/* 2025.02.11 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"

/* �f�[�^���X�g */
#include "DataList_GameResource.h"

/* UI(�G�f�B�b�g)�N���X�̐錾 */

// UI(�G�f�B�b�g)�N���X
class SceneUi_Edit : public SceneBase
{
	public:
		SceneUi_Edit();					// �R���X�g���N�^
		virtual ~SceneUi_Edit();		// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_GameResource* GameResourceList;	// �Q�[�������\�[�X�Ǘ�

		/* ���݂̃G�f�B�b�g�f�[�^ */
		EDIT_INFORMATION NowEditData[EDIT_MAX];		// ���݂̃G�f�B�b�g�f�[�^

		/* �g�p����摜�̃n���h�� */

};

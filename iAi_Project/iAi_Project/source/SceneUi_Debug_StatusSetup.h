/* 2025.03.16 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_PlayerStatus.h"

/* UI(�f�o�b�O���j���[/�X�e�[�^�X����)�N���X�̐錾 */

// UI(�f�o�b�O���j���[/�X�e�[�^�X����)�N���X
class SceneUi_Debug_StatusSetup : public SceneBase
{
	public:
		SceneUi_Debug_StatusSetup();				// �R���X�g���N�^
		virtual ~SceneUi_Debug_StatusSetup();		// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_PlayerStatus*	PlayerStatusList;	// �X�e�[�W��ԊǗ�

		/* �ϐ� */
		int						iSelectItem;		// �I�𒆂̍��ڂ̔ԍ�
		bool					bSelectFlg;			// �I����Ԃł��邩�̃t���O
};

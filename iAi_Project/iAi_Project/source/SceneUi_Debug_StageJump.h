/* 2025.03.11 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_StageStatus.h"

/* UI(�f�o�b�O���j���[/�X�e�[�W�W�����v)�N���X�̐錾 */

// UI(�f�o�b�O���j���[/�X�e�[�W�W�����v)�N���X
class SceneUi_Debug_StageJump : public SceneBase
{
	public:
		SceneUi_Debug_StageJump();					// �R���X�g���N�^
		virtual ~SceneUi_Debug_StageJump() {};		// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_StageStatus* StageStatusList;	// �X�e�[�W��ԊǗ�

		/* �ϐ� */
		int iJumpStageNo;	// �X�e�[�W�ԍ�
};

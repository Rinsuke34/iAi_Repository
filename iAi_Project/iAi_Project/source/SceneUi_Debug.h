/* 2025.01.27 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* UI(�f�o�b�O���j���[)�N���X�̐錾 */

// UI(�f�o�b�O���j���[)�N���X
class SceneUi_Debug : public SceneBase
{
	public:
		SceneUi_Debug();					// �R���X�g���N�^
		virtual ~SceneUi_Debug() {};		// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �֐� */
		void	GetInput();		// �v���C���[�̓��͎擾

		/* �ϐ� */
		int		iSelectNo;		// �I�𒆂̍��ڂ̔ԍ�
};

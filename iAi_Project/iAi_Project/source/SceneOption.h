/* 2025.03.05 �t�@�C���ǉ� ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �V�[���u�I�v�V�����v�̐錾 */

// �V�[�� "�I�v�V�������"
class SceneOption : public SceneBase
{
	public:
		SceneOption();							// �R���X�g���N�^
		virtual ~SceneOption();					// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:

	protected:
};

/* 2024.12.XX YYYY ZZZZ */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �V�[���u�z�[���v�̐錾 */

// �V�[�� "�z�[�����"
class SceneHome : public SceneBase
{
	public:
		SceneHome();							// �R���X�g���N�^
		virtual ~SceneHome();					// �f�X�g���N�^

		void	Initialization()	override;	// ������
		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:

	protected:
};

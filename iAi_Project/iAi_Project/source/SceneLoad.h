/* 2024.12.XX YYYY ZZZZ */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �V�[���u���[�h�v�̐錾 */

// �V�[�� "���[�h���"
class SceneLoad : public SceneBase
{
	public:
		SceneLoad();			// �R���X�g���N�^
		virtual ~SceneLoad();	// �f�X�g���N�^

		void	Initialization()	override;	// ������
		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:

	protected:
};

#pragma once
#include "AppFrame.h"

// �V�[�� "�^�C�g�����"
class SceneTitle : public SceneBase
{
	public:
		SceneTitle();							// �R���X�g���N�^
		virtual ~SceneTitle();					// �f�X�g���N�^

		void	Process()	override;			// �v�Z
		void	Draw()		override;			// �`��

	private:

	protected:
};

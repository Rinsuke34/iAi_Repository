#pragma once
#include "AppFrame.h"

// �V�[�� "�V�[�����[�h���"
class SceneLoad : public SceneBase
{
	public:
		SceneLoad();							// �R���X�g���N�^
		virtual ~SceneLoad();				// �f�X�g���N�^

		void	Process()	override;			// �v�Z
		void	Draw()		override;			// �`��

	private:

	protected:
};

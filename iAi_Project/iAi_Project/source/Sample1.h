#pragma once
#include "AppFrame.h"

// �V�[�� "�V�[���T���v��"
class SceneSample : public SceneBase
{
	public:
		SceneSample();							// �R���X�g���N�^
		virtual ~SceneSample();					// �f�X�g���N�^

		void	Process()	override;			// �v�Z
		void	Draw()		override;			// �`��

	private:

	protected:
};

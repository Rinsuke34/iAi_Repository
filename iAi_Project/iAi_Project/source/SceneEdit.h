/* 2025.01.19 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �V�[��"�G�f�B�b�g"�N���X�̐錾 */

// �V�[��"�G�f�B�b�g"
class SceneEdit : public SceneBase
{
	public:
		SceneEdit();							// �R���X�g���N�^
		virtual ~SceneEdit();					// �f�X�g���N�^

		void	Initialization()	override;	// ������
		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
	protected:
};

/* 2024.12.21 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �V�[���u���͐ݒ�v�̐錾 */

// �V�[�� "�I�v�V���� - ���͐ݒ���"
class SceneInputConfig : public SceneBase
{
	public:
		SceneInputConfig();						// �R���X�g���N�^
		virtual ~SceneInputConfig();			// �f�X�g���N�^

		void	Initialization()	override;	// ������
		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:

	protected:
};

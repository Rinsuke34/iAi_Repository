/* 2025.01.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �e�X�g�p�G�t�F�N�g�N���X */

// �G�t�F�N�g�N���X
class TestEffect : public EffectBase
{
	public:
		TestEffect();				// �R���X�g���N�^
		virtual ~TestEffect();		// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V

	private:
	protected:
		/* �֐� */

		/* �ϐ� */

		int iDeleteCount;
};

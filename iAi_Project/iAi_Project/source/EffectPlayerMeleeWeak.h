/* 2025.01.24 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �ߐڍU��(��)�G�t�F�N�g�N���X�̐錾 */

// �ߐڍU��(��)�G�t�F�N�g�N���X
class EffectPlayerMeleeWeak : public EffectBase
{
	public:
		EffectPlayerMeleeWeak();				// �R���X�g���N�^
		virtual ~EffectPlayerMeleeWeak();		// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V

	private:
	protected:
		/* �֐� */

		/* �ϐ� */
		int iDeleteCount;		// �N���X�폜�܂ł̃J�E���g
};


/* 2025.01.24 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �ߐڍU��(��)�N���X�̐錾 */

// �ߐڍU��(��)
class BulletPlayerMeleeWeak : public BulletBase
{
	public:
		BulletPlayerMeleeWeak();				// �R���X�g���N�^
		virtual ~BulletPlayerMeleeWeak();		// �f�X�g���N�^

		virtual void	Initialization()	override;	// ������
		virtual void	Update()			override;	// �X�V
		virtual void	Draw()				override;	// �`��
		virtual void	BloomDraw()			override;	// �����`��

	private:
	protected:
	
};

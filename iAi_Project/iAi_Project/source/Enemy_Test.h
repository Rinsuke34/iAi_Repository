/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �e�X�g�p�G�N���X */

// �G�l�~�[�x�[�X�N���X
class TestEnemy : public EnemyBase
{
	public:
		TestEnemy();				// �R���X�g���N�^
		virtual ~TestEnemy();		// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V
		virtual void	Draw()				override;		// �`��
		virtual void	BloomDraw()			override {};	// �����`��

	private:
	protected:
		/* �֐� */

		/* �ϐ� */
};

/* 2025.01.27 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"
#include "PublicInclude.h"

/* ��{�G�l�~�[�N���X�̐錾 */

// ��{�G�l�~�[�N���X
class EnemyBasic : public EnemyBase
{
	public:
		EnemyBasic();				// �R���X�g���N�^
		virtual ~EnemyBasic() {};	// �f�X�g���N�^

		int		iGetPlayerLockOnType()	{ return this->iPlayerLockOnType; }		// �v���C���[���_�ł̃��b�N�I����Ԃ��擾

		void	SetPlayerLockOnType(int iPlayerLockOnType)	{ this->iPlayerLockOnType = iPlayerLockOnType; }	// �v���C���[���_�ł̃��b�N�I����Ԃ�ݒ�

	private:
	protected:
		/* �ϐ� */
		int		iPlayerLockOnType;	// �v���C���[���_�ł̃��b�N�I�����
};

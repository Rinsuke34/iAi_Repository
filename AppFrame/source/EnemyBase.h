/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "CharacterBase.h"

/* ���ׂẴG�l�~�[�̃x�[�X�ƂȂ�N���X�̐錾 */

// �G�l�~�[�x�[�X�N���X
class EnemyBase : public CharacterBase
{
	public:
		EnemyBase();				// �R���X�g���N�^
		virtual ~EnemyBase() {};	// �f�X�g���N�^

		int		iGetMaxHP()				{ return this->iMaxHp; }			// �ő�HP���擾
		int		iGetNowHP()				{ return this->iNowHp; }			// ����HP���擾

		void	SetMaxHP(int iMaxHp)						{ this->iMaxHp				= iMaxHp; }					// �ő�HP��ݒ�
		void	SetNowHP(int iNowHP)						{ this->iNowHp				= iNowHP; }					// ����HP��ݒ�

	private:
	protected:
		/* �֐� */

		/* �ϐ� */
		int		iMaxHp;				// �ő�HP
		int		iNowHp;				// ����HP
};

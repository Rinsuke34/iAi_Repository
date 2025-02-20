/* 2025.01.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "ObjectBase.h"
#include <EffekseerForDXLib.h>

/* ���ׂẴG�t�F�N�g�̃x�[�X�ƂȂ�N���X�̐錾 */

// �G�t�F�N�g�x�[�X�N���X
class EffectBase : public ObjectBase
{
	public:
		EffectBase();			// �R���X�g���N�^
		virtual ~EffectBase();	// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update();							// �X�V
		virtual void	Draw();								// �`��

		int		iGetEffectHandle()					{ return this->iEffectHandle; }				// �G�t�F�N�g�n���h���擾

		void	SetEffectHandle(int iEffectHandle)	{ this->iEffectHandle = iEffectHandle; }	// �G�t�F�N�g�n���h���ݒ�

		void Effect_PosUpdate();						// �G�t�F�N�g�ʒu�X�V
		void Effect_RotationUpdate();					// �G�t�F�N�g��]�ʍX�V
		void Effect_ScaleUpdate();						// �G�t�F�N�g�g�嗦�X�V

	private:
		/* �֐� */

		/* �ϐ� */
		int iEffectHandle;		// �G�t�F�N�g�n���h��
};

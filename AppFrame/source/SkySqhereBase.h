/* 2025.02.06 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "ObjectBase.h"

/* ���ׂẴX�J�C�X�t�B�A(��Ƃ��ĕ`�ʂ��鋅��)�̃x�[�X�ƂȂ�N���X�̐錾 */

// �X�J�C�X�t�B�A�x�[�X�N���X
class SkySqhereBase : public ObjectBase
{
	public:
		SkySqhereBase();				// �R���X�g���N�^
		virtual ~SkySqhereBase();	// �f�X�g���N�^

		virtual void	Draw()				override;	// �`��

		int		iGetModelHandle()					{ return this->iModelHandle; };				// ���f���n���h�����擾

		void	SetModelHandle(int iModelHandle)	{ this->iModelHandle = iModelHandle; };		// ���f���n���h����ݒ�

	private:
	protected:
		/* �ϐ� */
		int						iModelHandle;			// ���f���n���h��
};

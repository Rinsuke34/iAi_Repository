/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "ObjectBase.h"

/* ���ׂẴA�N�^�̃x�[�X�ƂȂ�N���X�̐錾 */

// �A�N�^�x�[�X�N���X
class ActorBase : public ObjectBase
{
	public:
		ActorBase();			// �R���X�g���N�^
		virtual ~ActorBase();	// �f�X�g���N�^

		virtual void	Update() {};	// �X�V
		virtual void	Draw() {};		// �`��

		VECTOR	vecGetMovement()	{ return this->vecMovement; };		// �ړ��ʂ��擾
		int		iGetModelHandle()	{ return this->iModelHandle; };		// ���f���n���h�����擾

		void	SetMovement(VECTOR vecMovement)		{ this->vecMovement		= vecMovement; };	// �ړ��ʂ�ݒ�
		void	SetModelHandle(int iModelHandle)	{ this->iModelHandle	= iModelHandle; };	// ���f���n���h����ݒ�

	private:
	protected:
		/* �֐� */

		/* �ϐ� */
		VECTOR	vecMovement;	// �ړ���
		int		iModelHandle;	// ���f���n���h��
};

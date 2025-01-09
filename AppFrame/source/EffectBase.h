/* 2025.01.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "ActorBase.h"
#include "EffekseerForDXLib.h"

/* ���ׂẴG�t�F�N�g�̃x�[�X�ƂȂ�N���X�̐錾 */

// �G�t�F�N�g�x�[�X�N���X
class EffectBase : public ActorBase
{
	public:
		EffectBase();			// �R���X�g���N�^
		virtual ~EffectBase();	// �f�X�g���N�^

		virtual void	Update() {};		// �X�V
		virtual void	Draw() {};			// �`��

		int	iGetEffectHandle()	{ return this->iEffectHandle; };	// �G�t�F�N�g�n���h�����擾
		int	iGetCount()			{ return this->iCount; };			// �G�t�F�N�g�̃J�E���g���擾

		void SetEffectHandle(int iEffectHandle)	{ this->iEffectHandle	= iEffectHandle; };		// �G�t�F�N�g�n���h����ݒ�
		void SetCount(int iCount)				{ this->iCount			= iCount; };			// �G�t�F�N�g�̃J�E���g��ݒ�

	private:
	protected:
		/* �֐� */

		/* �ϐ� */
		int iEffectHandle;	// �G�t�F�N�g�n���h��
		int iCount;			// �G�t�F�N�g�̃J�E���g
};

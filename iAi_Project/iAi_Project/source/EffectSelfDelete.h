/* 2025.01.26 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* ���Ԍo�߂ō폜�����G�t�F�N�g�N���X�̐錾 */
// ���I�u�W�F�N�g�Ɉˑ����Ȃ��G�t�F�N�g�Ŏg�p

// �G�t�F�N�g�N���X(�����폜)
class EffectSelfDelete : public EffectBase
{
	public:
		EffectSelfDelete();					// �R���X�g���N�^
		virtual ~EffectSelfDelete() {};		// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V

		int 	iGetDeleteCount()	{ return this->iDeleteCount; };							// �폜�܂ł̃J�E���g���擾

		void	SetDeleteCount(int iDeleteCount)	{ this->iDeleteCount = iDeleteCount; };	// �폜�܂ł̃J�E���g��ݒ�

	protected:
	private:
		/* �ϐ� */
		int iDeleteCount;		// �N���X�폜�܂ł̃J�E���g
};

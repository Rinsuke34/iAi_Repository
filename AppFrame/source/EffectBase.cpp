/* 2025.01.08 ��򕗏� �t�@�C���쐬 */

#include "EffectBase.h"

/* ���ׂẴG�t�F�N�g�̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
EffectBase::EffectBase() : ActorBase()
{
	/* ������ */
	this->iEffectHandle	= -1;	// �G�t�F�N�g�n���h��
	this->iCount		= 0;	// �G�t�F�N�g�̃J�E���g
}

// �f�X�g���N�^
EffectBase::~EffectBase()
{
	/* �G�t�F�N�g�̃��\�[�X���폜 */
	DeleteEffekseerEffect(this->iEffectHandle);
}

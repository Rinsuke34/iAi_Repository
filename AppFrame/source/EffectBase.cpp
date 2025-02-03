/* 2025.01.08 ��򕗏� �t�@�C���쐬 */

#include "EffectBase.h"

/* ���ׂẴG�t�F�N�g�̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
EffectBase::EffectBase() : ObjectBase()
{
	/* ������ */
	this->iEffectHandle		= -1;	// �G�t�F�N�g�n���h��
}

// �f�X�g���N�^
EffectBase::~EffectBase()
{
	/* �G�t�F�N�g�̃��\�[�X���폜 */
	StopEffekseer3DEffect(this->iEffectHandle);
}

// ������
void EffectBase::Initialization()
{
	/* �G�t�F�N�g���W�X�V */
	Effect_PosUpdate();

	/* �G�t�F�N�g��]�ʍX�V */
	Effect_RotationUpdate();
}

// �X�V
void EffectBase::Update()
{
	/* �G�t�F�N�g���W�X�V */
	Effect_PosUpdate();

	/* �G�t�F�N�g��]�ʍX�V */
	Effect_RotationUpdate();
}


// �`��
void EffectBase::Draw()
{
	/* �G�t�F�N�g��`�� */
	DrawEffekseer3D_Draw(this->iEffectHandle);
}

// �G�t�F�N�g�ʒu�X�V
void EffectBase::Effect_PosUpdate()
{
	/* �G�t�F�N�g�̕`�ʍ��W�����݂�vecPosition�ɐݒ� */
	SetPosPlayingEffekseer3DEffect(this->iEffectHandle, this->vecPosition.x, this->vecPosition.y, this->vecPosition.z);
}

// �G�t�F�N�g��]�ʍX�V
void EffectBase::Effect_RotationUpdate()
{
	/* �G�t�F�N�g�̉�]�ʂ����݂�vecRotation�ɐݒ� */
	SetRotationPlayingEffekseer3DEffect(this->iEffectHandle, this->vecRotation.x, this->vecRotation.y, this->vecRotation.z);
}

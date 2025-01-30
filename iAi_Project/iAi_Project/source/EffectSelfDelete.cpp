/* 2025.01.26 ��򕗏� �t�@�C���쐬 */

#include "EffectSelfDelete.h"

/* �蓮�ō폜�^�C�~���O��ݒ肷��G�t�F�N�g�N���X�̒�` */
// �R���X�g���N�^
EffectSelfDelete::EffectSelfDelete() : EffectBase()
{
	/* ������ */
	this->iDeleteCount = 0;
}

// ������
void EffectSelfDelete::Initialization()
{
	/* �G�t�F�N�g���W�X�V */
	this->Effect_PosUpdate();

	/* �G�t�F�N�g��]�ʍX�V */
	Effect_RotationUpdate();

	/* �G�t�F�N�g�Đ��J�n */
	this->iEffectHandle_Play = PlayEffekseer3DEffect(this->iEffectHandle_Resource);
}

// �X�V
void EffectSelfDelete::Update()
{
	/* �폜�J�E���g���m�F */
	if (this->iDeleteCount > 0)
	{
		/* �J�E���g�����Z */
		this->iDeleteCount--;
	}
	else
	{
		/* �폜�t���O��L���� */
		this->bDeleteFlg = true;
	}

	/* �G�t�F�N�g���W�X�V */
	this->Effect_PosUpdate();

	/* �G�t�F�N�g��]�ʍX�V */
	Effect_RotationUpdate();
}

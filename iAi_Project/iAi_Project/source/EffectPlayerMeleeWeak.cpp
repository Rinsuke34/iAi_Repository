/* 2025.01.24 ��򕗏� �t�@�C���쐬 */

#include "EffectPlayerMeleeWeak.h"

/* �ߐڍU��(��)�G�t�F�N�g�N���X�̒�` */

// �R���X�g���N�^
EffectPlayerMeleeWeak::EffectPlayerMeleeWeak()
{

}

// �f�X�g���N�^
EffectPlayerMeleeWeak::~EffectPlayerMeleeWeak()
{

}

// ������
void EffectPlayerMeleeWeak::Initialization()
{
	/* �G�t�F�N�g�Đ��J�n */
	this->iEffectHandle_Play = PlayEffekseer3DEffect(this->iEffectHandle_Resource);

	/* ���W���v���C���[�ʒu+100�̈ʒu�ɐݒ� */
	this->vecPosition = VAdd(this->vecPosition, VGet(0.f, 100.f, 0.f));

	/* �N���X�폜�܂ł̃J�E���g�ݒ� */
	// ���Ƃ肠����60�t���[���ō폜
	this->iDeleteCount	= 60;

	/* ���W�X�V */
	this->Effect_PosUpdate();
}

// �X�V
void EffectPlayerMeleeWeak::Update()
{
	/* �N���X�폜�܂ł̃J�E���g��0�ȉ��ɂȂ�����폜�t���O�𗧂Ă� */
	if (this->iDeleteCount <= 0)
	{
		this->bDeleteFlg = true;
	}
	/* �N���X�폜�܂ł̃J�E���g�����Z */
	this->iDeleteCount--;
}

/* 2025.02.24 ��򕗏� �t�@�C���쐬 */

#include "ScreenEffect_Base.h"

/* ���ׂẲ�ʃG�t�F�N�g�̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
ScreenEffect_Base::ScreenEffect_Base()
{
	/* ������ */
	this->bDeleteFlg	= false;
	this->iDeleteTime	= 0;
}

// �X�V
void ScreenEffect_Base::Update(int iGrHandle_Screen)
{
	// ����
	// iGrHandle_Screen : �`�ʂ���摜�̃n���h��

	/* ��ʃG�t�F�N�g�`�� */
	ScreenEffectDraw(iGrHandle_Screen);

	/* �G�t�F�N�g�̎c�莞�Ԃ��X�V */
	this->iDeleteTime--;

	/* �G�t�F�N�g�̎c�莞�Ԃ�0�ȉ��ɂȂ������m�F */
	if (this->iDeleteTime <= 0)
	{
		// 0�ȉ��ɂȂ����ꍇ
		/* �폜�t���O��L���� */
		this->bDeleteFlg = true;
	}
}
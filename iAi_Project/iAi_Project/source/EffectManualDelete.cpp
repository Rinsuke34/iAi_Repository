/* 2025.01.26 ��򕗏� �t�@�C���쐬 */

#include "EffectManualDelete.h"

/* �蓮�ō폜�^�C�~���O��ݒ肷��G�t�F�N�g�N���X�̒�` */
// �R���X�g���N�^
EffectManualDelete::EffectManualDelete() : EffectBase()
{

}

// ������
void EffectManualDelete::Initialization()
{
	/* �G�t�F�N�g���W�X�V */
	Effect_PosUpdate();

	/* �G�t�F�N�g��]�ʍX�V */
	Effect_RotationUpdate();

	/* �G�t�F�N�g�Đ��J�n */
	this->iEffectHandle_Play = PlayEffekseer3DEffect(this->iEffectHandle_Resource);	
}

// �X�V
void EffectManualDelete::Update()
{
	/* �G�t�F�N�g���W�X�V */
	Effect_PosUpdate();

	/* �G�t�F�N�g��]�ʍX�V */
	Effect_RotationUpdate();
}

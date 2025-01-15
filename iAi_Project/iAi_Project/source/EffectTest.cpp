
#include "EffectTest.h"

// �R���X�g���N�^
TestEffect::TestEffect() : EffectBase()
{
	iDeleteCount = 0;
}

// �f�X�g���N�^
TestEffect::~TestEffect()
{

}

// ������
void TestEffect::Initialization()
{
	/* �`�ʎ��Ԑݒ�(�Ƃ肠����) */
	iDeleteCount = 60 * 2;

	/* �G�t�F�N�g�Đ��J�n */
	this->iEffectHandle_Play = PlayEffekseer3DEffect(this->iEffectHandle_Resource);

	/* ���W�X�V */
	this->Effect_PosUpdate();
}

// �X�V
void TestEffect::Update()
{
	/* ���W�X�V */
	this->Effect_PosUpdate();

	if (iDeleteCount <= 0)
	{
		this->bDeleteFlg = true;
	}

	iDeleteCount--;
}

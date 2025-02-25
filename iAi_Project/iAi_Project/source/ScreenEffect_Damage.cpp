/* 2025.02.24 ��򕗏� �t�@�C���쐬 */

#include "ScreenEffect_Damage.h"

/* ���ׂẲ�ʃG�t�F�N�g�̃x�[�X�ƂȂ�N���X�̐錾 */

// �R���X�g���N�^
ScreenEffect_Damage::ScreenEffect_Damage() : ScreenEffect_Base()
{
	/* ������ */
	this->iDeleteTime				= DAMAGE_EFFECT_TIME;
	this->iEffectShiftChangeCount	= 0;
}

// ��ʃG�t�F�N�g�`��
void ScreenEffect_Damage::ScreenEffectDraw(int iGrHandle_Screen)
{
	// ����
	// iGrHandle_Screen : �`�ʂ���摜�̃n���h��

	/* �G�t�F�N�g�̃V�t�g�ʕύX�J�E���g���X�V */
	this->iEffectShiftChangeCount--;

	/* �V�t�g�ʕύX�J�E���g��0�����ɂȂ������m�F */
	if (this->iEffectShiftChangeCount <= 0)
	{
		// �V�t�g�ʕύX�J�E���g��0�����ɂȂ����ꍇ
		/* �V�t�g�ʕύX�J�E���g�����Z�b�g */
		this->iEffectShiftChangeCount = DAMAGE_EFFECT_SHIFT_CHANGE;

		/* �V�t�g�ʂ��X�V */
		this->stEffectShift.ix = GetRand(DAMAGE_EFFECT_SHIFT) - DAMAGE_EFFECT_SHIFT / 2;
		this->stEffectShift.iy = GetRand(DAMAGE_EFFECT_SHIFT) - DAMAGE_EFFECT_SHIFT / 2;
	}

	//int iEffectShift = static_cast<int>(DAMAGE_EFFECT_SHIFT * ((1.0 - static_cast<float>(this->iDeleteTime)) / DAMAGE_EFFECT_TIME));
	//iEffectShift = DAMAGE_EFFECT_SHIFT;

	/* �`�ʃu�����h���[�h��"�A���t�@�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_ADD, DAMAGE_EFFECT_ALPHA);
	
	/* �ԐF�����̂ݕ`�� */
	SetDrawBright(255, 0, 0);

	/* �摜��`�� */
	DrawExtendGraph(0 + this->stEffectShift.ix, 0 + this->stEffectShift.iy, SCREEN_SIZE_WIDE + this->stEffectShift.ix, SCREEN_SIZE_HEIGHT + this->stEffectShift.iy, iGrHandle_Screen, TRUE);

	/* �F�����̂ݕ`�� */
	SetDrawBright(0, 0, 255);

	/* �摜��`�� */
	DrawExtendGraph(0 - this->stEffectShift.iy, 0 - this->stEffectShift.iy, SCREEN_SIZE_WIDE - this->stEffectShift.ix, SCREEN_SIZE_HEIGHT + this->stEffectShift.iy, iGrHandle_Screen, TRUE);

	/* �`�ʐF�����Z�b�g */
	SetDrawBright(255, 255, 255);

	/* �`�ʃu�����h���[�h��"�m�[�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/* 2025.02.24 ��򕗏� �t�@�C���쐬 */

#include "ScreenEffect_Damage.h"

/* ���ׂẲ�ʃG�t�F�N�g�̃x�[�X�ƂȂ�N���X�̐錾 */

// �R���X�g���N�^
ScreenEffect_Damage::ScreenEffect_Damage() : ScreenEffect_Base()
{
	/* ������ */
	this->iDeleteTime = DAMAGE_EFFECT_TIME;
}

// ��ʃG�t�F�N�g�`��
void ScreenEffect_Damage::ScreenEffectDraw(int iGrHandle_Screen)
{
	// ����
	// iGrHandle_Screen : �`�ʂ���摜�̃n���h��

	/* �G�t�F�N�g�̃V�t�g�ʂ��X�V */
	//int iEffectShift = DAMAGE_EFFECT_SHIFT * (this->iDeleteTime / DAMAGE_EFFECT_TIME);
	//int iEffectShift = (DAMAGE_EFFECT_TIME - this->iDeleteTime) * DAMAGE_EFFECT_SHIFT;
	int iEffectShift = DAMAGE_EFFECT_SHIFT;

	/* �`�ʃu�����h���[�h��"�A���t�@�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, DAMAGE_EFFECT_ALPHA);

	/* �ԐF�����̂ݕ`�� */
	SetDrawBright(255, 0, 0);

	DrawExtendGraph(0 + iEffectShift, 0, SCREEN_SIZE_WIDE + iEffectShift, SCREEN_SIZE_HEIGHT, iGrHandle_Screen, TRUE);

	/* �F�����̂ݕ`�� */
	SetDrawBright(0, 0, 255);

	DrawExtendGraph(0 - iEffectShift, 0, SCREEN_SIZE_WIDE - iEffectShift, SCREEN_SIZE_HEIGHT, iGrHandle_Screen, TRUE);

	SetDrawBright(255, 255, 255);

	/* �`�ʃu�����h���[�h��"�m�[�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

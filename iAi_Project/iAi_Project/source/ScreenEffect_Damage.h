/* 2025.02.24 ��򕗏� �t�@�C���쐬 */

#ifndef SCREEN_EFFECT_DAMAGE_H
#define SCREEN_EFFECT_DAMAGE_H

#include "ScreenEffect_Base.h"

/* ���ׂẲ�ʃG�t�F�N�g�̃x�[�X�ƂȂ�N���X�̐錾 */

// ��ʃG�t�F�N�g�x�[�X�N���X
class ScreenEffect_Damage : public ScreenEffect_Base
{
	public:
		ScreenEffect_Damage();				// �R���X�g���N�^
		virtual ~ScreenEffect_Damage() {};	// �f�X�g���N�^

		void	ScreenEffectDraw(int iGrHandle_Screen)	override;	// ��ʃG�t�F�N�g�`��

	private:
		/* �ϐ� */
		int				iEffectShiftChangeCount;	// �G�t�F�N�g�̃V�t�g�ʕύX�J�E���g
		st2DPosition	stEffectShift;				// �G�t�F�N�g�̃V�t�g��
};

#endif
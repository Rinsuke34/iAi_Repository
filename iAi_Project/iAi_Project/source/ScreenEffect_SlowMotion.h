/* 2025.03.12 ��򕗏� �t�@�C���쐬 */

#ifndef SCREEN_EFFECT_SLOWMOTION_H
#define SCREEN_EFFECT_SLOWMOTION_H

#include "ScreenEffect_Base.h"

/* �f�[�^���X�g */
#include "DataList_StageStatus.h"

/* ��ʃG�t�F�N�g(�X���[���[�V����)�N���X�̐錾 */

// ��ʃG�t�F�N�g(�X���[���[�V����)�N���X
class ScreenEffect_SlowMotion : public ScreenEffect_Base
{
	public:
		ScreenEffect_SlowMotion();				// �R���X�g���N�^
		virtual ~ScreenEffect_SlowMotion() {};	// �f�X�g���N�^

		void	Update(int iGrHandle_Screen)			override;	// �X�V
		void	ScreenEffectDraw(int iGrHandle_Screen)	override;	// ��ʃG�t�F�N�g�`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_StageStatus* StageStatusList;	// �X�e�[�W��ԊǗ�
};

#endif
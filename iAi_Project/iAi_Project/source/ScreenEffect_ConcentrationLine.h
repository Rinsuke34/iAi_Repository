/* 2025.03.17 ��򕗏� �t�@�C���쐬 */

#ifndef SCREEN_EFFECT_CONCENTRATIONLINE_H
#define SCREEN_EFFECT_CONCENTRATIONLINE_H

#include "ScreenEffect_Base.h"

/* �f�[�^���X�g */
#include "DataList_Image.h"

/* ��ʃG�t�F�N�g(�W����)�N���X�̐錾 */

// ��ʃG�t�F�N�g(�W����)�N���X
class ScreenEffect_ConcentrationLine : public ScreenEffect_Base
{
	public:
		ScreenEffect_ConcentrationLine();				// �R���X�g���N�^
		virtual ~ScreenEffect_ConcentrationLine() {};	// �f�X�g���N�^

		void	ScreenEffectDraw(int iGrHandle_Screen)	override;	// ��ʃG�t�F�N�g�`��

	private:
		/* �g�p����摜�n���h�� */
		int*	apiGrHandle_ConcentrationLine[3];	// �W�����摜�n���h��(3���)

		/* �ϐ� */
		int		iEffectTypeChangeCount;				// �G�t�F�N�g��ޕύX�J�E���g
		int		iEffectType;						// �G�t�F�N�g���(3���)
};

#endif
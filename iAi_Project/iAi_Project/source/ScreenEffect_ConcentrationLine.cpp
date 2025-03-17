/* 2025.03.17 �t�@�C���ǉ� ��򕗏� */

#include "ScreenEffect_ConcentrationLine.h"

/* ��ʃG�t�F�N�g(�W����)�N���X�̒�` */
// �R���X�g���N�^
ScreenEffect_ConcentrationLine::ScreenEffect_ConcentrationLine() : ScreenEffect_Base()
{
	/* �摜�擾 */
	{
		/* "�摜�Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �W�����摜(3���)���擾 */
		this->apiGrHandle_ConcentrationLine[0] = ImageList->piGetImage("ScreenEffect/ConcentrationLine_1");
		this->apiGrHandle_ConcentrationLine[1] = ImageList->piGetImage("ScreenEffect/ConcentrationLine_2");
		this->apiGrHandle_ConcentrationLine[2] = ImageList->piGetImage("ScreenEffect/ConcentrationLine_3");
	}

	/* ������ */
	this->iEffectTypeChangeCount	= CONCENTRATIONLINE_EFFECT_CHANGE;
	this->iEffectType				= 0;
}

// ��ʃG�t�F�N�g�`��
void ScreenEffect_ConcentrationLine::ScreenEffectDraw(int iGrHandle_Screen)
{
	// ����
	// iGrHandle_Screen : �`�ʂ���摜�̃n���h��

	/* �G�t�F�N�g�̎�ޕύX�J�E���g���X�V */
	this->iEffectTypeChangeCount--;

	/* �G�t�F�N�g�̎�ޕύX�J�E���g��0�ȉ��ɂȂ������m�F */
	if (this->iEffectTypeChangeCount <= 0)
	{
		// �G�t�F�N�g�̎�ޕύX�J�E���g��0�ȉ��ɂȂ����ꍇ
		/* �G�t�F�N�g�̎�ޕύX�J�E���g�����Z�b�g */
		this->iEffectTypeChangeCount = CONCENTRATIONLINE_EFFECT_CHANGE;

		/* �G�t�F�N�g�̎�ނ��X�V */
		this->iEffectType++;

		/* �G�t�F�N�g�̎�ނ��ő�l�𒴂��Ă��邩�m�F */
		if (this->iEffectType >= CONCENTRATIONLINE_EFFECT_TYPE)
		{
			// �G�t�F�N�g�̎�ނ��ő�l�𒴂��Ă���ꍇ
			/* �G�t�F�N�g�̎�ނ����Z�b�g */
			this->iEffectType = 0;
		}
	}

	/* �`�ʃu�����h���[�h��"�A���t�@�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, CONCENTRATIONLINE_EFFECT_ALPHA);

	/* �摜��`�� */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->apiGrHandle_ConcentrationLine[this->iEffectType], TRUE);

	/* �`�ʃu�����h���[�h��"�m�[�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

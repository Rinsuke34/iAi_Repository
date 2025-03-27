/* 2025.03.28 �t�@�C���ǉ� ��򕗏� */

#include "SceneLogo.h"

/* �V�[���u���S�v�̒�` */
// �R���X�g���N�^
SceneLogo::SceneLogo() : SceneBase("Logo", 20, true)
{
	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* ���S�摜(�w�Z) */
		this->piGrHandle_Logo_School	= ImageList->piGetImage("Logo/amgLOGO");

		/* ���S�摜(�`�[��) */
		this->piGrHandle_Logo_Team		= ImageList->piGetImage("Logo/LOGO1");
	}

	/* ������ */
	this->iDrawFaze		= 0;	// �`�ʃt�F�C�Y(0:�w�Z���S, 1:�`�[�����S)
	this->iAlpha		= 0;	// �`�ʂ̃A���t�@�l
	this->bFadeInFlg	= true;	// �t�F�[�h�C������J�n���邩�̃t���O
}

// �v�Z
void SceneLogo::Process()
{
	/* �t�F�[�h�C������J�n���邩�̊m�F */
	if (this->bFadeInFlg == true)
	{
		// �t�F�[�h�C������J�n����ꍇ
		/* �t�F�[�h�C���i�A���t�@�l�𑝉��j*/
		this->iAlpha += 2;
		if (this->iAlpha >= 255)
		{
			this->iAlpha		= 255;
			this->bFadeInFlg	= false;
		}
	}
	else
	{
		// �t�F�[�h�A�E�g����J�n����ꍇ
		/* �t�F�[�h�A�E�g�i�A���t�@�l�������j*/
		this->iAlpha -= 2;
		if (this->iAlpha <= 0)
		{
			this->iAlpha = 0;
			this->iDrawFaze++;

			/* �S�Ẵt�F�C�Y�������������m�F */
			if (this->iDrawFaze >= 2)
			{
				// ���������ꍇ
				/* �폜�t���O��L���ɂ��� */
				this->bDeleteFlg = true;
				return;
			}

			this->bFadeInFlg = true;
		}
	}
}

// �`��
void SceneLogo::Draw()
{
	/* �w�i�����F�ŕ`�� */
	DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);

	/* �u�����h���[�h�ݒ� */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->iAlpha);

	/* ���݂̃t�F�C�Y�ɉ����ĕ`�� */
	if (this->iDrawFaze == 0)
	{
		/* �w�Z���S */
		DrawGraph(0, 0, *this->piGrHandle_Logo_School, TRUE);
	}
	else if (this->iDrawFaze == 1)
	{
		/* �`�[�����S */
		DrawGraph(0, 0, *this->piGrHandle_Logo_Team, TRUE);
	}

	/* �u�����h���[�h�����ɖ߂� */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

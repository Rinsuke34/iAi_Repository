/* 2025.03.05 �t�@�C���ǉ� ��򕗏� */

#include "SceneOption.h"

/* �V�[���u�I�v�V�����v�̒�` */

// �R���X�g���N�^
SceneOption::SceneOption() : SceneBase("Option", 500, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�I�v�V�����ݒ�Ǘ�"���擾 */
		this->OptionList = dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));
	}

	/* �摜���\�[�X�擾 */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* ���U���g�p�t���[�� */
		this->piGrHandle_ResultFrame	= ImageList->piGetImage("Result/UI_Result_Frame");

		/* ��� */
		this->piGrHandle_Arrow			= ImageList->piGetImage("Test/Sign");
	}

	/* �I�v�V���������X�g�̃|�C���^���擾 */
	this->astOptionNameList = this->OptionList->stGetOptionNameList();

	/* ������ */
	this->iSelectItem		= 0;			// �I�𒆂̍��ڂ̔ԍ�
	this->bSelectFlg		= false;		// �I����Ԃł��邩�̃t���O
}

// �f�X�g���N�^
SceneOption::~SceneOption()
{
	/* �X�V�����I�v�V�����ݒ��json�t�@�C���ɏ������� */
	this->OptionList->SaveOptionData();
}

// �v�Z
void SceneOption::Process()
{
	/* "����"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// ���͂���Ă���ꍇ
		/* �I����ԃt���O��L���ɂ��� */
		this->bSelectFlg = true;

		return;
	}

	/* "�L�����Z��"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
	{
		// ���͂���Ă���ꍇ
		/* �I����ԃt���O���m�F */
		if (this->bSelectFlg == true)
		{
			// �L���ł���ꍇ
			/* �I����ԃt���O�𖳌��ɂ��� */
			this->bSelectFlg = false;
		}
		else
		{
			// �����ł���ꍇ
			/* ���̃V�[���̍폜�t���O��L���ɂ��� */
			this->bDeleteFlg = true;
		}

		return;
	}

	/* "��"���g���K���́A���邢�͉E�����͂���Ă��邩�m�F */
	if ((gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP) == true) || (gpDataList_Input->bGetInterfaceInput(INPUT_HOLD, UI_RIGHT) == true))
	{
		// ���͂���Ă���ꍇ
		/* �I����ԃt���O���m�F */
		if (this->bSelectFlg == true)
		{
			// �L���ł���ꍇ
			/* �f�[�^�^�ɉ����ď�����ύX */
			std::string OptionType = this->astOptionNameList->at(this->iSelectItem).Type.c_str();

			/* �f�[�^�^�ɉ����ď�����ύX */
			if (OptionType == DATA_TYPE_BOOL)
			{
				// �u�[���^�̏ꍇ
				/* �u�[���l�𔽓]���� */
				bool* pBoolValue	= static_cast<bool*>(this->astOptionNameList->at(this->iSelectItem).pValue);
				*pBoolValue			= !(*pBoolValue);
			}
			else if (OptionType == DATA_TYPE_INT)
			{
				// �����^�̏ꍇ
				/* ���݂̒l��float�^�Ŏ擾 */
				float fValue = static_cast<float>(*static_cast<int*>(this->astOptionNameList->at(this->iSelectItem).pValue));

				/* �l��ύX */
				fValue += static_cast<float>(this->astOptionNameList->at(this->iSelectItem).fStepValue);

				/* �ő�l�������Ă��Ȃ����m�F */
				if (fValue > this->astOptionNameList->at(this->iSelectItem).fMax)
				{
					// �����Ă���ꍇ
					/* �ő�l�ɐݒ� */
					fValue = this->astOptionNameList->at(this->iSelectItem).fMax;
				}

				/* �����^�ɕϊ����Đݒ� */
				*static_cast<int*>(this->astOptionNameList->at(this->iSelectItem).pValue) = static_cast<int>(fValue);
			}
			else if (OptionType == DATA_TYPE_FLOAT)
			{
				// ���������_�^�̏ꍇ
				/* ���݂̒l���擾 */
				float* pFloatValue = static_cast<float*>(this->astOptionNameList->at(this->iSelectItem).pValue);

				/* �l��ύX */
				*pFloatValue += this->astOptionNameList->at(this->iSelectItem).fStepValue;

				/* �ő�l�������Ă��Ȃ����m�F */
				if (*pFloatValue > this->astOptionNameList->at(this->iSelectItem).fMax)
				{
					// �����Ă���ꍇ
					/* �ő�l�ɐݒ� */
					*pFloatValue = this->astOptionNameList->at(this->iSelectItem).fMax;
				}
			}
		}
		else
		{
			// �����ł���ꍇ
			/* �I�����ڂ���ɐi�߂� */
			this->iSelectItem -= 1;
		}
	}

	/* "��"���g���K���́A���邢�͍������͂���Ă��邩�m�F */
	if ((gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN) == true) || (gpDataList_Input->bGetInterfaceInput(INPUT_HOLD, UI_LEFT) == true))
	{
		// ���͂���Ă���ꍇ
		/* �I����ԃt���O���m�F */
		if (this->bSelectFlg == true)
		{
			// �L���ł���ꍇ
			/* �f�[�^�^�ɉ����ď�����ύX */
			std::string OptionType = this->astOptionNameList->at(this->iSelectItem).Type.c_str();

			/* �f�[�^�^�ɉ����ď�����ύX */
			if (OptionType == DATA_TYPE_BOOL)
			{
				// �u�[���^�̏ꍇ
				/* �u�[���l�𔽓]���� */
				bool* pBoolValue = static_cast<bool*>(this->astOptionNameList->at(this->iSelectItem).pValue);
				*pBoolValue = !(*pBoolValue);
			}
			else if (OptionType == DATA_TYPE_INT)
			{
				// �����^�̏ꍇ
				/* ���݂̒l��float�^�Ŏ擾 */
				float fValue = static_cast<float>(*static_cast<int*>(this->astOptionNameList->at(this->iSelectItem).pValue));

				/* �l��ύX */
				fValue -= static_cast<float>(this->astOptionNameList->at(this->iSelectItem).fStepValue);

				/* �ŏ��l��������Ă��Ȃ����m�F */
				if (fValue < this->astOptionNameList->at(this->iSelectItem).fMin)
				{
					// ������Ă���ꍇ
					/* �ŏ��l�ɐݒ� */
					fValue = this->astOptionNameList->at(this->iSelectItem).fMin;
				}

				/* �����^�ɕϊ����Đݒ� */
				*static_cast<int*>(this->astOptionNameList->at(this->iSelectItem).pValue) = static_cast<int>(fValue);
			}
			else if (OptionType == DATA_TYPE_FLOAT)
			{
				// ���������_�^�̏ꍇ
				/* ���݂̒l���擾 */
				float* pFloatValue = static_cast<float*>(this->astOptionNameList->at(this->iSelectItem).pValue);

				/* �l��ύX */
				*pFloatValue -= this->astOptionNameList->at(this->iSelectItem).fStepValue;

				/* �ŏ��l��������Ă��Ȃ����m�F */
				if (*pFloatValue < this->astOptionNameList->at(this->iSelectItem).fMin)
				{
					// ������Ă���ꍇ
					/* �ŏ��l�ɐݒ� */
					*pFloatValue = this->astOptionNameList->at(this->iSelectItem).fMin;
				}
			}
		}
		else
		{
			// �����ł���ꍇ
			/* �I�����ڂ����ɐi�߂� */
			this->iSelectItem += 1;
		}
	}

	/* �I�𒆂̍��ڂ̔ԍ���͈͓��Ɏ��߂�*/
	if (this->iSelectItem < 0)
	{
		this->iSelectItem = 0;
	}
	else if (this->iSelectItem >= static_cast<int>(this->astOptionNameList->size()))
	{
		this->iSelectItem = static_cast<int>(this->astOptionNameList->size()) - 1;
	}

	/* BGM�̉��ʂ�ύX */
	// �����ʒ��������A���^�C���Ŕ��f���邽�߁A���t���[�����ʂ��X�V����
	gpDataList_Sound->BGM_VolumeChange();
}

// �`��
void SceneOption::Draw()
{
	/* ���U���g�p�̃t���[����`�ʂ��� */
	// �����U���g�p�̃t���[���𗬗p����
	DrawExtendGraph(0 + FRAME_SIZE_REDUCTION_AMOUNT, 0 + FRAME_SIZE_REDUCTION_AMOUNT, SCREEN_SIZE_WIDE - FRAME_SIZE_REDUCTION_AMOUNT, SCREEN_SIZE_HEIGHT - FRAME_SIZE_REDUCTION_AMOUNT, *this->piGrHandle_ResultFrame, FALSE);

	/* �I�v�V�����̍ő吔���擾 */
	int iOptionMax = this->astOptionNameList->size();

	/* �I�v�V�����`�� */
	for (int i = 0; i < iOptionMax; i++)
	{
		/* ���ڂ̐F��ݒ� */
		int iColor = GetColor(255, 255, 255);

		/* �`�ʈʒu��ݒ� */
		int iDrawPosX = OPTION_DRAWPOS_X;
		int iDrawPosY = OPTION_DRAWPOS_Y + i * 50;

		/* �I�𒆂̍��ڂ��m�F */
		if (i == this->iSelectItem)
		{
			// �I�𒆂̏ꍇ
			/* ����`�� */
			DrawExtendGraph(iDrawPosX - OPTION_ARROW_WIDTH, iDrawPosY, iDrawPosX, iDrawPosY + OPTION_ARROW_HEIGHT, *this->piGrHandle_Arrow, FALSE);

			/* �I�𒆂̍��ڂ̐F��ύX */
			iColor = GetColor(255, 0, 0);
		}

		/* �I�v�V��������`�� */
		DrawStringToHandle(iDrawPosX + 50, iDrawPosY, this->astOptionNameList->at(i).Name.c_str(), iColor, giFontHandle_Normal);

		/* �I�v�V�����̐ݒ�l��`�� */
		{
			/* �f�[�^�^�ɉ����ď�����ύX */
			std::string OptionType = this->astOptionNameList->at(i).Type.c_str();

			/* �f�[�^�^�ɉ����ď�����ύX */
			if (OptionType == DATA_TYPE_BOOL)
			{
				// �u�[���^�̏ꍇ
				/* �L���ł��邩�`�ʂ��s�� */
				if (*static_cast<bool*>(this->astOptionNameList->at(i).pValue) == true)
				{
					// �L���ł���ꍇ
					DrawStringToHandle(iDrawPosX + OPTION_STATUS_DRAWPOS_X, iDrawPosY, "�L��", iColor, giFontHandle_Normal);
				}
				else
				{
					// �����ł���ꍇ
					DrawStringToHandle(iDrawPosX + OPTION_STATUS_DRAWPOS_X, iDrawPosY, "����", iColor, giFontHandle_Normal);
				}
			}
			else if (OptionType == DATA_TYPE_INT)
			{
				// �����^�̏ꍇ
				/* ���݂̒l��`�ʂ��� */
				DrawFormatStringToHandle(iDrawPosX + OPTION_STATUS_DRAWPOS_X, iDrawPosY, iColor, giFontHandle_Normal, "%d", *static_cast<int*>(this->astOptionNameList->at(i).pValue));
			}
			else if (OptionType == DATA_TYPE_FLOAT)
			{
				// ���������_�^�̏ꍇ
				/* ���݂̒l��`�ʂ��� */
				DrawFormatStringToHandle(iDrawPosX + OPTION_STATUS_DRAWPOS_X, iDrawPosY, iColor, giFontHandle_Normal, "%.2f", *static_cast<float*>(this->astOptionNameList->at(i).pValue));
			}
		}
	}
}

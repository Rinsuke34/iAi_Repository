/* 2025.02.13 �t�@�C���쐬 ��򕗏� */

#include "SceneEdit.h"
#include "SceneResultDefine.h"

/* �V�[��"�G�f�B�b�g"�N���X�̒�`(�`�ʕ���) */

// �`��
void SceneEdit::Draw()
{
	/* ���U���g�p�̃t���[����`�� */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->piGrHandle_ResultFrame, FALSE);

	/* ��ʂ̔w�i�`�� */
	DrawExtendGraph(0 + RESULT_BACKGROUND_POSITION_REDUCTION, 0 + RESULT_BACKGROUND_POSITION_REDUCTION, SCREEN_SIZE_WIDE - RESULT_BACKGROUND_POSITION_REDUCTION, SCREEN_SIZE_HEIGHT - RESULT_BACKGROUND_POSITION_REDUCTION, *this->piGrHandle_ResultBackGround, TRUE);

	/* Custom(����) */
	DrawGraph(80, 30, *this->piGrHandle_Custom, TRUE);
	DrawBox(65, 140, 1810, 145, GetColor(255, 255, 255), TRUE);

	/* NEW(����) */
	DrawGraph(290, 180, *this->piGrHandle_New, TRUE);

	/* �w�i */
	DrawGraph(350, 885, *this->piGrHandle_UnderExplain_Under, TRUE);

	/* �G�f�B�b�g�w�i */
	// �V�K�G�f�B�b�g����
	for (int i = 0; i < 6; i++)
	{
		int iX = (i * 275) + 35;
		int iY = 250;
		DrawGraph(iX, iY, *this->piGrHandle_NewEdit_Under, TRUE);
	}
	// ���݃G�f�B�b�g����
	DrawGraph(350,	695, *this->piGrHandle_NowEdit_Under, TRUE);

	/* �����u���b�h�`�� */
	DrawGraph(630, 170, *this->piGrHandle_Blood, TRUE);
	DrawFormatStringToHandle(700, 150, GetColor(255, 255, 255), giFontHandle_Large, "%d", this->GameResourceList->iGetHaveBlood());

	/* �����u���b�h���� */
	DrawBox(645, 235, 1275, 240, GetColor(255, 255, 255), TRUE);

	/* �e���ڂ̕`�� */
	for (int i = 0; i < SELECT_ITEM_MAX; i++)
	{
		/* "����"�ł��邩�m�F */
		if (this->astSelectItemList[i].iSelectItemType == SELECT_TYPE_NEXT)
		{
			// "����"�ł���ꍇ
			/* "����"�{�^���`�� */
			DrawGraph(1515, 950, *this->piGrHandle_SelectNext, TRUE);
		}
		else
		{
			// "����"�ȊO�ł���ꍇ
			/* �G�f�B�b�g�t���[���`�� */
			DrawGraph(this->astSelectItemList[i].stDrawPos.ix, this->astSelectItemList[i].stDrawPos.iy, *this->GameResourceList->piGetGrHandle_EditFrame(this->astSelectItemList[i].pstEditData->iEditRank), TRUE);

			/* �G�f�B�b�g���ʕ`�� */
			DrawGraph(this->astSelectItemList[i].stDrawPos.ix, this->astSelectItemList[i].stDrawPos.iy, *this->GameResourceList->piGetGrHandle_EditEffect(this->astSelectItemList[i].pstEditData->iEditEffect), TRUE);

			/* �I�����ڂ̎�ނ��擾 */
			int iSelectItemType = this->astSelectItemList[i].iSelectItemType;

			/* �I�����ڂ̎�ނɉ��������� */
			switch (iSelectItemType)
			{
				/* �L�[�v���̃G�f�B�b�g */
				/* �V�K�̃G�f�B�b�g */
				case SELECT_TYPE_KEEP_EDIT:
				case SELECT_TYPE_NEW_EDIT:
					/* �G�f�B�b�g�����N��"����"�ȊO�ł��邩 */
					if (this->astSelectItemList[i].pstEditData->iEditRank != EDIT_RANK_NONE)
					{
						// "����"�ȊO�ł���ꍇ
						/* �K�v�u���b�h��`�� */
						int iX = (i * 280) + 30;
						int iY = 420;
						DrawGraph(iX, iY, *this->piGrHandle_Blood, TRUE);
						DrawFormatStringToHandle(iX + 70, iY, GetColor(255, 255, 255), giFontHandle_Medium, "%d", this->astSelectItemList[i].pstEditData->iEditCost);

						/* ��������`�� */
						std::string formattedText = PUBLIC_PROCESS::aInsertNewLine(this->astSelectItemList[i].pstEditData->aText, 6);
						DrawFormatStringToHandle(iX + 20, iY + 70, GetColor(255, 255, 255), giFontHandle_Small,	"%s", formattedText.c_str());

						/* �L�[�v���̃G�f�B�b�g�ł��邩�m�F */
						if (iSelectItemType == SELECT_TYPE_KEEP_EDIT)
						{
							// �L�[�v���̃G�f�B�b�g�ł���ꍇ
							/* �L�[�v�A�C�R��(��)��`�� */
							DrawExtendGraph(30 + 128, 210 + 128, 30 + 255, 210 + 255, *this->piGrHandle_EditLock, TRUE);
						}
					}
					else
					{
						// "����"�ł���ꍇ
						/* �L�[�v���̃G�f�B�b�g�ł��邩�m�F */
						if (iSelectItemType == SELECT_TYPE_KEEP_EDIT)
						{
							// �L�[�v���̃G�f�B�b�g�ł���ꍇ
							/* �L�[�v�A�C�R��(��)��`�� */
							DrawGraph(30, 210, *this->piGrHandle_EditLock, TRUE);
						}
					}
					break;

				/* �폜 */
				case SELECT_TYPE_DELETE_EDIT:
					/* �G�f�B�b�g�����N��"����"�ȊO�ł��邩 */
					if (this->astSelectItemList[i].pstEditData->iEditRank != EDIT_RANK_NONE)
					{
						// "����"�ȊO�ł���ꍇ
						/* �폜�A�C�R��(�S�~��)��`�� */
						DrawExtendGraph(30 + 128, 650 + 128, 30 + 255, 650 + 255, *this->piGrHandle_Delete, TRUE);
					}
					else
					{
						// "����"�ł���ꍇ
						/* �폜�A�C�R��(�S�~��)��`�� */
						DrawGraph(30, 650, *this->piGrHandle_Delete, TRUE);
					}
					break;

				/* ���݂̃G�f�B�b�g */
				case SELECT_TYPE_NOW_EDIT:
					break;

				/* ���� */
				case SELECT_TYPE_NEXT:
					break;
			}

			/* �I���t���[���̏�Ԃ��ݒ肳��Ă��邩�m�F */
			if (this->astSelectItemList[i].iSelectStatus != SELECT_STATUS_NONE)
			{
				// �t���[���̏�Ԃ��ݒ肳��Ă���ꍇ
				/* �I�����ڂ̏�Ԃ̃t���[����`�� */
				DrawGraph(this->astSelectItemList[i].stDrawPos.ix, this->astSelectItemList[i].stDrawPos.iy, *this->apiGrHandle_SelectStatus[this->astSelectItemList[i].iSelectStatus], TRUE);
			}
		}
	}

	/* �z�[���h��Ԃ��m�F */
	if (this->HoldEditData.iEditEffect == EDIT_EFFECT_NONE)
	{
		// �����z�[���h���Ă��Ȃ��ꍇ
		/* �I�𒆂̍��ڂɑ΂��đI���t���[����`�� */
		DrawGraph(this->astSelectItemList[this->iSelectItem].stDrawPos.ix, this->astSelectItemList[this->iSelectItem].stDrawPos.iy, *this->piGrHandle_SelectFrame[0], TRUE);
	}
	else
	{
		// ��������̃G�f�B�b�g���z�[���h���̏ꍇ
		// ���I�𒆂̍��ڂ̉E��Ƀz�[���h���̃G�f�B�b�g��`��
		/* �G�f�B�b�g�t���[���`�� */
		DrawGraph(this->astSelectItemList[this->iSelectItem].stDrawPos.ix + 20, this->astSelectItemList[this->iSelectItem].stDrawPos.iy - 20, *this->GameResourceList->piGetGrHandle_EditFrame(this->HoldEditData.iEditRank), TRUE);

		/* �I�𒆂̍��ڂɑ΂��đI���t���[����`�� */
		DrawGraph(this->astSelectItemList[this->iSelectItem].stDrawPos.ix, this->astSelectItemList[this->iSelectItem].stDrawPos.iy, *this->piGrHandle_SelectFrame[1], TRUE);

		/* �G�f�B�b�g���ʕ`�� */
		DrawGraph(this->astSelectItemList[this->iSelectItem].stDrawPos.ix + 20, this->astSelectItemList[this->iSelectItem].stDrawPos.iy - 20, *this->GameResourceList->piGetGrHandle_EditEffect(this->HoldEditData.iEditEffect), TRUE);
	}

	/* ���݂̑I���J�[�\����"�폜","���݂̃G�f�B�b�g"�ɂȂ��Ă��邩 */
	if ((SELECT_ITEM_DELETE <= this->iSelectItem) && (this->iSelectItem <= SELECT_ITEM_NOW_EDIT_END))
	{
		// "�폜","���݂̃G�f�B�b�g"�ł���ꍇ
		/* �J�[�\�������킳���Ă��鍀�ڂɍ��ڂ��ݒ肳��Ă��邩�m�F */
		if (this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect != EDIT_EFFECT_NONE)
		{
			// �ݒ肳��Ă���ꍇ
			/* ��������`�� */
			std::string formattedText = PUBLIC_PROCESS::aInsertNewLine(this->astSelectItemList[this->iSelectItem].pstEditData->aText, 14);
			DrawFormatStringToHandle(350, 895, GetColor(255, 255, 255), giFontHandle_Small, "%s", formattedText.c_str());
		}
	}
}

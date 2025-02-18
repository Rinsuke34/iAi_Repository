/* 2025.02.13 �t�@�C���쐬 ��򕗏� */

#include "SceneEdit.h"

/* �V�[��"�G�f�B�b�g"�N���X�̒�`(�`�ʕ���) */

// �`��
void SceneEdit::Draw()
{
	/* �e���ڂ̕`�� */
	for (int i = 0; i < SELECT_ITEM_MAX; i++)
	{
		/* "����"�ł��邩�m�F */
		if (this->astSelectItemList[i].iSelectItemType == SELECT_TYPE_NEXT)
		{
			// "����"�ł���ꍇ
			/* "����"�{�^���`�� */
			DrawGraph(this->astSelectItemList[i].stDrawPos.ix, this->astSelectItemList[i].stDrawPos.iy, *piGrHandle_SelectNext, TRUE);
		}
		else
		{
			// "����"�ȊO�ł���ꍇ
			/* �G�f�B�b�g�t���[���`�� */
			DrawGraph(this->astSelectItemList[i].stDrawPos.ix, this->astSelectItemList[i].stDrawPos.iy, *this->GameResourceList->piGetGrHandle_EditFrame(this->astSelectItemList[i].pstEditData->iEditRank), TRUE);

			/* �G�f�B�b�g���ʕ`�� */
			DrawGraph(this->astSelectItemList[i].stDrawPos.ix, this->astSelectItemList[i].stDrawPos.iy, *this->GameResourceList->piGetGrHandle_EditEffect(this->astSelectItemList[i].pstEditData->iEditEffect), TRUE);
		}

		/* �I���t���[���̏�Ԃ��ݒ肳��Ă��邩�m�F */
		if (this->astSelectItemList[i].iSelectStatus != SELECT_STATUS_NONE)
		{
			// �t���[���̏�Ԃ��ݒ肳��Ă���ꍇ
			/* �I�����ڂ̏�Ԃ̃t���[����`�� */
			DrawGraph(this->astSelectItemList[i].stDrawPos.ix, this->astSelectItemList[i].stDrawPos.iy, *this->apiGrHandle_SelectStatus[this->astSelectItemList[i].iSelectStatus], TRUE);
		}
	}

	/* �z�[���h��Ԃ��m�F */
	if (this->HoldEditData.iEditEffect == EDIT_EFFECT_NONE)
	{
		// �����z�[���h���Ă��Ȃ��ꍇ
		/* �I�𒆂̍��ڂɑ΂��đI���t���[����`�� */
		DrawGraph(this->astSelectItemList[this->iSelectItem].stDrawPos.ix, this->astSelectItemList[this->iSelectItem].stDrawPos.iy, *this->piGrHandle_SelectFrame, TRUE);
	}
	else
	{
		// ��������̃G�f�B�b�g���z�[���h���̏ꍇ
		// ���I�𒆂̍��ڂ̉E��Ƀz�[���h���̃G�f�B�b�g��`��
		/* �G�f�B�b�g�t���[���`�� */
		DrawGraph(this->astSelectItemList[this->iSelectItem].stDrawPos.ix + 20, this->astSelectItemList[this->iSelectItem].stDrawPos.iy - 20, *this->GameResourceList->piGetGrHandle_EditFrame(this->HoldEditData.iEditRank), TRUE);

		/* �G�f�B�b�g���ʕ`�� */
		DrawGraph(this->astSelectItemList[this->iSelectItem].stDrawPos.ix + 20, this->astSelectItemList[this->iSelectItem].stDrawPos.iy - 20, *this->GameResourceList->piGetGrHandle_EditEffect(this->HoldEditData.iEditEffect), TRUE);
	}

	/* �����u���b�h�`�� */
	DrawFormatStringToHandle(500, 200, GetColor(255, 0, 0),	giFontHandle, "����BLOOD : %d", this->GameResourceList->iGetHaveBlood());
}

/* 2025.02.13 �t�@�C���쐬 ��򕗏� */

#include "SceneEdit.h"

/* �V�[��"�G�f�B�b�g"�N���X�̒�`(�`�ʕ���) */

// �`��
void SceneEdit::Draw()
{
	/* �`�ʍ��W�ݒ�(��) */
	st2DPosition stSelectItemPos[SELECT_ITEM_MAX] =
	{
		{ 500 + (128 + 64) * 1, 1080 - 128 * 6 },
		{ 500 + (128 + 64) * 2, 1080 - 128 * 6 },
		{ 500 + (128 + 64) * 3, 1080 - 128 * 6 },
		{ 500 + (128 + 64) * 4, 1080 - 128 * 6 },
		{ 500 + (128 + 64) * 5, 1080 - 128 * 6 },
		{ 500 + (128 + 64) * 1, 1080 - 128 * 3 },
		{ 500 + (128 + 64) * 2, 1080 - 128 * 3 },
		{ 500 + (128 + 64) * 3, 1080 - 128 * 3 },
		{ 500 + (128 + 64) * 4, 1080 - 128 * 3 },
		{ 500 + (128 + 64) * 5, 1080 - 128 * 3 },
		{ 500 + (128 + 64) * 6, 1080 - 128 * 3 },
	};

	/* �e���ڂ̕`�� */
	for (int i = 0; i < SELECT_ITEM_MAX; i++)
	{
		/* �C���f�b�N�X�ɉ����ĕ`�ʓ��e��ύX */
		if (i < SELECT_ITEM_NEW_EDIT)
		{
			// �V�K�̃G�f�B�b�g
			/* �G�f�B�b�g�t���[���`�� */
			DrawGraph(stSelectItemPos[i].ix, stSelectItemPos[i].iy, *this->GameResourceList->piGetGrHandle_EditFrame(this->NewEditData[i].iEditRank), TRUE);

			/* �G�f�B�b�g���ʕ`�� */
			DrawGraph(stSelectItemPos[i].ix, stSelectItemPos[i].iy, *this->GameResourceList->piGetGrHandle_EditEffect(this->NewEditData[i].iEditEffect), TRUE);
		}
		else if (i < SELECT_ITEM_NOW_EDIT)
		{
			// ���݂̃G�f�B�b�g
			/* �G�f�B�b�g�t���[���`�� */
			DrawGraph(stSelectItemPos[i].ix, stSelectItemPos[i].iy, *this->GameResourceList->piGetGrHandle_EditFrame(this->GameResourceList->pGetNowEditData(i - SELECT_ITEM_NEW_EDIT).iEditRank), TRUE);

			/* �G�f�B�b�g���ʕ`�� */
			DrawGraph(stSelectItemPos[i].ix, stSelectItemPos[i].iy, *this->GameResourceList->piGetGrHandle_EditEffect(this->GameResourceList->pGetNowEditData(i - SELECT_ITEM_NEW_EDIT).iEditEffect), TRUE);
		}
		else
		{
			// ����
			/* "����"�{�^���`�� */
			DrawGraph(stSelectItemPos[i].ix, stSelectItemPos[i].iy, *this->piGrHandle_SelectNext, TRUE);
		}
	}

	/* �I���t���[���`�� */
	DrawGraph(stSelectItemPos[iSelectItem].ix, stSelectItemPos[iSelectItem].iy, *piGrHandle_SelectFrame, TRUE);

	/* �����u���b�h�`�� */
	DrawFormatStringToHandle(500, 200, GetColor(255, 0, 0),	giFontHandle, "����BLOOD : %d", this->GameResourceList->iGetHaveBlood());
}

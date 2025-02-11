/* 2025.02.11 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Edit.h"

/* UI(�G�f�B�b�g)�N���X�̒�` */
// �R���X�g���N�^
SceneUi_Edit::SceneUi_Edit() : SceneBase("UI_Edit", 105, false)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�Q�[�������\�[�X�Ǘ�"���擾 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}

	/* �G�f�B�b�g��񏉊��� */
	{
		/* �G�f�B�b�g���������� */
		for (int i = 0; i < EDIT_MAX; i++)
		{
			/* ������Ԃł͂��ׂ�"���ʂȂ�"�ɐݒ� */
			this->NowEditData[i].iEditEffect = EDIT_EFFECT_NONE;
		}

		/* �e�X�g */
		this->NowEditData[0].iEditEffect = EDIT_EFFECT_NORMAL_MOVE_SPEED_UP;
	}
}

// �f�X�g���N�^
SceneUi_Edit::~SceneUi_Edit()
{

}

// �v�Z
void SceneUi_Edit::Process()
{

}

// �`��
void SceneUi_Edit::Draw()
{
	/* ���݂̃G�f�B�b�g���e��`��(�e�X�g) */
	{
		/* �G�f�B�b�g���e��`�� */
		for (int i = 0; i < EDIT_MAX; i++)
		{
			std::string strEditType = "�Ȃ�";

			/* ���ʖ����擾 */
			for (int j = 0; j < EDIT_EFFECT_MAX; j++)
			{
				if (this->NowEditData[i].iEditEffect == EDIT_LIST[j].iEditEffect)
				{
					strEditType = EDIT_LIST[j].strEditName;
					break;
				}
			}

			/* �G�f�B�b�g���e��`�� */
			DrawFormatStringToHandle(0, 1000 + 24 * i, GetColor(255, 255, 255), giFontHandle, strEditType.c_str());
		}
	}
}

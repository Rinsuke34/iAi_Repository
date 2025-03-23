/* 2025.02.11 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Edit.h"

/* UI(�G�f�B�b�g)�N���X�̒�` */
// �R���X�g���N�^
SceneUi_Edit::SceneUi_Edit() : SceneBase("UI_Edit", 105, false)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�Q�[����ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "�Q�[�������\�[�X�Ǘ�"���擾 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}
}

// �v�Z
void SceneUi_Edit::Process()
{
	/* �Q�[����Ԃ�"�Q�[�����s"�ȊO�ł���Ȃ�V�[�����폜 */
	if (this->StageStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		/* �V�[���̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
		return;
	}
}

// �`��
void SceneUi_Edit::Draw()
{
	/* �G�f�B�b�g���e��`�� */
	for (int i = 0; i < EDIT_MAX; i++)
	{
		/* �G�f�B�b�g�t���[���`�� */
		DrawExtendGraph(150 + 75 * i, 777, 150 + 75 * i + 128, 777 + 128, *this->GameResourceList->piGetGrHandle_EditFrame(this->GameResourceList->stGetNowEditData(i).iEditRank), TRUE);

		/* �G�f�B�b�g���ʕ`�� */
		DrawExtendGraph(150 + 75 * i, 777, 150 + 75 * i + 128, 777 + 128, *this->GameResourceList->piGetGrHandle_EditEffect(this->GameResourceList->stGetNowEditData(i).iEditEffect), TRUE);
	}
}

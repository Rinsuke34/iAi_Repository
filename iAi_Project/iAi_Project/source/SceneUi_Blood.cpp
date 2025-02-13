/* 2025.02.11 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Blood.h"

/* UI(�u���b�h(�Q�[�����ʉ�))�N���X�̒�` */
// �R���X�g���N�^
SceneUi_Blood::SceneUi_Blood() : SceneBase("UI_Blood", 104, false)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�Q�[�������\�[�X�Ǘ�"���擾 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}
}

// �f�X�g���N�^
SceneUi_Blood::~SceneUi_Blood()
{

}

// �v�Z
void SceneUi_Blood::Process()
{

}

// �`��
void SceneUi_Blood::Draw()
{
	/* ���݂̃u���b�h��`��(��) */
	DrawFormatString(1600, 800 + 16 * 0, GetColor(255, 255, 255), "���݂�BLOOD : %d", this->GameResourceList->iGetHaveBlood());
}


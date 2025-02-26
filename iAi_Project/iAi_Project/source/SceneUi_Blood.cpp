/* 2025.02.11 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Blood.h"

/* UI(�u���b�h(�Q�[�����ʉ�))�N���X�̒�` */
// �R���X�g���N�^
SceneUi_Blood::SceneUi_Blood() : SceneBase("UI_Blood", 104, false)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�Q�[�������\�[�X�Ǘ�"���擾 */
		this->GameResourceList	= dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));

		/* "�X�e�[�W��ԊǗ�"���擾 */
		this->StageStatusList	= dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}
}

// �f�X�g���N�^
SceneUi_Blood::~SceneUi_Blood()
{

}

// �v�Z
void SceneUi_Blood::Process()
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
void SceneUi_Blood::Draw()
{
	/* ���݂̃u���b�h��`��(��) */
	DrawFormatString(1600, 800 + 16 * 0, GetColor(255, 255, 255), "���݂�BLOOD : %d", this->GameResourceList->iGetHaveBlood());
}

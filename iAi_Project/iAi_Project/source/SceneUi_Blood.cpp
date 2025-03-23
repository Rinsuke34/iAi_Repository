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

	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �u���b�h�A�C�R�� */
		this->piGrHandle_Blood_Icon		= ImageList->piGetImage("UI_Player_Blood/Blood");

		/* �e�L�X�g�t���[�� */
		this->piGrHandle_Text_Frame		= ImageList->piGetImage("UI_Player_Blood/UI_Blood_Timer_Frame");
	}
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
	/* �e�L�X�g�t���[����`�� */
	DrawGraph(1470, 35, *this->piGrHandle_Text_Frame, true);

	/* �u���b�h�A�C�R����`�� */
	DrawGraph(1470, 35, *this->piGrHandle_Blood_Icon, true);

	/* ���݂̃u���b�h��`�� */
	DrawFormatStringToHandle(1470 + 64, 35, GetColor(255, 255, 255), giFontHandle_Medium, "%d", this->GameResourceList->iGetHaveBlood());
}

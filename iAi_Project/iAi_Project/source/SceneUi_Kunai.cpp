/* 2025.01.28 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Kunai.h"

/* UI(�N�i�C)�N���X�̒�` */

// �R���X�g���N�^
SceneUi_Kunai::SceneUi_Kunai() : SceneBase("UI_Kunai", 102, false)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�v���C���[���"���擾 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "�Q�[����ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));
	}
}

// �f�X�g���N�^
SceneUi_Kunai::~SceneUi_Kunai()
{

}

// �v�Z
void SceneUi_Kunai::Process()
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
void SceneUi_Kunai::Draw()
{

}

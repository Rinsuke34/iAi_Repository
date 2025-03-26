/* 2025.01.28 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Hp.h"

/* UI(HP)�N���X�̒�` */

// �R���X�g���N�^
SceneUi_Hp::SceneUi_Hp() : SceneBase("UI_Hp", 101, false)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�v���C���[���"���擾 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "�X�e�[�W��ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList	= dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* HP�t���[�� */
		this->piGrHandle_Hp_Frame	= ImageList->piGetImage("UI_Player_HP/UI_Player_HP_frame");

		/* HP�Q�[�W */
		this->piGrHandle_Hp_Gauge	= ImageList->piGetImage("UI_Player_HP/UI_Player_HP_gauge");
	}
}

// �v�Z
void SceneUi_Hp::Process()
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
void SceneUi_Hp::Draw()
{
	/* HP�t���[���`��(��) */
	DrawGraph(60, 880, *this->piGrHandle_Hp_Frame, TRUE);

	/* HP�Q�[�W�`�� */
	for (int i = 0; i < this->PlayerStatusList->iGetPlayerNowHp(); i++)
	{
		DrawGraph(245 + (25 * i), 880 + 40, *this->piGrHandle_Hp_Gauge, TRUE);
	}
}

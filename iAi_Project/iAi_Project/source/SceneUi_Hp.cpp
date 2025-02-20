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

		/* "�Q�[����ԊǗ�"���擾 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
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

// �f�X�g���N�^
SceneUi_Hp::~SceneUi_Hp()
{

}

// �v�Z
void SceneUi_Hp::Process()
{
	/* �Q�[����Ԃ�"�Q�[�����s"�ȊO�ł���Ȃ�V�[�����폜 */
	if (this->GameStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
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
	DrawGraph(100, 740, *this->piGrHandle_Hp_Frame, TRUE);

	/* HP�Q�[�W�`�� */
	for (int i = 0; i < this->PlayerStatusList->iGetPlayerNowHp(); i++)
	{
		DrawGraph(100 + 185 + (25 * i), 740 + 40, *this->piGrHandle_Hp_Gauge, TRUE);
	}

	/* ����HP */
	DrawFormatString(500, 700 + 16 * 0, GetColor(255, 255, 255), "����HP : %d", this->PlayerStatusList->iGetPlayerNowHp());

	/* �ő�HP */
	DrawFormatString(500, 700 + 16 * 1, GetColor(255, 255, 255), "�ő�HP : %d", this->PlayerStatusList->iGetPlayerMaxHp());

	/* ���G���� */
	DrawFormatString(500, 700 + 16 * 2, GetColor(255, 255, 255), "���G���� : %d", this->PlayerStatusList->iGetPlayerNowInvincibleTime());
}

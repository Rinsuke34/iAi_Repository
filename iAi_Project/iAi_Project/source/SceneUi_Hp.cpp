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
		/* HP�t���[�� */
		this->iCgHandle_Hp_Frame	= LoadGraph("resource/ImageData/UI_Player_HP/UI_Player_HP_frame.png");

		/* HP�Q�[�W */
		this->iCgHandle_Hp_Gauge	= LoadGraph("resource/ImageData/UI_Player_HP/UI_Player_HP_gauge.png");
	}
}

// �f�X�g���N�^
SceneUi_Hp::~SceneUi_Hp()
{
	/* �摜�폜 */
	{
		/* HP�t���[�� */
		DeleteGraph(this->iCgHandle_Hp_Frame);

		/* HP�Q�[�W */
		DeleteGraph(this->iCgHandle_Hp_Gauge);
	}
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
	DrawGraph(100, 740, this->iCgHandle_Hp_Frame, TRUE);

	/* ����HP */
	DrawFormatString(500, 700 + 16 * 0, GetColor(255, 255, 255), "����HP : %d", this->PlayerStatusList->iGetPlayerNowHp());

	/* �ő�HP */
	DrawFormatString(500, 700 + 16 * 1, GetColor(255, 255, 255), "�ő�HP : %d", this->PlayerStatusList->iGetPlayerMaxHp());

	/* ���G���� */
	DrawFormatString(500, 700 + 16 * 2, GetColor(255, 255, 255), "���G���� : %d", this->PlayerStatusList->iGetPlayerNowInvincibleTime());
}

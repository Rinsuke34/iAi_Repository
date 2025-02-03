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
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
	}

	/* �摜�ǂݍ��� */
	{
		/* �N�i�C�A�C�R�� */
		this->iCgHandle_Kunai_Icon = LoadGraph("resource/ImageData/UI_Player_Kunai/UI_Player_Kunai.png");

		/* �N�i�C������(��) */
		this->iCgHandle_Kunai_No[0] = LoadGraph("resource/ImageData/UI_Player_Kunai/UI_Player_Kunai_three.png");
	}
}

// �f�X�g���N�^
SceneUi_Kunai::~SceneUi_Kunai()
{
	/* �摜�폜 */
	{
		/* �N�i�C�A�C�R�� */
		DeleteGraph(this->iCgHandle_Kunai_Icon);

		/* �N�i�C������(��) */
		DeleteGraph(this->iCgHandle_Kunai_No[0]);
	}
}

// �v�Z
void SceneUi_Kunai::Process()
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
void SceneUi_Kunai::Draw()
{
	/* �N�i�C�A�C�R���`��(��) */
	DrawGraph(100, 620, this->iCgHandle_Kunai_Icon, TRUE);
}

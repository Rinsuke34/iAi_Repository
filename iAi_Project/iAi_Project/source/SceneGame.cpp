/* 2024.12.XX YYYY ZZZZ */

#include "SceneGame.h"

/* �V�[���u�Q�[���v�̒�` */

// �R���X�g���N�^
SceneGame::SceneGame() : SceneBase("Game", 0, false)
{
	/* �񓯊��ǂݍ��݂�L�������� */
	SetUseASyncLoadFlag(true);

	/* �e�X�g�p���� �J�n */

	/* �f�[�^���X�g�쐬 */
	{
		/* �f�[�^���X�g�T�[�o�[��"�I�u�W�F�N�g�Ǘ�"��ǉ� */
		gpDataListServer->AddDataList(new DataList_Object());

		/* �f�[�^���X�g�T�[�o�[��"�v���C���[���"��ǉ� */
		gpDataListServer->AddDataList(new DataList_PlayerStatus());
	}
	
	/* �f�[�^���X�g�擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}
	
	/* �v�f�ǉ� */
	{
		/* "�I�u�W�F�N�g�Ǘ�"�Ƀv���C���[��ǉ� */
		ObjectList->SetCharacterPlayer(new CharacterPlayer());
	}

	/* �e�X�g�p���� �I�� */

	/* �V�[��"�J����"���쐬 */
	gpSceneServer->AddSceneReservation(new SceneGame_Camera(), false);

	/* �񓯊��ǂݍ��݂𖳌������� */
	SetUseASyncLoadFlag(false);
}

// �f�X�g���N�^
SceneGame::~SceneGame()
{
	/* �f�[�^���X�g�폜 */
	gpDataListServer->DeleteDataList("DataList_Object");		// �I�u�W�F�N�g�Ǘ�
	gpDataListServer->DeleteDataList("DataList_PlayerStatus");	// �v���C���[���
}

// �v�Z
void SceneGame::Process()
{
	/* ���ׂẴI�u�W�F�N�g�̍X�V */
	ObjectList->UpdateAll();
}

// �`��
void SceneGame::Draw()
{
	/* ���ׂẴI�u�W�F�N�g�̕`�� */
	ObjectList->DrawAll();
}

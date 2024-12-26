/* 2024.12.XX YYYY ZZZZ */

#include "SceneGame.h"

/* �V�[���u�Q�[���v�̒�` */

// �R���X�g���N�^
SceneGame::SceneGame() : SceneBase("Game", 0, false)
{
	/* �񓯊��ǂݍ��݂�L�������� */
	SetUseASyncLoadFlag(true);

	/* �e�X�g�p���� �J�n */

	/* "�I�u�W�F�N�g�Ǘ�"���쐬 */

	/* �f�[�^���X�g�T�[�o�[��"�I�u�W�F�N�g�Ǘ�"��ǉ� */
	gpDataListServer->AddDataList(new DataList_Object()); 

	/* ���ǉ�����"�I�u�W�F�N�g�Ǘ�"���擾 */
	ObjectList	=	dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

	/* "�I�u�W�F�N�g�Ǘ�"�ɗv�f�ǉ� */
	ObjectList->SetCharacterPlayer(new CharacterPlayer());

	/* �e�X�g�p���� �I�� */

	/* �񓯊��ǂݍ��݂𖳌������� */
	SetUseASyncLoadFlag(false);
}

// �f�X�g���N�^
SceneGame::~SceneGame()
{
	/* �I�u�W�F�N�g�T�[�o�[��"�I�u�W�F�N�g�Ǘ�"�폜 */
	gpDataListServer->DeleteDataList("DataList_Object");
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
	/* 3D��{�ݒ� */
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	/* ���ׂẴI�u�W�F�N�g�̕`�� */
	ObjectList->DrawAll();

	/* �J�����ݒ�(��) */
	VECTOR stVecCameraPosition	= VGet(0, 100, -300);
	VECTOR stVecCameraTarget	= VGet(0, 100, 0);
	VECTOR stVecCameraUp		= VGet(0, 1, 0);

	SetCameraPositionAndTargetAndUpVec(stVecCameraPosition, stVecCameraTarget, stVecCameraUp);
}

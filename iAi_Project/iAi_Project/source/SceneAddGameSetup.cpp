/* 2025.02.27 �t�@�C���쐬 ��򕗏� */

#include "SceneAddGameSetup.h"

/* �V�[��"�Q�[��"�ǉ��Z�b�g�A�b�v�̒�` */
// �R���X�g���N�^
SceneAddSceneGameSetup::SceneAddSceneGameSetup() : SceneBase("AddSceneGameSetup", 10, true)
{

}

// �v�Z
void SceneAddSceneGameSetup::Process()
{
	/* ���s�V�[���폜�t���O��L���� */
	gpSceneServer->SetDeleteCurrentSceneFlg(true);

	/* �V�[��"�Q�[��"��ǉ� */
	gpSceneServer->AddSceneReservation(new SceneGame());
}

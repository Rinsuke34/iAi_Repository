/* 2025.02.27 �t�@�C���쐬 ��򕗏� */

#include "SceneAddStageSetup.h"

/* �V�[���u�X�e�[�W�ǉ��Z�b�g�A�b�v�v�̒�` */
// �R���X�g���N�^
SceneAddStageSetup::SceneAddStageSetup() : SceneBase("AddStageSetup", 10, true)
{

}

// �v�Z
void SceneAddStageSetup::Process()
{
	/* ���s�V�[���폜�t���O��L���� */
	gpSceneServer->SetDeleteCurrentSceneFlg(true);

	/* �V�[��"�Q�[��"��ǉ� */
	gpSceneServer->AddSceneReservation(new SceneGame());
}

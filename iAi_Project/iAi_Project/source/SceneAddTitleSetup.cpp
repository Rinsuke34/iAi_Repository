/* 2025.03.05 �t�@�C���쐬 ��򕗏� */

#include "SceneAddTitleSetup.h"

/* �V�[��"�^�C�g��"�ǉ��Z�b�g�A�b�v�̒�` */
// �R���X�g���N�^
SceneAddTitleSetup::SceneAddTitleSetup() : SceneBase("AddSceneTitleSetup", 10, true)
{

}

// �v�Z
void SceneAddTitleSetup::Process()
{
	/* ���s�V�[���폜�t���O��L���� */
	gpSceneServer->SetDeleteCurrentSceneFlg(true);

	/* �V�[��"�^�C�g��"��ǉ� */
	gpSceneServer->AddSceneReservation(new SceneTitle());
}
